// Encapsualtion des fontions d'un dialogue Windev dans une classe.

// Le principe consiste à gérer une fenêtre WinDev comme une boîte de dialogue en MFC
// On utilise la classe de base CWDDialog comme la classe CDialog des MFC
// On dispose donc d'un système de WDTouche MAP qui permet d'associer une méthode de la classe 
// à un WDTouche renvoyé par la fenêtre WinDev.
// La fenêtre est ensuite "exécuter" par la méthode DoModal() qui gère une boucle de messages (WDTouche)
// et exécute les méthodes correspondantes.

// La classe CWDDialog est capable par défaut de piloter une fenêtre contenant 
//    - un bouton "OK"          renvoyant le WDTouche "RET"
//    - un bouton "Annuler"		renvoyant le WDTouche "ESC"
// 
// Vous aurez sans doute besoin de gérer d'autre WDTouche
// Il vous faut donc dérivée la classe CWDDialog et enrichir la WDTouche MAP 
//
// Exemple d'utilisation de la WDTouche MAP :-------------------------------
// ------> dans le .h
// class CBidule : public CWDDialog
// {
//		...
//		void MethodeDeCBidule();
// protected:
//		DECLARE_TOUCHE_MAP(CBidule);
//		HERITE_TOUCHE_MAP(CWDDialog); // Optionnel : permet d'hériter de la MAPTouche de CWDDialog
//		// NB : on n'hérite PAS de la MAP l'ancetre CWDDialog
// }
//
// ------> dans le .cpp
// 	START_TOUCHE_MAP(CBidule)
//		{"AAA", MethodeDeCBidule},	  // On associe le WDTouche "AAA" à la méthode MethodeDeCBidule
//		...
//  END_TOUCHE_MAP()
// --------------------------------------------------------------------------
//
// La classe CWDDialog ( comme la classe MFC CDialog) permet de gérer des champs de manière automatique
// Pour cela on associe un membre de la classe à chaque champ de la fenêtre qu'on veut gérer automatiquement
// Chaque membre est d'un type correspondant au champ qui lui est associé (utilisation des macros)
// Ensuite la méthode 
//	  UpdateData(TRUE) permet de mettre à jour les membres de la classe à partir des champs de la fenêtre
// et UpdateData(FALSE) permet de mettre à jour les champs de la fenêtre à partir des membres de la classe
// L'appel de DoModal() déclenche automatiquement un UpdateData(FALSE) àprès ouverture de la fenêtre 
// et un UpdateData(TRUE) avant fermeture de la fenêtre.
//
// Exemple d'utilisation des membres AUTO:------------------------------------
// -------> dans le .h
// Class CBidule : CWDDialog 
// {    
//	protected:
// 		DECLARE_MEMBER_SELECTEUR(NomChampWD, ValeurInit) // cree un membre 'm_NomChampWD' qui représent un sélecteur
//      DECLARE_MEMBER_SAISIE_STR(SAISIE2, "", 20)       // cree un membre 'm_SAISIE2' qui représente un champ de saisie de 20 chars
//       ...
//		DECLARE_GERE_AUTO(CBidule)
// }           
// ------> dans le .cpp
// // L'appel de 'UpdateData()' affecte tout ce qui est déclaré dans cette liste
//  START_GERE_AUTO(CBidule)
//	  GERE_AUTO(NomChampWD)
//    ...
//  END_GERE_AUTO()
// 
// ---------------------------------------------------------------------------


#ifndef __WDWDIAL_H
#define __WDWDIAL_H 

#include "WDExternApi.h"

//////////////////////////////////////////
// MACROS pour déclarer un "WDTouche MAP"
#define DECLARE_TOUCHE_MAP(CLASS) \
	typedef void (far CLASS::* MethodForWDTouche)();\
	typedef struct {LPCTSTR szWDTouche;MethodForWDTouche pfMethod;} stWDTOUCHETOMETHOD;\
	static stWDTOUCHETOMETHOD far  stToucheMap[];\
	virtual CWDDialog::stWDTOUCHETOMETHOD *pstGetMap() {return (CWDDialog::stWDTOUCHETOMETHOD *)stToucheMap;}

