// WDExtern.c
//---------------------------------------------------------------------------------------------------------------------------------------------------------
// Interface du Langage Externe WinDev
//---------------------------------------------------------------------------------------------------------------------------------------------------------

// PAD le 19/07/2002 :
#pragma warning(disable: 4115 4996)
//C4115: '_RPC_ASYNC_STATE' : named type definition in parentheses

//////////////////////////////////////////////////////////////////////////
//	Détection de la plateforme Windows CE
//////////////////////////////////////////////////////////////////////////
#if defined(ARMV4) || defined(ARMV4T)
	// -- CE ARM
	#ifndef ARM
		#define ARM
	#endif
	#ifndef _ARM_
		#define _ARM_
	#endif
#endif //ARMV4

#ifdef ARMV4T
	// -- CE ARM4T
	#ifndef THUMB
		#define THUMB
	#endif
	#ifndef _THUMB_
		#define _THUMB_
	#endif
#endif //ARMV4T

#ifdef _X86_
	// -- CE x86
	#ifndef _i386_
		#define _i386_
	#endif
	#ifndef x86
		#define x86 1
	#endif
#endif //ARMV4

#if defined(ARMV4) || defined(ARMV4T) || defined(_X86_)
	// CE (tous processeurs)
	#ifndef UNDER_CE
		#define UNDER_CE 0x300
	#endif
	#ifndef _WIN32_WCE
		#define _WIN32_WCE UNDER_CE
	#endif
#endif // defined(ARMV4) || defined(ARMV4T) || defined(X86)

// GP 26/02/2008 : La compilation de WDExtern.c en pocket déclenche une série de warnings dans les headers systemes
#if defined(UNDER_CE)
	#pragma warning(disable: 4201 4214 4514)
	// C4201: nonstandard extension used : nameless struct/union
	// C4214: nonstandard extension used : bit field types other than int
	// C4514: 'xxx' : unreferenced inline function has been removed
#endif	// UNDER_CE


//PAD le 07/10/2008 pour error LNK2001: unresolved external symbol __imp__splitpath en WIN64
#if defined (_MSC_VER) && (_MSC_VER >= 1400)
	#define _CRTIMP
#endif


#include "WDExtern.h"
#include <assert.h>
#ifdef _WINDOWS
	#include <tchar.h>
#endif //_WINDOWS

#ifdef __unix__
    #include <stdlib.h>
	#include <stdarg.h>
	#include <dlfcn.h>
#endif

#ifdef UNDER_CE
	#define GETPROCADDRESS	GetProcAddressA
#else // UNDER_CE
	#define GETPROCADDRESS	GetProcAddress
#endif // !UNDER_CE

#ifdef _WINDOWS
	#define VSNPRINTF	_vsntprintf
#elif defined(UNICODE)
	#define VSNPRINTF  vswprintf
	#define VSNPRINTFA _vsnprintf
#else
	#define VSNPRINTF  vsnprintf
	#define VSNPRINTFA vsnprintf
#endif

#ifdef _WINDOWS
	#define VSNPRINTF_A _vsnprintf
#else
	#define VSNPRINTF_A vsnprintf
#endif

#if defined(_WINDOWS) && (!defined(UNICODE))
	#define VSNPRINTF_W _vsnwprintf
#else
	#define VSNPRINTF_W VSNPRINTF
#endif

