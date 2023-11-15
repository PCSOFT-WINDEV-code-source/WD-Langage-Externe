//---------------------------------------------------------------------------------------------------------------------------------------------------------
// Interface du Langage Externe WinDev
//---------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef __WDEXTERN_H
#define __WDEXTERN_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plateformes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(__APPLE__) && defined(__MACH__) 

	#define WD_DLLVM	"wd220vm.dylib"
	#if !defined(__unix__)
		#define __unix__
	#endif

#elif defined(__unix__)

	#if defined(__LP64) || defined(_LP64)

		#define WD_DLLVM	"wd220vm64.so"
		#define _64_BITS

	#else	//#if defined(__LP64) || defined(_LP64)

		#define WD_DLLVM	"wd220vm.so"

	#endif	//#else	//#if defined(__LP64) || defined(_LP64)

#elif defined(UNDER_CE)

	#define WD_DLLVM	"wp220vm.dll"

#elif defined(_WIN64)

	#define WD_DLLVM	"wd220vm64.dll"
	#define _64_BITS

#else

	#define WD_DLLVM	"wd220vm.dll"

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// D�finitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#ifdef _WINDOWS

	#include <windows.h>
	#ifdef _WIN64
		typedef unsigned __int64	DWORD_PTR;
	#else	
		typedef unsigned long		DWORD_PTR;
	#endif

#else	//#ifdef _WINDOWS

	#include <stdint.h>
	#include <limits.h>
	#include <wchar.h>
    typedef unsigned int	UINT;
	typedef unsigned short 	WORD;
	typedef unsigned char	BYTE;
	typedef BYTE*			PBYTE;
	typedef uintptr_t		DWORD_PTR;

	#ifndef DWORD
		#define DWORD		uint32_t
	#endif	//DWORD

#if defined(__APPLE__) && defined(__MACH__)
	typedef signed char		BOOL;
#else	//#if defined(__APPLE__) && defined(__MACH__)
	typedef int 			BOOL;
#endif	//#else	//#if defined(__APPLE__) && defined(__MACH__)

	#ifndef FALSE
		#define	FALSE			0
		#define	TRUE			1
	#endif

	typedef const char* 	LPCSTR;
	typedef char* 			LPSTR;
	typedef const wchar_t*	LPCWSTR;
	typedef wchar_t*		LPWSTR;

	#ifdef UNICODE
		typedef LPCWSTR			LPCTSTR;
		typedef wchar_t*		LPTSTR;
		typedef wchar_t	 		TCHAR;
	#else //#ifdef UNICODE
		typedef LPCSTR			LPCTSTR;
		typedef char*	 		LPTSTR;
		typedef char	 		TCHAR;
	#endif //#else //#ifdef UNICODE

	typedef void*			PVOID;
	typedef const void*		LPCVOID;

	// d�finition des HANDLEs
	#ifndef HINSTANCE_ERROR
		#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
		DECLARE_HANDLE(HINSTANCE);
		DECLARE_HANDLE(HWND);
		DECLARE_HANDLE(HMODULE);
		#define HINSTANCE_ERROR		NULL       // DLL non charg�e
	#endif

    #define MAX_PATH  PATH_MAX

#endif	//#else	//#ifdef _WINDOWS

#if defined(__BORLANDC__) && (__BORLANDC__ < 0x550)
	typedef double WDINT64;
#elif defined __unix__
	typedef long long int	WDINT64;
#else
	typedef __int64 WDINT64;
#endif

#ifdef UNICODE
	#define WD_DECLARE_A_W(A,W)	W
#else	//UNICODE
	#define WD_DECLARE_A_W(A,W)	A
#endif	//!UNICODE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// num�ro de version
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	WD_VERSION_EXTERNE		15

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// type de ressource pour les WDL int�gr�s dans des ex�cutables
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TYPE_RES_WDL	"RT_WDL"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Prototype de la fonction "callback" appel�e par WDTouche et RenvoieWDTouche
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (*pfnWDCALLBACKA)	(DWORD_PTR dwUserParam, LPCSTR pszCodeAction);
typedef void (*pfnWDCALLBACK)	(DWORD_PTR dwUserParam, LPCWSTR pszCodeAction);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// types possibles pour les valeurs renvoy�es par la machine virtuelle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WDTYPE_VOID		0
#define WDTYPE_BOOL		1
#define WDTYPE_INT		2
#define WDTYPE_INT64	3
#define	WDTYPE_DOUBLE	4
#define WDTYPE_ASTR		5
#define WDTYPE_BIN		6
#define WDTYPE_ANY		7
#define WDTYPE_WSTR		8

