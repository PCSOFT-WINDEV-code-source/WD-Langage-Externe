//Encapsualtion des fontions d'un dialogue Windev dans une classe c++.

#include <string.h>
#include <malloc.h>
#include "WDWDial.h"
#include "WDExternApi.h"
#include <tchar.h>
#define xassert(exp)
#define STR_nUpCompare	_tcsicmp

//CWDDialog::stCTXCALLBACK CWDDialog::s_stCtxCallBack = { NULL };

CWDDialog::CWDDialog(LPCTSTR szNomWDW, HWND hWndMere) 
#ifdef _DEBUG 
: m_DEBUGbOuvert(FALSE) 
#endif
{
	// sauvegarde du nom de la fenetre à ouvir sur un DoModal()
	xassert(szNomWDW != NULL);
	m_pszName =  (LPTSTR)malloc((STRLEN(szNomWDW)+1)*sizeof(TCHAR));
	if (m_pszName)
		STRCPY(m_pszName,  szNomWDW); // copie du nom fournit.
	else
		m_pszName = _X(""); // plus de mémoire -> nom vide

	m_hWndMere = hWndMere;

	// on indique que les champs géré autmatiquement ne sont pas encore initialisé
	// NB: on NE PEUT PAS le faire dans ce constructeur, 
	// car il ne faut pas y appeller de fonctions virtuelle (vptr n'est pas initialisé) 
	m_bAutoMemberInitialized = FALSE;

	m_bModal=FALSE;
}

CWDDialog::~CWDDialog()
{
	XASSERT(m_bAutoMemberInitialized == FALSE);
	// comme pour le construteur, on NE PEUT PAS appeler TermAutoMembers(),
	// les classes dérivées doivent le faire au plus tard dans LEUR PROPRE destructeur
	
	if (m_pszName) free(m_pszName);
}

// destruction des champs gérés Automatiquement
// a appeler IMPERATIVEMENT si on utilise les champs auto !!!!
void CWDDialog::TermAutoMembers()
{
	if (m_bAutoMemberInitialized)
		ActionAuto(TERM_AUTO);
}

CWDDialog::MethodForWDTouche CWDDialog::pfGetAssociatedMethod(LPCTSTR pszWDTouche)
{
	stWDTOUCHETOMETHOD *pstPrvToucheMap;
	stWDTOUCHETOMETHOD *pstToucheMap = pstGetMap(); // virtuelle !!
	XASSERT(pstToucheMap != NULL);
	int nNiv=0;
	while (pstToucheMap != NULL)
	{
		for (int i=0;pstToucheMap[i].pfMethod;i++)
			if (!STRICMP(pszWDTouche, pstToucheMap[i].szWDTouche))
				return pstToucheMap[i].pfMethod; 

		pstPrvToucheMap = pstToucheMap;
		pstToucheMap = pstGetParentMap(nNiv);
		nNiv++;
		// on sort is c'est la meme map (pour éviter les boucles infinies)
		if (pstToucheMap == pstPrvToucheMap) break;
	};
 
	return NULL;
}

// callback de retour du Langage Externe
void CWDDialogCallBack(DWORD_PTR dwUserParam, LPCTSTR pszCodeAction)
{	
	CWDDialog::stCTXCALLBACK* pstCtxCallBack=(CWDDialog::stCTXCALLBACK*)dwUserParam;
	CHECKPTROK(pstCtxCallBack, sizeof(CWDDialog::stCTXCALLBACK));

	// appel la classe courante
	CHECKPTROK(pstCtxCallBack->pclDialogCourant, sizeof(CWDDialog*));
	pstCtxCallBack->pclDialogCourant->OnCallBack(pstCtxCallBack, pszCodeAction);
}

