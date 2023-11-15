// WD7 Langage Externe.cpp : Defines the class behaviors for the application.
//

#include "Central.h"
#include "WD Langage Externe.h"
#include "WD Langage ExterneDlg.h"
#include "FenPrincipale.h"
#include "IHFContext.h"	// SGBD Hyper File
#include "HFContext.h"	// SGBD Hyper File

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWD7LangageExterneApp

BEGIN_MESSAGE_MAP(CWD7LangageExterneApp, CWinApp)
	//{{AFX_MSG_MAP(CWD7LangageExterneApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWD7LangageExterneApp construction

CWD7LangageExterneApp::CWD7LangageExterneApp()
{
	m_pclHF = NULL;
}

CWD7LangageExterneApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWD7LangageExterneApp initialization

BOOL CWD7LangageExterneApp::InitInstance()
{
	//le programme d�bute ICI 

#ifdef _DEBUG
	// Initialisation des DLLs WinDev
	if (nWDInit(TRUE)!=WDERREUR_OK) //on passe vrai pour voir les messages d'erreur s'afficher
#else
	// Initialisation des DLLs WinDev
	if (nWDInit(FALSE)!=WDERREUR_OK) 
#endif
	{ 
		AfxMessageBox("Les DLLs WinDev n'ont pas pu �tre charg�es.\nElles doivent se trouver dans le r�pertoire de l'ex�cutable, dans le r�pertoire Windows ou dans un r�pertoire du path.");
		return FALSE;
	}
	
	// Allocation d'un contexte Hyper File (SGBD)
	m_pclHF = new CHFContext();

    // Initialisation de Hyper File
	IHFContext * pIHF;
	if (!((nWDGetHFContext((void**)&pIHF)==WDERREUR_OK) && (m_pclHF->bInit(pIHF)))) 
	{
		ArretAppli("Erreur d'initialisation du contexte HF.");
	}


	// Ouverture de la WDL (biblioth�que qui contients tous les �l�ments du projet WinDev)
	char szWDL[]="WD Langage Externe.WDL";			// Biblioth�que WinDev utilis�e
	if (nWDOuvreWDL(szWDL)!=WDERREUR_OK)
    {  
		// Biblioth�que non trouv�e
		nWDExecute("Erreur(\"La biblioth�que %s n'a pas �t� trouv�e.\")",szWDL);
		ArretAppli();
    }


	// Ouverture de l'analyse (fichier .WDD contenu dans la WDL)
	char szAnalyse[]="WD Langage externe.wdd";		// Analyse WinDev utilis�e (automatiquement int�gr�e par WD dans la WDL)
	char szMotDePasse[]="";				// Mot de passe de l'analyse
	if (!m_pclHF->HOuvreAnalyse(szAnalyse,szMotDePasse))
	{
		nWDExecute("Erreur(\"Impossible d'ouvrir l'analyse.\"+RC+\"%s\")",m_pclHF->HErreurInfo());
		ArretAppli();
	}

	// Ex�cution du code du projet WinDev
	if (nWDInitProjet("")==WDERREUR_INIT)
	{
		nWDExecute("Erreur(\"Erreur lors de l'initialisation du projet.\")");
		ArretAppli();
	}
	
	// R�initialisation du m�canisme de gestion des erreurs
	WDRepriseErreur();

	//Nous allons ouvrir la fen�tre WinDev correspondant � la fen�tre principale
	//Cette fen�tre est g�r�e par la classe CFenPrincipale

	CWDFenPrincipale clMain;
	//on ouvre la fen�tre en mode modal
	clMain.DoModal();

	// Fin de l'application lorsque la fen�tre principale est ferm�e
	ArretAppli();
	return FALSE;
}

// Arr�t de l'appli (message facultatif)
// -----------------------------------------------------------------------------------
void CWD7LangageExterneApp::ArretAppli(LPCTSTR pszMsg)
{
	if ((pszMsg!=NULL) && (*pszMsg!=0)) {MessageBox(NULL,pszMsg,"Erreur",MB_ICONERROR+MB_OK);};

	//lib�ration du context HF
	delete m_pclHF;
	m_pclHF = NULL;
	WDTerm();		// Lib�ration des ressources WinDev
	exit(0);		// Fin du programme
}