#define HERITE_TOUCHE_MAP(PARENTCLASS) 	\
	virtual CWDDialog::stWDTOUCHETOMETHOD *pstGetParentMap(int nNiv) { return nNiv<1 ? PARENTCLASS::pstGetMap() : PARENTCLASS::pstGetParentMap(nNiv-1); } \

#define START_TOUCHE_MAP(CLASS) CLASS::stWDTOUCHETOMETHOD CLASS::stToucheMap[] = {

#define END_TOUCHE_MAP() {NULL, NULL}};

/////////////////////////////////////////////////////////////
// MACRO pour gérer les Champs Windev de facon automatique...
                  
// MACRO générique, utiliséé par chaque type de champ, définit un membre et 4 méthodes associées
#define DECLARE_MEMBER(TYPECPP, NOMCHAMPWD, INIT_CODE, RECUP_CODE, AFFICHE_CODE, TERM_CODE)\
 	TYPECPP m_##NOMCHAMPWD; \
 	void AutoInit_##NOMCHAMPWD() INIT_CODE \
 	void AutoRecup_##NOMCHAMPWD() RECUP_CODE \
 	void AutoAffiche_##NOMCHAMPWD() AFFICHE_CODE \
 	void AutoTerm_##NOMCHAMPWD() TERM_CODE