// CallBack de la classe (appel depuis le Langage Externe)
void CWDDialog::OnCallBack(CWDDialog::stCTXCALLBACK* pstCtxCallBack, LPCTSTR pszCodeAction)
{
	// Creation de la fenetre
	if (STR_nUpCompare(pszCodeAction, _X("Creation"))==0)
	{
 		// init des champs gérés Automatiquement si necessaire.
		if (!m_bAutoMemberInitialized) 
			ActionAuto(INIT_AUTO);
			
		// init de la fenêtre
		OnInitDialog();

		// suite Init
		PostInitDialog(pstCtxCallBack);
		return;
	}

	// Aide Contextuelle
	if (STR_nUpCompare(pszCodeAction, _X("CtxHelp"))==0)
	{
		OnContextHelp();
		return;
	}

	//
	// Traitement automatique des WDTouche HLP et AID
	// 
	if ((STR_nUpCompare(pszCodeAction, _X("HLP"))==0) || (STR_nUpCompare(pszCodeAction, _X("AID"))==0))
	{
		MessageBox(Handle(m_pszName),_X("Non disponible dans cette version."),_X("WinDev"),MB_OK);
		return;
	}

	// appel methode pour signaler un retour
	OnEachTouche();

	// recherche si une action est associée
	MethodForWDTouche pfMethod = pfGetAssociatedMethod(pszCodeAction);
	if (pfMethod != NULL) (this->*pfMethod)();

	// si on doit terminer (fermer) la fenetre
	if (m_bFinModal)
	{
		// fermeture de la fenêtre
		Ferme();							
	}
}

int CWDDialog::DoModal()
{
	// init valeur de retour
	m_bFinModal = FALSE;
	m_nRetValue = 0;
	m_bModal=TRUE;

	// conserve l'ancienne class
	//m_pclLastDialog=s_stCtxCallBack.pclDialogCourant;
	// Positionne dans le contexte d'appel cette classe
	//s_stCtxCallBack.pclDialogCourant=this;
	m_stCtxCallBack.pclDialogCourant=this;
	// fixe la callback et le contexte
	nWDSetCallbackNext(CWDDialogCallBack, (DWORD_PTR)&m_stCtxCallBack);

	// indique que la fenetre est ouverte
	#ifdef _DEBUG
		m_DEBUGbOuvert=TRUE;
	#endif

	//ouverture du dialogue WindDev, 
 	OuvreModal(m_pszName, m_hWndMere);

	return m_nRetValue;
}

// effectue une des actions de l'enum pour tous les champs auto
// à savoir Initialisation/Terminaison/Mise à jour
void CWDDialog::ActionAuto(eAUTOACTION eAction) 
{
	// récupère la carte des actions sur les Champs Auto par un appel de fonction virtuelle
	const stAUTOMAP *pstPrv;
	const stAUTOMAP *pst = pstGetAutoMap(); 
	int i=0;
	while (pst != NULL)
	{
		i = 0;
		// boucle sur tous les champs
		while  (pst[i].AutoInit != NULL) 
		{      
			switch (eAction) 
			{    
				// initialisation des membres
				case INIT_AUTO:  	(this->*(pst[i].AutoInit))();break;
				// lecture des valeurs de la fenetre vers les membres
				case RECUP_AUTO: 	(this->*(pst[i].AutoRecup))();break;
				// changement des valeurs depuis les membres vers la fenetre
				case AFFICHE_AUTO: 	(this->*(pst[i].AutoAffiche))();break;
				// libération des membres
				case TERM_AUTO:     (this->*(pst[i].AutoTerm))();break;
				// toute autre action est invalide : erreur de programmation
				default : XASSERT(FALSE);break;	                                             
			}
			i++; // membres auto suivant
 		}

		pstPrv = pst;
		pst = pstGetParentAutoMap(); // pas trouvé ? on continue avec le parent.
		// on sort is c'est la meme map (pour éviter les boucles infinies)
		if (pst == pstPrv) break;
	}
	if ((i>0) && (eAction == INIT_AUTO)) m_bAutoMemberInitialized = TRUE;
	if (eAction == TERM_AUTO) m_bAutoMemberInitialized = FALSE;
}