#if defined(__BORLANDC__) && (__BORLANDC__ < 0x550)
	#define _wsplitpath(a,b,c,d,e) _splitpath((LPCSTR)a,(LPSTR)b,(LPSTR)c,d,e)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// prototypes des fonctions des points d'entrées
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef int 	(*pfnWDINITEX)(PVOID,STInitLE*);
typedef void	(*pfnWDTERM)(PVOID);
typedef int 	(*pfnWDOUVREWDLA)(PVOID,LPCSTR);
typedef int 	(*pfnWDOUVREWDL)(PVOID,LPCWSTR);
typedef int 	(*pfnWDOUVREWDLNUMA)(PVOID,LPCSTR,int*);
typedef int 	(*pfnWDOUVREWDLNUM)(PVOID,LPCWSTR,int*);
typedef void	(*pfnWDFERMEWDLNUM)(PVOID,int);
typedef int 	(*pfnWDOUVREWDLRES)(PVOID,HINSTANCE,UINT);
typedef void	(*pfnWDFERMEWDLRES)(PVOID,HINSTANCE,UINT);
typedef int 	(*pfnWDINITPROJETA)(PVOID,LPCSTR);
typedef int 	(*pfnWDINITPROJET)(PVOID,LPCVOID);
typedef int 	(*pfnWDSETCALLBACKA)(PVOID,pfnWDCALLBACKA,DWORD_PTR);
typedef int 	(*pfnWDSETCALLBACK)(PVOID,pfnWDCALLBACK,DWORD_PTR);
typedef void*	(*pfnWDSETCALLBACKELEMENTA)(PVOID,PVOID,LPCSTR,pfnWDCALLBACKA,DWORD_PTR);
typedef void*	(*pfnWDSETCALLBACKELEMENT)(PVOID,PVOID,LPCWSTR,pfnWDCALLBACK,DWORD_PTR);
typedef int 	(*pfnWDSETPARENT)(PVOID,HWND);
typedef int		(*pfnWDSETCONTEXT)(PVOID,PVOID);
typedef int 	(*pfnWDEXECUTEA)(PVOID,LPCSTR);
typedef int 	(*pfnWDEXECUTE)(PVOID,LPCWSTR);
typedef int 	(*pfnWDEVALUEA)(PVOID,LPCSTR);
typedef int 	(*pfnWDEVALUE)(PVOID,LPCWSTR);
typedef int 	(*pfnWDCOMPILEA)(PVOID,LPCSTR,LPCSTR);
typedef int 	(*pfnWDCOMPILE)(PVOID,LPCWSTR,LPCWSTR);
typedef int 	(*pfnWDEMPILE)(PVOID,LPCVOID,int);
typedef int 	(*pfnWDEMPILEEX)(PVOID,LPCVOID,int,int);
typedef int 	(*pfnWDAPPELLE)(PVOID,int,int,int,int);
typedef int 	(*pfnWDACCESVARIABLE)(PVOID,int,int,int);
typedef int 	(*pfnWDLITPROPELEMA)(PVOID,LPCSTR,int);
typedef int 	(*pfnWDLITPROPELEM)(PVOID,LPCWSTR,int);
typedef int 	(*pfnWDLITPROPELEMANYA)(PVOID,LPCSTR,int,PVOID);
typedef int 	(*pfnWDLITPROPELEMANY)(PVOID,LPCWSTR,int,PVOID);
typedef int 	(*pfnWDLITPROPELEMINDA)(PVOID,LPCSTR,int,int);
typedef int 	(*pfnWDLITPROPELEMIND)(PVOID,LPCWSTR,int,int);
typedef int 	(*pfnWDLITPROPELEMCLEA)(PVOID,LPCSTR,LPCSTR,int);
typedef int 	(*pfnWDLITPROPELEMCLE)(PVOID,LPCWSTR,LPCWSTR,int);
typedef int 	(*pfnWDLITPROPELEMANYINDA)(PVOID,LPCSTR,int,int,PVOID);
typedef int 	(*pfnWDLITPROPELEMANYIND)(PVOID,LPCWSTR,int,int,PVOID);
typedef int 	(*pfnWDLITPROPELEMIND2A)(PVOID,LPCSTR,int,int,int);
typedef int 	(*pfnWDLITPROPELEMIND2)(PVOID,LPCWSTR,int,int,int);
typedef int 	(*pfnWDLITPROPELEMANYIND2A)(PVOID,LPCSTR,int,int,int,PVOID);
typedef int 	(*pfnWDLITPROPELEMANYIND2)(PVOID,LPCWSTR,int,int,int,PVOID);
typedef int 	(*pfnWDACCESPROPSOUSELEMA)(PVOID,LPCSTR,int,LPCSTR,int);
typedef int 	(*pfnWDACCESPROPSOUSELEM)(PVOID,LPCWSTR,int,LPCWSTR,int);
typedef int 	(*pfnWDACCESPROPSOUSELEMINDA)(PVOID,LPCSTR,int,LPCSTR,int,int);
typedef int 	(*pfnWDACCESPROPSOUSELEMIND)(PVOID,LPCWSTR,int,LPCWSTR,int,int);
typedef int 	(*pfnWDECRITPROPELEMA)(PVOID,LPCSTR,int);
typedef int 	(*pfnWDECRITPROPELEM)(PVOID,LPCWSTR,int);
typedef int 	(*pfnWDECRITPROPELEMINDA)(PVOID,LPCSTR,int,int);
typedef int 	(*pfnWDECRITPROPELEMIND)(PVOID,LPCWSTR,int,int);
typedef int 	(*pfnWDECRITPROPELEMCLEA)(PVOID,LPCSTR,LPCSTR,int);
typedef int 	(*pfnWDECRITPROPELEMCLE)(PVOID,LPCWSTR,LPCWSTR,int);
typedef int 	(*pfnWDECRITPROPELEMIND2A)(PVOID,LPCSTR,int,int,int);
typedef int 	(*pfnWDECRITPROPELEMIND2)(PVOID,LPCWSTR,int,int,int);
typedef int 	(*pfnWDCHAMPEXISTEA)(PVOID,LPCSTR,BOOL*);
typedef int 	(*pfnWDCHAMPEXISTE)(PVOID,LPCWSTR,BOOL*);
typedef int 	(*pfnWDOPERATION)(PVOID,DWORD,DWORD_PTR,DWORD_PTR);
typedef int 	(*pfnWDREPRISE)(PVOID);
typedef int 	(*pfnWDGETINTERFACE)(PVOID,void**);
typedef int 	(*pfnWDOPERATIONTHREAD)(PVOID,int);
typedef void*	(*pfnWDGETCONTEXTE)(PVOID);
typedef void*	(*pfnWDSETCONTEXTE)(PVOID,PVOID);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// variables globales pour accès à la DLL
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// instance de la Machine Virtuelle
HMODULE								ghDLLVM = NULL;
// TRUE si la Machine Virtuelle doit être déchargée
static BOOL							gbDLLVM;
// point d'entrée pour la fonction nWDOuvreWDL
static pfnWDOUVREWDLA				gpfnOuvreWDLA;
static pfnWDOUVREWDL				gpfnOuvreWDL;
// point d'entrée pour la fonction nWDOuvreWDLNum
static pfnWDOUVREWDLNUMA			gpfnOuvreWDLNumA;
static pfnWDOUVREWDLNUM				gpfnOuvreWDLNum;
// point d'entrée pour la fonction WDFermeWDLNum
static pfnWDFERMEWDLNUM				gpfnFermeWDLNum;
// point d'entrée pour la fonction nWDOuvreWDLRes
static pfnWDOUVREWDLRES				gpfnOuvreWDLRes;
// point d'entrée pour la fonction nWDFermeWDLRes
static pfnWDFERMEWDLRES				gpfnFermeWDLRes;
// point d'entrée pour la fonction nWDInitProjet
static pfnWDINITPROJET				gpfnInitProjet;
// point d'entrée pour la fonction nWDSetCallback
static pfnWDSETCALLBACKA			gpfnSetCallbackA;
static pfnWDSETCALLBACK				gpfnSetCallback;
// point d'entrée pour la fonction nWDSetCallbackModule
static pfnWDSETCALLBACKA			gpfnSetCallbackModuleA;
static pfnWDSETCALLBACK				gpfnSetCallbackModule;
// point d'entrée pour la fonction nWDSetCallbackElement
static pfnWDSETCALLBACKELEMENTA		gpfnSetCallbackElementA;
static pfnWDSETCALLBACKELEMENT		gpfnSetCallbackElement;
// point d'entrée pour la fonction nWDSetCallbackCompatible
static pfnWDSETCALLBACKA			gpfnSetCompatibleA;
static pfnWDSETCALLBACK				gpfnSetCompatible;
// point d'entrée pour la fonction nWDSetPECallback
static pfnWDSETCALLBACKA			gpfnSetPECallbackA;
static pfnWDSETCALLBACK				gpfnSetPECallback;
// point d'entrée pour la fonction nWDSetParent
static pfnWDSETPARENT				gpfnSetParent;
// point d'entrée pour la fonction nWDSetHFContext
static pfnWDSETCONTEXT				gpfnSetHFContext;
// point d'entrée pour la fonction nWDExecute
static pfnWDEXECUTEA				gpfnExecuteA;
static pfnWDEXECUTE					gpfnExecute;
// point d'entrée pour la fonction nWDExecute
static pfnWDEVALUEA					gpfnEvalueA;
static pfnWDEVALUE					gpfnEvalue;
// point d'entrée pour la fonction nWDCompile
static pfnWDCOMPILEA				gpfnCompileA;
static pfnWDCOMPILE					gpfnCompile;
// point d'entrée pour la fonction nWDEmpile
static pfnWDEMPILE					gpfnEmpile;
// point d'entrée pour la fonction nWDEmpile
static pfnWDEMPILEEX				gpfnEmpileEx;
// point d'entrée pour la fonction nWDAppelle
static pfnWDAPPELLE					gpfnAppelle;
// points d'entrée pour les accès aux variables
static pfnWDACCESVARIABLE			gpfnLitVariableWL;
static pfnWDACCESVARIABLE			gpfnEcritVariableWL;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément
static pfnWDLITPROPELEMA			gpfnLitPropA;
static pfnWDLITPROPELEM				gpfnLitProp;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément
static pfnWDLITPROPELEMANYA			gpfnLitPropAnyA;
static pfnWDLITPROPELEMANY			gpfnLitPropAny;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément
static pfnWDECRITPROPELEMA			gpfnEcritPropA;
static pfnWDECRITPROPELEM			gpfnEcritProp;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément indicé
static pfnWDLITPROPELEMINDA			gpfnLitPropIndA;
static pfnWDLITPROPELEMIND			gpfnLitPropInd;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément par clé
static pfnWDLITPROPELEMCLEA			gpfnLitPropCleA;
static pfnWDLITPROPELEMCLE			gpfnLitPropCle;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément indicé
static pfnWDLITPROPELEMANYINDA		gpfnLitPropAnyIndA;
static pfnWDLITPROPELEMANYIND		gpfnLitPropAnyInd;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément indicé
static pfnWDECRITPROPELEMINDA		gpfnEcritPropIndA;
static pfnWDECRITPROPELEMIND		gpfnEcritPropInd;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément par clé
static pfnWDECRITPROPELEMCLEA		gpfnEcritPropCleA;
static pfnWDECRITPROPELEMCLE		gpfnEcritPropCle;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément indicé
static pfnWDLITPROPELEMIND2A		gpfnLitPropInd2A;
static pfnWDLITPROPELEMIND2			gpfnLitPropInd2;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément indicé
static pfnWDLITPROPELEMANYIND2A		gpfnLitPropAnyInd2A;
static pfnWDLITPROPELEMANYIND2		gpfnLitPropAnyInd2;
// point d'entrée pour accéder à la valeur d'une propriété d'un élément indicé
static pfnWDECRITPROPELEMIND2A		gpfnEcritPropInd2A;
static pfnWDECRITPROPELEMIND2		gpfnEcritPropInd2;
// point d'entrée pour accéder à la valeur d'une propriété d'un sous-élément
static pfnWDACCESPROPSOUSELEMA		gpfnLitPropSousElemA;
static pfnWDACCESPROPSOUSELEM		gpfnLitPropSousElem;
// point d'entrée pour accéder à la valeur d'une propriété d'un sous-élément
static pfnWDACCESPROPSOUSELEMA		gpfnEcritPropSousElemA;
static pfnWDACCESPROPSOUSELEM		gpfnEcritPropSousElem;
// point d'entrée pour accéder à la valeur d'une propriété d'un sous-élément indicé
static pfnWDACCESPROPSOUSELEMINDA	gpfnLitPropSousElemIndA;
static pfnWDACCESPROPSOUSELEMIND	gpfnLitPropSousElemInd;
// point d'entrée pour accéder à la valeur d'une propriété d'un sous-élément indicé
static pfnWDACCESPROPSOUSELEMINDA	gpfnEcritPropSousElemIndA;
static pfnWDACCESPROPSOUSELEMIND	gpfnEcritPropSousElemInd;
// point d'entrée pour vérifier si un champ existe
static pfnWDCHAMPEXISTEA			gpfnChampExisteA;
static pfnWDCHAMPEXISTE				gpfnChampExiste;
// point d'entrée pour les opérations du langage externe
static pfnWDOPERATION				gpfnOperation;
// point d'entrée pour la fonction WDTerm
static pfnWDTERM					gpfnTerm;
// point d'entrée pour la fonction WDReprise
static pfnWDREPRISE					gpfnReprise;
// récupération du contexte HF
static pfnWDGETINTERFACE			gpfnGetHFContext;
// récupération du contexte global
static pfnWDGETINTERFACE			gpfnGetVMData;
// récupération du contexte
static pfnWDGETINTERFACE			gpfnGetVM;
// récupération du libshop
static pfnWDGETINTERFACE			gpfnGetLibShop;
// récupération du contexte OBJ
static pfnWDGETINTERFACE			gpfnGetIEXE;
// récupération du contexte d'élément courant
static pfnWDGETCONTEXTE				gpfnGetContexteElement;
// modification du contexte d'élément courant
static pfnWDSETCONTEXTE				gpfnModifieContexteElement;
// restauraction du contexte d'élément courant
static pfnWDSETCONTEXTE				gpfnRestaureContexteElement;
// opérations sur les threads
static pfnWDOPERATIONTHREAD			gpfnOperationThread;
// structure du contexte local du module
static STWDExtern					gstWLELocalCtx;
// structure des valeurs de retour
static STWDValeur					gstWLELocalValeurRetour;
// structure des erreurs
static STWDErreur					gstWLELocalErreur;
// pointeur sur le contexte courant à utiliser
static STWDExtern*					gpstWLECtx;
// options d'initialisation du langage externe
static DWORD						gdwOptionInit = 0;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// taille maximale pour les commandes formattées
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WD_CMDMAXLEN		10240

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// noms des points d'entrée
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	WDENTRY_INITEX					"nWLEInitEx"
#define	WDENTRY_TERM					"WLETerm"
#define	WDENTRY_OUVREWDLA				"nWLEOuvreWDLA"
#define	WDENTRY_OUVREWDL				"nWLEOuvreWDL"
#define	WDENTRY_OUVREWDLNUMA			"nWLEOuvreWDLNumA"
#define	WDENTRY_OUVREWDLNUM				"nWLEOuvreWDLNum"
#define	WDENTRY_FERMEWDLNUM				"WLEFermeWDLNum"
#define	WDENTRY_OUVREWDLRES				"nWLEOuvreWDLRes"
#define	WDENTRY_FERMEWDLRES				"WLEFermeWDLRes"
#define WDENTRY_INITPROJET				"nWLEInitProjet"
#define	WDENTRY_SETCALLBACKA			"nWLESetCallbackA"
#define	WDENTRY_SETCALLBACK				"nWLESetCallback"
#define	WDENTRY_SETCALLBACKMODULEA		"nWLESetCallbackModuleA"
#define	WDENTRY_SETCALLBACKMODULE		"nWLESetCallbackModule"
#define	WDENTRY_SETCALLBACKELEMENTA		"pWLESetCallbackElementA"
#define	WDENTRY_SETCALLBACKELEMENT		"pWLESetCallbackElement"
#define	WDENTRY_SETCOMPATIBLEA			"nWLESetCompatibleA"
#define	WDENTRY_SETCOMPATIBLE			"nWLESetCompatible"
#define	WDENTRY_SETPECALLBACKA			"nWLESetPECallbackA"
#define	WDENTRY_SETPECALLBACK			"nWLESetPECallback"
#define	WDENTRY_SETPARENT				"nWLESetParent"
#define	WDENTRY_SETHFCONTEXT			"nWLESetHFContext"
#define	WDENTRY_EXECUTEA				"nWLEExecuteA"
#define	WDENTRY_EXECUTE					"nWLEExecute"
#define	WDENTRY_EVALUEA					"nWLEEvalueA"
#define	WDENTRY_EVALUE					"nWLEEvalue"
#define WDENTRY_COMPILEA				"nWLECompileA"
#define WDENTRY_COMPILE					"nWLECompile"
#define	WDENTRY_REPRISE					"WLEReprise"
#define	WDENTRY_EMPILE					"nWLEEmpile"
#define	WDENTRY_EMPILEEX				"nWLEEmpileEx"
#define	WDENTRY_APPELLE					"nWLEAppelle"
#define	WDENTRY_LITVARIABLE				"nWLELitVariableWL"
#define	WDENTRY_ECRITVARIABLE			"nWLEEcritVariableWL"
#define	WDENTRY_LITPROPA				"nWLELitPropElemA"
#define	WDENTRY_LITPROP					"nWLELitPropElem"
#define	WDENTRY_LITPROPANYA				"nWLELitPropElemAnyA"
#define	WDENTRY_LITPROPANY				"nWLELitPropElemAny"
#define	WDENTRY_LITPROPINDA				"nWLELitPropElemIndA"
#define	WDENTRY_LITPROPIND				"nWLELitPropElemInd"
#define	WDENTRY_LITPROPCLEA				"nWLELitPropElemCleA"
#define	WDENTRY_LITPROPCLE				"nWLELitPropElemCle"
#define	WDENTRY_LITPROPANYINDA			"nWLELitPropElemAnyIndA"
#define	WDENTRY_LITPROPANYIND			"nWLELitPropElemAnyInd"
#define	WDENTRY_LITPROPIND2A			"nWLELitPropElemInd2A"
#define	WDENTRY_LITPROPIND2				"nWLELitPropElemInd2"
#define	WDENTRY_LITPROPANYIND2A			"nWLELitPropElemAnyInd2A"
#define	WDENTRY_LITPROPANYIND2			"nWLELitPropElemAnyInd2"
#define	WDENTRY_LITPROPSOUSELEMA		"nWLELitPropSousElemA"
#define	WDENTRY_LITPROPSOUSELEM			"nWLELitPropSousElem"
#define	WDENTRY_ECRITPROPSOUSELEMA		"nWLEEcritPropSousElemA"
#define	WDENTRY_ECRITPROPSOUSELEM		"nWLEEcritPropSousElem"
#define	WDENTRY_LITPROPSOUSELEMINDA		"nWLELitPropSousElemIndA"
#define	WDENTRY_LITPROPSOUSELEMIND		"nWLELitPropSousElemInd"
#define	WDENTRY_ECRITPROPSOUSELEMINDA	"nWLEEcritPropSousElemIndA"
#define	WDENTRY_ECRITPROPSOUSELEMIND	"nWLEEcritPropSousElemInd"
#define	WDENTRY_ECRITPROPA				"nWLEEcritPropElemA"
#define	WDENTRY_ECRITPROP				"nWLEEcritPropElem"
#define	WDENTRY_ECRITPROPINDA			"nWLEEcritPropElemIndA"
#define	WDENTRY_ECRITPROPIND			"nWLEEcritPropElemInd"
#define	WDENTRY_ECRITPROPCLEA			"nWLEEcritPropElemCleA"
#define	WDENTRY_ECRITPROPCLE			"nWLEEcritPropElemCle"
#define	WDENTRY_ECRITPROPIND2A			"nWLEEcritPropElemInd2A"
#define	WDENTRY_ECRITPROPIND2			"nWLEEcritPropElemInd2"
#define	WDENTRY_CHAMPEXISTEA			"nWLEChampExisteA"
#define	WDENTRY_CHAMPEXISTE				"nWLEChampExiste"
#define	WDENTRY_OPERATION				"nWLEOperation"
#define	WDENTRY_GETHFCONTEXT			"nWLEGetHFContext"
#define	WDENTRY_GETVMDATA				"nWLEGetVMData"
#define	WDENTRY_GETVM					"nWLEGetVM"
#define	WDENTRY_GETLIBSHOP				"nWLEGetLibShop"
#define	WDENTRY_GETIEXE					"nWLEGetIEXE"
#define	WDENTRY_GETCONTEXTEELEMENT		"pWLEGetContexteElement"
#define	WDENTRY_MODIFIECONTEXTEELEMENT	"pWLEModifieContexteElement"
#define	WDENTRY_RESTAURECONTEXTEELEMENT	"pWLERestaureContexteElement"
#define	WDENTRY_OPERATIONTHREAD			"nWLEOPMT"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macro de récupération des points d'entrée
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	#ifdef __unix__
		#define		LINK(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)dlsym(hInstance,pszNom); \
						if(pfnPtr==NULL) \
						{ \
							/*MessageBox(NULL,"Problème d'interface","Interface Langage Externe WinDev",MB_OK|MB_ICONEXCLAMATION);*/ \
							assert(0); \
							return WDERREUR_VERSION; \
						}

		#define		LINK_NO_ERROR(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)dlsym(hInstance,pszNom);

		#define		CHECK_LINK(pfnPtr) \
						if(pfnPtr==NULL) \
						{ \
							/*MessageBox(NULL,"Problème d'interface","Interface Langage Externe WinDev",MB_OK|MB_ICONEXCLAMATION);*/ \
							assert(0); \
							return WDERREUR_VERSION; \
						}
	#else //windows

		#define		LINK(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)GETPROCADDRESS(hInstance,pszNom); \
						if(pfnPtr==NULL) \
						{ \
							MessageBox(NULL,_T("Problème d'interface"),_T("Interface Langage Externe WinDev"),MB_OK|MB_ICONEXCLAMATION); \
							return WDERREUR_VERSION; \
						}

		#define		LINK_NO_ERROR(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)GETPROCADDRESS(hInstance,pszNom);

		#define		CHECK_LINK(pfnPtr) \
						if(pfnPtr==NULL) \
						{ \
							MessageBox(NULL,_T("Problème d'interface"),_T("Interface Langage Externe WinDev"),MB_OK|MB_ICONEXCLAMATION); \
							return WDERREUR_VERSION; \
						}

	#endif //__unix__

