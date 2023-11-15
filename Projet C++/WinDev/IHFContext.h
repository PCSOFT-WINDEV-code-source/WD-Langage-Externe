// Interface des contextes Hyper File utilisée par le langage externe
// Fichier destiné à être envoyé en clientèle


#ifndef __IHFCONTEXT_H
#define __IHFCONTEXT_H

#include "Proxy.h"
#include "HFConstant.h"		// définition des constantes de la composante WDHF

class IGaugeControl;

#define PROXY_HFContext			71		// le 7 : numéro de la composante WDHF

PROXY_DECLARE_V( HFContext , 94, 69 )

	///////////////////////////////////////////////////////////////////////////
	// Gestion des versions
	PROXY_STDVERSION_METHODS( HFContext )

	///////////////////////////////////////////////////////////////////////////
	// Deréférencer le contexte, si plus de référence, le contexte est détruit
	PROXY_METHOD( UINT_32,	HFContext,	nExternalRelease,		( void ) )

#if !defined(HF_DESACTIVE_LANGEXT)
	///////////////////////////////////////////////////////////////////////////
	// Mettre à jour l'enregistrement en cours de la table sous WDHF
	PROXY_METHOD( BOOL,		HFContext,	bUpdateRecordToWDHF,	( PCXSTR pzTable, LPCVOID pBuffer, XUSIZE32 nSize ) )

	///////////////////////////////////////////////////////////////////////////
	// Mettre à jour l'enregistrement en cours de la table sous le langage externe
	PROXY_METHOD( BOOL,		HFContext,	bUpdateRecordFromWDHF,	( PCXSTR pzTable, LPVOID pBuffer, XUSIZE32 nSize ) )
#else //!defined(HF_DESACTIVE_LANGEXT)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_LANGEXT)

	///////////////////////////////////////////////////////////////////////////
	// Récupérer la dernière table utilisée
	PROXY_METHOD( void,		HFContext,	GetLastUsedTable,		( PXSTR pzTable ) const )

	///////////////////////////////////////////////////////////////////////////
	// Libérer un buffer alloué par Hyper File (ppBuffer et *ppBuffer peuvent être NULL)
	PROXY_METHOD( void,		HFContext,	FreeMemory,				( PVOID* ppBuffer ) const )

#ifndef WDHF_SERVER
	///////////////////////////////////////////////////////////////////////////
	// Définir le nom de la dll Hyper File 55 32bits à utiliser 
	PROXY_METHOD( BOOL,		HFContext,  bSetWDHF5Name,			( PCXSTR pzWDHF5Name ) )
#else
	PROXY_EMPTY_METHOD( HFContext )
#endif // !WDHF_SERVER

	///////////////////////////////////////////////////////////////////////////
	// Définir le contenu d'une rubrique mémo
	PROXY_METHOD( BOOL,		HFContext,	bSetMemoData,			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pData, XUSIZE32 nSize ) )
	// Récupérer un pointeur const sur les données du mémo de l'enregistrement en cours
	// (pour les mémos textes, pas de 0 final), taille renvoyé en octets (attention à l'unicode)
	PROXY_METHOD( BOOL,		HFContext,	bGetMemoData,			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID *ppData, XUSIZE32 *pnSize ) )

	// Renvoie TRUE si il y a une erreur, FALSE sinon
	// Ne touche à aucun flag interne à la DLL Hyper File
	// Utilisé uniquement par la casse CVHFContext
	PROXY_METHOD( BOOL,		HFContext,	bError,					( void ) )

	///////////////////////////////////////////////////////////////////////////
	// Fonctions WLangage
	PROXY_METHOD( BOOL,		HFContext,	bHActiveFiltre,			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHAjoute,				( PCXSTR pzTable=NULL, UINT nWriteFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHAlias,				( PCXSTR pzTable, PCXSTR pzAlias, PCXSTR pzAbrev=NULL ) )
	// Ferme et annule un alias
	PROXY_METHOD( BOOL,		HFContext,	bHAnnuleAlias,			( PCXSTR pzAlias ) )
	PROXY_METHOD( BOOL,		HFContext,	bHAnnuleDeclaration,	( PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHAnnuleRecherche,		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHAttacheMemo,			( PCXSTR pzTable, PCXSTR pzItem, PCXSTR pzFilename, eHMEMOTYPE eType=HMEMOTYPEBIN , PCXSTR pszUserInfo=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHAvance,				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, RECNUM llStep=1, UINT nFlags=HPARSEMODEDEFAULT ) )
#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHBloqueFichier,		( PCXSTR pzTable=NULL, eHPARSEMODE eMode=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHBloqueNumEnr,			( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, eHPARSEMODE eMode=HPARSEMODEDEFAULT ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHChangeCle,			( PCXSTR pzTable, PCXSTR pzItem, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHChangeNom,			( PCXSTR pzTable, PCXSTR pzFile ) )
	PROXY_METHOD( BOOL,		HFContext,	bHChangeRep,			( PCXSTR pzTable, PCXSTR pzDir ) )
#if !defined(HF_DESACTIVE_ACCESNATIFS) && !defined(WDHF_SERVER)
	PROXY_METHOD( BOOL,		HFContext,	bHPrepareRequeteSQL,	( PCXSTR pzQuery, PCXSTR pszConnection, int nMode, PCXSTR pzSelect ) )
#else //!defined(HF_DESACTIVE_ACCESNATIFS) && !defined(WDHF_SERVER)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_ACCESNATIFS) || defined(WDHF_SERVER)
	PROXY_METHOD( BOOL,		HFContext,	bHConstruitValCle,		( PVOID *ppKey, PCXSTR pzTable, PCXSTR pzComposedKey, va_list arg_ptr ) )
	PROXY_METHOD( BOOL,		HFContext,	bHCopieEnreg,			( PCXSTR NomFicDest, PCXSTR NomFicSource, PCXSTR RubriqueDest=NULL, PCXSTR RubriqueSource=NULL, DWORD flags=HCOPYRECORDDEFAULT))
	PROXY_METHOD( BOOL,		HFContext,	bHCreation,				( PCXSTR pzTable, PCXSTR pzPassword=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHCreationSiInexistant,	( PCXSTR pzTable=NULL, PCXSTR pzPassword=NULL ) )
#if !defined HF_DESACTIVE_LANGEXT && !defined HF_DESACTIVE_CREATION_STRUCTURES
	PROXY_METHOD( BOOL,		HFContext,	bHCreeStructureExterne,	( PCXSTR pszFilePath , PCXSTR pszWDDPath , PCXSTR pszWDDPassword , eHEXLANGTYPE eExLangType , BOOL bFormat ) )
#else //!defined HF_DESACTIVE_LANGEXT && !defined HF_DESACTIVE_CREATION_STRUCTURES
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined HF_DESACTIVE_LANGEXT && !defined HF_DESACTIVE_CREATION_STRUCTURES
	PROXY_METHOD( BOOL,		HFContext,	bHCreeVue,				( PCXSTR pzSnapShot, PCXSTR pzTable=NULL, PCXSTR pzListItems=ALLITEMS, PCXSTR pzSortingItem=NULL, PCXSTR pzCondition=NULL, int nMode=HVIEWDEFAULT, XUSIZE32 nPageSize=0 ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDeclare,				( PCXSTR pzTable, PCXSTR pzWDD, PCXSTR pzWDDPassword=NULL, PCXSTR pzAlias=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDeclareExterne,		( PCXSTR pzFullName, PCXSTR pzAlias, PCXSTR pszPassword=NULL ) )
#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHDebloqueFichier,		( PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDebloqueNumEnr,		( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHDernier,				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDesactiveFiltre,		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDetruitVue,			( PCXSTR pzSnapShot ) )
	PROXY_METHOD( BOOL,		HFContext,	bHEcrit,				( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, UINT nWriteFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHEffaceVue,			( PCXSTR pzSnapShot ) )
	PROXY_METHOD( BOOL,		HFContext,	bHEffaceVueIndex,		( PCXSTR pzSnapShot ) )
	PROXY_METHOD( BOOL,		HFContext,	bHEnDehors,				( BOOL *pbHOut, PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHErreur,				( int *pnError, eHERRORPARSE eErrorParse=HEP_CURRENT ) )
#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHErreurBlocage,		( BOOL *pbError ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHErreurDoublon,		( BOOL *pbError ) )
	PROXY_METHOD( BOOL,		HFContext,	bHErreurInfo,			( PXSTR *ppzErrorInfo, eHERRORINFO eErrorInfo=HEI_INFO ) )
	PROXY_METHOD( BOOL,		HFContext,	bHErreurIntegrite,		( BOOL *pbError ) )
	// Savoir s'il y a eu une erreur de mot de passe
	PROXY_METHOD( BOOL,		HFContext,	bHErreurMotDePasse,		( BOOL *pbError ) )
	// gestion des espaces
	PROXY_METHOD( BOOL,		HFContext,	bEspaceSignificatif,	( BOOL* pbOldValue, PCXSTR pzTable, PCXSTR pzItem, BOOL bSpace ) )
	PROXY_METHOD( BOOL,		HFContext,	bHEtat,					( eHRECORDSTATE* peHRecordState , PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM  ) )
	PROXY_METHOD( BOOL,		HFContext,	bHExecuteVue,			( PCXSTR pzSnapShot, PCXSTR pzCondition ) )
#if !defined(HF_DESACTIVE_XML)
	// Exporter
	PROXY_METHOD( BOOL,		HFContext,	bHExporteXML,			( PCXSTR pszTable , PCXSTR pszFilename=NULL , PCXSTR pszItemList=ALLITEMS, UINT nFlags=HEXPNORMAL, IGaugeControl* piGauge=NULL ) )
#else // !defined(HF_DESACTIVE_XML)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_XML)
	
	PROXY_METHOD( BOOL,		HFContext,	bHExtraitMemo,			( PCXSTR pzTable, PCXSTR pzItem, PCXSTR pzFilename=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHFerme,				( PCXSTR pzTable=NULL ) )
	// Fermer l'analyse en cours
	PROXY_METHOD( BOOL,		HFContext,	bHFermeAnalyse,			( void ) )
	// Poser un filtre
	// Si nMin=HDEFAULTSIZE alors la taille utile de pMin est calculée ainsi :
	//    si pMin=NULL alors nMin=0
	//    sinon, si la rubrique est de type texte, nMin=strlen(pMin)
	//    sinon nMin=taille de la rubrique
	// Idem pour nMax
	PROXY_METHOD( BOOL,		HFContext,	bHFiltre,				( PXSTR *ppzParsingItem, PCXSTR pzTable, PCXSTR pzItem, LPCVOID pMin, int nMin=HDEFAULTSIZE, LPCVOID pMax=NULL, int nMax=HDEFAULTSIZE, PCXSTR pzCondition=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHFiltreCondition,		( PXSTR *ppzParsingItem, PCXSTR pzTable, PCXSTR pzCondition ) )
	// savoir si une table existe sur disque
	PROXY_METHOD( BOOL,		HFContext,	bHFichierExiste,		( PCXSTR pzTable , BOOL* pbExists ) )
	PROXY_METHOD( BOOL,		HFContext,	bHFichierPosition,		( PXSTR pzTable, UINT nSize, HPOS hPosition ) )
	PROXY_METHOD( BOOL,		HFContext,	bHFusionneVue,			( PCXSTR pzSnapShot, PCXSTR pzView1, PCXSTR pzView2, int nOperation, PCXSTR pzSortingItem1=NULL, PCXSTR pzSortingItem2=NULL, int nMode=HVIEWDEFAULT, XUSIZE32 nPageSize=0 ) )
	PROXY_METHOD( BOOL,		HFContext,	bHGereDoublon,			( BOOL *pbOldValue, PCXSTR pzTable, PCXSTR pzItem, BOOL bCheckDuplicates ) )
	PROXY_METHOD( BOOL,		HFContext,	bHGereIntegrite,		( BOOL *pbOldValue, PCXSTR pzRelation, PCXSTR pzTable, DWORD dwRules, BOOL bCheckIntegrity ) )
#if !defined(HF_DESACTIVE_JNLRPL)
	// gestion du journal
	PROXY_METHOD( BOOL,		HFContext,	bHGereJournal,			( BOOL *pbOldValue, BOOL bManageJnl, PCXSTR psFile=NULL ) )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL)
	PROXY_METHOD( BOOL,		HFContext,	bHGereMemo,				( eHMEMO *peOldValue, PCXSTR pzTable, PCXSTR pzItem, eHMEMO eMemo ) )
#if !defined(HF_DESACTIVE_REP)
	// Activer/Désactiver la gestion du .REP
	PROXY_METHOD( BOOL,		HFContext,	bHGereREP,				( BOOL *pbOldValue, BOOL bManageREP, PCXSTR pzREPDirectory=NULL, PCXSTR pzREPFile=NULL ) )
#else //!defined(HF_DESACTIVE_REP)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_REP)
#if !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_HF5)
	PROXY_METHOD( BOOL,		HFContext,	bHImporteHF55,			( PCXSTR pszTable, PCXSTR pszTableHF5, PCXSTR pszPathHF5, PCXSTR pszPasswordHF5, PCXSTR pszWDD5, PCXSTR pszWDD5Password=NULL, PCXSTR pszItemList=NULL, PCXSTR pszItemListHF5=NULL, UINT nFlags=HIMPNORMAL, IGaugeControl *piGauge=NULL ) )
#else // !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_HF5)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(WDHF_SERVER) || defined(HF_DESACTIVE_HF5)
#if !defined(HF_DESACTIVE_IMPORTETEXTE)
	PROXY_METHOD( BOOL,		HFContext,	bHImporteTexte,			( PCXSTR pszTable , PCXSTR pszFilename , PCXSTR pszItemList=ALLITEMS, PCXSTR pszSeparator=DEFAULT_IMPORTSEPARATOR, UINT nFlags=HIMPNORMAL, IGaugeControl *piGauge=NULL ) )
#else //!defined(HF_DESACTIVE_IMPORTETEXTE)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_IMPORTETEXTE)
	//--- Initialiser les variables HF55 ---
	PROXY_METHOD( BOOL,		HFContext,	bHInfoGene,				( PCXSTR pszTable ) )
#if !defined(XVER_POCKET)
	PROXY_METHOD( BOOL,		HFContext,	bHInfoIndex,			( PCXSTR pzFileDest, PCXSTR pzTable=NULL ) )
#else //!defined(XVER_POCKET)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(XVER_POCKET)
	// récupération d'informations sur un mémo binaire
	PROXY_METHOD( BOOL,		HFContext,	bHInfoMemo,				( PXSTR *ppzInfo, PCXSTR pzTable, PCXSTR pzItem ) )
	PROXY_METHOD( BOOL,		HFContext,	bHExecuteRequeteSQL,	( PCXSTR pzQuery, PCXSTR pszConnection, int nMode, PCXSTR pzSelect ) )
	// description de rubrique
	PROXY_METHOD( BOOL,		HFContext,	bHInfoRubrique,			(PXSTR* pzInfo, PCXSTR pzTable, PCXSTR pzItemName) )
	PROXY_METHOD( BOOL,		HFContext,	bHInfoRubrique,			(PXSTR* pzInfo, PCXSTR pzTable, int nItemIndice) )
	// Libérer les enregistrements rayés
	PROXY_METHOD( BOOL,		HFContext,	bHLibere,				( PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLiberePosition,		( HPOS hPosition ) )
	// Récupérer la liste des analyses
	PROXY_METHOD( BOOL,		HFContext,	bHListeAnalyse,			( PXSTR *ppzList, PCXSTR pzPath, PCXSTR pzSep=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHListeCle,				( PXSTR* ppzDesc, PCXSTR pzTable, UINT nFlags=HLSTNORMAL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHListeCle,				( PXSTR* ppzDesc, PCXSTR pzTable, PCXSTR pzWDD, PCXSTR pzWDDPassword, UINT nFlags=HLSTNORMAL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHListeFichier,			( PXSTR* ppzDesc, UINT nFlags=HLSTNORMAL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHListeFichier,			( PXSTR* ppzDesc, PCXSTR pzWDD, PCXSTR pzWDDPassword, UINT nFlags=HLSTNORMAL ) )
	// Récupérer la liste des liaisons
	PROXY_METHOD( BOOL,		HFContext,	bHListeLiaison,			( PXSTR *ppzList, PCXSTR pzTable=NULL, PCXSTR pzWDD=NULL, PCXSTR pzPassword=NULL, UINT nFlags=HLSTNORMAL ) )
#if !defined(HF_DESACTIVE_REP)
	// Récupérer la liste des affectations des fichiers
	PROXY_METHOD( BOOL,		HFContext,	bHListeREP,				( PXSTR* ppzList, PCXSTR pzREPWDD=NULL, PCXSTR pzTable=NULL, PCXSTR pzFile=NULL, UINT nFlags=HREPDEFAULT ) )
#else //!defined(HF_DESACTIVE_REP)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_REP)
	PROXY_METHOD( BOOL,		HFContext,	bHListeRubrique,		( PXSTR* ppzDesc, PCXSTR pzTable, UINT nFlags=HLSTNORMAL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHListeRubrique,		( PXSTR* ppzDesc, PCXSTR pzTable, PCXSTR pzWDD, PCXSTR pzWDDPassword, UINT nFlags=HLSTNORMAL ) )
	// compatibilité HF5
	PROXY_METHOD( BOOL,		HFContext,	bHListeTrigger,			( PXSTR* ppzList, PCXSTR pzTable=NULL, PCXSTR pszWDDPath=NULL, PCXSTR pszPassword=NULL, UINT nFlags=HLSTNORMAL) )
	PROXY_METHOD( BOOL,		HFContext,	bHLit,					( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitDernier,			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitPrecedent,			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitPremier,			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
	// Si nValue=HDEFAULTSIZE alors la taille utile de pValue est calculée ainsi :
	//    si pValue=NULL alors nValue=0
	//    sinon, si la rubrique est de type texte, nValue=strlen(pValue)
	//    sinon nValue=taille de la rubrique
	PROXY_METHOD( BOOL,		HFContext,	bHLitRechercheDernier,	( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitRecherchePremier,	( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitSuivant,			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHMode,					( eHMODE *peOldValue, PCXSTR pzTable, eHMODE eMode, eHLOCKMETHOD eLockMethod=HLOCKMETHODDIRECT ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHModifie,				( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM , UINT nWriteFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHNbEnr,				( RECNUM *pllHNbEnr, PCXSTR pzTable=NULL , DWORD dwStates=HSTATEACTIVE ) )
	PROXY_METHOD( BOOL,		HFContext,	bHNumEnr,				( RECNUM *pllHNumEnr, PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHNumEnrPosition,		( RECNUM* pllRecNum, HPOS hPosition ) )
	PROXY_METHOD( BOOL,		HFContext,	bHOuvre,				( PCXSTR pzTable=NULL, PCXSTR pzPassword=NULL, eHACCESS eAccess=HODEFAULT ) )
//	PROXY_METHOD( BOOL,		HFContext,	bHOuvreAnalyse,			( PCXSTR pzAnalysis, PCXSTR pzPassword=NULL, PCXSTR pzServerAddress=NULL, PCXSTR pzUserName=NULL, PCXSTR pzNetworkPassword=NULL) )
	PROXY_METHOD( BOOL,		HFContext,	bHOuvreAnalyse,			( PCXSTR pzAnalysis, PCXSTR pzPassword=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHPasse,				( PCXSTR pzTable, PCXSTR pzPassword=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHPositionCourante,		( int *pnPos, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, eHPRECISION ePrecision=HPRECISIONMEDIUM ) )
	PROXY_METHOD( BOOL,		HFContext,	bHPositionne,			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nPos=1, eHPRECISION ePrecision=HPRECISIONMEDIUM ) )
	// gestion du journal
#if !defined(HF_DESACTIVE_JNLRPL)
	PROXY_METHOD( BOOL,		HFContext,	bHPoste,				( UINT nPoste ) )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL)
	PROXY_METHOD( BOOL,		HFContext,	bHPrecedent,			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHPremier,				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRaye,					( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, UINT nWriteFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRAZ,					( PCXSTR pzTable=NULL, PCXSTR pzItem=ALLITEMS ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRechercheDernier,		( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRecherchePremier,		( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRecule,				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, RECNUM llStep=1, UINT nFlags=HPARSEMODEDEFAULT ) )
	// Récupérer le contenu de tout l'enregistrement
	PROXY_METHOD( BOOL,		HFContext,	bHRecupereEnregistrement,( PXSTR *ppzValue, PCXSTR pzTable=NULL, PCXSTR pzItemSep=NULL, PCXSTR pzSubItemSep=NULL ) )
	// Récupérer le contenu d'une rubrique
	PROXY_METHOD( BOOL,		HFContext,	bHRecupereRubrique,		( PXSTR *ppzValue, PCXSTR pzTable, UINT nNumItem, int nIndItem=INVALID_ITEMINDEX, PCXSTR pzSubItemSep=NULL ) )
#if !defined(HF_DESACTIVE_JNLRPL)
	// régénération du fichier à partir du journal
	PROXY_METHOD( BOOL,		HFContext,	bHRegenereFichier,		( PCXSTR pszJnlFile , PCXSTR pszPassword=NULL, PCXSTR pszDstPath=NULL , UINT nOptions=0 , PCXSTR pszFromDate=NULL, PCXSTR pszToDate=NULL , IGaugeControl *piGaugeRestore=NULL, IGaugeControl *piGaugeReindexe=NULL) )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
#endif //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_METHOD( BOOL,		HFContext,	bHReindexe,				( PCXSTR pzTable=NULL, PCXSTR pzFileName=NULL, PCXSTR pzPath=NULL, eHNDXMODE eNdxMode=HNDXNORMAL, IGaugeControl *piGauge=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRetourPosition,		( HPOS hPosition, UINT nFlags=HRPDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHSauvePosition,		( HPOS *phPosition, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHStatCalcule,			( PCXSTR pzTable=NULL, PCXSTR pzItem=ALLITEMS, int nNbStep=-1 ) )
	PROXY_METHOD( BOOL,		HFContext,	bHStatDate,				( PXSTR* ppzDate, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHStatHeure,			( PXSTR* ppzTime, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHStatNbDoublon,		( RECNUM *pllNbDuplicates, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHStatNbEnr,			( RECNUM *pllNbRec, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	// Si nValue=HDEFAULTSIZE alors la taille utile de pValue est calculée ainsi :
	//    si pValue=NULL alors nValue=0
	//    sinon, si la rubrique est de type texte, nValue=strlen(pValue)
	//    sinon nValue=taille de la rubrique
	PROXY_METHOD( BOOL,		HFContext,	bHStatNbEnrIntervalle,	( RECNUM *pllNbRec, PCXSTR pzTable, PCXSTR pzItem, LPCVOID pMin, int nMin, LPCVOID pMax, int nMax ) )
	PROXY_METHOD( BOOL,		HFContext,	bHSubstRep,				( PCXSTR pzLogicalDir, PCXSTR pzPhysicalDir ) )
	PROXY_METHOD( BOOL,		HFContext,	bHSuivant,				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT ) )
	PROXY_METHOD( BOOL,		HFContext,	bHSupprime,				( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM ) )
	PROXY_METHOD( BOOL,		HFContext,	bHTrieVue,				( PCXSTR pzSnapShot, PCXSTR pzItem ) )
	PROXY_METHOD( BOOL,		HFContext,	bHTrouve,				( BOOL *pbHFound, PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHVerifieIndex,			( int* nResult, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, IGaugeControl *piGauge=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHVersion,				( int *pnVersion, PCXSTR pzTable=NULL ) )
	// Définir le contenu d'une rubrique
	PROXY_METHOD( BOOL,		HFContext,	bHVersRubrique,			( PCXSTR pzTable, UINT nNumItem, int nIndItem, PCXSTR pzSubItemSep, PCXSTR pzValue ) )
	PROXY_METHOD( BOOL,		HFContext,	bHVueVersFichier,		( PCXSTR pzSnapShot ) )

	///////////////////////////////////////////////////////////////////////////////
	// compatibilité HF55
	PROXY_METHOD( BOOL,		HFContext,	bHCopieEnreg_55,		( int* pnResult, PCXSTR pzNomFicDest, PCXSTR pzNomFicSource, BOOL bIdAutoCopy=FALSE ))

#if !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_HF5)
	PROXY_METHOD( BOOL,		HFContext,	bHDecritCle_55,			( PCXSTR pzLogicalName, PCXSTR pzKeyName, PCXSTR pzItemList=NULL, BOOL bDuplicates=TRUE ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDecritFichier_55,		( PCXSTR pzLogicalName, PCXSTR pzAbrev, PCXSTR pzDefaultDirectory=CURRENTDIR ) )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_METHOD( BOOL,		HFContext,	bHDecritRubrique_55,	( PCXSTR pszTable, PCXSTR pszItem, int nDimension=1 ) )
#else
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(WDHF_SERVER) || defined(HF_DESACTIVE_HF5)

	PROXY_METHOD( BOOL,		HFContext,	bHNbEnr_55,				( RECNUM *pllHNbRaye, PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHNbSup_55,				( RECNUM *pllHNbSup, PCXSTR pzTable=NULL ) )
#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHDejaBloque,			( BOOL *pbError ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHDoublon,				( BOOL *pbError ) )
	PROXY_METHOD( BOOL,		HFContext,	bHReindexe_55,			( int* pnResult, PCXSTR pzTable=NULL, PCXSTR pzFileName=NULL, PCXSTR pzPath=NULL, eHNDXMODE eNdxMode=HNDXNORMAL, IGaugeControl *piGauge=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHCreeVue_55,			( int* pnIdVue, PCXSTR pzTable=NULL, PCXSTR pzListItems=ALLITEMS, PCXSTR pzSortingItem=NULL, PCXSTR pzCondition=NULL, int nMode=HVIEWDEFAULT, XUSIZE32 nPageSize=0 ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRetourPosition_55,	( PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHTrieVue_55,			( PCXSTR pzSnapShot, UINT nItemIndice, BOOL bAscendant=TRUE ) )
#if !defined(HF_DESACTIVE_IMPORTETEXTE)
	PROXY_METHOD( BOOL,		HFContext,	bHImporteTexte_55,		( int* pnResult, PCXSTR pszTable , PCXSTR pszFilename , PCXSTR pszItemList=ALLITEMS, PCXSTR pszSeparator=DEFAULT_IMPORTSEPARATOR, UINT nFlags=HIMPNORMAL, IGaugeControl *piGauge=NULL ) )
#else //!defined(HF_DESACTIVE_IMPORTETEXTE)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_IMPORTETEXTE)
#if !defined(HF_DESACTIVE_FONCCOMPAT55)
	PROXY_METHOD( BOOL,		HFContext,	bHAlias_55,				( int* pnResult, PCXSTR pzTable, PCXSTR pzAlias=NULL, PCXSTR pzAbrev=NULL ) )
#else //!defined(HF_DESACTIVE_FONCCOMPAT55)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCCOMPAT55)
	PROXY_METHOD( BOOL,		HFContext,	bHCreeVueDeVue_55,		( int* pnIdVue, int nSnapShotIdA, int nSnapShotIdB, int nOperationType, PCXSTR pszSortItem=NULL ) )
	
	///////////////////////////////////////////////////////////////////////////
	// Ajouter une référence au contexte, il faudra appeler Release plus tard pour rendre la référence
	// Note :
	// Lorsque HF renvoie un contexte soit par WLL_pQueryOtherProxy, soit par le copie de contexte du IHFManager,
	// une référence est automatiquement mise sur le contexte, il suffit de faire un Release pour le libérer.
	PROXY_METHOD( void,		HFContext,	ExternalAddRef,			( void ) )

	
	PROXY_METHOD( BOOL,		HFContext,	bHSubstNom,				( PCXSTR pzTable, PCXSTR pzFile ) )
	PROXY_METHOD( BOOL,		HFContext,	bHAssigne,				( PCXSTR pzTable, PCXSTR pzDir ) )

#if !defined(HF_DESACTIVE_HCONVERT)
	// pour compatibilité HF5 : Conversion de valeurs numériques en chaines
	PROXY_METHOD( BOOL,		HFContext,	bHConvertC,				( BYTE* pbyResult, BYTE nValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertD,				( BYTE* pbyResult, double dValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertE,				( BYTE* pbyResult, short nValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertL,				( BYTE* pbyResult, INT_32 nValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertM,				( BYTE* pbyResult, void* pcyValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertP,				( BYTE* pbyResult, void* pfValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertR,				( BYTE* pbyResult, float fValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertU,				( BYTE* pbyResult, short nValue) )
	PROXY_METHOD( BOOL,		HFContext,	bHConvertV,				( BYTE* pbyResult, char cValue) )
#else //!defined(HF_DESACTIVE_HCONVERT)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_HCONVERT)

#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHLitBloque,			( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitDernierBloque,		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitDernierSansBloquer,( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitPrecedentBloque,	( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitPrecedentSansBloquer,( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitPremierBloque,		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitPremierSansBloquer,( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)

	PROXY_METHOD( BOOL,		HFContext,	bHLitRecherche,			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE ) )
	
#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHLitRechercheBloque,	( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitRechercheSansBloquer,( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitSansBloquer,		( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitSuivantBloque,		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHLitSuivantSansBloquer,( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)
	
	PROXY_METHOD( BOOL,		HFContext,	bHRecherche,			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE ) )
	
#if !defined(HF_DESACTIVE_FONCLOCK)
	PROXY_METHOD( BOOL,		HFContext,	bHRechercheBloque,		( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE ) )
	PROXY_METHOD( BOOL,		HFContext,	bHRechercheSansBloquer,	( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)
	
#if !defined(HF_DESACTIVE_MIGRECLECOMP)
	PROXY_METHOD( BOOL,		HFContext,	bHMigreCleComposeeReliee, ( PCXSTR pszOriginalTable, PCXSTR pszOriginalItem, PCXSTR pszLinkedTable, PCXSTR pszLinkedItem, IGaugeControl* piGauge=NULL  ) )
#else // !defined(HF_DESACTIVE_MIGRECLECOMP)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_MIGRECLECOMP)
	
	// description de trigger
	PROXY_METHOD( BOOL,		HFContext,	bHActiveTrigger,		( PCXSTR pszFileNameList=NULL, PCXSTR pszFctNameList=NULL, int nType=0 ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDetruitTrigger,		( PCXSTR pszFileNameList=NULL, PCXSTR pszFctNameList=NULL, int nType=0 ) )

#if !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_RPC)
	// gestion de l'accès distant
	PROXY_METHOD( BOOL,		HFContext,	bHGereAccesDistant,		( int* nOldMode, int mode ) )
#else // !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_RPC)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(WDHF_SERVER) || defined(HF_DESACTIVE_RPC)

#if !defined(HF_DESACTIVE_TRANSACTION)
	// transactions
	PROXY_METHOD( BOOL,		HFContext,	bHTransactionLibere,	( PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHGereTransaction,		( PCXSTR pzTable=NULL, BOOL bMode=TRUE ) )
	PROXY_METHOD( BOOL,		HFContext,	bHTransactionDebut,		( PCXSTR pzTable=NULL, PCXSTR pzFileList=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHTransactionFin,		( void ) )
	PROXY_METHOD( BOOL,		HFContext,	bHTransactionAnnule,	( PCXSTR pszNomFichierTRS=NULL ) )
#else //!defined(HF_DESACTIVE_TRANSACTION)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_TRANSACTION)

#if !defined(HF_DESACTIVE_FONCLOCK)
	// accès
	PROXY_METHOD( BOOL,		HFContext,	bHInterditModif,		( PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHFinInterditModif,		( PCXSTR pzTable=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHDebutVerrou,			( void ) )
	PROXY_METHOD( BOOL,		HFContext,	bHFinVerrou,			( void ) )
#else //!defined(HF_DESACTIVE_FONCLOCK)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_FONCLOCK)

	// sécurité
	PROXY_METHOD( BOOL,		HFContext,	bHSecurite,				( int* pnOldValue, PCXSTR pszTable, int nLevel ) )
	
	// déclaration de fichiers externes
	PROXY_METHOD( BOOL,		HFContext,	bHAliasExterne,			( int* pnResult, PCXSTR pzTable, PCXSTR pszWDDFullName, PCXSTR pszPassword=NULL, PCXSTR pszAliasName=NULL) )

	// gestion des trigger
	PROXY_METHOD( BOOL,		HFContext,	bHGereTrigger,			( int* peOldValue, int gestion ) )

#if !defined(HF_DESACTIVE_XML) && !defined(HF_DESACTIVE_XMLDLL)
	PROXY_METHOD( BOOL,		HFContext,	bHImporteXML,			( PCXSTR pszTable , PCXSTR pszFilename=NULL , PCXSTR pszItemList=ALLITEMS,  PCXSTR pszAttrList=ALLITEMS, UINT nFlags=HIMPNORMAL, IGaugeControl* piGauge=NULL ) )
#else // !defined(HF_DESACTIVE_XML) && !defined(HF_DESACTIVE_XMLDLL)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_XML) && !defined(HF_DESACTIVE_XMLDLL)

	// description de trigger
	PROXY_METHOD( BOOL,		HFContext,	bHDesactiveTrigger,		( PCXSTR pszFileNameList=NULL, PCXSTR pszFctNameList=NULL, int nType=0 ) )

	// Renvoie le nombre d'essais de blocage
	PROXY_METHOD( BOOL,		HFContext,	bHNbEssais,				( int* pnOldNbRetry, PCXSTR pzTable, int nNbRetry ) )

	// Le HDéclareExterne sur les bases OLEDB
	PROXY_METHOD( BOOL,		HFContext,	bHDeclareExterneOLEDB,	( PCXSTR pszTableName, PCXSTR pszAlias, PCXSTR pszUser, PCXSTR pszPassword, PCXSTR pszDataSource, PCXSTR pszProvider, eHACCESS eAccess=HOREADWRITE ) )


#if !defined(HF_DESACTIVE_CONNECTION)
//----------------- A C C E S   N A T I F  ----------------------------------//
	// Redefinition des paramètres de la connexion en Accès Natif
	PROXY_METHOD( BOOL,		HFContext,	bHConnecte,				( PCXSTR pzTable, PCXSTR pzUser=NULL, PCXSTR pzPassword=NULL, PCXSTR pzSource=NULL, PCXSTR pzProvider=NULL, eHACCESS eAccess=HOREADWRITE, eHTESTOPERATION eOperation=HCUNSPECIFIED, PXSTR * ppsztabParam=NULL, int nNbParam=0) )
#else //!defined(HF_DESACTIVE_CONNECTION)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_CONNECTION)

#if !defined(HF_DESACTIVE_JNLRPL_C) && !defined(WDHF_SERVER)
	// récupérer le chemin complet du fichier de sauvegarde du fichier spécifié
	// paramètres :
	//    pszSaveFilePath (sortie) : buffer de taille XMAXPATH+1 = nom du fichier de sauvegarde
	//    pszFilePath : nom complet du fichier journalé
	PROXY_METHOD( BOOL,		HFContext,	bGetPathJnlSave,		(PXSTR pszSaveFilePath, PCXSTR pszFilePath) )

	// Archiver le fichier journal du fichier spécifié
	// paramètres :
	//    pszFullFileName : nom complet du fichier journalé
	//    pszBackupPath : emplacement du backup du fichier de sauvegarde
	PROXY_METHOD( BOOL,		HFContext,	bBackupJnlSave,			(PCXSTR pszFullFileName, PCXSTR pszBackupPath) )

	// Détruire le fichier journal du fichier spécifié
	// paramètres :
	//    pszFilePath : nom complet du fichier journalé
	PROXY_METHOD( BOOL,		HFContext,	bDeleteJnlSave,			(PCXSTR pszFullFileName) )
#else //!defined(HF_DESACTIVE_JNLRPL_C) && !defined(WDHF_SERVER)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL_C) && !defined(WDHF_SERVER)

//----------------- F O N C T I O N S   D B A S E ---------------------------//
	
#if !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_XBASE)
	// Crée un fichier décrit avec HDBDecritFichier
	PROXY_METHOD( BOOL,		HFContext,	bHDBCreation,			( void ) )

	// Décrit un fichier au format xBase (dBase 3)
	PROXY_METHOD( BOOL,		HFContext,	bHDBDecritFichier,		( PCXSTR pszTable, PCXSTR pszAbbreviation, PCXSTR pszCompleteName ) )
	
	// Décrit le fichier d'index d'un fichier xBase (dBase 3) décrit avec HDBDecritFichier
	PROXY_METHOD( BOOL,		HFContext,	bHDBDecritIndex,		( PCXSTR pszCompleteIndexName, PCXSTR pszKeyName, PCXSTR pszKeyCompExpression=NULL) )
	
	// Décrit la structure d'un fichier xBase décrit avec HDBDecritFichier
	PROXY_METHOD( BOOL,		HFContext,	bHDBDecritRubrique,		( PCXSTR pszItemName ) )
	
	// Ouvre un fichier d'index xBase
	PROXY_METHOD( BOOL,		HFContext,	bHDBIndex,				( PCXSTR pszTable, PCXSTR pszCompleteIndexName , PCXSTR pszKeyName=NULL ) )
	
	// Ouvre un fichier de données xBase
	PROXY_METHOD( BOOL,		HFContext,	bHDBOuvre,				( PCXSTR pszTable, PCXSTR pszAbbreviation, PCXSTR pszCompleteName ) )
	
	// Ouvre un fichier de données xBase sans le bloquer en mode automatique
	PROXY_METHOD( BOOL,		HFContext,	bHDBOuvreSansBloquer,	( PCXSTR pszTable, PCXSTR pszAbbreviation, PCXSTR pszCompleteName ) )
	
	// Modifie la relation d'ordre des rubriques texte dans les fichier xBase
	PROXY_METHOD( BOOL,		HFContext,	bHDBTypeTri,			( int* pnOldType, int nType=HDBDONOTSETSORTTYPE ) )
#else //!defined(WDHF_SERVER) && !defined(HF_DESACTIVE_XBASE)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(WDHF_SERVER) || defined(HF_DESACTIVE_XBASE)

#if !defined(HF_DESACTIVE_ACCESNATIFS)
	// Lister les fichiers d'une connexion (Accès natif)
	PROXY_METHOD( BOOL,		HFContext,	bHListeFichierNA,		( PXSTR* ppzDesc, PCXSTR pzUser, PCXSTR pzPassword, PCXSTR pzDataSource, PCXSTR pzProvider, eHACCESS eAccess=HOREADWRITE, UINT nFlags=HLSTTABLE ) )
#else // !defined(HF_DESACTIVE_ACCESNATIFS)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_ACCESNATIFS)

#if !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_HF5)
	// Init de la Dll Hyper File 5.5
	PROXY_METHOD( BOOL,		HFContext,	bHInitHF55,				( PCXSTR pzsWDD, PCXSTR pszWDDPassword=NULL ) )
#else // !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_HF5)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(WDHF_SERVER) || defined(HF_DESACTIVE_HF5)

#if !defined(HF_DESACTIVE_CONNECTION)
	// Ouvrir la connexion
	PROXY_METHOD( BOOL,		HFContext,	bHOuvreConnexion,		( PCXSTR pszConnectionName ) )
	// Fermer la connexion
	PROXY_METHOD( BOOL,		HFContext,	bHFermeConnexion,		( PCXSTR pszConnectionName ) )
	// Changer la connexion associée à un fichier
	PROXY_METHOD( BOOL,		HFContext,	bHChangeConnexion,		( PCXSTR pszTable, PCXSTR pszConnectionName ) )
	// Ouvrir une connexion avec les paramètres transmis 
	// (invisible, supportée pour compat)
	PROXY_METHOD( BOOL,		HFContext,	bHOuvreNouvelleConnexion,	( PCXSTR pszConnectionName, PCXSTR pzUser, PCXSTR pzPassword, PCXSTR pzDataSource, PCXSTR pzDataBase, PCXSTR pzProvider, eHACCESS eAccess=HOREADWRITE, PCXSTR pzOptions=NULL, UINT nCursorOptions=0 ) )
#else //!defined(HF_DESACTIVE_CONNECTION)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_CONNECTION)

#if !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_FONCSQL)
	// Débuter/Annuler/Valider une transaction
	PROXY_METHOD( BOOL,		HFContext,	bSQLTransaction,		( int * pnResultat, int nType, PCXSTR pszConnectionName=NULL) )
#else //!defined(WDHF_SERVER) && !defined(HF_DESACTIVE_FONCSQL)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(WDHF_SERVER) || defined(HF_DESACTIVE_FONCSQL)

	// exporter le contenu d'un fichier
	PROXY_METHOD( BOOL,		HFContext,	bHVersFichier,			( PCXSTR pszSource, PCXSTR pszCompleteDestName ) )

#if !defined(HF_DESACTIVE_CONNECTION)
	// Décrire une nouvelle connexion
	PROXY_METHOD( BOOL,		HFContext,	bHDecritConnexion,		( PCXSTR pszConnectionName, PCXSTR pzUser, PCXSTR pzPassword, PCXSTR pzDataSource, PCXSTR pzDataBase, PCXSTR pzProvider, eHACCESS eAccess=HOREADWRITE, PCXSTR pzOptions=NULL, UINT nCursorOptions=0 ) )

	// Diagnostiquer une connexion
	PROXY_METHOD( BOOL,		HFContext,	bHDiagnostiqueConnexion,( PXSTR* ppzDesc, PCXSTR pszConnectionName, PCXSTR pszFileName=NULL, UINT nOptions=0 ) )
#else //!defined(HF_DESACTIVE_CONNECTION)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_CONNECTION)

#if !defined(HF_DESACTIVE_ACCESNATIFS)
	// lister les providers OLEDB présents sur la machine
	PROXY_METHOD( BOOL,		HFContext,	bHListeProvider,		( PXSTR* ppzDesc ) )
#else //!defined(HF_DESACTIVE_ACCESNATIFS)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_ACCESNATIFS)
	// Créer un fichier seulement s'il n'existe pas
	PROXY_METHOD( BOOL,		HFContext,	bHCreationSiInexistantOptimise, ( PCXSTR pzTable=NULL, PCXSTR pzPassword=NULL, UINT nFlags=0 ) )

#if !defined(HF_DESACTIVE_HOPTIMISE)
	// Chargement des index HF7 dans les caches du système
	PROXY_METHOD( BOOL,		HFContext,	bHOptimise,				( PCXSTR pszTable=NULL, PCXSTR pszItem=NULL ) )
#else // !defined(HF_DESACTIVE_HOPTIMISE)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_HOPTIMISE)

	// Supprimer un enregistrement, idem bHSupprime mais peut prendre un flag en plus
	PROXY_METHOD( BOOL,		HFContext,	bHSupprimeEx,			( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, UINT nFlags=HPARSEMODEDEFAULT ) )

#if !defined(HF_DESACTIVE_CONNECTION)
	// Lister les connexions
	PROXY_METHOD( BOOL,		HFContext,	bHListeConnexion,		( PXSTR* ppzDesc, UINT nFlags=HLSTNORMAL ) )
#else //!defined(HF_DESACTIVE_CONNECTION)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_CONNECTION)

#if !defined(HF_DESACTIVE_JNLRPL)
	// Changer l'emplacement des fichiers du journal
	PROXY_METHOD( BOOL,		HFContext,	bHChangeRepJournal,		( PCXSTR pszPath, UINT nFlags=0 ) )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL)

	// HLitRecherche avec flag
	PROXY_METHOD( BOOL,		HFContext,	bHLitRechercheEx,		( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT ) )
	// HRecherche avec flag
	PROXY_METHOD( BOOL,		HFContext,	bHRechercheEx,			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT ) )

#if !defined(HF_DESACTIVE_RPC)
	// HOuvreAnalyse distant
	PROXY_METHOD( BOOL,		HFContext,	bHOuvreAnalyseDistante,	( PCXSTR pzAnalysis, PCXSTR pzPassword, PCXSTR pzServerAddress, PCXSTR pzUserName, PCXSTR pzNetworkPassword) )
#else //!defined(HF_DESACTIVE_RPC)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_RPC)

#if !defined(HF_DESACTIVE_TRANSACTION)
	// Savoir si une transaction a été interrompue sans avoir été validée ou annulée
	PROXY_METHOD( BOOL,		HFContext,	bHTransactionInterrompue,( PCXSTR pszNomFichierTRS=NULL ) )
#else //!defined(HF_DESACTIVE_TRANSACTION)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_TRANSACTION)
#if !defined(HF_DESACTIVE_JNLRPL)
	// fixe l'id de poste d'une transaction
	PROXY_METHOD( BOOL,		HFContext,	bHPosteTrs,				( PCXSTR pszId ) )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL)

#if !defined(HF_DESACTIVE_JNLRPL_C)
	// HCreation en spécifiant l'emplacement du fichier journal
	PROXY_METHOD( BOOL,		HFContext,	bHCreationJNL,			( PCXSTR pzTable, PCXSTR pzPassword, PCXSTR pzPathJNL, PCXSTR pzPathOP=NULL, UINT nFlags=0 ) )
	PROXY_METHOD( BOOL,		HFContext,	bHCreationSiInexistantOptimiseJNL,	( PCXSTR pzTable, PCXSTR pzPassword, PCXSTR pzPathJNL, PCXSTR pzPathOP=NULL, UINT nFlags=0 ) )
#else //!defined(HF_DESACTIVE_JNLRPL_C)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL_C)

#if !defined(HF_DESACTIVE_JNLRPL)
	// Changer l'emplacement des fichiers du journal
	PROXY_METHOD( BOOL,		HFContext,	bHChangeRepJournalEx,	( PCXSTR pzTable, PCXSTR pszPathJNL, PCXSTR pszPathOP=NULL, UINT nFlags=0 ) )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL)

	// Définir si comment on gère l'ouverture des fichier (comparaison des structures)
	PROXY_METHOD( BOOL,		HFContext,	bHVerifieStructure,		( eHDESCRIPTION *peOldValue, PCXSTR pzTable, eHDESCRIPTION eDescriptionCheck=HSTRICT ) )
	
#if !defined(HF_DESACTIVE_JNLRPL)
	// gestion du journal
	PROXY_METHOD( BOOL,		HFContext,	bHJournalInfo,			( PCXSTR pszMessage=NULL ) )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL)

	///////////////////////////////////////////////////////////////////////////
	// Deréférencer le contexte, si plus de référence, le contexte est détruit
	// EXACTEMEMNT le même fonctionnement que  nExternalRelease
	// Gardé pour les macros de libération d'interface
	PROXY_METHOD( UINT_32,	HFContext,	Release,				( void ) )

#if !defined(HF_DESACTIVE_JNLRPL)
	// gestion du journal
	PROXY_METHOD( BOOL,		HFContext,	bHJournalInfoEx,		( PCXSTR pszTable, PCXSTR pszMessage=NULL ) )
	PROXY_METHOD( BOOL,		HFContext,	bHJournalRecree,		( PCXSTR pszTable, UINT nFlags=0 ) )

	PROXY_EMPTY_METHOD( HFContext )
#else //!defined(HF_DESACTIVE_JNLRPL)
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
	PROXY_EMPTY_METHOD( HFContext )
#endif //defined(HF_DESACTIVE_JNLRPL)

	// connaître l'avancement d'une réindexation en cours sur le fichier
	PROXY_METHOD( BOOL,		HFContext,	bHReindexationEnCours,	( int *pnRes, PCXSTR pszTable, IGaugeControl *piGauge=NULL ) )

#if !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_FONCSQL)
	// récupérer les types de données gérées par la connexion dont le nom est transmis
	PROXY_METHOD( BOOL,		HFContext,	bSQLFormatColonneEx,	( XCHAR **ppzDesc, PCXSTR pszConnexion, UINT nFlags=0 ) )
#else // !defined(WDHF_SERVER) && !defined(HF_DESACTIVE_FONCSQL)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(WDHF_SERVER) || defined(HF_DESACTIVE_FONCSQL)

	// récupérer la liste des paramètres d'une requête
	PROXY_METHOD( BOOL,		HFContext,	bHListeParamRequete,	( XCHAR **ppzDesc, PCXSTR pszQuery, UINT nFlags=0 ) )

#if !defined(HF_DESACTIVE_XML)
	// Recupère l'enregistrement au format XML
	PROXY_METHOD( BOOL,		HFContext,	bHEnregistrementVersXML, ( PSTR *ppzValue, PCXSTR pszTable=NULL, PCXSTR pszItemList=ALLITEMS ) )
#else // !defined(HF_DESACTIVE_XML)
	PROXY_EMPTY_METHOD( HFContext )
#endif // defined(HF_DESACTIVE_XML)
	
	///////////////////////////////////////////////////////////////////////////
	// Emplacements disponibles pour fonctions futures	
	
//	PROXY_EMPTY_METHOD( HFContext )

PROXY_END

#endif //#ifndef __IHFCONTEXT_H