// ouverture d'une fenetre WinDev en mode modal (hWnd est la fenetre mere)
void CWDDialog::OuvreModal(LPCTSTR pszWindowName,HWND hWnd)
{
	// ouvre la fenetre WD
	::Ouvre(pszWindowName, hWnd);
}

void CWDDialog::DoNonModal()
{
	// init valeur de retour
	m_bFinModal = FALSE;
	m_nRetValue = 0;
	m_bModal=FALSE;

	// conserve l'ancienne class
	//m_pclLastDialog=s_stCtxCallBack.pclDialogCourant;
	// Positionne dans le contexte d'appel cette classe
	//s_stCtxCallBack.pclDialogCourant=this;
	m_stCtxCallBack.pclDialogCourant=this;
	// fixe la callback et le contexte
	nWDSetCallbackNext(CWDDialogCallBack, (DWORD_PTR)&m_stCtxCallBack);

	// indique que la fenetre est ouverte
	#ifdef _DEBUG
		m_DEBUGbOuvert=TRUE;
	#endif

	//ouverture du dialogue WindDev, 
 	OuvreNonModal(m_pszName, m_hWndMere);
}


// ouverture d'une fenetre WinDev en mode non-modal (hWnd est la fenetre mere)
void CWDDialog::OuvreNonModal(LPCTSTR pszWindowName, HWND hWnd)
{
	// ouvre la fenetre WD
	nWDSetParentNext(hWnd);
	WDLEVERIFY(nWDExecute(_X("OuvreFille(\"%s\")"), pszWindowName));
}

void CWDDialog::Ferme(void) 
{ 
	XASSERT(m_DEBUGbOuvert);

#ifdef _AFXDLL
	if (AfxGetMainWnd()->GetSafeHwnd()!=NULL)
		AfxGetMainWnd()->SetForegroundWindow();
#endif //AFXDLL

	::Ferme();

	// indique que la fenetre est fermee
	#ifdef _DEBUG
		m_DEBUGbOuvert=FALSE;
	#endif
}


// méthode appelée juste après la création de la fenêtre
void CWDDialog::OnInitDialog()
{
	// mise a jour des donnees de la fenetre
	UpdateData(FALSE);

}

// apres l'init de la fenetre
void CWDDialog::PostInitDialog(CWDDialog::stCTXCALLBACK* /*pstCtxCallBack*/)
{
}


// mise à jour automatique des champs du dialogue
// bRecupere :  TRUE   copie du dialogue vers les membres
//				FALSE  copie des membres vers le dialogue
void CWDDialog::UpdateData(BOOL bRecupere /*TRUE*/)
{
	if (bRecupere) 
	   ActionAuto(RECUP_AUTO);
	else                      
	   ActionAuto(AFFICHE_AUTO);
}


void CWDDialog::OnOk() 
{
	// recuperation des donnees de la fenetre
	UpdateData(TRUE);

	m_nRetValue=IDOK;
	m_bFinModal = TRUE;
} 

void CWDDialog::OnCancel() 
{
	m_nRetValue=IDCANCEL;
	m_bFinModal = TRUE;
}  

void CWDDialog::OnContextHelp()
{
	// simule le fct du bouton d'aide contextuelle
	PostMessage(Handle(), WM_SYSCOMMAND, SC_CONTEXTHELP, 0);
}

/////////////////////////////////////////////////////////////
// Carte des message pour le dialogue de base.
START_TOUCHE_MAP(CWDDialog)
	{_X("RET"), &OnOk},
	{_X("ESC"), &OnCancel},
END_TOUCHE_MAP()

    
/////////////////////////////////////////////////////////////
// liste des champs gere automtiquement sur UpdateData.
// (pour CWDDialog la liste est vide)
START_GERE_AUTO(CWDDialog)
    
END_GERE_AUTO()