#else	//_DEBUG

	#ifdef __unix__

		#define		LINK(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)dlsym(hInstance,pszNom); \
						if(pfnPtr==NULL)\
							return WDERREUR_VERSION;

		#define		LINK_NO_ERROR(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)dlsym(hInstance,pszNom);

	#else
		#define		LINK(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)GETPROCADDRESS(hInstance,pszNom); \
						if(pfnPtr==NULL)\
							return WDERREUR_VERSION;

		#define		LINK_NO_ERROR(hInstance,pfnPtr,pfnType,pszNom) \
						pfnPtr = (pfnType)GETPROCADDRESS(hInstance,pszNom);

	#endif //__unix__

	#define		CHECK_LINK(pfnPtr) \
						if(pfnPtr==NULL)\
							return WDERREUR_VERSION;

#endif	//_DEBUG

#define WD_SAFE_CONTEXTE(pContexte) ( (pContexte)==NULL ? gpstWLECtx : (STWDExtern*)(pContexte) )


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigne le module utilisateur du langage externe
void WDSetModuleA(LPCSTR pszModule)
{	// on initialise le module
	gstWLELocalCtx.pszModuleA = pszModule;
	gstWLELocalCtx.pszModuleW = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigne le module utilisateur du langage externe
void WDSetModuleW(LPCWSTR pszModule)
{	// on initialise le module
	gstWLELocalCtx.pszModuleA = NULL;
	gstWLELocalCtx.pszModuleW = pszModule;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// active une option du langage externe
// doit être appelé avant l'appel à nWDInitXxxx
void WDActiveOption(int nOption)
{	// on rajoute l'option
	gdwOptionInit |= nOption;
}

#if defined(__unix__) && !defined(DESACTIVE_PROXY_TERMLIBRARY)
	typedef BOOL (*PFNINITLIBRARY)(HINSTANCE hInstance);
#endif	// __unix__ && !DESACTIVE_PROXY_TERMLIBRARY

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialisation interne
static int __nWDInitVM(HINSTANCE hDLLVM,BOOL bAfficheErreur,LPCSTR pszNomDLL_A,LPCWSTR pszNomDLL_W,DWORD dwOption)
{
	pfnWDINITEX	pfnInitEx;
	int			nRes;
	char		szCheminDLL_A[MAX_PATH+2];
	wchar_t		szCheminDLL_W[MAX_PATH+2];
	STInitLE	stInitLE;
#if defined(__unix__) && !defined(DESACTIVE_PROXY_TERMLIBRARY)
	PFNINITLIBRARY pfnInitLibrary;
#endif	// __unix__ && !DESACTIVE_PROXY_TERMLIBRARY

	// on initialise la structure
	gstWLELocalCtx.pstValeurRetour = &gstWLELocalValeurRetour;
	gstWLELocalCtx.pstErreur = &gstWLELocalErreur;
	// le contexte courant par défaut est le contexte local
	gpstWLECtx = &gstWLELocalCtx;
	// si la dll n'a pas pu être trouvée, on renvoie le code d'erreur
	if(hDLLVM==NULL)
		return WDERREUR_DLLLOAD;
	// on essaie de récupérer la nouvelle version de la fonction d'initisliation
	LINK(hDLLVM,pfnInitEx,pfnWDINITEX,WDENTRY_INITEX);
	// on remplit la structure d'initialisation
	stInitLE.dwVersion = WD_VERSION_EXTERNE;
	stInitLE.nTaille = sizeof(STInitLE);
	stInitLE.bAfficheErreur = bAfficheErreur;
	stInitLE.dwOption = dwOption;
	*szCheminDLL_A = 0;
	*szCheminDLL_W = 0;
	stInitLE.pszCheminDLLA = NULL;
	stInitLE.pszCheminDLLW = NULL;

#ifndef __unix__

	// si on a fourni un nom de DLL, on récupère le chemin
	if(pszNomDLL_A!=NULL)
	{
#ifdef UNDER_CE
		LPCSTR pszSlah = strrchr(pszNomDLL_A,'\\');
		if(pszSlah!=NULL)
		{
			strncpy(szCheminDLL_A,pszNomDLL_A,pszSlah-pszNomDLL_A);
			szCheminDLL_A[pszSlah-pszNomDLL_A] = 0;
		}
#else //UNDER_CE
	_splitpath(pszNomDLL_A,szCheminDLL_A,NULL,NULL,NULL);
	_splitpath(pszNomDLL_A,NULL,szCheminDLL_A+strlen(szCheminDLL_A),NULL,NULL);
#endif //UNDER_CE

		stInitLE.pszCheminDLLA = szCheminDLL_A;
	}
	// si on a fourni un nom de DLL, on récupère le chemin
	if(pszNomDLL_W!=NULL)
	{
#ifdef UNDER_CE
		LPCWSTR pszSlah = _tcsrchr(pszNomDLL_W,'\\');
		if(pszSlah!=NULL)
		{
			_tcsncpy(szCheminDLL_W,pszNomDLL_W,pszSlah-pszNomDLL_W);
			szCheminDLL_W[pszSlah-pszNomDLL_W] = 0;
		}
#else //UNDER_CE
		_wsplitpath(pszNomDLL_W,szCheminDLL_W,NULL,NULL,NULL);
		_wsplitpath(pszNomDLL_W,NULL,szCheminDLL_W+wcslen(szCheminDLL_W),NULL,NULL);
#endif //UNDER_CE

		stInitLE.pszCheminDLLW = szCheminDLL_W;
	}

#endif	//!__unix__

	//En WebDev, bInitLibrary a déjà été appelé par la VM à l'init de wdsession
	//on ne doit pas le refaire ici pour ne pas réinitialiser les variables internes de la VM
#if defined(__unix__) && !defined(DESACTIVE_PROXY_TERMLIBRARY)
	// on appelle la fonction d'init
	pfnInitLibrary = (PFNINITLIBRARY)dlsym(hDLLVM,"bInitLibrary");
	// si on ne peut pas initialiser
	if(pfnInitLibrary==NULL)
		return FALSE;
	// on initialise
	if(!pfnInitLibrary(hDLLVM))
		return FALSE;
#endif	// __unix__ && !DESACTIVE_PROXY_TERMLIBRARY

	// on initialise le langage externe
	nRes = pfnInitEx(&gstWLELocalCtx,&stInitLE);
	// en cas d'échec de l'initialisation, on renseigne l'erreur
	if(nRes!=WDERREUR_OK)
		return nRes;
	// on récupère les autres points d'entrée du langage externe
	LINK_NO_ERROR	(hDLLVM	,gpfnOuvreWDLA					,pfnWDOUVREWDLA				,WDENTRY_OUVREWDLA)
	LINK_NO_ERROR	(hDLLVM	,gpfnOuvreWDL					,pfnWDOUVREWDL				,WDENTRY_OUVREWDL)
	LINK_NO_ERROR	(hDLLVM	,gpfnOuvreWDLNumA				,pfnWDOUVREWDLNUMA			,WDENTRY_OUVREWDLNUMA)
	LINK_NO_ERROR	(hDLLVM	,gpfnOuvreWDLNum				,pfnWDOUVREWDLNUM			,WDENTRY_OUVREWDLNUM)
	LINK_NO_ERROR	(hDLLVM	,gpfnFermeWDLNum				,pfnWDFERMEWDLNUM			,WDENTRY_FERMEWDLNUM)
	LINK_NO_ERROR	(hDLLVM	,gpfnOuvreWDLRes				,pfnWDOUVREWDLRES			,WDENTRY_OUVREWDLRES)
	LINK_NO_ERROR	(hDLLVM	,gpfnFermeWDLRes				,pfnWDFERMEWDLRES			,WDENTRY_FERMEWDLRES)
	LINK_NO_ERROR	(hDLLVM	,gpfnInitProjet					,pfnWDINITPROJET			,WDENTRY_INITPROJET)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCallbackA				,pfnWDSETCALLBACKA			,WDENTRY_SETCALLBACKA)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCallback				,pfnWDSETCALLBACK			,WDENTRY_SETCALLBACK)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCompatibleA				,pfnWDSETCALLBACKA			,WDENTRY_SETCOMPATIBLEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCompatible				,pfnWDSETCALLBACK			,WDENTRY_SETCOMPATIBLE)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetParent					,pfnWDSETPARENT				,WDENTRY_SETPARENT)
	LINK_NO_ERROR	(hDLLVM	,gpfnExecuteA					,pfnWDEXECUTEA				,WDENTRY_EXECUTEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnExecute					,pfnWDEXECUTE				,WDENTRY_EXECUTE)
	LINK_NO_ERROR	(hDLLVM	,gpfnEvalueA					,pfnWDEVALUEA				,WDENTRY_EVALUEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnEvalue						,pfnWDEVALUE				,WDENTRY_EVALUE)
	LINK_NO_ERROR	(hDLLVM	,gpfnCompileA					,pfnWDCOMPILEA				,WDENTRY_COMPILEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnCompile					,pfnWDCOMPILE				,WDENTRY_COMPILE)
	LINK_NO_ERROR	(hDLLVM	,gpfnEmpile						,pfnWDEMPILE				,WDENTRY_EMPILE)
	LINK_NO_ERROR	(hDLLVM	,gpfnEmpileEx					,pfnWDEMPILEEX				,WDENTRY_EMPILEEX)
	LINK_NO_ERROR	(hDLLVM	,gpfnAppelle					,pfnWDAPPELLE				,WDENTRY_APPELLE)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitVariableWL				,pfnWDACCESVARIABLE			,WDENTRY_LITVARIABLE)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritVariableWL			,pfnWDACCESVARIABLE			,WDENTRY_ECRITVARIABLE)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropA					,pfnWDLITPROPELEMA			,WDENTRY_LITPROPA)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitProp					,pfnWDLITPROPELEM			,WDENTRY_LITPROP)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropAnyA				,pfnWDLITPROPELEMANYA		,WDENTRY_LITPROPANYA)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropAny					,pfnWDLITPROPELEMANY		,WDENTRY_LITPROPANY)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropIndA				,pfnWDLITPROPELEMINDA		,WDENTRY_LITPROPINDA)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropInd					,pfnWDLITPROPELEMIND		,WDENTRY_LITPROPIND)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropCleA				,pfnWDLITPROPELEMCLEA		,WDENTRY_LITPROPCLEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropCle					,pfnWDLITPROPELEMCLE		,WDENTRY_LITPROPCLE)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropAnyIndA				,pfnWDLITPROPELEMANYINDA	,WDENTRY_LITPROPANYINDA)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropAnyInd				,pfnWDLITPROPELEMANYIND		,WDENTRY_LITPROPANYIND)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropInd2A				,pfnWDLITPROPELEMIND2A		,WDENTRY_LITPROPIND2A)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropInd2				,pfnWDLITPROPELEMIND2		,WDENTRY_LITPROPIND2)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropAnyInd2A			,pfnWDLITPROPELEMANYIND2A	,WDENTRY_LITPROPANYIND2A)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropAnyInd2				,pfnWDLITPROPELEMANYIND2	,WDENTRY_LITPROPANYIND2)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropA					,pfnWDECRITPROPELEMA		,WDENTRY_ECRITPROPA)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritProp					,pfnWDECRITPROPELEM			,WDENTRY_ECRITPROP)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropIndA				,pfnWDECRITPROPELEMINDA		,WDENTRY_ECRITPROPINDA)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropInd				,pfnWDECRITPROPELEMIND		,WDENTRY_ECRITPROPIND)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropCleA				,pfnWDECRITPROPELEMCLEA		,WDENTRY_ECRITPROPCLEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropCle				,pfnWDECRITPROPELEMCLE		,WDENTRY_ECRITPROPCLE)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropInd2A				,pfnWDECRITPROPELEMIND2A	,WDENTRY_ECRITPROPIND2A)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropInd2				,pfnWDECRITPROPELEMIND2		,WDENTRY_ECRITPROPIND2)
	LINK_NO_ERROR	(hDLLVM	,gpfnChampExisteA				,pfnWDCHAMPEXISTEA			,WDENTRY_CHAMPEXISTEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnChampExiste				,pfnWDCHAMPEXISTE			,WDENTRY_CHAMPEXISTE)
	LINK_NO_ERROR	(hDLLVM	,gpfnTerm						,pfnWDTERM					,WDENTRY_TERM)
	LINK_NO_ERROR	(hDLLVM	,gpfnReprise					,pfnWDREPRISE				,WDENTRY_REPRISE)
	LINK_NO_ERROR	(hDLLVM	,gpfnGetHFContext				,pfnWDGETINTERFACE			,WDENTRY_GETHFCONTEXT)
	LINK_NO_ERROR	(hDLLVM	,gpfnGetVMData					,pfnWDGETINTERFACE			,WDENTRY_GETVMDATA)
	LINK_NO_ERROR	(hDLLVM	,gpfnGetLibShop					,pfnWDGETINTERFACE			,WDENTRY_GETLIBSHOP)
	LINK_NO_ERROR	(hDLLVM	,gpfnGetIEXE					,pfnWDGETINTERFACE			,WDENTRY_GETIEXE)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetHFContext				,pfnWDSETCONTEXT			,WDENTRY_SETHFCONTEXT)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCallbackModuleA			,pfnWDSETCALLBACKA			,WDENTRY_SETCALLBACKMODULEA)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCallbackModule			,pfnWDSETCALLBACK			,WDENTRY_SETCALLBACKMODULE)
	LINK_NO_ERROR	(hDLLVM	,gpfnGetContexteElement			,pfnWDGETCONTEXTE			,WDENTRY_GETCONTEXTEELEMENT)
	LINK_NO_ERROR	(hDLLVM	,gpfnModifieContexteElement		,pfnWDSETCONTEXTE			,WDENTRY_MODIFIECONTEXTEELEMENT)
	LINK_NO_ERROR	(hDLLVM	,gpfnRestaureContexteElement	,pfnWDSETCONTEXTE			,WDENTRY_RESTAURECONTEXTEELEMENT)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetPECallbackA				,pfnWDSETCALLBACKA			,WDENTRY_SETPECALLBACKA)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetPECallback				,pfnWDSETCALLBACK			,WDENTRY_SETPECALLBACK)
	LINK_NO_ERROR	(hDLLVM	,gpfnOperation					,pfnWDOPERATION				,WDENTRY_OPERATION)
	LINK_NO_ERROR	(hDLLVM	,gpfnGetVM						,pfnWDGETINTERFACE			,WDENTRY_GETVM)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropSousElemA			,pfnWDACCESPROPSOUSELEMA	,WDENTRY_LITPROPSOUSELEMA)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropSousElem			,pfnWDACCESPROPSOUSELEM		,WDENTRY_LITPROPSOUSELEM)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropSousElemA			,pfnWDACCESPROPSOUSELEMA	,WDENTRY_ECRITPROPSOUSELEMA)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropSousElem			,pfnWDACCESPROPSOUSELEM		,WDENTRY_ECRITPROPSOUSELEM)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropSousElemIndA		,pfnWDACCESPROPSOUSELEMINDA	,WDENTRY_LITPROPSOUSELEMINDA)
	LINK_NO_ERROR	(hDLLVM	,gpfnLitPropSousElemInd			,pfnWDACCESPROPSOUSELEMIND	,WDENTRY_LITPROPSOUSELEMIND)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropSousElemIndA		,pfnWDACCESPROPSOUSELEMINDA	,WDENTRY_ECRITPROPSOUSELEMINDA)
	LINK_NO_ERROR	(hDLLVM	,gpfnEcritPropSousElemInd		,pfnWDACCESPROPSOUSELEMIND	,WDENTRY_ECRITPROPSOUSELEMIND)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCallbackElementA		,pfnWDSETCALLBACKELEMENTA	,WDENTRY_SETCALLBACKELEMENTA)
	LINK_NO_ERROR	(hDLLVM	,gpfnSetCallbackElement			,pfnWDSETCALLBACKELEMENT	,WDENTRY_SETCALLBACKELEMENT)
	
	// on remplit la structure de communication
	gstWLELocalCtx.wVersion = WD_VERSION_EXTERNE;
	// quand on arrive ici, le langage externe est prêt
