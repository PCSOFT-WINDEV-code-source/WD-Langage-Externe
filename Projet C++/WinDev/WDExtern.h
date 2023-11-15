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
// Définitions
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

	// définition des HANDLEs
	#ifndef HINSTANCE_ERROR
		#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
		DECLARE_HANDLE(HINSTANCE);
		DECLARE_HANDLE(HWND);
		DECLARE_HANDLE(HMODULE);
		#define HINSTANCE_ERROR		NULL       // DLL non chargée
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
// numéro de version
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	WD_VERSION_EXTERNE		15

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// type de ressource pour les WDL intégrés dans des exécutables
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TYPE_RES_WDL	"RT_WDL"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Prototype de la fonction "callback" appelée par WDTouche et RenvoieWDTouche
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (*pfnWDCALLBACKA)	(DWORD_PTR dwUserParam, LPCSTR pszCodeAction);
typedef void (*pfnWDCALLBACK)	(DWORD_PTR dwUserParam, LPCWSTR pszCodeAction);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// types possibles pour les valeurs renvoyées par la machine virtuelle
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
// structure pouvant contenir des valeurs renvoyées par la machine virtuelle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _STWDValeur
{	// type de la valeur
	WORD		wType;
	// valeur entière
	int			nValeur;
	// valeur entière sur 64 bits
	WDINT64		i64Valeur;
	// valeur flottante
	double		dValeur;
	// valeur chaine de caractères
	LPWSTR		pszValeurW;
	// valeur binaire
	PBYTE		pbyBinaire;
	// TRUE si la valeur de retour est NULL
	BOOL		bNull;
	// valeur chaine de caractères
	LPSTR		pszValeurA;
	// informations supplémentaires
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
	// informations supplémentaires
	DWORD		dwInfoSup[5];
} STWDErreur;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structure de communication entre programme hôte et machine virtuelle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _STWDExtern
{	// numéro de version
	WORD		wVersion;
	// contexte d'exécution de la machine virtuelle
	PVOID		pContexte;
	// valeur de retour de la fonction appelée
	STWDValeur*	pstValeurRetour;
	// erreur
	STWDErreur*	pstErreur;
	// identifiant du module hôte
	LPCWSTR		pszModuleW;
	// identifiant du module hôte
	LPCSTR		pszModuleA;
	// informations supplémentaires
	DWORD		dwInfoSup[5];
} STWDExtern;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structure d'initialisation de la machine virtuelle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _STInitLE
{	// numéro de version
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
	// informations supplémentaires
	DWORD_PTR	dwInfoSup[5];
} STInitLE;