// SELECTEUR
#define DECLARE_MEMBER_SELECTEUR(NOM, INITVAL) \
	DECLARE_MEMBER(int, NOM, {m_##NOM = INITVAL;}, {m_##NOM = nRecup(_X(#NOM));}, {Affiche(_X(#NOM), m_##NOM);}, {} )

// LIBELLE
#define DECLARE_MEMBER_LIBELLE(NOM, INITSTR, TAILLE) \
 	DECLARE_MEMBER(XCHAR *, NOM, {m_##NOM = (XCHAR *)malloc((TAILLE+1)*sizeof(XCHAR));STRCPY(m_##NOM ,INITSTR);}, {RecupTexteLong(_X(#NOM), m_##NOM, TAILLE+1);}, {Affiche(_X(#NOM), m_##NOM);}, {free(m_##NOM);} )
	
// SAISIE CHAINE
#define DECLARE_MEMBER_SAISIE_STR(NOM, INITSTR, TAILLE) \
 	DECLARE_MEMBER(XCHAR *, NOM, {m_##NOM = (XCHAR *)malloc((TAILLE+1)*sizeof(XCHAR));STRCPY(m_##NOM ,INITSTR);}, {RecupTexteLong(_X(#NOM), m_##NOM, TAILLE+1);}, {Affiche(_X(#NOM), m_##NOM);}, {free(m_##NOM);} )

// SAISIE CHAINE CTSTRING sans limite de taille
#define DECLARE_MEMBER_SAISIE_CTSTRING(NOM, INITSTR) \
	DECLARE_MEMBER(CTString, NOM, {m_##NOM = INITSTR;}, { m_##NOM.Set(szRecup(_X(#NOM)));}, {Affiche(_X(#NOM), m_##NOM);}, {} )

// SAISIE ENTIER
#define DECLARE_MEMBER_SAISIE_INT(NOM, INITVAL) \
  	DECLARE_MEMBER(int, NOM, {m_##NOM = INITVAL;}, {m_##NOM = nRecup(_X(#NOM));}, {Affiche(_X(#NOM), m_##NOM);}, {} )

// INTERRUPTEUR MULTIPLE 
// Exemple :
// 		DECLARE_MEMBER_TABINTERRUPTEUR(INTER1, 10, "x x x x x ")
// 			Declare un ensemble de 10 interrupteurs initialise de maniere a n'en cocher qu'un sur deux
#define DECLARE_MEMBER_TABINTERRUPTEUR(NOMCHAMPWD, NOMBRE, INITSTR) \
 	BOOL m_##NOMCHAMPWD[NOMBRE]; \
 	void AutoInit_##NOMCHAMPWD() {XCHAR *szInit=INITSTR; for(int i=0;szInit[i]!=0;i++) m_##NOMCHAMPWD[i] = (szInit[i]=='x');} \
 	void AutoRecup_##NOMCHAMPWD() {RecupInterrupteur(#NOMCHAMPWD, m_##NOMCHAMPWD, NOMBRE);} \
 	void AutoAffiche_##NOMCHAMPWD() {AfficheInterrupteur(#NOMCHAMPWD, m_##NOMCHAMPWD, NOMBRE);} \
 	void AutoTerm_##NOMCHAMPWD() {}

// INTERRUPTEUR SIMPLE
#define DECLARE_MEMBER_INTERRUPTEUR(NOM,  INITSTATE) \
	DECLARE_MEMBER(BOOL, NOM, {m_##NOM = INITSTATE;}, {RecupInterrupteur(_X(#NOM) , &m_##NOM, 1);}, {AfficheInterrupteur(_X(#NOM), &m_##NOM, 1);}, {})

// COMBO CHAINE
#define DECLARE_MEMBER_COMBO_STR(NOM, INITSTR, TAILLE)\
 	DECLARE_MEMBER(XCHAR *, NOM, {m_##NOM = (XCHAR *)malloc((TAILLE+1)*sizeof(XCHAR));STRCPY(m_##NOM ,INITSTR);}, {RecupTexteLong(_X(#NOM), m_##NOM, TAILLE+1);}, {Affiche(_X(#NOM), m_##NOM);}, {free(m_##NOM);} )

// LISTE CHAINE
#define DECLARE_MEMBER_LISTE_STR(NOM, INITSTR, TAILLE)\
 	DECLARE_MEMBER(XCHAR *, NOM, {m_##NOM = (XCHAR *)malloc((TAILLE+1)*sizeof(XCHAR));STRCPY(m_##NOM ,INITSTR);}, { int nSel;ListeRecup(_X(#NOM),m_##NOM,&nSel); } , {}, {free(m_##NOM);} )

// COMBO CHAINE CTString sans limite de taille
#define DECLARE_MEMBER_COMBO_CTSTRING(NOM, INITSTR)\
	DECLARE_MEMBER(CTString, NOM, {m_##NOM = INITSTR;}, { m_##NOM.Set(szRecup(_X(#NOM)));}, {Affiche(_X(#NOM), m_##NOM);}, {} )

// COMBO ENTIER
#define DECLARE_MEMBER_COMBO_INT(NOM, INITVAL)\
	DECLARE_MEMBER(int, NOM, {m_##NOM = INITVAL;}, {m_##NOM = nRecup(_X(#NOM));}, {Affiche(_X(#NOM), m_##NOM);}, {} )
	
//---MACRO DE GESTION AUTO
#define DECLARE_GERE_AUTO(CLASS)\
 	typedef void (far CLASS::* pfAuto_##CLASS)(); \
 	typedef struct {pfAuto_##CLASS AutoInit, AutoRecup, AutoAffiche, AutoTerm;} stAUTOMAP;\
  	static const stAUTOMAP far stAutoMap[];\
 	virtual const CWDDialog::stAUTOMAP *pstGetAutoMap() {return (CWDDialog::stAUTOMAP *)stAutoMap;}

#define HERITE_GERE_AUTO(PARENTCLASS)\
	virtual const CWDDialog::stAUTOMAP* pstGetParentAutoMap() { return PARENTCLASS::pstGetAutoMap(); } 

#define START_GERE_AUTO(CLASS) \
 	const CLASS::stAUTOMAP CLASS::stAutoMap[] = {
 
#define GERE_AUTO(NOMCHAMPWD) \
 	{ &AutoInit_##NOMCHAMPWD, &AutoRecup_##NOMCHAMPWD, &AutoAffiche_##NOMCHAMPWD, &AutoTerm_##NOMCHAMPWD },
 
#define END_GERE_AUTO() \
 	{NULL, NULL, NULL, NULL} };


////////////////////////////////////////////////////////////////////////////////
//--- dialogue WinDev de base
class CWDDialog;

class CWDDialog 
{	
public:
	struct stCTXCALLBACK { CWDDialog* pclDialogCourant; };

protected:
	// membres:
 	LPTSTR m_pszName; // nom de la fenetre WinDev
	HWND m_hWndMere; // Handle de la fenetre Mere 
	BOOL m_bModal;	 // si ouverture modale
	int m_nRetValue;
	BOOL m_bFinModal;

	// context pour la callback du Langage Externe
	//static stCTXCALLBACK s_stCtxCallBack;
	stCTXCALLBACK m_stCtxCallBack;
	
	// conserve l'ancienne DialogCourante
	//CWDDialog* m_pclLastDialog;

private:
	
	BOOL m_bAutoMemberInitialized;
	BOOL m_bLastg_bExtern;

public:
	// constructeur avec comme paramêtre le nom de la fenêtre WinDev (sans l'extension! )
	// et le handle de la fenêtre mere
	CWDDialog(LPCTSTR szNomWDW, HWND hWndMere= NULL);
	virtual ~CWDDialog(); // destructeur virtuel pour un héritage sans soucis.

	//affiche l'interface en mode modal.
	int DoModal();

	//affiche l'interface en mode non modal, retour immediat
	void DoNonModal();

	virtual void Ferme(void);
	
	// retoure le HWND de la fenetre 
	virtual HWND GetSafeHwnd() { XASSERT(m_DEBUGbOuvert); return Handle(); }

	// Ferme la fenetre et fixe la valeur renvoyer par DoModal
	void EndDialog(int nRetValue=0) { m_bFinModal=TRUE; m_nRetValue=nRetValue; } // méthode à appeler dans une methode de la WDTOuche MAP pour que DoModal se termine.

	// CallBack de la classe (appel depuis le Langage Externe)
	void OnCallBack(CWDDialog::stCTXCALLBACK* pstCtxCallBack, LPCTSTR pszCodeAction);

protected:
	virtual void OnOk();   		// méthode par défaut pour "OK"
	virtual void OnCancel();        // méthode par défaut pour "Cancel"
	virtual void OnInitDialog();   // appelé juste après la création
	virtual void OnEachTouche() {} // appelé avant chaque évènement WDTouche
	
	void OnContextHelp(); // appelé pour l'aide contextuelle
	
	// apres l'init de la fenetre
	virtual void PostInitDialog(CWDDialog::stCTXCALLBACK* pstCtxCallBack);

	// implémente la Touche Map par defaut
	DECLARE_TOUCHE_MAP(CWDDialog);
 	virtual stWDTOUCHETOMETHOD *pstGetParentMap(int /*nNiv*/) {return NULL;}
	MethodForWDTouche pfGetAssociatedMethod(LPCTSTR pszWDTouche);
	
	// implémente la relation auto entre un champ du dialogue et le membre de la classe associé par DECLARE_MEMBER_XXX(...)
	DECLARE_GERE_AUTO(CWDDialog);
	virtual const stAUTOMAP* pstGetParentAutoMap() { return NULL; }

	// Mise à jour membres de la classe/ champ de la fenêre
	// TRUE  pour mettre à jour les membres de la classe à partir des champs de la fenêtre
	// FALSE pour mettre à jour les champs de la fenêtre à partir des membres de la classe
	virtual void UpdateData(BOOL=TRUE);

	enum eAUTOACTION {INIT_AUTO, RECUP_AUTO, AFFICHE_AUTO, TERM_AUTO};
	void ActionAuto(eAUTOACTION eAction); // effectue une des actions pour tous les champs auto
	void InitAutoMembers() {ActionAuto(INIT_AUTO);} // INIT des membres auto, appellé dans DoModal si on le le fait pas avant
	void TermAutoMembers(); // RAZ des membres auto, a appeler IMPERATIVEMENT !!! ( si on utilise les membres auto)

	// ouverture modale d'une fenêtre
	virtual void OuvreModal(LPCTSTR WindowName,HWND hWnd); 

	// ouverture non modale d'une fenêtre
	virtual void OuvreNonModal(LPCTSTR WindowName,HWND hWnd); 

	#ifdef _DEBUG
		BOOL m_DEBUGbOuvert;
	#endif
};


#endif //__WDWDIAL_H