#ifdef __unix__
    ghDLLVM = (HMODULE)hDLLVM;
#else
	ghDLLVM = hDLLVM;
#endif
	// on renvoie 0 pour signifier qu'il n'y a pas eu d'erreur lors de l'initialisation du langage externe
	return WDERREUR_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise un nouveau contexte de langage externe pour utilisation depuis un thread secondaire
PVOID pWDMTInitThread(void)
{
	STWDExtern* pstContexte;
	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return NULL;
	// on alloue dynamiquement un nouveau contexte de langage externe et ses éléments liés
	pstContexte = (STWDExtern*)malloc(sizeof(STWDExtern));
	pstContexte->pstValeurRetour = (STWDValeur*)malloc(sizeof(STWDValeur));
	pstContexte->pstErreur = (STWDErreur*)malloc(sizeof(STWDErreur));
	// on recopie le module global
	pstContexte->pszModuleA = gstWLELocalCtx.pszModuleA;
	pstContexte->pszModuleW = gstWLELocalCtx.pszModuleW;
	// si ce n'est pas encore fait, on récupère le point d'entrée pour les opérations sur les threads
	if(gpfnOperationThread==NULL)
	{	// on récupère le point d'entrée pour les opérations sur les threads
		LINK_NO_ERROR(ghDLLVM,gpfnOperationThread,pfnWDOPERATIONTHREAD,WDENTRY_OPERATIONTHREAD);
		// si on n'a pas pu récupérer le point d'entrée, on sort en erreur
		if(gpfnOperationThread==NULL)
			return NULL;
	}
	// on initialise le nouveau contexte de langage externe
	// en cas d'échec de l'initialisation, on sort en erreur
	if(gpfnOperationThread(pstContexte,WDOPMT_INIT_CONTEXTE)!=WDERREUR_OK)
		return NULL;
	// on remplit la structure de communication
	pstContexte->wVersion = WD_VERSION_EXTERNE;
	// on renvoie le nouveau contexte initialisé
	return pstContexte;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// termine le contexte de langage externe pour utilisation depuis un thread secondaire
void WDMTTermThread(PVOID pContexte)
{	// si le langage externe n'est pas initialisé ou si on n'a pas pu initialiser de contexte de thread, on ne peut rien faire
	if(ghDLLVM==NULL||gpfnOperationThread==NULL)
		return;
	// on termine le contexte
	gpfnOperationThread(pContexte,WDOPMT_TERM_CONTEXTE);
	// on libère le contexte de langage externe et ses éléments liés
	free(((STWDExtern*)pContexte)->pstErreur);
	free(((STWDExtern*)pContexte)->pstValeurRetour);
	free(pContexte);
}

#define AFFECTE_UTF8(chaine,c) { (*(chaine)) = (char)(c); (chaine)++; }

#if defined(UNICODE) && defined(__unix__)
// conversion d'une chaine Wide en UTF8
void WideCharToUTF8(const wchar_t* pszWide, char* pszUtf8)
{
	// pour chaque caractère d'entrée
	while( *pszWide != 0 )
	{
		wchar_t wc = *pszWide;
		pszWide++;

		if( wc < 0x80 ) 
		{
			AFFECTE_UTF8( pszUtf8, wc );
		} 
		else if( wc < 0x800 ) 
		{
			AFFECTE_UTF8( pszUtf8, (wc >> 6)   | 0xc0 );
			AFFECTE_UTF8( pszUtf8, (wc & 0x3f) | 0x80 );
		} 
		else if( wc < 0x10000 ) 
		{
			AFFECTE_UTF8( pszUtf8, (wc >> 12)         | 0xe0 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 6) & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, (wc        & 0x3f) | 0x80 );
		} 
		else if( wc < 0x200000 ) 
		{
			AFFECTE_UTF8( pszUtf8, (wc >> 18)          | 0xf0 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 12) & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 6)  & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, (wc         & 0x3f) | 0x80 );
		}
		else if( wc < 0x4000000 ) 
		{
			AFFECTE_UTF8( pszUtf8, (wc >> 24)          | 0xf8 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 18) & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 12) & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 6)  & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, (wc         & 0x3f) | 0x80 );
		} 
		else if( wc <= 0x7FFFFFFF ) 
		{
			AFFECTE_UTF8( pszUtf8, (wc >> 30)          | 0xfc );
			AFFECTE_UTF8( pszUtf8, ((wc >> 24) & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 18) & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 12) & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, ((wc >> 6)  & 0x3f) | 0x80 );
			AFFECTE_UTF8( pszUtf8, (wc         & 0x3f) | 0x80 );
		} 
	}
	AFFECTE_UTF8( pszUtf8, 0 );
}
#endif // #if defined(UNICODE) && defined(__unix__)