#pragma pack()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// options d'initialisation du langage externe
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WDOILE_COMPOSANTE						0x00000001	// langage externe pour une composante
#define WDOILE_AUTORISE_ATTACHEMENT_DEBOGUEUR	0x00000002	// autorise l'attachement du débogueur sur l'application
#define WDOILE_AUTORISE_LOG_EXECUTION			0x00000004	// autorise la trace d'exécution
#define WDOILE_DESACTIVE_COLLECTEUR_TOPO		0x00000008	// désactive le collecteur topologique
#define WDOILE_AUTORISE_AUDIT_EXECUTION			0x00000010	// autorise l'audit d'exécution

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// codes d'erreur
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	WDERREUR_OK					0	// succés
#define	WDERREUR_VERSION			1	// incompatibilité de numéro de version
#define	WDERREUR_DLLLOAD			2	// problème au chargement de la DLL
#define WDERREUR_WDLLOAD			3	// problème au chargement de la WDL
#define WDERREUR_DLLCPL				4	// dll de compilation non trouvée
#define WDERREUR_ERREURCPL			5	// erreur de compilation
#define WDERREUR_MEMOIRE			6	// plus de mémoire disponible
#define WDERREUR_TYPE				8	// type non convertible
#define WDERREUR_INIT				9	// langage externe pas initialisé
#define	WDERREUR_EXECUTION			10	// erreur en cours d'exécution
#define WDERREUR_ERREUR				11	// erreur précédente non traitée
#define WDERREUR_COMMANDE			12	// commande de nWDExecute trop longue
#define WDERREUR_INITPROJET			13	// le code d'init du projet a déjà été exécuté
#define WDERREUR_ELEMINCONNU		14	// élément inconnu
#define WDERREUR_AUCUNEWDL			15	// aucune WDL n'a été chargée
#define WDERREUR_AUCUNPROJET		16	// aucun projet n'est présent dans la première WDL
#define WDERREUR_OUVERTUREANALYSE	17	// erreur à l'ouverture de l'analyse
#define WDERREUR_COMPOSANT			18	// erreur à l'ouverture des composants
#define WDERREUR_THREAD				19	// erreur en manipulation des threads
#define WDERREUR_DEBOGUEUR			20	// erreur à l'initialisation du débogueur

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Opérations du langage externe
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WLE_MESSTRADUIT					1
#define WLE_MESSTRADUIT_ELEMENT			2
#define WLE_EMPILE_MESSTRADUIT			3
#define WLE_EMPILE_MESSTRADUIT_ELEMENT	4
#define WLE_CONVERSION_RESULTAT			5
#define WLE_CONVERSION_ERREUR			6

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Opérations multithread
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
// doit être appelé avant l'appel à nWDInitXxxx
void	WDSetModuleA				(LPCSTR pszModule);
void	WDSetModuleW				(LPCWSTR pszModule);
#define WDSetModule WD_DECLARE_A_W(WDSetModuleA,WDSetModuleW)
// active une option du langage externe
// doit être appelé avant l'appel à nWDInitXxxx
void	WDActiveOption				(int nOption);
// initialise le langage externe
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int		nWDInit						(BOOL bAfficheErreur);
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int		nWDInitFromInstance			(HINSTANCE hInstanceVM,BOOL bAfficheErreur);
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
//	dwOption : options WDOILE_XXX
int		nWDInitFromInstanceEx		(HINSTANCE hInstanceVM,BOOL bAfficheErreur,DWORD dwOption);
// initialise le langage externe et utilise le chemin de la DLL comme répertoire contenant les DLL
//	pszNomCompletVM : nom et chemin complet de la DLL VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int		nWDInitFromNameA			(LPCSTR pszNomCompletVM,BOOL bAfficheErreur);
int		nWDInitFromNameW			(LPCWSTR pszNomCompletVM,BOOL bAfficheErreur);
#define nWDInitFromName WD_DECLARE_A_W(nWDInitFromNameA,nWDInitFromNameW)
// initialise le langage externe et utilise le chemin de la DLL comme répertoire contenant les DLL
//	hInstanceVM : instance de la VM déjà chargée
//	pszNomCompletVM : nom et chemin complet de la DLL VM chargée
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int		nWDInitFromInstanceNameA	(HINSTANCE hInstanceVM,LPCSTR pszNomCompletVM,BOOL bAfficheErreur);
int		nWDInitFromInstanceNameW	(HINSTANCE hInstanceVM,LPCWSTR pszNomCompletVM,BOOL bAfficheErreur);
#define nWDInitFromInstanceName WD_DECLARE_A_W(nWDInitFromInstanceNameA,nWDInitFromInstanceNameW)
// initialise le langage externe et utilise le chemin de la DLL comme répertoire contenant les DLL
//	hInstanceVM : instance de la VM déjà chargée
//	pszNomCompletVM : nom et chemin complet de la DLL VM chargée
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
//	dwOption : options WDOILE_XXX
int		nWDInitFromInstanceNameExA	(HINSTANCE hInstanceVM,LPCSTR pszNomCompletVM,BOOL bAfficheErreur,DWORD dwOption);
int		nWDInitFromInstanceNameExW	(HINSTANCE hInstanceVM,LPCWSTR pszNomCompletVM,BOOL bAfficheErreur,DWORD dwOption);
#define nWDInitFromInstanceNameEx WD_DECLARE_A_W(nWDInitFromInstanceNameExA,nWDInitFromInstanceNameExW)
// terminaison du langage externe
void	WDTerm						(void);
// ouverture d'une WDL (qui contient les fenêtres, le code, le(s) WDD, ...)
//	pszNomCompletWDL : nom et chemin complet de la WDL à ouvrir
int		nWDOuvreWDLA				(LPCSTR pszNomCompletWDL);
int		nWDOuvreWDLW				(LPCWSTR pszNomCompletWDL);
#define nWDOuvreWDL WD_DECLARE_A_W(nWDOuvreWDLA,nWDOuvreWDLW)
// ouverture d'une WDL
//	pszNomCompletWDL : nom et chemin complet de la WDL à ouvrir
//	pnNumWDL : remplit le numéro de la WDL
int		nWDOuvreWDLNumA				(LPCSTR pszNomCompletWDL,int* pnNumWDL);
int		nWDOuvreWDLNumW				(LPCWSTR pszNomCompletWDL,int* pnNumWDL);
#define nWDOuvreWDLNum WD_DECLARE_A_W(nWDOuvreWDLNumA,nWDOuvreWDLNumW)
// fermeture d'une WDL contenue dans les ressources d'un exécutable (qui contient les fenêtres, le code, le(s) WDD, ...)
//	nNumWDL : numéro de la WDL renvoyé par nWDOuvreWDLNum()
void	WDFermeWDLNum				(int nNumWDL);
// ouverture d'une WDL contenue dans les ressources d'un exécutable (qui contient les fenêtres, le code, le(s) WDD, ...)
//	hInstanceModule : instance du module contenant la ressource
//	nIdRessource : identifiant de la ressource
int		nWDOuvreWDLRes				(HINSTANCE hInstanceModule,UINT nIdRessource);
// fermeture d'une WDL contenue dans les ressources d'un exécutable (qui contient les fenêtres, le code, le(s) WDD, ...)
//	hInstanceModule : instance du module contenant la ressource
//	nIdRessource : identifiant de la ressource
void	WDFermeWDLRes				(HINSTANCE hInstanceModule,UINT nIdRessource);
// exécute le code d'init d'un projet
//	!!! un seul code d'init de projet peut être exécuté
int		nWDInitProjetA				(LPCSTR pszNomProjet);
int		nWDInitProjetW				(LPCWSTR pszNomProjet);
#define nWDInitProjet WD_DECLARE_A_W(nWDInitProjetA,nWDInitProjetW)
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche pour la prochaine fenêtre à ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int		nWDSetCallbackNextA			(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetCallbackNextW			(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetCallbackNext WD_DECLARE_A_W(nWDSetCallbackNextA,nWDSetCallbackNextW)
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche pour la prochaine fenêtre à ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
PVOID	pWDSetCallbackElementA		(PVOID pParent,LPCSTR pszElement,pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
PVOID	pWDSetCallbackElementW		(PVOID pParent,LPCWSTR pszElement,pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define pWDSetCallbackElement WD_DECLARE_A_W(pWDSetCallbackElementA,pWDSetCallbackElementW)
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche pour la prochaine fenêtre à ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int		nWDSetCallbackModuleA		(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetCallbackModuleW		(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetCallbackModule WD_DECLARE_A_W(nWDSetCallbackModuleA,nWDSetCallbackModuleW)
// renseigner la callback pour le mode compatible
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int		nWDSetCallbackCompatibleA	(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetCallbackCompatibleW	(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetCallbackCompatible WD_DECLARE_A_W(nWDSetCallbackCompatibleA,nWDSetCallbackCompatibleW)
// renseigner la callback pour le mode édition
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int		nWDSetPECallbackA			(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam);
int		nWDSetPECallbackW			(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam);
#define nWDSetPECallback WD_DECLARE_A_W(nWDSetPECallbackA,nWDSetPECallbackW)
// renseigner le contexte HF de la prochaine fenêtre à ouvrir
//	pHFContext : contexte HF à utiliser dans la prochaine fenêtre
int		nWDSetHFContextNext			(void* pHFContext);
// renseigner le parent de la prochaine fenêtre à ouvrir
// hWnd : handle de la fenêtre parent de la prochaine fenêtre à ouvrir
int		nWDSetParentNext			(HWND hWnd);

#ifndef LANGAGE_EXTERNE_SANS_COMPILATION_DYNAMIQUE

// exécution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande à exécuter
int		nWDExecuteA					(LPCSTR pszCommande,...);
int		nWDExecuteW					(LPCWSTR pszCommande,...);
#define nWDExecute WD_DECLARE_A_W(nWDExecuteA,nWDExecuteW)
// exécution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande à exécuter
int		nWDExecuteExA				(LPCSTR pszCommande);
int		nWDExecuteExW				(LPCWSTR pszCommande);
#define nWDExecuteEx WD_DECLARE_A_W(nWDExecuteExA,nWDExecuteExW)
// compile une procédure globale
//	pszProcedure : nom de la procédure
//	pszCode : code de la procédure
int		nWDCompileA					(LPCSTR pszProcedure,LPCSTR pszCode);
int		nWDCompileW					(LPCWSTR pszProcedure,LPCWSTR pszCode);
#define nWDCompile WD_DECLARE_A_W(nWDCompileA,nWDCompileW)

#endif	//!LANGAGE_EXTERNE_SANS_COMPILATION_DYNAMIQUE

// évalue la valeur d'un élément : champ, variable, rubrique HF (ex : fenetre.champ, variable, fichier.rubrique)
// les accès aux éléments indicés ne sont pas possibles (ex : table[1] renvoie une erreur)
//	pszElement : nom de l'élément à évaleur
int		nWDEvalueA					(LPCSTR pszElement);
int		nWDEvalueW					(LPCWSTR pszElement);
#define nWDEvalue WD_DECLARE_A_W(nWDEvalueA,nWDEvalueW)
// empile un paramètre sur la pile
//	pAdresse : adresse du paramètre
//	nType : type du paramètre
int		nWDEmpile					(LPCVOID pAdresse,int nType);
// empile un paramètre sur la pile
//	pAdresse : adresse du paramètre
//	nTaille : taille du paramètre
//	nType : type du paramètre
int		nWDEmpileEx					(LPCVOID pAdresse,int nTaille,int nType);
// appelle directement une fonction composante
//	nNumCompo : numéro de la composante
//	nNumFonc : numéro de la fonction
//	nNumSyntaxe : numéro de la syntaxe
//	nNbParam : nombre de paramètres
int		nWDAppelle					(int nNumCompo,int nNumFonc,int nNumSyntaxe,int nNbParam);
// lit la valeur d'une variable de composante
int		nWDLitVariableWL			(int nNumCompo,int nNumVar,int nIndice);
// écrit dans une variable de composante
int		nWDEcritVariableWL			(int nNumCompo,int nNumVar,int nIndice);
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à lire
int		nWDLitPropElemA				(LPCSTR pszElement,int nNumProp);
int		nWDLitPropElemW				(LPCWSTR pszElement,int nNumProp);
#define nWDLitPropElem WD_DECLARE_A_W(nWDLitPropElemA,nWDLitPropElemW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int		nWDLitPropElemAnyA			(LPCSTR pszElement,int nNumProp,PVOID pclAny);
int		nWDLitPropElemAnyW			(LPCWSTR pszElement,int nNumProp,PVOID pclAny);
#define nWDLitPropElemAny WD_DECLARE_A_W(nWDLitPropElemAnyA,nWDLitPropElemAnyW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
int		nWDLitPropElemIndA			(LPCSTR pszElement,int nIndice,int nNumProp);
int		nWDLitPropElemIndW			(LPCWSTR pszElement,int nIndice,int nNumProp);
#define nWDLitPropElemInd WD_DECLARE_A_W(nWDLitPropElemIndA,nWDLitPropElemIndW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
int		nWDLitPropElemCleA			(LPCSTR pszElement,LPCSTR pszCle,int nNumProp);
int		nWDLitPropElemCleW			(LPCWSTR pszElement,LPCWSTR pszCle,int nNumProp);
#define nWDLitPropElemCle WD_DECLARE_A_W(nWDLitPropElemCleA,nWDLitPropElemCleW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int		nWDLitPropElemAnyIndA		(LPCSTR pszElement,int nIndice,int nNumProp,PVOID pclAny);
int		nWDLitPropElemAnyIndW		(LPCWSTR pszElement,int nIndice,int nNumProp,PVOID pclAny);
#define nWDLitPropElemAnyInd WD_DECLARE_A_W(nWDLitPropElemAnyIndA,nWDLitPropElemAnyIndW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à lire
int		nWDLitPropElemInd2A			(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
int		nWDLitPropElemInd2W			(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
#define nWDLitPropElemInd2 WD_DECLARE_A_W(nWDLitPropElemInd2A,nWDLitPropElemInd2W)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int		nWDLitPropElemAnyInd2A		(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp,PVOID pclAny);
int		nWDLitPropElemAnyInd2W		(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp,PVOID pclAny);
#define nWDLitPropElemAnyInd2 WD_DECLARE_A_W(nWDLitPropElemAnyInd2A,nWDLitPropElemAnyInd2W)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nNumProp : numéro de la propriété à lire
int		nWDLitPropSousElemA			(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nNumProp);
int		nWDLitPropSousElemW			(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nNumProp);
#define nWDLitPropSousElem WD_DECLARE_A_W(nWDLitPropSousElemA,nWDLitPropSousElemW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nNumProp : numéro de la propriété à lire
int		nWDEcritPropSousElemA		(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nNumProp);
int		nWDEcritPropSousElemW		(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nNumProp);
#define nWDEcritPropSousElem WD_DECLARE_A_W(nWDEcritPropSousElemA,nWDEcritPropSousElemW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nIndiceSousElement : indice du sous-élément
//	nNumProp : numéro de la propriété à lire
int		nWDLitPropSousElemIndA		(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nIndiceSousElement,int nNumProp);
int		nWDLitPropSousElemIndW		(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nIndiceSousElement,int nNumProp);
#define nWDLitPropSousElemInd WD_DECLARE_A_W(nWDLitPropSousElemIndA,nWDLitPropSousElemIndW)
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nIndiceSousElement : indice du sous-élément
//	nNumProp : numéro de la propriété à lire
int		nWDEcritPropSousElemIndA	(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nIndiceSousElement,int nNumProp);
int		nWDEcritPropSousElemIndW	(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nIndiceSousElement,int nNumProp);
#define nWDEcritPropSousElemInd WD_DECLARE_A_W(nWDEcritPropSousElemIndA,nWDEcritPropSousElemIndW)
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à écrire
int		nWDEcritPropElemA			(LPCSTR pszElement,int nNumProp);
int		nWDEcritPropElemW			(LPCWSTR pszElement,int nNumProp);
#define nWDEcritPropElem WD_DECLARE_A_W(nWDEcritPropElemA,nWDEcritPropElemW)
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à écrire
int		nWDEcritPropElemIndA		(LPCSTR pszElement,int nIndice,int nNumProp);
int		nWDEcritPropElemIndW		(LPCWSTR pszElement,int nIndice,int nNumProp);
#define nWDEcritPropElemInd WD_DECLARE_A_W(nWDEcritPropElemIndA,nWDEcritPropElemIndW)
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	pszCle : clé
//	nNumProp : numéro de la propriété à écrire
int		nWDEcritPropElemCleA		(LPCSTR pszElement,LPCSTR pszCle,int nNumProp);
int		nWDEcritPropElemCleW		(LPCWSTR pszElement,LPCWSTR pszCle,int nNumProp);
#define nWDEcritPropElemCle WD_DECLARE_A_W(nWDEcritPropElemCleA,nWDEcritPropElemCleW)
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à écrire
int		nWDEcritPropElemInd2A		(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
int		nWDEcritPropElemInd2W		(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp);
#define nWDEcritPropElemInd2 WD_DECLARE_A_W(nWDEcritPropElemInd2A,nWDEcritPropElemInd2W)
// vérifie si un champ existe
int		nWDChampExisteA				(LPCSTR pszNomChamp,BOOL* pbExiste);
int		nWDChampExisteW				(LPCWSTR pszNomChamp,BOOL* pbExiste);
#define nWDChampExiste WD_DECLARE_A_W(nWDChampExisteA,nWDChampExisteW)
// récupère un message multilangue
int		nWDMessTraduit				(int nMessage);
// récupère un message multilangue
int		nWDMessTraduitElementA		(LPCSTR pszElement,int nMessage);
int		nWDMessTraduitElementW		(LPCWSTR pszElement,int nMessage);
#define nWDMessTraduitElement WD_DECLARE_A_W(nWDMessTraduitElementA,nWDMessTraduitElementW)
// empile un message multilangue
int		nWDEmpileMessTraduit		(int nMessage);
// récupère un message multilangue
int		nWDEmpileMessTraduitElementA(LPCSTR pszElement,int nMessage);
int		nWDEmpileMessTraduitElementW(LPCWSTR pszElement,int nMessage);
#define nWDEmpileMessTraduitElement WD_DECLARE_A_W(nWDEmpileMessTraduitElementA,nWDEmpileMessTraduitElementW)
// récupère le contexte HF
int		nWDGetHFContext				(void** ppHFContext);
// récupère le contexte global VM
int		nWDGetVMData				(void** ppVMData);
// récupère le contexte VM
int		nWDGetVM					(void** ppVM);
// récupère le libshop
int		nWDGetLibShop				(void** ppLibShop);
// récupère l'interface IInfoLocale
int		nWDGetInfoLocale			(void** ppInfoLocale);
// récupère le contexte OBJ
int		nWDGetIEXE					(void** ppEXE);
// renvoie le type de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
WORD	wWDGetTypeValeurRetour		(void);
// renvoie TRUE si le type de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue() est une chaîne Ansi ou Unicode
BOOL	bWDValeurRetourChaine		(void);
// renvoie TRUE si la valeur de retour est NULL
BOOL	bWDValeurRetourNULL			(void);
// renvoie la valeur booléenne de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type booléen, la fonction renvoie FALSE
BOOL	bWDGetValeurRetour			(void);
// renvoie la valeur entière de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type entier, la fonction renvoie 0
int		nWDGetValeurRetour			(void);
// renvoie la valeur entière sur 8 octets de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type entier sur 8 octets, la fonction renvoie 0
WDINT64	i64WDGetValeurRetour		(void);
// renvoie la valeur flottante de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type flottant, la fonction renvoie 0.0
double	dWDGetValeurRetour			(void);
// renvoie la longueur d'une chaine ou d'un buffer binaire
//	!!! attention : si la valeur n'est pas de type chaine ou binaire, la fonction renvoie 0
size_t	nWDLongueurValeurRetour		(void);
// renvoie la valeur chaine de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type chaine, la fonction renvoie NULL
LPCSTR	pszWDGetValeurRetourA		(void);
LPCWSTR	pszWDGetValeurRetourW		(void);
LPCTSTR	pszWDGetValeurRetour		(void);
// renvoie la valeur binaire de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
//	!!! attention : si la valeur n'est pas de type binaire, la fonction renvoie NULL
PBYTE	pbyWDGetValeurRetour		(void);
// renvoie le code d'erreur de la dernière erreur
int		nWDGetLastError				(void);
// renvoie le message de la dernière erreur
LPCSTR	pszWDGetLastErrorA			(void);
LPCWSTR	pszWDGetLastErrorW			(void);
LPCTSTR	pszWDGetLastError			(void);
// reprise sur erreur : force la reprise normale de l'exécution après une erreur
void	WDRepriseErreur				(void);
// renvoie le contexte courant
PVOID	pWDGetContexte				();
// modifie le contexte courant
// renvoie l'ancien contexte en cours
// si pContexte est NULL, se replace sur le contexte local
PVOID	pWDSetContexte				(PVOID pContexte);
// renvoie le contexte d'élément courant
PVOID	pWDGetContexteElement		();
// modifie le contexte d'élément courant
// renvoie l'ancien contexte en cours
PVOID	pWDModifieContexteElement	(PVOID pContexteElement);
// restaure le contexte d'élément courant
// renvoie l'ancien contexte en cours
PVOID	pWDRestaureContexteElement	(PVOID pContexteElement);

// initialise un nouveau contexte de langage externe pour utilisation depuis un thread secondaire
PVOID	pWDMTInitThread				(void);
// termine le contexte de langage externe pour utilisation depuis un thread secondaire
//	pContexte : contexte de langage externe du thread à terminer
void	WDMTTermThread				(PVOID pContexte);
// empile un paramètre sur la pile
//	pContexte : contexte de langage externe du thread
//	pAdresse : adresse du paramètre
//	nType : type du paramètre
int		nWDMTEmpile					(PVOID pContexte,LPCVOID pAdresse,int nType);
// appelle directement une fonction composante
//	pContexte : contexte de langage externe du thread
//	nNumCompo : numéro de la composante
//	nNumFonc : numéro de la fonction
//	nNumSyntaxe : numéro de la syntaxe
//	nNbParam : nombre de paramètres
int		nWDMTAppelle				(PVOID pContexte,int nNumCompo,int nNumFonc,int nNumSyntaxe,int nNbParam);
// lit la valeur d'une variable de composante
int		nWDMTLitVariableWL			(PVOID pContexte,int nNumCompo,int nNumVar,int nIndice);
// écrit dans une variable de composante
int		nWDMTEcritVariableWL		(PVOID pContexte,int nNumCompo,int nNumVar,int nIndice);
// renvoie le type de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
WORD	wWDMTGetTypeValeurRetour	(PVOID pContexte);
// renvoie TRUE si le type de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue() est une chaîne Ansi ou Unicode
BOOL	bWDMTValeurRetourChaine		(PVOID pContexte);
// renvoie TRUE si la valeur de retour est NULL
BOOL	bWDMTValeurRetourNULL		(PVOID pContexte);
// renvoie la valeur booléenne de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type booléen, la fonction renvoie FALSE
BOOL	bWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur entière de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type entier, la fonction renvoie 0
int		nWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur entière sur 8 octets de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type entier sur 8 octets, la fonction renvoie 0
WDINT64	i64WDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur flottante de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type flottant, la fonction renvoie 0.0
double	dWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la longueur d'une chaine ou d'un buffer binaire
//	!!! attention : si la valeur n'est pas de type chaine ou binaire, la fonction renvoie 0
size_t	nWDMTLongueurValeurRetour	(PVOID pContexte);
// renvoie la valeur chaine de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type chaine, la fonction renvoie NULL
LPCSTR	pszWDMTGetValeurRetourA		(PVOID pContexte);
LPCWSTR	pszWDMTGetValeurRetourW		(PVOID pContexte);
LPCTSTR	pszWDMTGetValeurRetour		(PVOID pContexte);
// renvoie la valeur binaire de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
//	!!! attention : si la valeur n'est pas de type binaire, la fonction renvoie NULL
PBYTE	pbyWDMTGetValeurRetour		(PVOID pContexte);
// renvoie le code d'erreur de la dernière erreur
int		nWDMTGetLastError			(PVOID pContexte);
// renvoie le message de la dernière erreur
LPCSTR	pszWDMTGetLastErrorA		(PVOID pContexte);
LPCWSTR	pszWDMTGetLastErrorW		(PVOID pContexte);
LPCTSTR	pszWDMTGetLastError			(PVOID pContexte);
// reprise sur erreur : force la reprise normale de l'exécution après une erreur
void	WDMTRepriseErreur			(PVOID pContexte);

#ifdef __cplusplus
	}
#endif	//__cplusplus

#endif	//!__WDEXTERN_H
