// Classe des contextes HyperFile utilis�e par le langage externe
//
//
// Pour cr�er et travailler sur un contexte HF :
//
//	IHFContext	m_WDHF;			// client Hyper File
//	CHFContext	m_HFCTX;		// contexte Hyper File
//	stCLIENT	m_stClient;		// fichier stCLIENT : structure r�cup�r�e via HCreeStructureExterne
//	stCOMMANDE	m_stCommande;	// fichier stCOMMANDE : structure r�cup�r�e via HCreeStructureExterne
//
//
//	...
//	// charge la dll wdhf
//	m_WDHF.Load( "WD70HF.DLL" );
//	// cr�e un nouveau contexte
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
//  // cr�e le fichier client
//  if( !m_CTX.HCreation( "client" ) )
//		{ XASSERT(FALSE); return FALSE; }
//	...
//

#ifndef __HFCONTEXT_H
#define __HFCONTEXT_H

#include "IHFContext.h"		// Interface sur un contexte

class IGaugeControl;

///////////////////////////////////////////////////////////////////////////////
// Classe abstraite g�rant un contexte Hyper File.
// D�finir les m�thode bAssociate et _pGetBuffer qui g�rent les associations
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
	// entr�e
	//   pclWDHF : gestion de la composante WDHF
	// retour
	//   TRUE ssi tout s'est bien pass�
	BOOL			bInit					( IHFContext *piHFContext );

	///////////////////////////////////////////////////////////////////////////////
	// Initialisation
	void			Init					( IHFContext *piHFContext );

	///////////////////////////////////////////////////////////////////////////
	// R�cup�rer l'interface du contexte avec la dll WDHF
	// retour
	//   pointeur sur l'interface
	IHFContext*		piGetHFContext		( void ) const;

	///////////////////////////////////////////////////////////////////////////
	// Mettre � jour l'enregistrement en cours dans la dll WDHF
	// entr�e
	//   pzTable : nom de la table concern�e
	void			UpdateRecordToWDHF		( PCXSTR pzTable ) const;
	
	///////////////////////////////////////////////////////////////////////////
	// Mettre � jour l'enregistrement en cours depuis la dll WDHF
	// entr�e
	//   pzTable : nom de la table concern�e
	void			UpdateRecordFromWDHF	( PCXSTR pzTable ) const;

	///////////////////////////////////////////////////////////////////////////
	// Associer une table et un buffer contenant son enregistrement en cours
	// entr�e
	//   pzTable : nom de la table concern�e
	//   pBuffer : buffer contenant l'enregistrement en cours de pzTable
	//   nSize : taille du buffer
	// retour
	//   TRUE ssi l'association a pu se faire
	//   FALSE : l'association existait d�j� ou probl�me m�moire
	virtual BOOL	bAssociate			( PCXSTR pzTable, LPVOID pBuffer, XUSIZE32 nSize ) = 0;

	///////////////////////////////////////////////////////////////////////////
	// R�cup�rer le buffer qui contient l'enregistrement en cours
	// entr�e
	//   pzTable : nom de la table concern�e
	// sortie
	//   ppBuffer : buffer contenant l'enregistrement en cours de pzTable
	//   pnSize : taille du buffer
	// retour
	//   TRUE ssi l'association existe
	virtual BOOL	bGetAssociation	( PCXSTR pzTable, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const = 0;

	///////////////////////////////////////////////////////////////////////////
	// Supprimer une association
	// entr�e
	//   pzTable : nom de la table concern�e
	// retour
	//   TRUE ssi l'association existait et a �t� supprim�e
	//   FALSE : l'association n'existait pas
	virtual BOOL	bDeleteAssociation( PCXSTR pzTable ) = 0;

	///////////////////////////////////////////////////////////////////////////
	// Lib�rer un buffer allou� par Hyper File
	// entr�e/sortie
	//   ppBuffer : pointeur sur la donn�e � lib�rer
	//              (ppBuffer et *ppBuffer peuvent �tre NULL)
	//              il vaut NULL en sortie
	virtual void	FreeMemory			( PVOID *ppBuffer );

	///////////////////////////////////////////////////////////////////////////
	// Lib�rer une cha�ne allou�e par Hyper File
	// entr�e/sortie
	//   ppszString : pointeur sur la donn�e � lib�rer
	//                (ppszString et *ppszString peuvent �tre NULL)
	//                il vaut NULL en sortie
	virtual void	DeleteString		( PXSTR *ppszString );

	///////////////////////////////////////////////////////////////////////////
	// D�finir le nom de la dll Hyper File 5 � 32bits utiliser (dans le cas o�
	// l'on acc�de � des tables Hyper File 5). Par d�faut ce sera WD553HF.DLL.
	// entr�e
	//   pzWDHF5Name : nom de la dll Hyper File 5
	// retour
	//   TRUE ssi tout s'est bien pass�
	virtual BOOL	bSetWDHF5Name		( PCXSTR pzWDHF5Name );

	///////////////////////////////////////////////////////////////////////////
	// D�finir le contenu d'une rubrique m�mo
	// entr�e
	//   pzTable : nom logique de la table
	//   pzItem : nom de la rubrique m�mo
	//   pData : pointeur sur contenu du m�mo
	//   nSize : taille du contenu
	// retour
	//   TRUE ssi tout s'est bien pass�
	BOOL			bSetMemoData			( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pData, XUSIZE32 nSize );

	///////////////////////////////////////////////////////////////////////////
	// R�cup�rer un pointeur const sur les donn�es du m�mo de l'enregistrement en cours
	// entr�e
	//   pzTable : nom logique de la table
	//   pzItem : nom de la rubrique m�mo
	// sortie
	//   ppData : pointeur sur le contenu du m�mo (attention, les donn�es sont
	//            partag�es avec la dll Hyper File !), pour les m�mos textes, pas de 0 final
	//   pnSize : taille du contenu en octets (sans le 0 final)
	// retour
	//   TRUE ssi tout s'est bien pass�
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
	// Construire la valeur d'une cl� compos�e
	// entr�e
	//   pzTable : table
	//   pzComposedKey : cl� compos�e dont on veut construire la valeur
	//   ... : - suite de couples (LPCVOID pDataAdr, XUSIZE32 nDataSize)
	//           avec : pDataAdr : pointeur vers la valeur de la composante
	//                  nDataSize : taille de la valeur de la composante (-1 pour laisser WDHF la d�terminer)
	//         - un couple correspond � l'une des composantes de la cl� compos�e
	//         - passer NULL comme dernier argument lorsque toutes les composantes ne sont pas renseign�es
	// retour
	//   pointeur vers la cl� compos�e (� lib�rer lorsqu'il ne sert plus)
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
	// R�cup�rer la table � utiliser
	// sortie
	//   pzTableName : table � utiliser
	// entr�e
	//   pzTable : nom table donn� par l'utilisateur (si NULL on r�cup�re la
	//             derni�re table utilis�e)
	void			_GetTableName			( PXSTR pzTableName, PCXSTR pzTable ) const;
};




///////////////////////////////////////////////////////////////////////////////
// Classe g�rant les associations nom_de_table /
// buffer_contenant_l'enregistrement_en_cours
///////////////////////////////////////////////////////////////////////////////
class CHFTabAssociation
{
private:
	// structures
	typedef struct
	{
		PXSTR	pzKey;				// table
		LPVOID	pBuffer;			// buffer associ�
		XUSIZE32	nSize;				// taille du buffer
	} stASSOC;
	
	// objets membres
	UINT		m_nNumKeys;			// nombre d'entr�es
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
	// Associer un buffer � une table
	// entr�e
	//   pzTable : nom de la table concern�e
	//   pBuffer : buffer associ�
	//   nSize : taille du buffer
	// retour
	//   TRUE ssi l'association a pu se faire
	//   FALSE : l'association existait d�j� ou probl�me m�moire
	virtual BOOL	bAssociate		( PCXSTR pzKey, LPVOID pBuffer, XUSIZE32 nSize );

	///////////////////////////////////////////////////////////////////////////
	// Chercher le buffer associ� � une table
	// entr�e
	//   pzKey : nom de la table dont on cherche le buffer associ�
	// sortie
	//   ppBuffer : adresse du buffer
	//   pnSize : taille du buffer
	// retour
	//   TRUE ssi l'association a �t� trouv�e
	virtual BOOL	bGetAssociation	( PCXSTR pzKey, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const;

	///////////////////////////////////////////////////////////////////////////
	// Supprimer l'association table / buffer 
	// entr�e
	//   pzTable : nom de la table concern�e
	// retour
	//   TRUE ssi l'association existait et a �t� supprim�e
	//   FALSE : l'association n'existait pas
	virtual BOOL	bDeleteAssociation( PCXSTR pzTable );



protected:
	// Agrandir le tableau
	virtual BOOL	_bGrow			( void );
};

	

	
///////////////////////////////////////////////////////////////////////////////
// Classe g�rant un contexte Hyper File
// Les associations nom_de_table / buffer_contenant_l'enregistrement_en_cours
// sont r�alis�es par la classe CHFTabAssociation (elle g�re un simple tableau).
// Cette classe peut �tre red�finie. Dans ce cas, h�riter de CVHFContext.
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
	// R�cup�rer le buffer qui contient l'enregistrement en cours
	virtual BOOL	bGetAssociation	( PCXSTR pzTable, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const;

	///////////////////////////////////////////////////////////////////////////
	// Supprimer une association
	virtual BOOL	bDeleteAssociation( PCXSTR pzTable );
};



#endif //#ifndef __HFCONTEXT_H