#ifndef UNDER_CE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	pszNomCompletVM : nom et chemin complet de la DLL VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromNameA(LPCSTR pszNomCompletVM,BOOL bAfficheErreur)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il faudra libérer la VM à la fin
	gbDLLVM = TRUE;

	// on charge et on initialise la DLL
	#if defined(__unix__)
		return __nWDInitVM((HINSTANCE)dlopen(pszNomCompletVM, RTLD_NOW),bAfficheErreur,pszNomCompletVM,NULL,gdwOptionInit);
	#else
		return __nWDInitVM(LoadLibraryA(pszNomCompletVM),bAfficheErreur,pszNomCompletVM,NULL,gdwOptionInit);
	#endif
}
#endif // #ifndef UNDER_CE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	pszNomCompletVM : nom et chemin complet de la DLL VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromNameW(LPCWSTR pszNomCompletVM,BOOL bAfficheErreur)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il faudra libérer la VM à la fin
	gbDLLVM = TRUE;

	// on charge et on initialise la DLL
	#if defined(__unix__)
		char* pszNomCompletVMUTF8 = alloca(wcslen(pszNomCompletVM)*6+1);
		WideCharToUTF8(pszNomCompletVM, pszNomCompletVMUTF8);
		return __nWDInitVM((HINSTANCE)dlopen(pszNomCompletVMUTF8, RTLD_NOW),bAfficheErreur,NULL,pszNomCompletVM,gdwOptionInit);
	#elif defined(__unix__)
		return __nWDInitVM((HINSTANCE)dlopen(pszNomCompletVM, RTLD_NOW),bAfficheErreur,pszNomCompletVM,NULL,gdwOptionInit);
	#else
		return __nWDInitVM(LoadLibraryW(pszNomCompletVM),bAfficheErreur,NULL,pszNomCompletVM,gdwOptionInit);
	#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromInstance(HINSTANCE hInstanceVM,BOOL bAfficheErreur)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il ne faudra surtout PAS libérer la VM à la fin
	gbDLLVM = FALSE;
	// la DLL a été chargée par ailleurs, on initialise la DLL
	return __nWDInitVM(hInstanceVM,bAfficheErreur,NULL,NULL,gdwOptionInit);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromInstanceEx(HINSTANCE hInstanceVM,BOOL bAfficheErreur,DWORD dwOption)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il ne faudra surtout PAS libérer la VM à la fin
	gbDLLVM = FALSE;
	// la DLL a été chargée par ailleurs, on initialise la DLL
	return __nWDInitVM(hInstanceVM,bAfficheErreur,NULL,NULL,dwOption);
}

#ifndef UNDER_CE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromInstanceNameA(HINSTANCE hInstanceVM,LPCSTR pszNomCompletVM,BOOL bAfficheErreur)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il ne faudra surtout PAS libérer la VM à la fin
	gbDLLVM = FALSE;
	// la DLL a été chargée par ailleurs, on initialise la DLL
	return __nWDInitVM(hInstanceVM,bAfficheErreur,pszNomCompletVM,NULL,gdwOptionInit);
}
#endif // #ifndef UNDER_CE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromInstanceNameW(HINSTANCE hInstanceVM,LPCWSTR pszNomCompletVM,BOOL bAfficheErreur)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il ne faudra surtout PAS libérer la VM à la fin
	gbDLLVM = FALSE;
	// la DLL a été chargée par ailleurs, on initialise la DLL
	return __nWDInitVM(hInstanceVM,bAfficheErreur,NULL,pszNomCompletVM,gdwOptionInit);
}

#ifndef UNDER_CE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromInstanceNameExA(HINSTANCE hInstanceVM,LPCSTR pszNomCompletVM,BOOL bAfficheErreur,DWORD dwOption)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il ne faudra surtout PAS libérer la VM à la fin
	gbDLLVM = FALSE;
	// la DLL a été chargée par ailleurs, on initialise la DLL
	return __nWDInitVM(hInstanceVM,bAfficheErreur,pszNomCompletVM,NULL,dwOption);
}
#endif // #ifndef UNDER_CE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	hInstanceVM : instance de la VM
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInitFromInstanceNameExW(HINSTANCE hInstanceVM,LPCWSTR pszNomCompletVM,BOOL bAfficheErreur,DWORD dwOption)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il ne faudra surtout PAS libérer la VM à la fin
	gbDLLVM = FALSE;
	// la DLL a été chargée par ailleurs, on initialise la DLL
	return __nWDInitVM(hInstanceVM,bAfficheErreur,NULL,pszNomCompletVM,dwOption);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialise le langage externe
//	bAfficheErreur : TRUE si on veut voir la fenêtre d'erreur du WL
int nWDInit(BOOL bAfficheErreur)
{	// si le langage externe a déjà été initialisé, on sort sans rien faire ; on renvoie 0 pour ne pas provoquer d'erreur
	if(ghDLLVM!=NULL)
		return WDERREUR_OK;
	// il faudra libérer la VM à la fin
	gbDLLVM = TRUE;

	// on charge et on initialise la DLL
	#ifdef __unix__
		return __nWDInitVM((HINSTANCE)dlopen("./" WD_DLLVM, RTLD_NOW),bAfficheErreur,NULL,NULL,gdwOptionInit);
	#else
		return __nWDInitVM(LoadLibrary(_T(WD_DLLVM)),bAfficheErreur,NULL,NULL,gdwOptionInit);
	#endif
}

