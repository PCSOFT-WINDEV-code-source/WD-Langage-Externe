/*	WinDev.c
   Interface WINDEV avec le C                  
   Gestion des syntaxes compatibles v5.5 et inférieures
*/

#define WINDEV_C
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <process.h>
#include "windev.h"

/* Nom de la DLL de gestion du langage Externe compatible 5.5 */
#define NOMDLLEXE "WD220LE.DLL"

#define STRCPY  strcpy
#define STRNCPY	strncpy

/* contexte WL global pour ce module */
stWDCTX gstWDCtx	=	{
/* nVersion */					VERSIONWDCTX,
/* WDEntier */					0,
/* WDReelD */					0.0,
/* WDChaine */					"",
/* WDNom */						"",
/* WDTouche */					"",
/* WDpTexteLong */				NULL,
/* bInit */						FALSE,
							};
pstWDCTX pstWDCtx	= &gstWDCtx;

/* routine d'init */

/* handle de la DLL du langage externe de WinDev */
HMODULE ghDLLEXT = NULL;		
	
/* fonctions exportées de la DLL : */
typedef void  (__stdcall * PFInitModule)( pstWDCTX );
PFInitModule WDEXT_InitModule = NULL;
typedef void  (__stdcall * PFTermModule)( pstWDCTX );
PFTermModule WDEXT_TermModule = NULL;
typedef void  (__stdcall * PFWDExecuteCommande)( pstWDCTX, LPCSTR );
PFWDExecuteCommande WDEXT_WDExecuteCommande = NULL;
typedef void * (__stdcall * PFpGetHFContext)(void);
PFpGetHFContext WDEXT_pGetHFContext = NULL;

/* Chargement dynamique des points d'entrée de la DLL EXT */
void _ChargeDllExt( void )
{
	BOOL bOK = TRUE;

	/* Chargement de la DLL */
	ghDLLEXT = LoadLibrary( NOMDLLEXE );

	/* si echec à l'ouverture. */
	if (ghDLLEXT == NULL)
	{
		// Message d'erreur
        MessageBox(NULL,"La fonction loadlibrary sur la DLL " NOMDLLEXE " a échoué.\nCette DLL doit se trouver dans le répertoire de l'exécutable, dans le répertoire Windows ou dans un répertoire du path.\nProgramme arrêté!","Erreur",MB_OK|MB_ICONSTOP);
		// echec fatal.
        exit(0);
	}

	// Récup des adresses des points d'entrée	   
	// InitModule
	WDEXT_InitModule =		(PFInitModule)		GetProcAddress(ghDLLEXT,  "InitModule");
	bOK &= (WDEXT_InitModule != NULL);
 	// TermModule
	WDEXT_TermModule =		(PFTermModule)		GetProcAddress(ghDLLEXT,  "TermModule");
	bOK &= (WDEXT_TermModule != NULL);
 	// TermModule
	WDEXT_WDExecuteCommande = (PFWDExecuteCommande)GetProcAddress(ghDLLEXT, "WDExecuteCommande");
	bOK &= (WDEXT_WDExecuteCommande != NULL);
 	// Contexte HF
	WDEXT_pGetHFContext = (PFpGetHFContext)GetProcAddress(ghDLLEXT, "pGetHFContext");
	bOK &= (WDEXT_pGetHFContext != NULL);

	// si echec à la récupération d'un point d'entrée
	if (!bOK)
	{
		// Message d'erreur
        MessageBox(NULL,"La résolution des liens avec la DLL WinDev a échoué.\nProgramme arrêté!","Erreur",MB_OK|MB_ICONSTOP);
		// echec fatal.
        abort();
	}

}

/* Vérification de l'init (l'effecutue si pas encore faite) */
void _CHECKINIT(void)
{
	/* si déja initialisé, on ne fait rien */
	if (pstWDCtx->bInit) return;

	/* Init */

	/* On charge la DLL EXT */
	_ChargeDllExt();
	/* On appelle la fonction d'init de la DLL EXT */
	WDEXT_InitModule( pstWDCtx );
	/* Init effectuée */
	pstWDCtx->bInit = TRUE;

}

/*  point d'entrée principal du langage externe */
void APPELWD( char *fmt, ... )
{
	char command[LG_CDE_WD]; /* buffer  pour la commande à exécuter */
    va_list arg_ptr;

	/* Vérification de l'init (l'effecutue si pas encore faite) */
	_CHECKINIT();
	/* Création de la commande à éxécuter à partir des arguments */
    va_start(arg_ptr, fmt);
    vsprintf(command, fmt, arg_ptr);
    va_end(arg_ptr);
	/* Exécution de la commande par WinDev via la DLL EXT */
	WDEXT_WDExecuteCommande( pstWDCtx, command );
}

/* AfficheTexteLong : Modification de la valeur d'un champ */ 
void AfficheTexteLong( char *pszChamp, char *pPointeur, short nTaille)
{
	/* Vérification de l'init (l'effecutue si pas encore faite) */
	_CHECKINIT();
	/* Mise des paramètres dans le contexte */
	/*pstWDCtx->*/ WDpTexteLong = pPointeur;
  	/*pstWDCtx->*/ WDEntier	    = nTaille;
	/* Exécution de la commande spéciale "AfficheTexteLong" */
	APPELWD( "_ATL,%s", pszChamp );

}

/* WDTermine: fin du langage externe */
void WDTermine	( void )
{
	/* si déja initialisé, on ne fait rien */
	if (!pstWDCtx->bInit) return;

	/* fin du module */
	WDEXT_TermModule( pstWDCtx );

	/* déchargement de la dll langage externe */
	FreeLibrary( ghDLLEXT	);

	/* on est plus initialisé */
	pstWDCtx->bInit = FALSE;
}

/* Récupération du contexte HF */
int nWDGetHFContext(void **ppContexte)
{
	/* Vérification de l'init (l'effecutue si pas encore faite) */
	_CHECKINIT();

	/* Récupération contexte HF */
	if (ppContexte == NULL) return 1;
	*ppContexte = WDEXT_pGetHFContext();

	/* Résultat */
	return (*ppContexte == NULL) ? 1 : 0;
}