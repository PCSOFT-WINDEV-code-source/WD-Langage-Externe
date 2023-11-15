/*

   Gestion du langage externe WinDev en mode compatible WinDev 5.5	

*/
#ifndef __WINDEV_H
#define __WINDEV_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* longeur maxi d'une commande en langage externe */
#define  LG_CDE_WD 255

/* Numéro de version du contexte */
#define VERSIONWDCTX 2

/* Contexte interface WinDev */
#pragma pack(1)
typedef struct _stWDCTX
{
	/* Numéro de version du contexte */
	short  nVersion;
	/* variables pour la valeur de retour */
	int    WDEntier;
	double WDReelD;
	char   WDChaine[207];
	char   WDNom[11];
	char   WDTouche[4];
	char  *WDpTexteLong;
	/* indique si l'init à eu lieu */
	BOOL   bInit;

} stWDCTX, far *pstWDCTX;
#pragma pack()

#ifndef STRUCTONLY_	// define interne PC-Soft, pour n'avoir que la structure. Ne pas utiliser

extern pstWDCTX pstWDCtx;

/* macro pour récupérer les valeurs de retour */
#define WDCommande   (pstWDCtx->WDCommande)
#define WDEntier	 (pstWDCtx->WDEntier)
#define WDLong		 WDEntier				    /* comme WDEntier */
#define WDReelD		 (pstWDCtx->WDReelD)
#define WDReel		 ((float)WDReelD)			/* cast de WDReelD */
#define WDChaine	 (pstWDCtx->WDChaine)	    
#define WDNom		 (pstWDCtx->WDNom)		    /* pour "Ecran,Courant" */
#define WDTouche	 (pstWDCtx->WDTouche)  
#define WDpTexteLong (pstWDCtx->WDpTexteLong)
#define WDIndice	 WDEntier					/* OBSOLETE */				   

/* APPELDW : exécution d'un ordre WinDev  */
void APPELWD	( char *fmt, ... );

/* WDTermine: fin du langage externe */
void WDTermine	( void );

/* AfficheTexteLong : Modification de la valeur d'un champ */ 
void AfficheTexteLong( char *pszChamp, char *pPointeur, short nTaille);

/* Contexte HF */
int nWDGetHFContext(void **ppHFContexte);


#define WDToucheEgal(x)      (strcmp(WDTouche,x)==0)

#endif//! STRUCTONLY_


#ifdef __cplusplus
}
#endif

#endif /*__WINDEV_H */