#ifdef UNICODE
#define WDTYPE_TSTR		WDTYPE_WSTR
#else	//UNICODE
#define WDTYPE_TSTR		WDTYPE_ASTR
#endif	//!UNICODE

#pragma pack(2)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structure pouvant contenir des valeurs renvoy�es par la machine virtuelle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _STWDValeur
{	// type de la valeur
	WORD		wType;
	// valeur enti�re
	int			nValeur;
	// valeur enti�re sur 64 bits
	WDINT64		i64Valeur;
	// valeur flottante
	double		dValeur;
	// valeur chaine de caract�res
	LPWSTR		pszValeurW;
	// valeur binaire
	PBYTE		pbyBinaire;
	// TRUE si la valeur de retour est NULL
	BOOL		bNull;
	// valeur chaine de caract�res
	LPSTR		pszValeurA;
	// informations suppl�mentaires
	DWORD_PTR	dwInfoSup[5];
} STWDValeur;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structure pouvant contenir des informations sur les erreurs lors de l'utilisation du langage externe
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _STWDErreur
{	// code de l'erreur
	int			nCodeErreur;
	// message de l'erreur
	LPWSTR		pszMessageW;
	// affichage des erreurs
	BOOL		bAfficheErreur;
	// message de l'erreur
	LPSTR		pszMessageA;
	// informations suppl�mentaires
	DWORD		dwInfoSup[5];
} STWDErreur;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structure de communication entre programme h�te et machine virtuelle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _STWDExtern
{	// num�ro de version
	WORD		wVersion;
	// contexte d'ex�cution de la machine virtuelle
	PVOID		pContexte;
	// valeur de retour de la fonction appel�e
	STWDValeur*	pstValeurRetour;
	// erreur
	STWDErreur*	pstErreur;
	// identifiant du module h�te
	LPCWSTR		pszModuleW;
	// identifiant du module h�te
	LPCSTR		pszModuleA;
	// informations suppl�mentaires
	DWORD		dwInfoSup[5];
} STWDExtern;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structure d'initialisation de la machine virtuelle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _STInitLE
{	// num�ro de version
	DWORD		dwVersion;
	// taille de la structure
	size_t		nTaille;
	// TRUE si on veut l'affichage des erreurs WL
	BOOL		bAfficheErreur;
	// options d'initialisation
	DWORD		dwOption;
	// chemin des DLL
	LPCWSTR		pszCheminDLLW;
	// chemin des DLL
	LPCSTR		pszCheminDLLA;
	// informations suppl�mentaires
	DWORD_PTR	dwInfoSup[5];
} STInitLE;

#pragma pack()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// options d'initialisation du langage externe
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WDOILE_COMPOSANTE						0x00000001	// langage externe pour une composante
#define WDOILE_AUTORISE_ATTACHEMENT_DEBOGUEUR	0x00000002	// autorise l'attachement du d�bogueur sur l'application
#define WDOILE_AUTORISE_LOG_EXECUTION			0x00000004	// autorise la trace d'ex�cution
#define WDOILE_DESACTIVE_COLLECTEUR_TOPO		0x00000008	// d�sactive le collecteur topologique
#define WDOILE_AUTORISE_AUDIT_EXECUTION			0x00000010	// autorise l'audit d'ex�cution

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// codes d'erreur
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	WDERREUR_OK					0	// succ�s
#define	WDERREUR_VERSION			1	// incompatibilit� de num�ro de version
#define	WDERREUR_DLLLOAD			2	// probl�me au chargement de la DLL
#define WDERREUR_WDLLOAD			3	// probl�me au chargement de la WDL
#define WDERREUR_DLLCPL				4	// dll de compilation non trouv�e
#define WDERREUR_ERREURCPL			5	// erreur de compilation
#define WDERREUR_MEMOIRE			6	// plus de m�moire disponible
#define WDERREUR_TYPE				8	// type non convertible
#define WDERREUR_INIT				9	// langage externe pas initialis�
#define	WDERREUR_EXECUTION			10	// erreur en cours d'ex�cution
#define WDERREUR_ERREUR				11	// erreur pr�c�dente non trait�e
#define WDERREUR_COMMANDE			12	// commande de nWDExecute trop longue
#define WDERREUR_INITPROJET			13	// le code d'init du projet a d�j� �t� ex�cut�
#define WDERREUR_ELEMINCONNU		14	// �l�ment inconnu
#define WDERREUR_AUCUNEWDL			15	// aucune WDL n'a �t� charg�e
#define WDERREUR_AUCUNPROJET		16	// aucun projet n'est pr�sent dans la premi�re WDL
#define WDERREUR_OUVERTUREANALYSE	17	// erreur � l'ouverture de l'analyse
#define WDERREUR_COMPOSANT			18	// erreur � l'ouverture des composants
#define WDERREUR_THREAD				19	// erreur en manipulation des threads
#define WDERREUR_DEBOGUEUR			20	// erreur � l'initialisation du d�bogueur

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Op�rations du langage externe
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WLE_MESSTRADUIT					1
#define WLE_MESSTRADUIT_ELEMENT			2
#define WLE_EMPILE_MESSTRADUIT			3
#define WLE_EMPILE_MESSTRADUIT_ELEMENT	4
#define WLE_CONVERSION_RESULTAT			5
#define WLE_CONVERSION_ERREUR			6

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Op�rations multithread
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WDOPMT_INIT_CONTEXTE		0x00000001
#define WDOPMT_TERM_CONTEXTE		0x80000000

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonctions d'interface du langage externe
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

// renseigne le module utilisateur du langage externe
// doit �tre appel� avant l'appel � nWDInitXxxx
void	WDSetModuleA				(LPCSTR pszModule);
void	WDSetModuleW				(LPCWSTR pszModule);
#define WDSetModule WD_DECLARE_A_W(WDSetModuleA,WDSetModuleW)
// active une option du langage externe
// doit �tre appel� avant l'appel � nWDInitXxxx
void	WDActiveOption				(int nOption);
// initialise le langage externe
//	bAfficheErreur : TRUE si on veut voir la fen�tre d'erreur du WL
int		nWDInit						(BOOL bAfficheErreur);
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fen�tre d'erreur du WL
int		nWDInitFromInstance			(HINSTANCE hInstanceVM,BOOL bAfficheErreur);
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fen�tre d'erreur du WL
//	dwOption : options WDOILE_XXX
int		nWDInitFromInstanceEx		(HINSTANCE hInstanceVM,BOOL bAfficheErreur,DWORD dwOption);
// initialise le langage externe et utilise le chemin de la DLL comme r�pertoire contenant les DLL
//	pszNomCompletVM : nom et chemin complet de la DLL VM
//	bAfficheErreur : TRUE si on veut voir la fen�tre d'erreur du WL
int		nWDInitFromNameA			(LPCSTR pszNomCompletVM,BOOL bAfficheErreur);
int		nWDInitFromNameW			(LPCWSTR pszNomCompletVM,BOOL bAfficheErreur);
#define nWDInitFromName WD_DECLARE_A_W(nWDInitFromNameA,nWDInitFromNameW)
// initialise le langage externe et utilise le chemin de la DLL comme r�pertoire contenant les DLL
//	hInstanceVM : instance de la VM d�j� charg�e
//	pszNomCompletVM : nom et chemin complet de la DLL VM charg�e
//	bAfficheErreur : TRUE si on veut voir la fen�tre d'erreur du WL
int		nWDInitFromInstanceNameA	(HINSTANCE hInstanceVM,LPCSTR pszNomCompletVM,BOOL bAfficheErreur);
int		nWDInitFromInstanceNameW	(HINSTANCE hInstanceVM,LPCWSTR pszNomCompletVM,BOOL bAfficheErreur);
#define nWDInitFromInstanceName WD_DECLARE_A_W(nWDInitFromInstanceNameA,nWDInitFromInstanceNameW)
// initialise le langage externe et utilise le chemin de la DLL comme r�pertoire contenant les DLL
//	hInstanceVM : instance de la VM d�j� charg�e
//	pszNomCompletVM : nom et chemin complet de la DLL VM charg�e
//	bAfficheErreur : TRUE si on veut voir la fen�tre d'erreur du WL
//	dwOption : options WDOILE_XXX
int		nWDInitFromInstanceNameExA	(HINSTANCE hInstanceVM,LPCSTR pszNomCompletVM,BOOL bAfficheErreur,DWORD dwOption);
int		nWDInitFromInstanceNameExW	(HINSTANCE hInstanceVM,LPCWSTR pszNomCompletVM,BOOL bAfficheErreur,DWORD dwOption);
#define nWDInitFromInstanceNameEx WD_DECLARE_A_W(nWDInitFromInstanceNameExA,nWDInitFromInstanceNameExW)
// terminaison du langage externe
void	WDTerm						(void);
// ouverture d'une WDL (qui contient les fen�tres, le code, le(s) WDD, ...)
//	pszNomCompletWDL : nom et chemin complet de la WDL � ouvrir
int		nWDOuvreWDLA				(LPCSTR pszNomCompletWDL);
int		nWDOuvreWDLW				(LPCWSTR pszNomCompletWDL);
#define nWDOuvreWDL WD_DECLARE_A_W(nWDOuvreWDLA,nWDOuvreWDLW)
// ouverture d'une WDL
//	pszNomCompletWDL : nom et chemin complet de la WDL � ouvrir
//	pnNumWDL : remplit le num�ro de la WDL
int		nWDOuvreWDLNumA				(LPCSTR pszNomCompletWDL,int* pnNumWDL);
int		nWDOuvreWDLNumW				(LPCWSTR pszNomCompletWDL,int* pnNumWDL);
#define nWDOuvreWDLNum WD_DECLARE_A_W(nWDOuvreWDLNumA,nWDOuvreWDLNumW)
// fermeture d'une WDL contenue dans les ressources d'un ex�cutable (qui contient les fen�tres, le code, le(s) WDD, ...)
//	nNumWDL : num�ro de la WDL renvoy� par nWDOuvreWDLNum()
void	WDFermeWDLNum				(int nNumWDL);
// ouverture d'une WDL contenue dans les ressources d'un ex�cutable (qui contient les fen�tres, le code, le(s) WDD, ...)
//	hInstanceModule : instance du module contenant la ressource
//	nIdRessource : identifiant de la ressource
int		nWDOuvreWDLRes				(HINSTANCE hInstanceModule,UINT nIdRessource);
// fermeture d'une WDL contenue dans les ressources d'un ex�cutable (qui contient les fen�tres, le code, le(s) WDD, ...)
//	hInstanceModule : instance du module contenant la ressource
//	nIdRessource : identifiant de la ressource
void	WDFermeWDLRes				(HINSTANCE hInstanceModule,UINT nIdRessource);
// ex�cute le code d'init d'un projet
//	!!! un seul code d'init de projet peut �tre ex�cut�
int		nWDInitProjetA				(LPCSTR pszNomProjet);
int		nWDInitProjetW				(LPCWSTR pszNomProjet);
#define nWDInitProjet WD_DECLARE_A_W(nWDInitProjetA,nWDInitProjetW)
// renseigner la callback appel�e lors des WDTouche et RenvoieWDTouche pour la prochaine fen�tre � ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : param�tre utilisateur pass� en param�tre � la callback
int		nWDSetCallbackNextA			(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetCallbackNextW			(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetCallbackNext WD_DECLARE_A_W(nWDSetCallbackNextA,nWDSetCallbackNextW)
// renseigner la callback appel�e lors des WDTouche et RenvoieWDTouche pour la prochaine fen�tre � ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : param�tre utilisateur pass� en param�tre � la callback
PVOID	pWDSetCallbackElementA		(PVOID pParent,LPCSTR pszElement,pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
PVOID	pWDSetCallbackElementW		(PVOID pParent,LPCWSTR pszElement,pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define pWDSetCallbackElement WD_DECLARE_A_W(pWDSetCallbackElementA,pWDSetCallbackElementW)
// renseigner la callback appel�e lors des WDTouche et RenvoieWDTouche pour la prochaine fen�tre � ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : param�tre utilisateur pass� en param�tre � la callback
int		nWDSetCallbackModuleA		(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetCallbackModuleW		(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetCallbackModule WD_DECLARE_A_W(nWDSetCallbackModuleA,nWDSetCallbackModuleW)
// renseigner la callback pour le mode compatible
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : param�tre utilisateur pass� en param�tre � la callback
int		nWDSetCallbackCompatibleA	(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetCallbackCompatibleW	(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetCallbackCompatible WD_DECLARE_A_W(nWDSetCallbackCompatibleA,nWDSetCallbackCompatibleW)
// renseigner la callback pour le mode �dition
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : param�tre utilisateur pass� en param�tre � la callback
int		nWDSetPECallbackA			(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetPECallbackW			(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetPECallback WD_DECLARE_A_W(nWDSetPECallbackA,nWDSetPECallbackW)
// renseigner le contexte HF de la prochaine fen�tre � ouvrir
//	pHFContext : contexte HF � utiliser dans la prochaine fen�tre
int		nWDSetHFContextNext			(void* pHFContext);
// renseigner le parent de la prochaine fen�tre � ouvrir
// hWnd : handle de la fen�tre parent de la prochaine fen�tre � ouvrir
int		nWDSetParentNext			(HWND hWnd);

#ifndef LANGAGE_EXTERNE_SANS_COMPILATION_DYNAMIQUE

// ex�cution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande � ex�cuter
int		nWDExecuteA					(LPCSTR pszCommande,...);
int		nWDExecuteW					(LPCWSTR pszCommande,...);
#define nWDExecute WD_DECLARE_A_W(nWDExecuteA,nWDExecuteW)
// ex�cution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande � ex�cuter
int		nWDExecuteExA				(LPCSTR pszCommande);
int		nWDExecuteExW				(LPCWSTR pszCommande);
#define nWDExecuteEx WD_DECLARE_A_W(nWDExecuteExA,nWDExecuteExW)
// compile une proc�dure globale
//	pszProcedure : nom de la proc�dure
//	pszCode : code de la proc�dure
int		nWDCompileA					(LPCSTR pszProcedure,LPCSTR pszCode);
int		nWDCompileW					(LPCWSTR pszProcedure,LPCWSTR pszCode);
#define nWDCompile WD_DECLARE_A_W(nWDCompileA,nWDCompileW)

#endif	//!LANGAGE_EXTERNE_SANS_COMPILATION_DYNAMIQUE

// �value la valeur d'un �l�ment : champ, variable, rubrique HF (ex : fenetre.champ, variable, fichier.rubrique)
// les acc�s aux �l�ments indic�s ne sont pas possibles (ex : table[1] renvoie une erreur)
//	pszElement : nom de l'�l�ment � �valeur
int		nWDEvalueA					(LPCSTR pszElement);
int		nWDEvalueW					(LPCWSTR pszElement);
#define nWDEvalue WD_DECLARE_A_W(nWDEvalueA,nWDEvalueW)
// empile un param�tre sur la pile
//	pAdresse : adresse du param�tre
//	nType : type du param�tre
int		nWDEmpile					(LPCVOID pAdresse,int nType);
// empile un param�tre sur la pile
//	pAdresse : adresse du param�tre
//	nTaille : taille du param�tre
//	nType : type du param�tre
int		nWDEmpileEx					(LPCVOID pAdresse,int nTaille,int nType);
// appelle directement une fonction composante
//	nNumCompo : num�ro de la composante
//	nNumFonc : num�ro de la fonction
//	nNumSyntaxe : num�ro de la syntaxe
//	nNbParam : nombre de param�tres
int		nWDAppelle					(int nNumCompo,int nNumFonc,int nNumSyntaxe,int nNbParam);
// lit la valeur d'une variable de composante
int		nWDLitVariableWL			(int nNumCompo,int nNumVar,int nIndice);
// �crit dans une variable de composante
int		nWDEcritVariableWL			(int nNumCompo,int nNumVar,int nIndice);
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDLitPropElemA				(LPCSTR pszElement,int nNumProp);
int		nWDLitPropElemW				(LPCWSTR pszElement,int nNumProp);
#define nWDLitPropElem WD_DECLARE_A_W(nWDLitPropElemA,nWDLitPropElemW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nNumProp : num�ro de la propri�t� � lire
//	pointeur sur la valeur � remplir
int		nWDLitPropElemAnyA			(LPCSTR pszElement,int nNumProp,PVOID pclAny);
int		nWDLitPropElemAnyW			(LPCWSTR pszElement,int nNumProp,PVOID pclAny);
#define nWDLitPropElemAny WD_DECLARE_A_W(nWDLitPropElemAnyA,nWDLitPropElemAnyW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndice : indice de l'�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDLitPropElemIndA			(LPCSTR pszElement,int nIndice,int nNumProp);
int		nWDLitPropElemIndW			(LPCWSTR pszElement,int nIndice,int nNumProp);
#define nWDLitPropElemInd WD_DECLARE_A_W(nWDLitPropElemIndA,nWDLitPropElemIndW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndice : indice de l'�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDLitPropElemCleA			(LPCSTR pszElement,LPCSTR pszCle,int nNumProp);
int		nWDLitPropElemCleW			(LPCWSTR pszElement,LPCWSTR pszCle,int nNumProp);
#define nWDLitPropElemCle WD_DECLARE_A_W(nWDLitPropElemCleA,nWDLitPropElemCleW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndice : indice de l'�l�ment
//	nNumProp : num�ro de la propri�t� � lire
//	pointeur sur la valeur � remplir
int		nWDLitPropElemAnyIndA		(LPCSTR pszElement,int nIndice,int nNumProp,PVOID pclAny);
int		nWDLitPropElemAnyIndW		(LPCWSTR pszElement,int nIndice,int nNumProp,PVOID pclAny);
#define nWDLitPropElemAnyInd WD_DECLARE_A_W(nWDLitPropElemAnyIndA,nWDLitPropElemAnyIndW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndice1, nIndice2 : indices de l'�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDLitPropElemInd2A			(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
int		nWDLitPropElemInd2W			(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
#define nWDLitPropElemInd2 WD_DECLARE_A_W(nWDLitPropElemInd2A,nWDLitPropElemInd2W)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndice1, nIndice2 : indices de l'�l�ment
//	nNumProp : num�ro de la propri�t� � lire
//	pointeur sur la valeur � remplir
int		nWDLitPropElemAnyInd2A		(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp,PVOID pclAny);
int		nWDLitPropElemAnyInd2W		(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp,PVOID pclAny);
#define nWDLitPropElemAnyInd2 WD_DECLARE_A_W(nWDLitPropElemAnyInd2A,nWDLitPropElemAnyInd2W)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndiceElement : indice de l'�l�ment
//	pszSousElement : nom du sous-�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDLitPropSousElemA			(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nNumProp);
int		nWDLitPropSousElemW			(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nNumProp);
#define nWDLitPropSousElem WD_DECLARE_A_W(nWDLitPropSousElemA,nWDLitPropSousElemW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndiceElement : indice de l'�l�ment
//	pszSousElement : nom du sous-�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDEcritPropSousElemA		(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nNumProp);
int		nWDEcritPropSousElemW		(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nNumProp);
#define nWDEcritPropSousElem WD_DECLARE_A_W(nWDEcritPropSousElemA,nWDEcritPropSousElemW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndiceElement : indice de l'�l�ment
//	pszSousElement : nom du sous-�l�ment
//	nIndiceSousElement : indice du sous-�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDLitPropSousElemIndA		(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nIndiceSousElement,int nNumProp);
int		nWDLitPropSousElemIndW		(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nIndiceSousElement,int nNumProp);
#define nWDLitPropSousElemInd WD_DECLARE_A_W(nWDLitPropSousElemIndA,nWDLitPropSousElemIndW)
// acc�de directement � une propri�t� d'un �l�ment en lecture
//	pszElement : nom de l'�l�ment
//	nIndiceElement : indice de l'�l�ment
//	pszSousElement : nom du sous-�l�ment
//	nIndiceSousElement : indice du sous-�l�ment
//	nNumProp : num�ro de la propri�t� � lire
int		nWDEcritPropSousElemIndA	(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nIndiceSousElement,int nNumProp);
int		nWDEcritPropSousElemIndW	(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nIndiceSousElement,int nNumProp);
#define nWDEcritPropSousElemInd WD_DECLARE_A_W(nWDEcritPropSousElemIndA,nWDEcritPropSousElemIndW)
// acc�de directement � une propri�t� d'un �l�ment en �criture
//	pszElement : nom de l'�l�ment
//	nNumProp : num�ro de la propri�t� � �crire
int		nWDEcritPropElemA			(LPCSTR pszElement,int nNumProp);
int		nWDEcritPropElemW			(LPCWSTR pszElement,int nNumProp);
#define nWDEcritPropElem WD_DECLARE_A_W(nWDEcritPropElemA,nWDEcritPropElemW)
// acc�de directement � une propri�t� d'un �l�ment en �criture
//	pszElement : nom de l'�l�ment
//	nIndice : indice de l'�l�ment
//	nNumProp : num�ro de la propri�t� � �crire
int		nWDEcritPropElemIndA		(LPCSTR pszElement,int nIndice,int nNumProp);
int		nWDEcritPropElemIndW		(LPCWSTR pszElement,int nIndice,int nNumProp);
#define nWDEcritPropElemInd WD_DECLARE_A_W(nWDEcritPropElemIndA,nWDEcritPropElemIndW)
// acc�de directement � une propri�t� d'un �l�ment en �criture
//	pszElement : nom de l'�l�ment
//	pszCle : cl�
//	nNumProp : num�ro de la propri�t� � �crire
int		nWDEcritPropElemCleA		(LPCSTR pszElement,LPCSTR pszCle,int nNumProp);
int		nWDEcritPropElemCleW		(LPCWSTR pszElement,LPCWSTR pszCle,int nNumProp);
#define nWDEcritPropElemCle WD_DECLARE_A_W(nWDEcritPropElemCleA,nWDEcritPropElemCleW)
// acc�de directement � une propri�t� d'un �l�ment en �criture
//	pszElement : nom de l'�l�ment
//	nIndice1, nIndice2 : indices de l'�l�ment
//	nNumProp : num�ro de la propri�t� � �crire
int		nWDEcritPropElemInd2A		(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
int		nWDEcritPropElemInd2W		(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
#define nWDEcritPropElemInd2 WD_DECLARE_A_W(nWDEcritPropElemInd2A,nWDEcritPropElemInd2W)
// v�rifie si un champ existe
int		nWDChampExisteA				(LPCSTR pszNomChamp,BOOL* pbExiste);
int		nWDChampExisteW				(LPCWSTR pszNomChamp,BOOL* pbExiste);
#define nWDChampExiste WD_DECLARE_A_W(nWDChampExisteA,nWDChampExisteW)
// r�cup�re un message multilangue
int		nWDMessTraduit				(int nMessage);
// r�cup�re un message multilangue
int		nWDMessTraduitElementA		(LPCSTR pszElement,int nMessage);
int		nWDMessTraduitElementW		(LPCWSTR pszElement,int nMessage);
#define nWDMessTraduitElement WD_DECLARE_A_W(nWDMessTraduitElementA,nWDMessTraduitElementW)
// empile un message multilangue
int		nWDEmpileMessTraduit		(int nMessage);
// r�cup�re un message multilangue
int		nWDEmpileMessTraduitElementA(LPCSTR pszElement,int nMessage);
int		nWDEmpileMessTraduitElementW(LPCWSTR pszElement,int nMessage);
#define nWDEmpileMessTraduitElement WD_DECLARE_A_W(nWDEmpileMessTraduitElementA,nWDEmpileMessTraduitElementW)
// r�cup�re le contexte HF
int		nWDGetHFContext				(void** ppHFContext);
// r�cup�re le contexte global VM
int		nWDGetVMData				(void** ppVMData);
// r�cup�re le contexte VM
int		nWDGetVM					(void** ppVM);
// r�cup�re le libshop
int		nWDGetLibShop				(void** ppLibShop);
// r�cup�re l'interface IInfoLocale
int		nWDGetInfoLocale			(void** ppInfoLocale);
// r�cup�re le contexte OBJ
int		nWDGetIEXE					(void** ppEXE);
// renvoie le type de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue()
WORD	wWDGetTypeValeurRetour		(void);
// renvoie TRUE si le type de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue() est une cha�ne Ansi ou Unicode
BOOL	bWDValeurRetourChaine		(void);
// renvoie TRUE si la valeur de retour est NULL
BOOL	bWDValeurRetourNULL			(void);
// renvoie la valeur bool�enne de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type bool�en, la fonction renvoie FALSE
BOOL	bWDGetValeurRetour			(void);
// renvoie la valeur enti�re de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type entier, la fonction renvoie 0
int		nWDGetValeurRetour			(void);
// renvoie la valeur enti�re sur 8 octets de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type entier sur 8 octets, la fonction renvoie 0
WDINT64	i64WDGetValeurRetour		(void);
// renvoie la valeur flottante de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type flottant, la fonction renvoie 0.0
double	dWDGetValeurRetour			(void);
// renvoie la longueur d'une chaine ou d'un buffer binaire
//	!!! attention : si la valeur n'est pas de type chaine ou binaire, la fonction renvoie 0
size_t	nWDLongueurValeurRetour		(void);
// renvoie la valeur chaine de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type chaine, la fonction renvoie NULL
LPCSTR	pszWDGetValeurRetourA		(void);
LPCWSTR	pszWDGetValeurRetourW		(void);
LPCTSTR	pszWDGetValeurRetour		(void);
// renvoie la valeur binaire de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type binaire, la fonction renvoie NULL
PBYTE	pbyWDGetValeurRetour		(void);
// renvoie le code d'erreur de la derni�re erreur
int		nWDGetLastError				(void);
// renvoie le message de la derni�re erreur
LPCSTR	pszWDGetLastErrorA			(void);
LPCWSTR	pszWDGetLastErrorW			(void);
LPCTSTR	pszWDGetLastError			(void);
// reprise sur erreur : force la reprise normale de l'ex�cution apr�s une erreur
void	WDRepriseErreur				(void);
// renvoie le contexte courant
PVOID	pWDGetContexte				();
// modifie le contexte courant
// renvoie l'ancien contexte en cours
// si pContexte est NULL, se replace sur le contexte local
PVOID	pWDSetContexte				(PVOID pContexte);
// renvoie le contexte d'�l�ment courant
PVOID	pWDGetContexteElement		();
// modifie le contexte d'�l�ment courant
// renvoie l'ancien contexte en cours
PVOID	pWDModifieContexteElement	(PVOID pContexteElement);
// restaure le contexte d'�l�ment courant
// renvoie l'ancien contexte en cours
PVOID	pWDRestaureContexteElement	(PVOID pContexteElement);

// initialise un nouveau contexte de langage externe pour utilisation depuis un thread secondaire
PVOID	pWDMTInitThread				(void);
// termine le contexte de langage externe pour utilisation depuis un thread secondaire
//	pContexte : contexte de langage externe du thread � terminer
void	WDMTTermThread				(PVOID pContexte);
// empile un param�tre sur la pile
//	pContexte : contexte de langage externe du thread
//	pAdresse : adresse du param�tre
//	nType : type du param�tre
int		nWDMTEmpile					(PVOID pContexte,LPCVOID pAdresse,int nType);
// appelle directement une fonction composante
//	pContexte : contexte de langage externe du thread
//	nNumCompo : num�ro de la composante
//	nNumFonc : num�ro de la fonction
//	nNumSyntaxe : num�ro de la syntaxe
//	nNbParam : nombre de param�tres
int		nWDMTAppelle				(PVOID pContexte,int nNumCompo,int nNumFonc,int nNumSyntaxe,int nNbParam);
// lit la valeur d'une variable de composante
int		nWDMTLitVariableWL			(PVOID pContexte,int nNumCompo,int nNumVar,int nIndice);
// �crit dans une variable de composante
int		nWDMTEcritVariableWL		(PVOID pContexte,int nNumCompo,int nNumVar,int nIndice);
// renvoie le type de la valeur de retour de la derni�re instruction nWDMTExecute() ou nWDMTEvalue()
WORD	wWDMTGetTypeValeurRetour	(PVOID pContexte);
// renvoie TRUE si le type de la valeur de retour de la derni�re instruction nWDExecute() ou nWDEvalue() est une cha�ne Ansi ou Unicode
BOOL	bWDMTValeurRetourChaine		(PVOID pContexte);
// renvoie TRUE si la valeur de retour est NULL
BOOL	bWDMTValeurRetourNULL		(PVOID pContexte);
// renvoie la valeur bool�enne de la valeur de retour de la derni�re instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type bool�en, la fonction renvoie FALSE
BOOL	bWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur enti�re de la valeur de retour de la derni�re instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type entier, la fonction renvoie 0
int		nWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur enti�re sur 8 octets de la valeur de retour de la derni�re instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type entier sur 8 octets, la fonction renvoie 0
WDINT64	i64WDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur flottante de la valeur de retour de la derni�re instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type flottant, la fonction renvoie 0.0
double	dWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la longueur d'une chaine ou d'un buffer binaire
//	!!! attention : si la valeur n'est pas de type chaine ou binaire, la fonction renvoie 0
size_t	nWDMTLongueurValeurRetour	(PVOID pContexte);
// renvoie la valeur chaine de la valeur de retour de la derni�re instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type chaine, la fonction renvoie NULL
LPCSTR	pszWDMTGetValeurRetourA		(PVOID pContexte);
LPCWSTR	pszWDMTGetValeurRetourW		(PVOID pContexte);
LPCTSTR	pszWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur binaire de la valeur de retour de la derni�re instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type binaire, la fonction renvoie NULL
PBYTE	pbyWDMTGetValeurRetour		(PVOID pContexte);
// renvoie le code d'erreur de la derni�re erreur
int		nWDMTGetLastError			(PVOID pContexte);
// renvoie le message de la derni�re erreur
LPCSTR	pszWDMTGetLastErrorA		(PVOID pContexte);
LPCWSTR	pszWDMTGetLastErrorW		(PVOID pContexte);
LPCTSTR	pszWDMTGetLastError			(PVOID pContexte);
// reprise sur erreur : force la reprise normale de l'ex�cution apr�s une erreur
void	WDMTRepriseErreur			(PVOID pContexte);

#ifdef __cplusplus
	}
#endif	//__cplusplus

#endif	//!__WDEXTERN_H
