/*-----------------------------------------------------------------------------------------------------------*/
/* Interface avec la dll HyperFile - PC SOFT 1998 - Ne pas modifier                                          */
/*-----------------------------------------------------------------------------------------------------------*/
#ifndef __WDHF_H
#define __WDHF_H

#if !defined(_INC_WINDOWS) && !defined(__WINDOWS_H)
#include <windows.h>
#endif

typedef DWORD PCTXHF;  /*numéro d'instance*/
typedef PCTXHF far * PPCTXHF;

#define HFCTX_NULL (PCTXHF)NULL
    						  
#ifdef __cplusplus
extern "C" {      
#endif

/*-----------------------------------------------------------------------------------------------------------*/
/* STRUCTURES                                                                                                */
/*-----------------------------------------------------------------------------------------------------------*/
#if !defined(__HF_H) && !defined(__HFINT_H)

#pragma pack(1)

/*Contexte d'enreg pour un fichier*/
typedef struct _stHFFileCtx {                                        
	LPVOID pData;				/*pointeur vers une structure d'enreg*/
	short nSize;				/*taille de la structure d'enreg*/
	LPCSTR pszNomFic;			/*nom logique du fichier associé*/
	LPVOID pStorage;			/*copie de la structure d'enreg*/
}	stHFFileCtx;         

typedef stHFFileCtx far * pstHFFileCtx;

/*Contexte HF pour une instance*/
typedef struct _stHFContexte {
	stHFFileCtx far *pTabCtx;   /*tableau des structures d'enreg*/
	short nMaxCtx;              /*nombre de structures d'enreg*/
}	stHFContexte;

typedef stHFContexte far * pstHFContexte;
#pragma pack()

#endif

/*-----------------------------------------------------------------------------------------------------------*/
/* CONSTANTES                                                                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* Pour le paramètre <format> de Hlisterubrique et Hinforubrique */
#define RUBMAX				0x0001		/* Bits 2 à 6 (0x0004 à 0x0040) */
#define RUBODBC				0x0002		/* Format ODBC */
#define RUBNATURE			0x0004		/* Type de la rubrique (numérique ou texte) */
#define RUBTYPE				0x0008		/* Type de la rubrique au format  HF ou ODBC */
#define RUBTAILLE			0x0010		/* Taille de la rubrique */
#define RUBNBELEMENT		0x0020		/* Nombre d'éléments du tableau */
#define RUBLIBELLE			0x0040		/* Libellé de la rubrique */
#define RUBTAILLEENTIER		0x0080		/* Nombre de chiffres de la partie entière */
#define RUBTAILLEDECIMAL	0x0100		/* Nombre de chiffres de la partie décimale */
#define RUBFORMAT			0x0200		/* Format d'affichage des numériques */

#define FIELDMAX			RUBMAX
#define	FIELDODBC			RUBODBC
#define	FIELDNATURE			RUBNATURE
#define	FIELDTYPE			RUBTYPE
#define	FIELDSIZE			RUBTAILLE
#define	FIELDNBELEMENT		RUBNBELEMENT
#define	FIELDCAPTION		RUBLIBELLE
#define	FIELDINTEGERSIZE	RUBTAILLEENTIER
#define	FIELDDECIMALSIZE	RUBTAILLEDECIMAL
#define	FIELDFORMAT			RUBFORMAT


/*-----------------------------------------------------------------------------------------------------------*/
/* FONCTIONS                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------*/

BOOL bInitHF(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL bAssociate( LPCSTR pzTable, LPVOID pBuffer, size_t nSize );

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hinit(pstHFFileCtx pTabCtx, short/* nMaxCtx*/);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hinitpartage( long /*pCtx*/, pstHFFileCtx pTabCtx, short /*nMaxCtx*/ );

/*-----------------------------------------------------------------------------------------------------------*/
void Hftermine(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hfterminepartage(void);
/*-----------------------------------------------------------------------------------------------------------*/
BOOL Houvreanalyse(LPCSTR pszNomWDD, LPCSTR pszMotDePasse, LPCSTR pszAdrServ, LPCSTR pszUser, LPCSTR pszPwd);

/*-----------------------------------------------------------------------------------------------------------*/
void Hfermeanalyse(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hajoute(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hassigne(LPCSTR pszNomFic, LPCSTR pszNomRep);

/*-----------------------------------------------------------------------------------------------------------*/
void Hcreation(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hecrit (LPCSTR pszNomFic, DWORD dwNumEnr);

/*-----------------------------------------------------------------------------------------------------------*/
void Hferme(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hfermesanscommit(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hinfogene(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hinfogenevue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlit(LPCSTR pszNomFic, DWORD dwNumEnreg);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitvue(DWORD dwHdlVue, DWORD dwNumEnreg);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitdernier(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitderniervue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Hdernier(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedent(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentvue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Hprecedent(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremier(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremiervue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Hpremier(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherche(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchenum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech, WORD wSize);

/*-----------------------------------------------------------------------------------------------------------*/
/* Hlitrecherche pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HlitrechercheWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech );

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchevue(DWORD dwHdlVue, LPCSTR pszNomCle, LPCSTR pszValRech);

/*-----------------------------------------------------------------------------------------------------------*/
void Hrecherche(LPCSTR pszNomFic, LPCSTR pszNomCle, LPSTR pszValRech);

/*-----------------------------------------------------------------------------------------------------------*/
void Hrecherchenum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPSTR pszValRech, WORD wSize);

/*-----------------------------------------------------------------------------------------------------------*/
/* Hrecherche pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HrechercheWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech );

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivant(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantvue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Hsuivant(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlibere(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodifie(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodifievue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Houvre(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Houvresansbloquer(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hraye(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hrayevue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Hreplace(LPCSTR /*pszNomFic*/, LPCSTR /*pszNomCle*/, LPSTR /*pszValCle*/, DWORD /*dwNumEnr*/, LPSTR /*pszCleGen*/);
/*-----------------------------------------------------------------------------------------------------------*/
void Hreplacenum(LPCSTR /*pszNomFic*/, LPCSTR /*pszNomCle*/, LPSTR /*pszValCle*/, WORD /*wTailleCle*/, DWORD /*dwNumEnr*/, LPSTR /*pszCleGen*/);
/*-----------------------------------------------------------------------------------------------------------*/
/* Hreplace pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HreplaceWD4( LPCSTR /*pszNomFic*/, LPCSTR /*pszNomCle*/, LPSTR /*pszValCle*/, DWORD /*dwNumEnr*/, LPSTR /*pszCleGen */);
/*-----------------------------------------------------------------------------------------------------------*/
void Hsecurite (short nLevel);

/*-----------------------------------------------------------------------------------------------------------*/
void Hsubstrep (LPCSTR pszRepLog, LPCSTR pszRepPhys);

/*-----------------------------------------------------------------------------------------------------------*/
void Hsubstnom (LPCSTR pszNomFicLog, LPCSTR pszNomFicPhys);

/*-----------------------------------------------------------------------------------------------------------*/
void Hsupprime(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hsupprimevue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
void Hvalcle(LPCSTR pszNomFic, LPSTR pszValCle);
/*-----------------------------------------------------------------------------------------------------------*/
void HconvertE(LPSTR pszDest, short far *pnEntier);

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertU(LPSTR pszDest, unsigned short far *pnUEntier);

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertC(LPSTR pszDest, unsigned char far *pcCar);

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertV(LPSTR pszDest, void far *pEntierCourt);

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertL(LPSTR pszDest, long far *plLong);

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertR(LPSTR pszDest,float far *pfReel);

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertD(LPSTR pszDest,double far *pfDouble);

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertP(LPSTR pszDest,void far *pReel6);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitbloque(LPCSTR pszNomFic, DWORD dwNumEnreg);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitdernierbloque(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentbloque(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentbloquesitrouve(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremierbloque(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchebloque(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchebloquenum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech, WORD wSize);

/*-----------------------------------------------------------------------------------------------------------*/
/* Hlitrecherchebloque pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HlitrecherchebloqueWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech );

/*-----------------------------------------------------------------------------------------------------------*/
void HlitrecherchebloqueConv(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech,WORD wSize, BOOL /*bConvert*/);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchebloquesitrouve(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantbloque(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantbloquesitrouve(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hbloquefichier(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebloquefichier(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hbloquetotalfichier(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebloquetotalfichier(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebloquenumenr(LPCSTR pszNomFic, DWORD dwNumEnr);

/*-----------------------------------------------------------------------------------------------------------*/
void Hinterditmodif(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hfininterditmodif(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodeauto(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodesemiperso(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodeperso(BOOL /*bLectureBloquante*/);

/*-----------------------------------------------------------------------------------------------------------*/
/*fonctions de gestion du journal*/
void Hjournalrecree(LPCSTR /*pszNomFic*/);
/*-----------------------------------------------------------------------------------------------------------*/
void Hjournalredemarre(LPCSTR /*pszNomFic*/);
/*-----------------------------------------------------------------------------------------------------------*/
void Hjournalstop(LPCSTR /*pszNomFic*/);
/*-----------------------------------------------------------------------------------------------------------*/
void Hjournalinfo(LPCSTR /*pszNomFic*/, LPSTR /*pszInfo*/);
/*-----------------------------------------------------------------------------------------------------------*/
void Hposte(short nVal);

/*-----------------------------------------------------------------------------------------------------------*/
/*fonctions de gestion des transactions*/
void Htransactiondebut(LPCSTR pszNomLst);

/*-----------------------------------------------------------------------------------------------------------*/
void Htransactionfin(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Htransactionannule(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebutverrou(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hfinverrou(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsansbloquer(LPCSTR pszNomFic, DWORD dwNumEnreg);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitderniersansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentsansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremiersansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchesansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech);

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchesansbloquernum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech, WORD wSize);

/*-----------------------------------------------------------------------------------------------------------*/
/* Hlitrecherchesansbloquer pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HlitrecherchesansbloquerWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech );

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantsansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Hcreationsiinexistant(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hversion(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
short Hsauveposition(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hretourposition (short nCtx);

/*-----------------------------------------------------------------------------------------------------------*/
/*fonction de gestion des filtres*/
LPSTR Hfiltre(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszBorneMin, WORD wSizeMin, LPCSTR pszBorneMax, WORD wSizeMax, LPCSTR pszWhere);

/*-----------------------------------------------------------------------------------------------------------*/
void Hactivefiltre(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hdesactivefiltre(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
void Hchangecle(LPCSTR pszNomFic, LPCSTR pszNomCle);

/*-----------------------------------------------------------------------------------------------------------*/
void Havance(LPCSTR pszNomFic, LPCSTR pszNomCle, DWORD dwNbrEnreg);

/*-----------------------------------------------------------------------------------------------------------*/
void Hrecule(LPCSTR pszNomFic, LPCSTR pszNomCle, DWORD dwNbrEnreg);

/*-----------------------------------------------------------------------------------------------------------*/
DWORD Hpositionne(LPCSTR pszNomFic, LPCSTR pszNomCle, DWORD dwPos, DWORD/* dwPosMax*/);

/*-----------------------------------------------------------------------------------------------------------*/
short Halias(LPCSTR pszNomFic, LPCSTR pszNomAlias, LPCSTR pszAbrAlias);

/*-----------------------------------------------------------------------------------------------------------*/
short Hcopieenreg(LPCSTR pszNomFic, LPCSTR pszNomAlias);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubrique(LPCSTR pszNomFic, short nIndice);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubriquevue(DWORD dwHdlVue, short nIndice);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubriquetout(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubriquetoutvue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hlisteanalyse(LPSTR pszRepInit, LPSTR pszSep);

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlistefichier(NULL, NULL, <flag>)*/
/*         Hlistefichier(<nomwdd>, NULL, <flag>)*/
/*         Hlistefichier(<nomwdd>, <passwd>, <flag>)*/
/**/
LPSTR Hlistefichier(LPCSTR pszNomWDD, LPCSTR pszPasswd, BOOL bFormatLong);

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlisterubrique(<nomfic>, NULL, NULL, <format>)*/
/*         Hlisterubrique(<nomfic>, <nomwdd>, NULL, <format>)*/
/*         Hlisterubrique(<nomfic>, <nomwdd>, <passwd>, <format>)*/
/**/
LPSTR Hlisterubrique(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszPasswd, int nFormat);

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlistecle(<nomfic>, NULL, NULL, <flag>)*/
/*         Hlistecle(<nomfic>, <nomwdd>, NULL, <flag>)*/
/*         Hlistecle(<nomfic>, <nomwdd>, <passwd>, <flag>)*/
/**/
LPSTR Hlistecle(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszPasswd, BOOL bFormatLong);

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlistetrigger(NULL,NULL)*/
/*         Hlistetrigger(<nomfic>, NULL)*/
/*         Hlistetrigger(<nomfic>, <nomwdd>)*/
/**/
LPSTR Hlistetrigger(LPCSTR pszNomFic, LPCSTR pszNomWDD);

void Hversrubrique(LPCSTR pszNomFic, short nIndice, LPSTR pszVal);

/*-----------------------------------------------------------------------------------------------------------*/
void Hraz(LPCSTR pszNomFic);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hlisterep(LPCSTR pszNomFicRep, LPCSTR pszNomFicLog, LPCSTR pszNomFicPhys, short nMode);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hinfofichier(LPCSTR pszNomFic,LPCSTR pszReserved);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hinforubrique(LPCSTR pszNomFic, LPCSTR pszNomRub, int /*nFormat*/);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hinforubriquenum(LPCSTR pszNomFic, short nIndiceRub, int /*nFormat*/);

/*-----------------------------------------------------------------------------------------------------------*/
/* NDX_NORMAL=0, 		:réindexation normale*/
/* NDX_SUPPRESSION=1,	:pour supprimer les enregs endommagés*/
/* NDX_COMPACTAGE=2,	:pour compacter le .FIC*/
/* NDX_MUET=4,			:pour n'afficher aucune jauge ni aucun message*/
/**/
short Hreindexe(LPCSTR pszFicL,LPCSTR pszFicP,LPCSTR pszRepP,short nMode, long /*hWnd*/,LPCSTR /*pszDesc*/);

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlisteliaison(NULL, NULL, NULL)*/
/*         Hlisteliaison(<nomfic>, NULL, NULL)*/
/*         Hlisteliaison(<nomfic>, <nomwdd>, NULL)*/
/*         Hlisteliaison(<nomfic>, <nomwdd>, <passwd>)*/
/**/
LPSTR Hlisteliaison(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszPasswd);

/*-----------------------------------------------------------------------------------------------------------*/
/* <pszFicL> est un nom de fichier logique, c'est le fichier HF destination*/
/* <pszNomTxt> est un nom de fichier texte complet, c'est le fichier source*/
/* <pszListeRub> est la liste des rubriques correspondant aux colonnes du fichier texte*/
/*        format: "rub1+RC+rub2+RC+rub3"*/
/* <pszSep> contient le séparateur de colonnes, de lignes, et le délimiteur de chaînes*/
/*        format: séparateur colonne + Caract(0x7F) + délimiteur de chaînes + Caract(0x7F) +  séparateur  de lignes*/
/* <nMode> = combinaison des valeurs suivantes*/
/*	1:IMP_CREATION		: création du .FIC (écrasement s'il existe déjà)*/
/*	2:IMP_OEM2ANSI		: conversion OEM vers ANSI des chaînes*/
/*	4:IMP_NONEXCLUSIF		: prise de tour à chaque HAjoute*/
/*	8:IMP_TESTDOUBLON		: test des doublons*/
/*	16:IMP_TESTINTEGRITE	: test de l'intégrité*/
/*	32:IMP_SANSDELIMITEUR	: pas de délimiteur de chaines*/
/**/
short Himportetexte(LPSTR pszFicL, LPSTR pszNomTxt, LPSTR pszListeRub, LPSTR pszSep, short nMode, long /*hWnd*/);

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe 0: <nResult>=HAliasExterne(<nomfic>)*/
/*Syntaxe 1: <nResult>=HAliasExterne(<nomfic>,<nomwdd>)*/
/*Syntaxe 2: <nResult>=HAliasExterne(<nomfic>,<nomwdd>,<nomalias>)*/
/**/
/*Renvoie 0 si ok, un code d'erreur sinon:*/
/**/
/* 1 = fichier .WDD introuvable*/
/* 2 = fichier logique existant déjà dans l'analyse en cours*/
/* 3 = alias existant déjà dans l'analyse en cours*/
/* 4 = aucune analyse en cours*/
/* 5 = erreur lors du chargement de la description*/
/**/
short Haliasexterne(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszMotDePasse, LPCSTR pszNomAlias);

/*----------------- Fonctions de gestion des vues -----------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
/*valeurs pour mle mode de création de la vue (combinaison de bits)*/
/**/
/* 1 = pour bloquer les enregs lus dans le fichier principal seulement*/
/* 2 = pour ne garder que les enregs dont les liaisons ont pu être réalisées*/
/* 4 = pour ne pas exécuter la vue dès la création*/
/* 8 = pour prendre son tour 1 seule fois avant d'exécuter la vue*/
/* 16 = pour ne pas vider la vue lors du HExecuteVue (mode ajoût)*/
/**/
DWORD Hcreevue(LPCSTR pszNomFic, LPCSTR pszDescRub, LPCSTR pszRubTri, LPCSTR pszWhere, BYTE byMode, short nTaillePage);

/*-----------------------------------------------------------------------------------------------------------*/
/*Valeur de nOperation:*/
/*	1025 = union de 2 vues*/
/*	1026 = intersection de 2 vues*/
/*	1027 = vue A - intersection de A et B*/
/*	1028 = union exclusive de 2 vues*/
/*  1029 = jointure entre 2 vues*/
/**/
DWORD Hcreevueindirecte(DWORD dwHdlA, DWORD dwHdlB, short nOperation, LPCSTR pszRubTriA, LPCSTR /*pszRubTriB*/);

/*-----------------------------------------------------------------------------------------------------------*/
short Hdetruitvue(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
short Htrivue(DWORD dwHdlVue, short nIndRub, short nSens);

/*-----------------------------------------------------------------------------------------------------------*/
short Hvueversfichier(DWORD dwHdlVue);

/*-----------------------------------------------------------------------------------------------------------*/
short Hexecutevue(DWORD dwHdlVue, LPCSTR pszWhere);

/*-----------------------------------------------------------------------------------------------------------*/
short Heffacevue(DWORD dwHdlVue);

/*----------------- Fonctions de compte-rendu ---------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
long Hnbenr(void);

/*-----------------------------------------------------------------------------------------------------------*/
long Hnumenr(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hendehors(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hactif(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hsup(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Herreur(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Herreurint(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hdoublon(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Herrintegrite(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hdejabloque(void);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hcommentaire(void);

/*-----------------------------------------------------------------------------------------------------------*/
/*Renvoie 0 si le fichier n'a aucun index, une valeur positive sinon*/
/**/
short Htyp(void);

/*-----------------------------------------------------------------------------------------------------------*/
long Hnbsup(void);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hnomfichier(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Htrouve(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hgen(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hlenr(void);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hdesc(void);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hcre(void);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrep(void);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hind(void);

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hext(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hechange(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hmemo(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hjnl(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hnbessais(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hnbessaismessage(void);

/*-----------------------------------------------------------------------------------------------------------*/
short Hniveau(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Herrignore(void);

/*-----------------------------------------------------------------------------------------------------------*/
char Hmodeblocage(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hmodedebug(void);

/*-----------------------------------------------------------------------------------------------------------*/
char Haction(void);

/*-----------------------------------------------------------------------------------------------------------*/
char Hafaire(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hsetnbessais(short nVal);
/*-----------------------------------------------------------------------------------------------------------*/
void Hsetnbessaismessage(short nVal);
/*-----------------------------------------------------------------------------------------------------------*/
void Hseterrignore(BOOL bVal);
/*-----------------------------------------------------------------------------------------------------------*/
void Hseterrormode(short nVal);
/*-----------------------------------------------------------------------------------------------------------*/
void Hsetpasse(LPCSTR pszNomFic, LPSTR pszPasse);
/*-----------------------------------------------------------------------------------------------------------*/
void Hsetnumenr(DWORD dwNumEnr);
/*-----------------------------------------------------------------------------------------------------------*/
void Hsetafaire(char cVal);
/*-----------------------------------------------------------------------------------------------------------*/
void Hsetaction(char cVal);
/*-----------------------------------------------------------------------------------------------------------*/
void Hgeredoublonoui(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgeredoublonnon(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgereintegritenon(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgereintegriteoui(void);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hgerereplication(BOOL bMode);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hgeretrigger(BOOL bMode);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hgereaccesdistant(BOOL bMode);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerejnloui(void);
                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerejnlnon(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgeretrsoui(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgeretrsnon(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerememooui(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerememonon(void);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgererepoui(LPCSTR pszRepFile);

/*-----------------------------------------------------------------------------------------------------------*/
void Hgererepnon(void);

/*---------------- GESTION DES MEMOS ------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
BOOL HGetMemoData(LPCSTR pszNomFic, LPCSTR pszNomRub, LPVOID *ppData, DWORD *pdwSize);

/*-----------------------------------------------------------------------------------------------------------*/
BOOL HSetMemoData(LPCSTR pszNomFic, LPCSTR pszNomRub, LPVOID pData, DWORD dwSize);

/*---------------- FICHIERS DYNAMIQUES ----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
void Hdecritfichier(LPCSTR pszNomFic, LPCSTR pszAbrFic, LPCSTR pszRepFic);

/*-----------------------------------------------------------------------------------------------------------*/
/*
<pszNomFic> est une chaîne de caractères contenant le nom logique du fichier
<pszDescRub> est une chaîne de caractères qui a la forme <Nom Rubrique>,<Type Rubrique>
	<Nom Rubrique> contient le nom logique de la rubrique
	<Type Rubrique> contient le type de la rubrique et peut prendre pour valeur : 

	- E : pour les entier
	- L : pour les entier long
	- C : pour les entier court
	- S : pour les texte réel simple
	- D : pour les réel double
	- A : pour les date sur 8 (AAAAMMJJ)
	- H : pour les heure HHMM
	- T,<Taille> : pour les rubriques texte (<Taille> est la taille de la chaîne de caractères)
	- M : pour les Mémo texte
	- F : pour les monétaire

	Il ne doit pas y avoir d'espace entre <Nom Rubrique> et <Type Rubrique>.

<NIndice> est un entier optionnel qui donne la taille du tableau de rubriques, 0 sinon
*/
void Hdecritrubrique(LPCSTR pszNomFic, LPCSTR pszDescRub, short nIndice);

/*-----------------------------------------------------------------------------------------------------------*/
/*
<pszNomFic> contient le nom du fichier logique
<pszNomCle> contient le nom de la clé (100 caractères maximum)
<pszLstRub> est une chaine de caractères optionnelle contenant la liste des rubriques composant la clé.
	- dans le cas d'une clé composée, dans <pszLstRub> chaque rubrique est séparée par une virgule : 
	<NomRub1>, <NomRub2>, ...
	- dans le cas d'une clé simple, <pszLstRub> contient le nom de la clé.
<Multiple> est un BOOLéen optionnel permettant de savoir si la clé est unique ou multiple : 
	- à Vrai si la clé est multiple (avec doublons)
	- à Faux si la clé est unique
    Par défaut, <Multiple> est à Vrai
*/
void Hdecritcle(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszLstRub, BOOL bMultiple);

/*-----------------------------------------------------------------------------------------------------------*/
void Hdecritliaison(LPCSTR pszNomFic1, LPCSTR pszNomRub1, LPCSTR pszCard1, LPCSTR pszNomFic2, LPCSTR pszNomRub2, LPCSTR pszCard2);

/*-----------------------------------------------------------------------------------------------------------*/
/*Création d'un trigger*/
/*TRIG_AVANT = 1, TRIG_APRES = 2*/
/**/
short Hdecrittrigger(LPCSTR /*pszNomFic*/, LPCSTR /*pszNomFoncHF*/, FARPROC /*pFonc*/, short /*nType*/);

/*-----------------------------------------------------------------------------------------------------------*/
/*Activation, Désactivation ou destruction d'un trigger*/
/**/
short Hannuletrigger(LPCSTR pszNomFic, LPCSTR pszNomFoncHF, short nType, BOOL * /*pbStatus*/);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif


