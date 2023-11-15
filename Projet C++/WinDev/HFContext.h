// Classe des contextes HyperFile utilisée par le langage externe
//
//
// Pour créer et travailler sur un contexte HF :
//
//	IHFContext	m_WDHF;			// client Hyper File
//	CHFContext	m_HFCTX;		// contexte Hyper File
//	stCLIENT	m_stClient;		// fichier stCLIENT : structure récupérée via HCreeStructureExterne
//	stCOMMANDE	m_stCommande;	// fichier stCOMMANDE : structure récupérée via HCreeStructureExterne
//
//
//	...
//	// charge la dll wdhf
//	m_WDHF.Load( "WD70HF.DLL" );
//	// crée un nouveau contexte
//	if( !m_HFCTX.bInit( &m_WDHF ) )
//		{ XASSERT(FALSE); return FALSE; }
//	// ouvre l'analyse
//	if( !m_HFCTX.HOuvreAnalyse( "C:\\WinDev7\\Personnel\\Analyse.WD7\\Analyse.wdd", NULL ) )
//		{ XASSERT(FALSE); return FALSE; }
//	// associe buffer/enregistrement
//	if( !m_HFCTX.bAssociate( "client", &m_stClient, sizeof(m_stClient) ) )
//		{ XASSERT(FALSE); return FALSE; }
//	if( !m_HFCTX.bAssociate( "commande", &m_stCommande, sizeof(m_stCommande) ) )
//		{ XASSERT(FALSE); return FALSE; }
//  // crée le fichier client
//  if( !m_CTX.HCreation( "client" ) )
//		{ XASSERT(FALSE); return FALSE; }
//	...
//

#ifndef __HFCONTEXT_H
#define __HFCONTEXT_H

#include "IHFContext.h"		// Interface sur un contexte

class IGaugeControl;

///////////////////////////////////////////////////////////////////////////////
// Classe abstraite gérant un contexte Hyper File.
// Définir les méthode bAssociate et _pGetBuffer qui gèrent les associations
// nom_de_table / buffer_contenant_l'enregistrement_en_cours pour pouvoir
// l'instancier.
// CHFContext les instancie.
///////////////////////////////////////////////////////////////////////////////
class CVHFContext
{
protected:
	IHFContext* m_pHFContext;		// interface sur un contexte


public:
	///////////////////////////////////////////////////////////////////////////
	// Constructeur
	CVHFContext						( void );
	
	///////////////////////////////////////////////////////////////////////////
	// Destructeur
	virtual	~CVHFContext			();
	
	///////////////////////////////////////////////////////////////////////////
	// Initialisation
	// entrée
	//   pclWDHF : gestion de la composante WDHF
	// retour
	//   TRUE ssi tout s'est bien passé
	BOOL			bInit					( IHFContext *piHFContext );

	///////////////////////////////////////////////////////////////////////////////
	// Initialisation
	void			Init					( IHFContext *piHFContext );

	///////////////////////////////////////////////////////////////////////////
	// Récupérer l'interface du contexte avec la dll WDHF
	// retour
	//   pointeur sur l'interface
	IHFContext*		piGetHFContext		( void ) const;

	///////////////////////////////////////////////////////////////////////////
	// Mettre à jour l'enregistrement en cours dans la dll WDHF
	// entrée
	//   pzTable : nom de la table concernée
	void			UpdateRecordToWDHF		( PCXSTR pzTable ) const;
	
	///////////////////////////////////////////////////////////////////////////
	// Mettre à jour l'enregistrement en cours depuis la dll WDHF
	// entrée
	//   pzTable : nom de la table concernée
	void			UpdateRecordFromWDHF	( PCXSTR pzTable ) const;

	///////////////////////////////////////////////////////////////////////////
	// Associer une table et un buffer contenant son enregistrement en cours
	// entrée
	//   pzTable : nom de la table concernée
	//   pBuffer : buffer contenant l'enregistrement en cours de pzTable
	//   nSize : taille du buffer
	// retour
	//   TRUE ssi l'association a pu se faire
	//   FALSE : l'association existait déjà ou problème mémoire
	virtual BOOL	bAssociate			( PCXSTR pzTable, LPVOID pBuffer, XUSIZE32 nSize ) = 0;

	///////////////////////////////////////////////////////////////////////////
	// Récupérer le buffer qui contient l'enregistrement en cours
	// entrée
	//   pzTable : nom de la table concernée
	// sortie
	//   ppBuffer : buffer contenant l'enregistrement en cours de pzTable
	//   pnSize : taille du buffer
	// retour
	//   TRUE ssi l'association existe
	virtual BOOL	bGetAssociation	( PCXSTR pzTable, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const = 0;

	///////////////////////////////////////////////////////////////////////////
	// Supprimer une association
	// entrée
	//   pzTable : nom de la table concernée
	// retour
	//   TRUE ssi l'association existait et a été supprimée
	//   FALSE : l'association n'existait pas
	virtual BOOL	bDeleteAssociation( PCXSTR pzTable ) = 0;

	///////////////////////////////////////////////////////////////////////////
	// Libérer un buffer alloué par Hyper File
	// entrée/sortie
	//   ppBuffer : pointeur sur la donnée à libérer
	//              (ppBuffer et *ppBuffer peuvent être NULL)
	//              il vaut NULL en sortie
	virtual void	FreeMemory			( PVOID *ppBuffer );

	///////////////////////////////////////////////////////////////////////////
	// Libérer une chaîne allouée par Hyper File
	// entrée/sortie
	//   ppszString : pointeur sur la donnée à libérer
	//                (ppszString et *ppszString peuvent être NULL)
	//                il vaut NULL en sortie
	virtual void	DeleteString		( PXSTR *ppszString );

	///////////////////////////////////////////////////////////////////////////
	// Définir le nom de la dll Hyper File 5 à 32bits utiliser (dans le cas où
	// l'on accède à des tables Hyper File 5). Par défaut ce sera WD553HF.DLL.
	// entrée
	//   pzWDHF5Name : nom de la dll Hyper File 5
	// retour
	//   TRUE ssi tout s'est bien passé
	virtual BOOL	bSetWDHF5Name		( PCXSTR pzWDHF5Name );

	///////////////////////////////////////////////////////////////////////////
	// Définir le contenu d'une rubrique mémo
	// entrée
	//   pzTable : nom logique de la table
	//   pzItem : nom de la rubrique mémo
	//   pData : pointeur sur contenu du mémo
	//   nSize : taille du contenu
	// retour
	//   TRUE ssi tout s'est bien passé
	BOOL			bSetMemoData			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pData, XUSIZE32 nSize );

	///////////////////////////////////////////////////////////////////////////
	// Récupérer un pointeur const sur les données du mémo de l'enregistrement en cours
	// entrée
	//   pzTable : nom logique de la table
	//   pzItem : nom de la rubrique mémo
	// sortie
	//   ppData : pointeur sur le contenu du mémo (attention, les données sont
	//            partagées avec la dll Hyper File !), pour les mémos textes, pas de 0 final
	//   pnSize : taille du contenu en octets (sans le 0 final)
	// retour
	//   TRUE ssi tout s'est bien passé
	BOOL			bGetMemoData			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID *ppData, XUSIZE32 *pnSize );
	
	///////////////////////////////////////////////////////////////////////////
	// Fonctions WLangage
	BOOL			HActiveFiltre			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	BOOL			HAjoute					( PCXSTR pzTable=NULL, UINT nWriteFlags=HPARSEMODEDEFAULT );
	BOOL			HAlias					( PCXSTR pzTable, PCXSTR pzAlias=NULL, PCXSTR pzAbrev=NULL );
	BOOL			HAnnuleAlias			( PCXSTR pzAlias );
	BOOL			HAnnuleDeclaration		( PCXSTR pzTable=NULL );
	BOOL			HAnnuleRecherche		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	BOOL			HAttacheMemo			( PCXSTR pzTable, PCXSTR pzItem, PCXSTR pzFilename, eHMEMOTYPE eType=HMEMOTYPEBIN , PCXSTR pszUserInfo=NULL );
	BOOL			HAvance					( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, RECNUM llStep=1, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HBloqueFichier			( PCXSTR pzTable=NULL, eHPARSEMODE eMode=HPARSEMODEDEFAULT );
	BOOL			HBloqueNumEnr			( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, eHPARSEMODE eMode=HPARSEMODEDEFAULT );
	BOOL			HChangeCle				( PCXSTR pzTable, PCXSTR pzItem );
	BOOL			HChangeNom				( PCXSTR pzTable, PCXSTR pzFile );
	BOOL			HChangeRep				( PCXSTR pzTable, PCXSTR pzDir );

	///////////////////////////////////////////////////////////////////////////
	// Construire la valeur d'une clé composée
	// entrée
	//   pzTable : table
	//   pzComposedKey : clé composée dont on veut construire la valeur
	//   ... : - suite de couples (LPCVOID pDataAdr, XUSIZE32 nDataSize)
	//           avec : pDataAdr : pointeur vers la valeur de la composante
	//                  nDataSize : taille de la valeur de la composante (-1 pour laisser WDHF la déterminer)
	//         - un couple correspond à l'une des composantes de la clé composée
	//         - passer NULL comme dernier argument lorsque toutes les composantes ne sont pas renseignées
	// retour
	//   pointeur vers la clé composée (à libérer lorsqu'il ne sert plus)
	PVOID			HConstruitValCle		( PCXSTR pzTable, PCXSTR pzComposedKey, ... );
	BOOL			HCopieEnreg				( PCXSTR pzTableDst, PCXSTR pzTableSrc, PCXSTR pzItemDst=NULL, PCXSTR pzItemSrc=NULL, DWORD flags=HCOPYRECORDDEFAULT );
	BOOL			HCreation				( PCXSTR pzTable, PCXSTR pzPassword=NULL );
	BOOL			HCreationSiInexistant	( PCXSTR pzTable=NULL, PCXSTR pzPassword=NULL );
	BOOL			HCreationSiInexistantOptimise ( PCXSTR pzTable=NULL, PCXSTR pzPassword=NULL, UINT nFlags=0 );
#ifndef HF_DESACTIVE_CREATION_STRUCTURES
	BOOL			HCreeStructureExterne	( PCXSTR pszFilePath , PCXSTR pszWDDPath , PCXSTR pszWDDPassword , eHEXLANGTYPE eExLangType , BOOL bFormat );
#endif //#ifndef HF_DESACTIVE_CREATION_STRUCTURES
	BOOL			HCreeVue				( PCXSTR pzSnapShot, PCXSTR pzTable=NULL, PCXSTR pzListItems=ALLITEMS, PCXSTR pzSortingItem=NULL, PCXSTR pzCondition=NULL, int nMode=HVIEWDEFAULT, XUSIZE32 nPageSize=100 );
	BOOL			HDeclare				( PCXSTR pzTable, PCXSTR pzWDD, PCXSTR pzWDDPassword=NULL, PCXSTR pzAlias=NULL );
	BOOL			HDeclareExterne			( PCXSTR pzFullName, PCXSTR pzAlias, PCXSTR pszPassword=NULL );
	BOOL			HDecritCle				( PCXSTR pzLogicalName, PCXSTR pzKeyName, PCXSTR pzItemList, BOOL bDuplicates );
	BOOL			HDecritFichier			( PCXSTR pzLogicalName, PCXSTR pzAbrev, PCXSTR pzDefaultDirectory=CURRENTDIR );
	BOOL			HDecritRubrique			( PCXSTR pzLogicalName, PCXSTR pzItemDescription, int nArraySize=1 );
	BOOL			HDebloqueFichier		( PCXSTR pzTable=NULL );
	BOOL			HDebloqueNumEnr			( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM );
	BOOL			HDernier				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HDesactiveFiltre		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	BOOL			HDetruitVue				( PCXSTR pzSnapShot=NULL );
	BOOL			HEcrit					( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, UINT nWriteFlags=HPARSEMODEDEFAULT );
	BOOL			HEffaceVue				( PCXSTR pzSnapShot=NULL );
	BOOL			HEffaceVueIndex			( PCXSTR pzSnapShot=NULL );
	BOOL			HEnDehors				( PCXSTR pzTable=NULL );
	int				HErreur					( eHERRORPARSE eErrorParse=HEP_CURRENT );
	BOOL			HErreurBlocage			( void );
	BOOL			HErreurDoublon			( void );
	PXSTR			HErreurInfo				( eHERRORINFO eErrorInfo=HEI_INFO );
	BOOL			HErreurIntegrite		( void );
	BOOL			HErreurMotDePasse		( void );
	eHRECORDSTATE 	HEtat			( PCXSTR pzTable=NULL , RECNUM llRecNum=HCURRENTRECNUM );
	BOOL			HExecuteVue				( PCXSTR pzSnapShot, PCXSTR pzCondition );
	BOOL			HExtraitMemo			( PCXSTR pzTable, PCXSTR pzItem, PCXSTR pzFilename=NULL );
	BOOL			HFerme					( PCXSTR pzTable=NULL );
	BOOL			HFermeAnalyse			( void );
	BOOL			HFichierExiste			( PCXSTR pzTable=NULL );
	BOOL			HFichierPosition		( PXSTR pzTable, UINT nSize, HPOS hPosition );
	PXSTR			HFiltre					( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pMin, int nMin=HDEFAULTSIZE, LPCVOID pMax=NULL, int nMax=HDEFAULTSIZE , PCXSTR pzondition=NULL );
	PXSTR			HFiltre					( PCXSTR pzTable, PCXSTR pzCondition );
	int				HSecurite				( PCXSTR pzTable, int nSecurity );
	BOOL			HGereDoublon			( PCXSTR pzTable, PCXSTR pzItem, BOOL bCheckDuplicates );
	BOOL			HGereIntegrite			( PCXSTR pzRelation, PCXSTR pzTable, DWORD dwRules, BOOL bCheckIntegrity );
	eHMEMO			HGereMemo				( PCXSTR pzTable, PCXSTR pzItem, eHMEMO eMemo );
	BOOL			HGereREP				( BOOL bManageREP, PCXSTR pzREPDirectory=NULL, PCXSTR pzREPFile=NULL );
	BOOL			HImporteHF55			( PCXSTR pszTable, PCXSTR pszTableHF5, PCXSTR pszPathHF5, PCXSTR pszPasswordHF5, PCXSTR pszWDD5, PCXSTR pszWDD5Password=NULL, PCXSTR pszItemList=NULL, PCXSTR pszItemListHF5=NULL, UINT nFlags=HIMPNORMAL, IGaugeControl *piGauge=NULL );
#ifndef HF_DESACTIVE_IMPORTETEXTE
	BOOL			HImporteTexte			( PCXSTR pszTable , PCXSTR pszFilename , PCXSTR pszItemList=ALLITEMS, PCXSTR pszSeparator=DEFAULT_IMPORTSEPARATOR, UINT nFlags=HIMPNORMAL, IGaugeControl *piGauge=NULL );
#endif //HF_DESACTIVE_IMPORTETEXTE
#ifndef XVER_POCKET
	BOOL			HInfoIndex				( PCXSTR pzFileDest, PCXSTR pzTable=NULL );
#endif //XVER_POCKET
	PXSTR			HInfoMemo				( PCXSTR pzTable, PCXSTR pzItem );
	BOOL			HExecuteRequeteSQL		( PCXSTR pzQuery, PCXSTR pszConnection, eHQUERYMODE eMode, PCXSTR pzSelect );
	BOOL			HLibere					( PCXSTR pzTable=NULL );
	BOOL			HLiberePosition			( HPOS hPosition );
	PXSTR			HListeAnalyse			( PCXSTR pzPath, PCXSTR pzSep=NULL );
	PXSTR			HListeCle				( PCXSTR pzTable, UINT nFlags=HLSTNORMAL );
	PXSTR			HListeCle				( PCXSTR pzTable, PCXSTR pzWDD, PCXSTR pszWDDPassword=NULL, UINT nFlags=HLSTNORMAL );
	PXSTR			HListeFichier			( UINT nFlags=HLSTNORMAL );
	PXSTR			HListeFichier			( PCXSTR pzWDD, PCXSTR pszWDDPassword=NULL, UINT nFlags=HLSTNORMAL );
	PXSTR			HListeLiaison			( PCXSTR pzTable=NULL, PCXSTR pzWDD=NULL, PCXSTR pzWDDPassword=NULL, UINT nFlags=HLSTNORMAL );
	PXSTR			HListeREP				( PCXSTR pzREPWDD=NULL, PCXSTR pzTable=NULL, PCXSTR pzFile=NULL, UINT nFlags=HREPDEFAULT );
	PXSTR			HListeRubrique			( PCXSTR pzTable, UINT nFlags=HLSTNORMAL );
	PXSTR			HListeRubrique			( PCXSTR pzTable, PCXSTR pzWDD, PCXSTR pszWDDPassword=NULL, UINT nFlags=HLSTNORMAL );
	BOOL			HLit					( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HLitDernier				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HLitPrecedent			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HLitPremier				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HLitRecherchePremier	( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HLitRechercheDernier	( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HLitSuivant				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	eHMODE			HMode					( PCXSTR pzTable, eHMODE eMode, eHLOCKMETHOD eLockMethod=HLOCKMETHODDIRECT );
	BOOL			HModifie				( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM , UINT nWriteFlags=HPARSEMODEDEFAULT );
	RECNUM			HNbEnr					( PCXSTR pzTable=NULL , DWORD dwStates=HSTATEACTIVE );
	RECNUM			HNbEnr_55				( PCXSTR pzTable=NULL );
	RECNUM			HNbSup_55				( PCXSTR pzTable=NULL );
	RECNUM			HNumEnr					( PCXSTR pzTable=NULL );
	RECNUM			HNumEnrPosition			( HPOS hPosition );
	BOOL			HOuvre					( PCXSTR pzTable=NULL, PCXSTR pzPassword=NULL, eHACCESS eAccess=HODEFAULT );
	BOOL			HOuvreAnalyse			( PCXSTR pzAnalysis, PCXSTR pzPassword=NULL );
	BOOL			HPasse					( PCXSTR pzTable, PCXSTR pzPassword=NULL );
	int				HPositionCourante		( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, eHPRECISION ePrecision=HPRECISIONMEDIUM );
	BOOL			HPositionne				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nPos=1, eHPRECISION ePrecision=HPRECISIONMEDIUM );
	BOOL			HPrecedent				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HPremier				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HRaye					( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM );
	BOOL			HRAZ					( PCXSTR pzTable=NULL, PCXSTR pzItem=ALLITEMS );
	BOOL			HRecherchePremier		( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HRechercheDernier		( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue=HDEFAULTSIZE, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HRecule					( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, RECNUM llStep=1, UINT nFlags=HPARSEMODEDEFAULT );
	PXSTR			HRecupereEnregistrement	( PCXSTR pzTable=NULL, PCXSTR pzItemSep=NULL, PCXSTR pzSubItemSep=NULL );
	PXSTR			HRecupereRubrique		( PCXSTR pzTable, UINT nItem, PCXSTR pzSubItemSep=NULL );
	PXSTR			HRecupereRubrique		( PCXSTR pzTable, UINT nItem, int nIndex );
	BOOL			HReindexe				( PCXSTR pzTable=NULL, eHNDXMODE eNdxMode=HNDXNORMAL, IGaugeControl *piGauge=NULL );
	BOOL			HReindexe				( PCXSTR pzTable, PCXSTR pzFileName, PCXSTR pzPath, eHNDXMODE eNdxMode=HNDXNORMAL, IGaugeControl *piGauge=NULL );
	BOOL			HRetourPosition			( HPOS hPosition, UINT nFlags=HRPDEFAULT );
	BOOL			HStatCalcule			( PCXSTR pzTable=NULL, PCXSTR pzItem=ALLITEMS );
	PXSTR			HStatDate				( PXSTR* ppzDate, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	PXSTR			HStatHeure				( PXSTR* ppzTime, PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	RECNUM			HStatNbDoublon			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	RECNUM			HStatNbEnr				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	RECNUM			HStatNbEnrIntervalle	( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pMin, int nMin, LPCVOID pMax, int nMax );
	HPOS			HSauvePosition			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL );
	BOOL			HSubstRep				( PCXSTR pzLogicalDir, PCXSTR pzPhysicalDir );
	BOOL			HSuivant				( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, UINT nFlags=HPARSEMODEDEFAULT );
	BOOL			HSupprime				( PCXSTR pzTable=NULL, RECNUM llRecNum=HCURRENTRECNUM );
	BOOL			HTrieVue				( PCXSTR pzSnapShot=NULL, PCXSTR pzItem=NULL );
	BOOL			HTrouve					( PCXSTR pzTable=NULL );
	int				HVerifieIndex			( PCXSTR pzTable=NULL, PCXSTR pzItem=NULL, IGaugeControl *piGauge=NULL );
	eHDESCRIPTION	HVerifieStructure		( PCXSTR pzTable=NULL, eHDESCRIPTION eDescriptionCheck=HSTRICT );
	int				HVersion				( PCXSTR pzTable=NULL );
	BOOL			HVersRubrique			( PCXSTR pzTable, UINT nItem, PCXSTR pzValue );
	BOOL			HVersRubrique			( PCXSTR pzTable, UINT nItem, int nIndex, PCXSTR pzValue );
	BOOL			HVersRubrique			( PCXSTR pzTable, UINT nItem, PCXSTR pzSubItemSep, PCXSTR pzValue );
	BOOL			HVueVersFichier			( PCXSTR pzSnapShot=NULL );
	BOOL			HConnecte				( PCXSTR pzTable, PCXSTR pzUser=NULL, PCXSTR pzPassword=NULL, PCXSTR pzSource=NULL, PCXSTR pzProvider=NULL, eHACCESS eAccess=HOREADWRITE, eHTESTOPERATION eOperation=HCUNSPECIFIED, PXSTR * ppsztabParam=NULL, int nNbParam=0);
	BOOL			HGereTransaction		( PCXSTR pzTable=NULL, BOOL bMode=TRUE );
	BOOL			HTransactionDebut		( PCXSTR pzFile=NULL, PCXSTR pzFileList=NULL );
	BOOL			HTransactionFin			( void );
	BOOL			HTransactionAnnule		( PCXSTR pszNomFichierTRS=NULL );
	BOOL			HTransactionLibere		( PCXSTR pszTable=NULL );
#ifndef HF_DESACTIVE_JNLRPL_C
	BOOL			bGetPathJnlSave			( PXSTR pszFullFileName, PCXSTR pszFilePath);
	BOOL			bBackupJnlSave			( PCXSTR pszFullFileName, PCXSTR pszBackupPath );
	BOOL			bDeleteJnlSave			( PCXSTR pszFullFileName );
#endif //#ifndef HF_DESACTIVE_JNLRPL_C

protected:
	///////////////////////////////////////////////////////////////////////////
	// Récupérer la table à utiliser
	// sortie
	//   pzTableName : table à utiliser
	// entrée
	//   pzTable : nom table donné par l'utilisateur (si NULL on récupère la
	//             dernière table utilisée)
	void			_GetTableName			( PXSTR pzTableName, PCXSTR pzTable ) const;
};




///////////////////////////////////////////////////////////////////////////////
// Classe gérant les associations nom_de_table /
// buffer_contenant_l'enregistrement_en_cours
///////////////////////////////////////////////////////////////////////////////
class CHFTabAssociation
{
private:
	// structures
	typedef struct
	{
		PXSTR	pzKey;				// table
		LPVOID	pBuffer;			// buffer associé
		XUSIZE32	nSize;				// taille du buffer
	} stASSOC;
	
	// objets membres
	UINT		m_nNumKeys;			// nombre d'entrées
	UINT		m_nTabSize;			// taille du tableau
	UINT		m_nGrowingStep;		// pas d'agrandissement du tableau
	stASSOC*	m_tabAssoc;			// tableau

	// constantes
	#define DEFAULTGROWINGSTEP	5	// pas d'agrandissement du tableau


public:
	///////////////////////////////////////////////////////////////////////////
	// Constructeur
	CHFTabAssociation				( UINT nGrowingStep=DEFAULTGROWINGSTEP );

	///////////////////////////////////////////////////////////////////////////
	// Destructeur
	virtual ~CHFTabAssociation		();

	///////////////////////////////////////////////////////////////////////////
	// Associer un buffer à une table
	// entrée
	//   pzTable : nom de la table concernée
	//   pBuffer : buffer associé
	//   nSize : taille du buffer
	// retour
	//   TRUE ssi l'association a pu se faire
	//   FALSE : l'association existait déjà ou problème mémoire
	virtual BOOL	bAssociate		( PCXSTR pzKey, LPVOID pBuffer, XUSIZE32 nSize );

	///////////////////////////////////////////////////////////////////////////
	// Chercher le buffer associé à une table
	// entrée
	//   pzKey : nom de la table dont on cherche le buffer associé
	// sortie
	//   ppBuffer : adresse du buffer
	//   pnSize : taille du buffer
	// retour
	//   TRUE ssi l'association a été trouvée
	virtual BOOL	bGetAssociation	( PCXSTR pzKey, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const;

	///////////////////////////////////////////////////////////////////////////
	// Supprimer l'association table / buffer 
	// entrée
	//   pzTable : nom de la table concernée
	// retour
	//   TRUE ssi l'association existait et a été supprimée
	//   FALSE : l'association n'existait pas
	virtual BOOL	bDeleteAssociation( PCXSTR pzTable );



protected:
	// Agrandir le tableau
	virtual BOOL	_bGrow			( void );
};

	

	
///////////////////////////////////////////////////////////////////////////////
// Classe gérant un contexte Hyper File
// Les associations nom_de_table / buffer_contenant_l'enregistrement_en_cours
// sont réalisées par la classe CHFTabAssociation (elle gère un simple tableau).
// Cette classe peut être redéfinie. Dans ce cas, hériter de CVHFContext.
///////////////////////////////////////////////////////////////////////////////
class CHFContext : public CVHFContext
{
private:
	CHFTabAssociation m_clAssociation;	// table des associations table / enreg en cours



public:
	///////////////////////////////////////////////////////////////////////////
	// Associer une table et un buffer contenant son enregistrement en cours
	virtual BOOL	bAssociate		( PCXSTR pzTable, LPVOID pBuffer, XUSIZE32 nSize );

	///////////////////////////////////////////////////////////////////////////
	// Récupérer le buffer qui contient l'enregistrement en cours
	virtual BOOL	bGetAssociation	( PCXSTR pzTable, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const;

	///////////////////////////////////////////////////////////////////////////
	// Supprimer une association
	virtual BOOL	bDeleteAssociation( PCXSTR pzTable );
};



#endif //#ifndef __HFCONTEXT_H

