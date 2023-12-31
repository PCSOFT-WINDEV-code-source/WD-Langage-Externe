/*	WinDev.c
   Interface WINDEV avec le C                  
   Gestion des syntaxes compatibles v5.5 et inf�rieures
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
	
/* fonctions export�es de la DLL : */
typedef void  (__stdcall * PFInitModule)( pstWDCTX );
PFInitModule WDEXT_InitModule = NULL;
typedef void  (__stdcall * PFTermModule)( pstWDCTX );
PFTermModule WDEXT_TermModule = NULL;
typedef void  (__stdcall * PFWDExecuteCommande)( pstWDCTX, LPCSTR );
PFWDExecuteCommande WDEXT_WDExecuteCommande = NULL;
typedef void * (__stdcall * PFpGetHFContext)(void);
PFpGetHFContext WDEXT_pGetHFContext = NULL;

/* Chargement dynamique des points d'entr�e de la DLL EXT */
void _ChargeDllExt( void )
{
	BOOL bOK = TRUE;

	/* Chargement de la DLL */
	ghDLLEXT = LoadLibrary( NOMDLLEXE );

	/* si echec � l'ouverture. */
	if (ghDLLEXT == NULL)
	{
		// Message d'erreur
        MessageBox(NULL,"La fonction loadlibrary sur la DLL " NOMDLLEXE " a �chou�.\nCette DLL doit se trouver dans le r�pertoire de l'ex�cutable, dans le r�pertoire Windows ou dans un r�pertoire du path.\nProgramme arr�t�!","Erreur",MB_OK|MB_ICONSTOP);
		// echec fatal.
        exit(0);
	}

	// R�cup des adresses des points d'entr�e	   
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

	// si echec � la r�cup�ration d'un point d'entr�e
	if (!bOK)
	{
		// Message d'erreur
        MessageBox(NULL,"La r�solution des liens avec la DLL WinDev a �chou�.\nProgramme arr�t�!","Erreur",MB_OK|MB_ICONSTOP);
		// echec fatal.
        abort();
	}

}

/* V�rification de l'init (l'effecutue si pas encore faite) */
void _CHECKINIT(void)
{
	/* si d�ja initialis�, on ne fait rien */
	if (pstWDCtx->bInit) return;

	/* Init */

	/* On charge la DLL EXT */
	_ChargeDllExt();
	/* On appelle la fonction d'init de la DLL EXT */
	WDEXT_InitModule( pstWDCtx );
	/* Init effectu�e */
	pstWDCtx->bInit = TRUE;

}

/*  point d'entr�e principal du langage externe */
void APPELWD( char *fmt, ... )
{
	char command[LG_CDE_WD]; /* buffer  pour la commande � ex�cuter */
    va_list arg_ptr;

	/* V�rification de l'init (l'effecutue si pas encore faite) */
	_CHECKINIT();
	/* Cr�ation de la commande � �x�cuter � partir des arguments */
    va_start(arg_ptr, fmt);
    vsprintf(command, fmt, arg_ptr);
    va_end(arg_ptr);
	/* Ex�cution de la commande par WinDev via la DLL EXT */
	WDEXT_WDExecuteCommande( pstWDCtx, command );
}

/* AfficheTexteLong : Modification de la valeur d'un champ */ 
void AfficheTexteLong( char *pszChamp, char *pPointeur, short nTaille)
{
	/* V�rification de l'init (l'effecutue si pas encore faite) */
	_CHECKINIT();
	/* Mise des param�tres dans le contexte */
	/*pstWDCtx->*/ WDpTexteLong = pPointeur;
  	/*pstWDCtx->*/ WDEntier	    = nTaille;
	/* Ex�cution de la commande sp�ciale "AfficheTexteLong" */
	APPELWD( "_ATL,%s", pszChamp );

}

/* WDTermine: fin du langage externe */
void WDTermine	( void )
{
	/* si d�ja initialis�, on ne fait rien */
	if (!pstWDCtx->bInit) return;

	/* fin du module */
	WDEXT_TermModule( pstWDCtx );

	/* d�chargement de la dll langage externe */
	FreeLibrary( ghDLLEXT	);

	/* on est plus initialis� */
	pstWDCtx->bInit = FALSE;
}

/* R�cup�ration du contexte HF */
int nWDGetHFContext(void **ppContexte)
{
	/* V�rification de l'init (l'effecutue si pas encore faite) */
	_CHECKINIT();

	/* R�cup�ration contexte HF */
	if (ppContexte == NULL) return 1;
	*ppContexte = WDEXT_pGetHFContext();

	/* R�sultat */
	return (*ppContexte == NULL) ? 1 : 0;
}