#if defined(__unix__) && !defined(DESACTIVE_PROXY_TERMLIBRARY)
	typedef void (*PFNTERMLIBRARY)(void);
#endif	// __unix__ && !DESACTIVE_PROXY_TERMLIBRARY

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// terminaison du langage externe
void WDTerm(void)
{
#if defined(__unix__) && !defined(DESACTIVE_PROXY_TERMLIBRARY)
	PFNTERMLIBRARY pfnTermLibrary;
#endif	// __unix__ && !DESACTIVE_PROXY_TERMLIBRARY

	// si le langage externe n'est pas en cours d'utilisation, on ne fait rien
	if(ghDLLVM==NULL)
		return;
	// on termine l'utilisation du langage externe
	gpfnTerm(&gstWLELocalCtx);

	//En WebDev, TermLibrary est appelé au dernier déchargement de la VM
	//on ne doit pas le refaire ici pour ne pas casser le langage externe (RAZ le libshop)
#if defined(__unix__) && !defined(DESACTIVE_PROXY_TERMLIBRARY)
	// on appelle la fonction de terminaison
	pfnTermLibrary = (PFNTERMLIBRARY)dlsym(ghDLLVM,"TermLibrary");
	// si on ne peut pas initialiser
	if(pfnTermLibrary!=NULL)
		pfnTermLibrary();
#endif	// __unix__ && !DESACTIVE_PROXY_TERMLIBRARY

	// on décharge la DLL si nécessaire
	if(gbDLLVM)
	{
		#ifdef __unix__
			dlclose(ghDLLVM);
		#else
			FreeLibrary(ghDLLVM);
		#endif
	}
	// on signale que la langage externe est terminé
	ghDLLVM = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le contexte courant
PVOID pWDGetContexte()
{	// on renvoie le contexte courant
	return gpstWLECtx;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// modifie le contexte courant
// renvoie l'ancien contexte en cours
// si pContexte est NULL, se replace sur le contexte local
PVOID pWDSetContexte(PVOID pContexte)
{	// on récupère l'ancien contexte courant
	PVOID pAncienContexte = gpstWLECtx;
	// on modifie le contexte courant
	gpstWLECtx = ( pContexte==NULL ? &gstWLELocalCtx : (STWDExtern *)pContexte );
	// on renvoie l'ancien contexte courant
	return pAncienContexte;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le contexte d'élément courant
PVOID pWDGetContexteElement()
{	// si le langage externe n'est pas initialisé ou si la fonction n'est pas disponible, on sort
	if(ghDLLVM==NULL)
		return NULL;
	// on récupère le contexte d'élément courant
	return gpfnGetContexteElement(gpstWLECtx);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// modifie le contexte d'élément courant
// renvoie l'ancien contexte en cours
// si pContexte est NULL, se replace sur le contexte global
PVOID pWDModifieContexteElement(PVOID pContexteElement)
{	// si le langage externe n'est pas initialisé, on sort
	if(ghDLLVM==NULL)
		return NULL;
	// on appelle le langage externe
	return gpfnModifieContexteElement(gpstWLECtx,pContexteElement);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// restaure le contexte d'élément courant
// renvoie l'ancien contexte en cours
PVOID pWDRestaureContexteElement(PVOID pContexteElement)
{	// si le langage externe n'est pas initialisé, on sort
	if(ghDLLVM==NULL)
		return NULL;
	// on appelle le langage externe
	return gpfnRestaureContexteElement(gpstWLECtx,pContexteElement);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ouverture d'une WDL (qui contient les fenêtres, le code, le(s) WDD, ...)
//	pszNomCompletWDL : nom et chemin complet de la WDL à ouvrir
int nWDOuvreWDLA(LPCSTR pszNomCompletWDL)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnOuvreWDLA(gpstWLECtx,pszNomCompletWDL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ouverture d'une WDL (qui contient les fenêtres, le code, le(s) WDD, ...)
//	pszNomCompletWDL : nom et chemin complet de la WDL à ouvrir
int nWDOuvreWDLW(LPCWSTR pszNomCompletWDL)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnOuvreWDL(gpstWLECtx,pszNomCompletWDL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ouverture d'une WDL
//	pszNomCompletWDL : nom et chemin complet de la WDL à ouvrir
//	pnNumWDL : remplit le numéro de la WDL
int nWDOuvreWDLNumA(LPCSTR pszNomCompletWDL,int* pnNumWDL)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnOuvreWDLNumA(gpstWLECtx,pszNomCompletWDL,pnNumWDL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ouverture d'une WDL
//	pszNomCompletWDL : nom et chemin complet de la WDL à ouvrir
//	pnNumWDL : remplit le numéro de la WDL
int nWDOuvreWDLNumW(LPCWSTR pszNomCompletWDL,int* pnNumWDL)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnOuvreWDLNum(gpstWLECtx,pszNomCompletWDL,pnNumWDL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fermeture d'une WDL contenue dans les ressources d'un exécutable (qui contient les fenêtres, le code, le(s) WDD, ...)
//	nNumWDL : numéro de la WDL renvoyé par nWDOuvreWDLNum()
void WDFermeWDLNum(int nNumWDL)
{	// si le langage externe n'est pas initialisé, on l'initialise
	if(ghDLLVM==NULL)
		return;
	// on appelle le langage externe
	gpfnFermeWDLNum(gpstWLECtx,nNumWDL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ouverture d'une WDL contenue dans les ressources d'un exécutable (qui contient les fenêtres, le code, le(s) WDD, ...)
//	pszNomCompletEXE : nom et chemin complet de la EXE à ouvrir
//	pszNomWDL : nom de la WDL à ouvrir
int nWDOuvreWDLRes(HINSTANCE hInstanceModule,UINT nIdRessource)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnOuvreWDLRes(gpstWLECtx,hInstanceModule,nIdRessource);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fermeture d'une WDL contenue dans les ressources d'un exécutable (qui contient les fenêtres, le code, le(s) WDD, ...)
//	nNumDLL : numéro de la DLL renvoyé par nWDOuvreWDLResNum
void WDFermeWDLRes(HINSTANCE hInstanceModule,UINT nIdRessource)
{	// si le langage externe n'est pas initialisé, on l'initialise
	if(ghDLLVM==NULL)
		return;
	// on appelle le langage externe
	gpfnFermeWDLRes(gpstWLECtx,hInstanceModule,nIdRessource);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exécute le code d'init d'un projet
//	!!! un seul code d'init de projet peut être exécuté
int nWDInitProjetA(LPCSTR pszProjet)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnInitProjet(gpstWLECtx,pszProjet);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exécute le code d'init d'un projet
//	!!! un seul code d'init de projet peut être exécuté
int nWDInitProjetW(LPCWSTR pszProjet)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnInitProjet(gpstWLECtx,pszProjet);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetCallbackNextA(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetCallbackA(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetCallbackNextW(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetCallback(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche pour la prochaine fenêtre à ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetCallbackModuleA(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetCallbackModuleA(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche pour la prochaine fenêtre à ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetCallbackModuleW(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetCallbackModule(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche pour la prochaine fenêtre à ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
PVOID pWDSetCallbackElementA(PVOID pParent,LPCSTR pszElement,pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return NULL;
	// on appelle le langage externe
	return gpfnSetCallbackElementA(gpstWLECtx,pParent,pszElement,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback appelée lors des WDTouche et RenvoieWDTouche pour la prochaine fenêtre à ouvrir
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
PVOID pWDSetCallbackElementW(PVOID pParent,LPCWSTR pszElement,pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return NULL;
	// on appelle le langage externe
	return gpfnSetCallbackElement(gpstWLECtx,pParent,pszElement,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback pour le mode compatible
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetCallbackCompatibleA(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetCompatibleA(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback pour le mode compatible
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetCallbackCompatibleW(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetCompatible(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback pour le mode édition
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetPECallbackA(pfnWDCALLBACKA pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on active la callback
	return gpfnSetPECallbackA(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner la callback pour le mode édition
//	pfnCallBack : adresse de la fonction callback
//	dwUserParam : paramètre utilisateur passé en paramètre à la callback
int nWDSetPECallbackW(pfnWDCALLBACK pfnCallBack,DWORD_PTR dwUserParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on active la callback
	return gpfnSetPECallback(gpstWLECtx,pfnCallBack,dwUserParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner le parent de la prochaine fenêtre à ouvrir
// hWnd : handle de la fenêtre parent de la prochaine fenêtre à ouvrir
int nWDSetParentNext(HWND hWnd)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetParent(gpstWLECtx,hWnd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renseigner le contexte HF de la prochaine fenêtre à ouvrir
//	pHFContext : contexte HF à utiliser dans la prochaine fenêtre
int nWDSetHFContextNext(void* pHFContext)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnSetHFContext(gpstWLECtx,pHFContext);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exécution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande à exécuter
int nWDExecuteA(LPCSTR pszCommande,...)
{
	va_list argList;
	char	szCommande[WD_CMDMAXLEN];
	int		nRes;
	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on récupère la liste des arguments
	va_start(argList,pszCommande);
	// on formatte la commande
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x550)
	nRes = vsprintf(szCommande,pszCommande,argList);
#else
	nRes = VSNPRINTF_A(szCommande,WD_CMDMAXLEN,pszCommande,argList);
#endif
	// fin de l'utilisation de la liste
	va_end(argList);
	// on appelle le langage externe
	return(nRes>0?gpfnExecuteA(gpstWLECtx,szCommande):WDERREUR_COMMANDE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exécution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande à exécuter
int nWDExecuteW(LPCWSTR pszCommande,...)
{
	va_list argList;
	wchar_t	szCommande[WD_CMDMAXLEN];
	int		nRes;
	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on récupère la liste des arguments
	va_start(argList,pszCommande);
	// on formatte la commande
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x550)
	nRes = wvsprintfW(szCommande,pszCommande,argList);
#else
	nRes = VSNPRINTF_W(szCommande,WD_CMDMAXLEN,pszCommande,argList);
#endif
	// fin de l'utilisation de la liste
	va_end(argList);
	// on appelle le langage externe
	return(nRes>0?gpfnExecute(gpstWLECtx,szCommande):WDERREUR_COMMANDE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exécution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande à exécuter
int nWDExecuteExA(LPCSTR pszCommande)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnExecuteA(gpstWLECtx,pszCommande);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exécution d'une fonction du WLangage par compilation dynamique
//	pszCommande : commande à exécuter
int nWDExecuteExW(LPCWSTR pszCommande)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnExecute(gpstWLECtx,pszCommande);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// évalue la valeur d'un élément : champ, variable, rubrique HF (ex : fenetre.champ, variable, fichier.rubrique)
// les accès aux éléments indicés ne sont pas possibles (ex : table[1] renvoie une erreur)
//	pszElement : nom de l'élément à évaleur
int nWDEvalueA(LPCSTR pszElement)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEvalueA(gpstWLECtx,pszElement);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// évalue la valeur d'un élément : champ, variable, rubrique HF (ex : fenetre.champ, variable, fichier.rubrique)
// les accès aux éléments indicés ne sont pas possibles (ex : table[1] renvoie une erreur)
//	pszElement : nom de l'élément à évaleur
int nWDEvalueW(LPCWSTR pszElement)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEvalue(gpstWLECtx,pszElement);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// compilation d'un procédure
//	pszProcedure : nom de la procédure
//	pszCode : code
int nWDCompileA(LPCSTR pszProcedure,LPCSTR pszCode)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnCompileA(gpstWLECtx,pszProcedure,pszCode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// compilation d'un procédure
//	pszProcedure : nom de la procédure
//	pszCode : code
int nWDCompileW(LPCWSTR pszProcedure,LPCWSTR pszCode)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnCompile(gpstWLECtx,pszProcedure,pszCode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// empile un paramètre sur la pile
//	pAdresse : adresse du paramètre
//	nType : type du paramètre
int nWDEmpile(LPCVOID pAdresse,int nType)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEmpile(gpstWLECtx,pAdresse,nType);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// empile un paramètre sur la pile
//	pContexte : contexte de langage externe du thread
//	pAdresse : adresse du paramètre
//	nType : type du paramètre
int nWDMTEmpile(PVOID pContexte,LPCVOID pAdresse,int nType)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEmpile(WD_SAFE_CONTEXTE(pContexte),pAdresse,nType);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// empile un paramètre sur la pile
//	pAdresse : adresse du paramètre
//	nTaille : taille du paramètre
//	nType : type du paramètre
int nWDEmpileEx(LPCVOID pAdresse,int nTaille,int nType)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEmpileEx(gpstWLECtx,pAdresse,nTaille,nType);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// appelle directement une fonction composante
//	nNumCompo : numéro de la composante
//	nNumFonc : numéro de la fonction
//	nNumSyntaxe : numéro de la syntaxe
//	nNbParam : nombre de paramètres
int nWDAppelle(int nNumCompo,int nNumFonc,int nNumSyntaxe,int nNbParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnAppelle(gpstWLECtx,nNumCompo,nNumFonc,nNumSyntaxe,nNbParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// appelle directement une fonction composante
//	pContexte : contexte de langage externe du thread
//	nNumCompo : numéro de la composante
//	nNumFonc : numéro de la fonction
//	nNumSyntaxe : numéro de la syntaxe
//	nNbParam : nombre de paramètres
int nWDMTAppelle(PVOID pContexte,int nNumCompo,int nNumFonc,int nNumSyntaxe,int nNbParam)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnAppelle(WD_SAFE_CONTEXTE(pContexte),nNumCompo,nNumFonc,nNumSyntaxe,nNbParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// lit la valeur d'une variable de composante
int nWDLitVariableWL(int nNumCompo,int nNumVar,int nIndice)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitVariableWL(gpstWLECtx,nNumCompo,nNumVar,nIndice);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// lit la valeur d'une variable de composante
int nWDMTLitVariableWL(PVOID pContexte,int nNumCompo,int nNumVar,int nIndice)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitVariableWL(WD_SAFE_CONTEXTE(pContexte),nNumCompo,nNumVar,nIndice);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// écrit dans une variable de composante
int nWDEcritVariableWL(int nNumCompo,int nNumVar,int nIndice)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritVariableWL(gpstWLECtx,nNumCompo,nNumVar,nIndice);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// écrit dans une variable de composante
int nWDMTEcritVariableWL(PVOID pContexte,int nNumCompo,int nNumVar,int nIndice)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritVariableWL(WD_SAFE_CONTEXTE(pContexte),nNumCompo,nNumVar,nIndice);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemA(LPCSTR pszElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropA(gpstWLECtx,pszElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemW(LPCWSTR pszElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitProp(gpstWLECtx,pszElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int nWDLitPropElemAnyA(LPCSTR pszElement,int nNumProp,PVOID pclAny)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropAnyA(gpstWLECtx,pszElement,nNumProp,pclAny);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int nWDLitPropElemAnyW(LPCWSTR pszElement,int nNumProp,PVOID pclAny)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropAny(gpstWLECtx,pszElement,nNumProp,pclAny);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemIndA(LPCSTR pszElement,int nIndice,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropIndA(gpstWLECtx,pszElement,nIndice,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemIndW(LPCWSTR pszElement,int nIndice,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropInd(gpstWLECtx,pszElement,nIndice,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemCleA(LPCSTR pszElement,LPCSTR pszCle,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if( ghDLLVM==NULL || gpfnLitPropCleA==NULL )
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropCleA(gpstWLECtx,pszElement,pszCle,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemCleW(LPCWSTR pszElement,LPCWSTR pszCle,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if( ghDLLVM==NULL || gpfnLitPropCle==NULL )
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropCle(gpstWLECtx,pszElement,pszCle,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int nWDLitPropElemAnyIndA(LPCSTR pszElement,int nIndice,int nNumProp,PVOID pclAny)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropAnyIndA(gpstWLECtx,pszElement,nIndice,nNumProp,pclAny);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int nWDLitPropElemAnyIndW(LPCWSTR pszElement,int nIndice,int nNumProp,PVOID pclAny)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropAnyInd(gpstWLECtx,pszElement,nIndice,nNumProp,pclAny);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemInd2A(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropInd2A(gpstWLECtx,pszElement,nIndice1,nIndice2,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropElemInd2W(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropInd2(gpstWLECtx,pszElement,nIndice1,nIndice2,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int nWDLitPropElemAnyInd2A(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp,PVOID pclAny)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropAnyInd2A(gpstWLECtx,pszElement,nIndice1,nIndice2,nNumProp,pclAny);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à lire
//	pointeur sur la valeur à remplir
int nWDLitPropElemAnyInd2W(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp,PVOID pclAny)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropAnyInd2(gpstWLECtx,pszElement,nIndice1,nIndice2,nNumProp,pclAny);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropSousElemA(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropSousElemA(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropSousElemW(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropSousElem(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDEcritPropSousElemA(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropSousElemA(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDEcritPropSousElemW(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropSousElem(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nIndiceSousElement : indice du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropSousElemIndA(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nIndiceSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropSousElemIndA(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nIndiceSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nIndiceSousElement : indice du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDLitPropSousElemIndW(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nIndiceSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnLitPropSousElemInd(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nIndiceSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nIndiceSousElement : indice du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDEcritPropSousElemIndA(LPCSTR pszElement,int nIndiceElement,LPCSTR pszSousElement,int nIndiceSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropSousElemIndA(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nIndiceSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en lecture
//	pszElement : nom de l'élément
//	nIndiceElement : indice de l'élément
//	pszSousElement : nom du sous-élément
//	nIndiceSousElement : indice du sous-élément
//	nNumProp : numéro de la propriété à lire
int nWDEcritPropSousElemIndW(LPCWSTR pszElement,int nIndiceElement,LPCWSTR pszSousElement,int nIndiceSousElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropSousElemInd(gpstWLECtx,pszElement,nIndiceElement,pszSousElement,nIndiceSousElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemA(LPCSTR pszElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropA(gpstWLECtx,pszElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemW(LPCWSTR pszElement,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritProp(gpstWLECtx,pszElement,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemIndA(LPCSTR pszElement,int nIndice,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropIndA(gpstWLECtx,pszElement,nIndice,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nIndice : indice de l'élément
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemIndW(LPCWSTR pszElement,int nIndice,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropInd(gpstWLECtx,pszElement,nIndice,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	pszCle : clé
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemCleA(LPCSTR pszElement,LPCSTR pszCle,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if( ghDLLVM==NULL || gpfnEcritPropCleA==NULL )
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropCleA(gpstWLECtx,pszElement,pszCle,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	pszCle : clé
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemCleW(LPCWSTR pszElement,LPCWSTR pszCle,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if( ghDLLVM==NULL || gpfnEcritPropCle==NULL )
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropCle(gpstWLECtx,pszElement,pszCle,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemInd2A(LPCSTR pszElement,int nIndice1,int nIndice2,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropInd2A(gpstWLECtx,pszElement,nIndice1,nIndice2,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// accède directement à une propriété d'un élément en écriture
//	pszElement : nom de l'élément
//	nIndice1, nIndice2 : indices de l'élément
//	nNumProp : numéro de la propriété à écrire
int nWDEcritPropElemInd2W(LPCWSTR pszElement,int nIndice1,int nIndice2,int nNumProp)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnEcritPropInd2(gpstWLECtx,pszElement,nIndice1,nIndice2,nNumProp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vérifie si un champ existe
int nWDChampExisteA(LPCSTR pszNomChamp,BOOL* pbExiste)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnChampExisteA(gpstWLECtx,pszNomChamp,pbExiste);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vérifie si un champ existe
int nWDChampExisteW(LPCWSTR pszNomChamp,BOOL* pbExiste)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnChampExiste(gpstWLECtx,pszNomChamp,pbExiste);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère un message multilangue
int nWDMessTraduit(int nMessage)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// si la version de la VM est trop ancienne
	if(gpfnOperation==NULL)
		return WDERREUR_VERSION;
	// on appelle le langage externe
	return gpfnOperation(gpstWLECtx,WLE_MESSTRADUIT,nMessage,(DWORD_PTR)NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère un message multilangue
int nWDMessTraduitElementA(LPCSTR pszElement,int nMessage)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// si la version de la VM est trop ancienne
	if(gpfnOperation==NULL)
		return WDERREUR_VERSION;
	// on appelle le langage externe
	return gpfnOperation(gpstWLECtx,WLE_MESSTRADUIT_ELEMENT,(DWORD_PTR)pszElement,nMessage);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère un message multilangue
int nWDMessTraduitElementW(LPCWSTR pszElement,int nMessage)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// si la version de la VM est trop ancienne
	if(gpfnOperation==NULL)
		return WDERREUR_VERSION;
	// on appelle le langage externe
	return gpfnOperation(gpstWLECtx,WLE_MESSTRADUIT_ELEMENT,(DWORD_PTR)pszElement,nMessage);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère un message multilangue
int nWDEmpileMessTraduit(int nMessage)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// si la version de la VM est trop ancienne
	if(gpfnOperation==NULL)
		return WDERREUR_VERSION;
	// on appelle le langage externe
	return gpfnOperation(gpstWLECtx,WLE_EMPILE_MESSTRADUIT,nMessage,(DWORD_PTR)NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère un message multilangue
int nWDEmpileMessTraduitElementA(LPCSTR pszElement,int nMessage)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// si la version de la VM est trop ancienne
	if(gpfnOperation==NULL)
		return WDERREUR_VERSION;
	// on appelle le langage externe
	return gpfnOperation(gpstWLECtx,WLE_EMPILE_MESSTRADUIT_ELEMENT,(DWORD_PTR)pszElement,nMessage);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère un message multilangue
int nWDEmpileMessTraduitElementW(LPCWSTR pszElement,int nMessage)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// si la version de la VM est trop ancienne
	if(gpfnOperation==NULL)
		return WDERREUR_VERSION;
	// on appelle le langage externe
	return gpfnOperation(gpstWLECtx,WLE_EMPILE_MESSTRADUIT_ELEMENT,(DWORD_PTR)pszElement,nMessage);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère le contexte HF
int nWDGetHFContext(void** ppHFContext)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnGetHFContext(gpstWLECtx,ppHFContext);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère le contexte globale VM
int nWDGetVMData(void** ppVMData)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnGetVMData(gpstWLECtx,ppVMData);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère le contexte VM
int nWDGetVM(void** ppVM)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// si la version de la VM est trop ancienne
	if(gpfnGetVM==NULL)
		return WDERREUR_VERSION;
	// on appelle le langage externe
	return gpfnGetVM(gpstWLECtx,ppVM);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère le libshop
int nWDGetLibShop(void** ppLibShop)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnGetLibShop(gpstWLECtx,ppLibShop);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// récupère le contexte OBJ
int nWDGetIEXE(void** ppEXE)
{	// si le langage externe n'est pas initialisé, on sort en erreur
	if(ghDLLVM==NULL)
		return WDERREUR_INIT;
	// on appelle le langage externe
	return gpfnGetIEXE(gpstWLECtx,ppEXE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le type de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
WORD wWDGetTypeValeurRetour(void)					{ return gpstWLECtx->pstValeurRetour->wType; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie TRUE si le type de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue() est une chaîne Ansi ou Unicode
BOOL bWDValeurRetourChaine(void)					{ return ( wWDGetTypeValeurRetour()==WDTYPE_ASTR || wWDGetTypeValeurRetour()==WDTYPE_WSTR ); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le type de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
WORD wWDMTGetTypeValeurRetour(PVOID pContexte)		{ return WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->wType; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie TRUE si le type de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue() est une chaîne Ansi ou Unicode
BOOL bWDMTValeurRetourChaine(PVOID pContexte)		{ return ( wWDMTGetTypeValeurRetour(pContexte)==WDTYPE_ASTR || wWDMTGetTypeValeurRetour(pContexte)==WDTYPE_WSTR ); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie TRUE si la valeur de retour est NULL
BOOL bWDValeurRetourNULL(void)						{ return gpstWLECtx->pstValeurRetour->bNull; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie TRUE si la valeur de retour est NULL
BOOL bWDMTValeurRetourNULL(PVOID pContexte)			{ return WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->bNull; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur booléenne de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
BOOL bWDGetValeurRetour(void)						{ return((BOOL)gpstWLECtx->pstValeurRetour->nValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur booléenne de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
BOOL bWDMTGetValeurRetour(PVOID pContexte)			{ return((BOOL)WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->nValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur entière de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
int nWDGetValeurRetour(void)						{ return(gpstWLECtx->pstValeurRetour->nValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur entière de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
int	nWDMTGetValeurRetour(PVOID pContexte)			{ return(WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->nValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur entière sur 8 octets de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
WDINT64 i64WDGetValeurRetour(void)					{ return(gpstWLECtx->pstValeurRetour->i64Valeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur entière sur 8 octets de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
WDINT64	i64WDMTGetValeurRetour(PVOID pContexte)		{ return(WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->i64Valeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur flottante de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
double dWDGetValeurRetour(void)						{ return(gpstWLECtx->pstValeurRetour->dValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur flottante de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
double dWDMTGetValeurRetour(PVOID pContexte)		{ return(WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->dValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la longueur d'une chaine ou d'un buffer binaire
size_t nWDLongueurValeurRetour(void)				{ return(gpstWLECtx->pstValeurRetour->nValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la longueur d'une chaine ou d'un buffer binaire
size_t nWDMTLongueurValeurRetour(PVOID pContexte)	{ return(WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->nValeur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur chaine de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
LPCSTR	pszWDGetValeurRetourA(void)					{ return gpstWLECtx->pstValeurRetour->pszValeurA; }
LPCWSTR pszWDGetValeurRetourW(void)					{ return gpstWLECtx->pstValeurRetour->pszValeurW; }
#ifdef UNICODE
LPCTSTR pszWDGetValeurRetour(void)					{ return ( gpfnOperation(gpstWLECtx,WLE_CONVERSION_RESULTAT,WDTYPE_WSTR,0)==WDERREUR_OK ? gpstWLECtx->pstValeurRetour->pszValeurW : NULL ); }
#else	//UNICODE
LPCTSTR pszWDGetValeurRetour(void)					{ return ( gpfnOperation(gpstWLECtx,WLE_CONVERSION_RESULTAT,WDTYPE_ASTR,0)==WDERREUR_OK ? gpstWLECtx->pstValeurRetour->pszValeurA : NULL ); }
#endif	//!UNICODE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur chaine de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
LPCSTR	pszWDMTGetValeurRetourA(PVOID pContexte)	{ return WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->pszValeurA; }
LPCWSTR	pszWDMTGetValeurRetourW(PVOID pContexte)	{ return WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->pszValeurW; }
#ifdef UNICODE
LPCTSTR	pszWDMTGetValeurRetour(PVOID pContexte)		{ return ( gpfnOperation(WD_SAFE_CONTEXTE(pContexte),WLE_CONVERSION_RESULTAT,WDTYPE_WSTR,0)==WDERREUR_OK ? WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->pszValeurW : NULL ); }
#else	//UNICODE
LPCTSTR	pszWDMTGetValeurRetour(PVOID pContexte)		{ return ( gpfnOperation(WD_SAFE_CONTEXTE(pContexte),WLE_CONVERSION_RESULTAT,WDTYPE_ASTR,0)==WDERREUR_OK ? WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->pszValeurA : NULL ); }
#endif	//!UNICODE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur binaire de la valeur de retour de la dernière instruction nWDExecute() ou nWDEvalue()
PBYTE	pbyWDGetValeurRetour(void)					{ return(gpstWLECtx->pstValeurRetour->pbyBinaire); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie la valeur binaire de la valeur de retour de la dernière instruction nWDMTExecute() ou nWDMTEvalue()
PBYTE	pbyWDMTGetValeurRetour(PVOID pContexte)		{ return(WD_SAFE_CONTEXTE(pContexte)->pstValeurRetour->pbyBinaire); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le code d'erreur de la dernière erreur
int nWDGetLastError(void)							{ return(gpstWLECtx->pstErreur->nCodeErreur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le code d'erreur de la dernière erreur
int nWDMTGetLastError(PVOID pContexte)				{ return(WD_SAFE_CONTEXTE(pContexte)->pstErreur->nCodeErreur); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le message de la dernière erreur
LPCSTR	pszWDGetLastErrorA(void)					{ return gpstWLECtx->pstErreur->pszMessageA; }
LPCWSTR	pszWDGetLastErrorW(void)					{ return gpstWLECtx->pstErreur->pszMessageW; }
#ifdef UNICODE
LPCTSTR pszWDGetLastError(void)						{ return ( gpfnOperation(gpstWLECtx,WLE_CONVERSION_ERREUR,WDTYPE_WSTR,0)==WDERREUR_OK ? gpstWLECtx->pstErreur->pszMessageW : NULL ); }
#else	//UNICODE
LPCTSTR pszWDGetLastError(void)						{ return ( gpfnOperation(gpstWLECtx,WLE_CONVERSION_ERREUR,WDTYPE_ASTR,0)==WDERREUR_OK ? gpstWLECtx->pstErreur->pszMessageA : NULL ); }
#endif	//!UNICODE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// renvoie le message de la dernière erreur
LPCSTR	pszWDMTGetLastErrorA(PVOID pContexte)		{ return WD_SAFE_CONTEXTE(pContexte)->pstErreur->pszMessageA; }
LPCWSTR pszWDMTGetLastErrorW(PVOID pContexte)		{ return WD_SAFE_CONTEXTE(pContexte)->pstErreur->pszMessageW; }
#ifdef UNICODE
LPCTSTR pszWDMTGetLastError(PVOID pContexte)		{ return ( gpfnOperation(WD_SAFE_CONTEXTE(pContexte),WLE_CONVERSION_ERREUR,WDTYPE_WSTR,0)==WDERREUR_OK ? WD_SAFE_CONTEXTE(pContexte)->pstErreur->pszMessageW : NULL ); }
#else	//UNICODE
LPCTSTR pszWDMTGetLastError(PVOID pContexte)		{ return ( gpfnOperation(WD_SAFE_CONTEXTE(pContexte),WLE_CONVERSION_ERREUR,WDTYPE_ASTR,0)==WDERREUR_OK ? WD_SAFE_CONTEXTE(pContexte)->pstErreur->pszMessageA : NULL ); }
#endif	//!UNICODE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// reprise sur erreur : force la reprise normale de l'exécution après une erreur
void WDRepriseErreur(void)							{ gpfnReprise(gpstWLECtx); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// reprise sur erreur : force la reprise normale de l'exécution après une erreur
void WDMTRepriseErreur(PVOID pContexte)				{ gpfnReprise(WD_SAFE_CONTEXTE(pContexte)); }
