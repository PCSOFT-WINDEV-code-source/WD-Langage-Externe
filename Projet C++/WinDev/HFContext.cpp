// Classe des contextes Hyper File utilisée par le langage externe

#include "Central.h"

#ifdef _WINDOWS
	#include <windows.h>		// include principal pour les applications Windows
#endif

#include <assert.h>			// assertions lorsque _DEBUG est défini
#include "HFContext.h"

//Conversion d'une chaîne en UNICODE
#ifdef UNICODE
	#define CONVU(s)	s
	#define PCONVU(s)	s
	#define NBCARU(n)	n
	#define CONVA(s)
#else
	class CConvU
	{
		WCHAR	m_wszRes[1024 + 1];
		PXSTR	pszRes;
	public:
		CConvU(PCXSTR pszChaine)
		{
			if (pszChaine == NULL) pszRes = NULL;
			else
			{
				MultiByteToWideChar(CP_ACP,0,pszChaine,-1,m_wszRes,sizeof(m_wszRes)/sizeof(m_wszRes[0]));
				pszRes = (PXSTR)m_wszRes;
			}
		}
		PXSTR pszGet(void){return pszRes;}
		PXSTR * ppszGet(void){return &pszRes;}
	};
	#define CONVU(s)	(CConvU(s).pszGet())
	#define PCONVU(s)	(CConvU(*s).ppszGet())
	#define NBCARU(n)	(2 * (n))
	void ConvA(PXSTR pszChaine)
	{
		XCHAR	szRes[1024 + 1] = _X("");
		WideCharToMultiByte(CP_ACP,0,(WCHAR *)pszChaine,-1,szRes,sizeof(szRes)/sizeof(szRes[0]),NULL,NULL);
		STRCPY(pszChaine,szRes);
	};
	#define CONVA(s)	ConvA(s);
#endif

///////////////////////////////////////////////////////////////////////////////
// Constructeur
///////////////////////////////////////////////////////////////////////////////
CVHFContext::CVHFContext( void ) : m_pHFContext(NULL)
{
}



///////////////////////////////////////////////////////////////////////////////
// Destructeur
///////////////////////////////////////////////////////////////////////////////
CVHFContext::~CVHFContext()
{
	if ( m_pHFContext != NULL )
		m_pHFContext->nExternalRelease();
}



///////////////////////////////////////////////////////////////////////////////
// Initialisation
///////////////////////////////////////////////////////////////////////////////
BOOL CVHFContext::bInit( IHFContext *pclWDHF )
{
	assert( m_pHFContext == NULL );
	// demande l'interface de base d'un nouveau contexte Hyper File
	m_pHFContext = pclWDHF;
	pclWDHF->ExternalAddRef();
	return( m_pHFContext != NULL );
}



///////////////////////////////////////////////////////////////////////////////
// Initialisation
///////////////////////////////////////////////////////////////////////////////
void CVHFContext::Init( IHFContext* piHFContext )
{
	assert( m_pHFContext == NULL );
	assert( piHFContext != NULL );
	// fixe l'interface du nouveau contexte Hyper File
	m_pHFContext = piHFContext;
	m_pHFContext->ExternalAddRef();
}



///////////////////////////////////////////////////////////////////////////////
// Récupérer l'interface du contexte avec la dll WDHF
// retour
//   pointeur sur l'interface
///////////////////////////////////////////////////////////////////////////////
IHFContext* CVHFContext::piGetHFContext( void ) const
{
	return m_pHFContext;
}



///////////////////////////////////////////////////////////////////////////////
// Mettre à jour l'enregistrement en cours dans la dll WDHF
///////////////////////////////////////////////////////////////////////////////
void CVHFContext::UpdateRecordToWDHF( PCXSTR pzTable ) const
{
	assert( m_pHFContext != NULL );
	LPVOID pBuffer;
	XUSIZE32 nSize;
	// si l'association a été définie
	if( bGetAssociation( pzTable, &pBuffer, &nSize ) )
		// mise à jour
		if( !m_pHFContext->bUpdateRecordToWDHF( CONVU(pzTable), pBuffer, nSize ) )
			assert(FALSE);
}



///////////////////////////////////////////////////////////////////////////////
// Mettre à jour l'enregistrement en cours depuis la dll WDHF
///////////////////////////////////////////////////////////////////////////////
void CVHFContext::UpdateRecordFromWDHF( PCXSTR pzTable ) const
{
	assert( m_pHFContext != NULL );
	LPVOID pBuffer;
	XUSIZE32 nSize;
	// si l'association a été définie
	if( bGetAssociation( pzTable, &pBuffer, &nSize ) )
		// mise à jour
		if( !m_pHFContext->bUpdateRecordFromWDHF( CONVU(pzTable), pBuffer, nSize ) )
			assert(FALSE);
}



///////////////////////////////////////////////////////////////////////////////
// Libérer un buffer alloué par Hyper File
///////////////////////////////////////////////////////////////////////////////
void CVHFContext::FreeMemory( PVOID* ppBuffer )
{
	assert( m_pHFContext != NULL );
	m_pHFContext->FreeMemory( ppBuffer );
}



///////////////////////////////////////////////////////////////////////////////
// Libérer une chaîne allouée par Hyper File
///////////////////////////////////////////////////////////////////////////////
void CVHFContext::DeleteString( PXSTR* ppzString )
{
	assert( m_pHFContext != NULL );
	m_pHFContext->FreeMemory( (PVOID*)ppzString );
}



///////////////////////////////////////////////////////////////////////////
// Définir le nom de la dll Hyper File 5 à 32bits utiliser (dans le cas où
// l'on accède à des tables Hyper File 5). Par défaut ce sera WD553HF.DLL.
///////////////////////////////////////////////////////////////////////////
BOOL CVHFContext::bSetWDHF5Name( PCXSTR pzWDHF5Name )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bSetWDHF5Name( CONVU(pzWDHF5Name ));
}



///////////////////////////////////////////////////////////////////////////////
// Récupérer la table à utiliser
///////////////////////////////////////////////////////////////////////////////
void CVHFContext::_GetTableName( PXSTR pzTableName, PCXSTR pzTable ) const
{
	assert( m_pHFContext != NULL );
	assert( pzTableName != NULL );
	// si on a donné une table, on la renvoie
	if( pzTable != NULL && *pzTable != _X('\0') )
	{		
		STRCPY( pzTableName, pzTable );
	}
	// sinon, on récupère la dernière table utilisée
	else
	{
		m_pHFContext->GetLastUsedTable( pzTableName );
		CONVA(pzTableName)
	}
}



///////////////////////////////////////////////////////////////////////////////
// Définir le contenu d'une rubrique mémo
///////////////////////////////////////////////////////////////////////////////
BOOL CVHFContext::bSetMemoData( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pData, XUSIZE32 nSize )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bSetMemoData( CONVU(pzTable), CONVU(pzItem), pData, nSize );
}



///////////////////////////////////////////////////////////////////////////////
// Récupérer un pointeur const sur les données du mémo de l'enregistrement en cours
///////////////////////////////////////////////////////////////////////////////
BOOL CVHFContext::bGetMemoData( PCXSTR pzTable, PCXSTR pzItem, LPCVOID *ppData, XUSIZE32 *pnSize )
{
	assert( m_pHFContext != NULL );
	assert( ppData != NULL );
	assert( pnSize != NULL );
	return m_pHFContext->bGetMemoData( CONVU(pzTable), CONVU(pzItem), ppData, pnSize );
}


// ne met pas à jour le buffer du langage externe si erreur
#define NOUPDATEONERROR( zTableName )	if ( !m_pHFContext->bError() ) UpdateRecordFromWDHF( zTableName );

///////////////////////////////////////////////////////////////////////////////
// FONCTIONS WLANGAGE
///////////////////////////////////////////////////////////////////////////////
BOOL CVHFContext::HActiveFiltre( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHActiveFiltre( CONVU(pzTable), CONVU(pzItem ));
}

BOOL CVHFContext::HAjoute( PCXSTR pzTable/*=NULL*/, UINT nWriteFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[NBCARU(SMAX_TABLENAME+1)];
	_GetTableName( zTableName, pzTable );
	UpdateRecordToWDHF( zTableName );
	BOOL bResult = m_pHFContext->bHAjoute( CONVU(zTableName), nWriteFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HAlias( PCXSTR pzTable, PCXSTR pzAlias/*=NULL*/, PCXSTR pzAbrev/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHAlias( CONVU(pzTable), CONVU(pzAlias), CONVU(pzAbrev ));
}

BOOL CVHFContext::HAnnuleAlias( PCXSTR pzAlias )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHAnnuleAlias( CONVU(pzAlias ));
}

BOOL CVHFContext::HAnnuleDeclaration( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHAnnuleDeclaration( CONVU(pzTable ));
}

BOOL CVHFContext::HAnnuleRecherche( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHAnnuleRecherche( CONVU(pzTable), CONVU(pzItem ));
}

BOOL CVHFContext::HAttacheMemo( PCXSTR pzTable, PCXSTR pzItem, PCXSTR pzFilename, eHMEMOTYPE eType/*=HMEMOTYPEBIN*/ , PCXSTR pszUserInfo/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[NBCARU(SMAX_TABLENAME+1)];
	_GetTableName( zTableName, pzTable );
	return m_pHFContext->bHAttacheMemo( CONVU(pzTable ), CONVU(pzItem ), CONVU(pzFilename ), eType , CONVU(pszUserInfo ));
}

BOOL CVHFContext::HAvance( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, RECNUM llStep/*=1*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[NBCARU(SMAX_TABLENAME+1)];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHAvance( CONVU(zTableName), CONVU(pzItem), llStep, nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HBloqueFichier( PCXSTR pzTable/*=NULL*/, eHPARSEMODE eMode/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHBloqueFichier( CONVU(pzTable), eMode );
}

BOOL CVHFContext::HBloqueNumEnr( PCXSTR pzTable/*=NULL*/, RECNUM llRecNum/*=HCURRENTRECNUM*/, eHPARSEMODE eMode/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHBloqueNumEnr( CONVU(pzTable), llRecNum, eMode );
}

BOOL CVHFContext::HChangeCle( PCXSTR pzTable, PCXSTR pzItem )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHChangeCle( CONVU(pzTable), CONVU(pzItem ));
}

BOOL CVHFContext::HChangeNom( PCXSTR pzTable, PCXSTR pzFile )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHChangeNom( CONVU(pzTable), CONVU(pzFile ));
}

BOOL CVHFContext::HChangeRep( PCXSTR pzTable, PCXSTR pzDir )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHChangeRep( CONVU(pzTable), CONVU(pzDir ));
}

PVOID CVHFContext::HConstruitValCle( PCXSTR pzTable, PCXSTR pzComposedKey, ... )
{
	assert( m_pHFContext != NULL );
	PVOID pKey;
	va_list	arg_ptr;
	va_start( arg_ptr, pzComposedKey );
	m_pHFContext->bHConstruitValCle( &pKey, CONVU(pzTable), CONVU(pzComposedKey), arg_ptr );
   	va_end( arg_ptr );
	return pKey;
}

BOOL CVHFContext::HCopieEnreg( PCXSTR pzTableDst, PCXSTR pzTableSrc, PCXSTR pzItemDst, PCXSTR pzItemSrc, DWORD dwFlags )
{
	UpdateRecordToWDHF( pzTableSrc );
	BOOL bResult = m_pHFContext->bHCopieEnreg( CONVU(pzTableDst), CONVU(pzTableSrc), CONVU(pzItemDst), CONVU(pzItemSrc), dwFlags );
	NOUPDATEONERROR( pzTableDst );
	return bResult;
}

BOOL CVHFContext::HCreation( PCXSTR pzTable, PCXSTR pzPassword/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHCreation( CONVU(pzTable), pzPassword );
}

BOOL CVHFContext::HCreationSiInexistant( PCXSTR pzTable/*=NULL*/, PCXSTR pzPassword/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHCreationSiInexistant( CONVU(pzTable), CONVU(pzPassword ));
}


BOOL CVHFContext::HCreationSiInexistantOptimise ( PCXSTR pzTable/*=NULL*/, PCXSTR pzPassword/*=NULL*/, UINT nFlags/*=0*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHCreationSiInexistantOptimise( CONVU(pzTable), CONVU(pzPassword ), nFlags );
}

#ifndef HF_DESACTIVE_CREATION_STRUCTURES
BOOL CVHFContext::HCreeStructureExterne( PCXSTR pszFilePath , PCXSTR pszWDDPath , PCXSTR pszWDDPassword , eHEXLANGTYPE eExLangType , BOOL bFormat )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHCreeStructureExterne( CONVU(pszFilePath ), CONVU(pszWDDPath ), CONVU(pszWDDPassword ), eExLangType , bFormat );
}
#endif //HF_DESACTIVE_CREATION_STRUCTURES

BOOL CVHFContext::HCreeVue( PCXSTR pzSnapShot, PCXSTR pzTable/*=NULL*/, PCXSTR pzListItems/*=ALLITEMS*/, PCXSTR pzSortingItem/*=NULL*/, PCXSTR pzCondition/*=NULL*/, int nMode/*=HVIEWDEFAULT*/, XUSIZE32 nPageSize/*=100*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHCreeVue( CONVU(pzSnapShot), CONVU(pzTable), CONVU(pzListItems), CONVU(pzSortingItem), CONVU(pzCondition), nMode, nPageSize );
}

#ifndef HF_DESACTIVE_HF5
BOOL CVHFContext::HDecritCle( PCXSTR pzLogicalName, PCXSTR pzKeyName, PCXSTR pzItemList, BOOL bDuplicates )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDecritCle_55( CONVU(pzLogicalName), CONVU(pzKeyName), CONVU(pzItemList), bDuplicates );
}
#endif //HF_DESACTIVE_HF5

#ifndef HF_DESACTIVE_HF5
BOOL CVHFContext::HDecritFichier( PCXSTR pzLogicalName, PCXSTR pzAbrev, PCXSTR pzDefaultDirectory/*=CURRENTDIR*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDecritFichier_55( CONVU(pzLogicalName), CONVU(pzAbrev), CONVU(pzDefaultDirectory ));
}
#endif //HF_DESACTIVE_HF5

#ifndef HF_DESACTIVE_HF5
BOOL CVHFContext::HDecritRubrique( PCXSTR pzLogicalName, PCXSTR pzItemDescription, int nArraySize/*=1*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDecritRubrique_55( CONVU(pzLogicalName), CONVU(pzItemDescription), nArraySize );
}
#endif //HF_DESACTIVE_HF5

BOOL CVHFContext::HDebloqueFichier( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDebloqueFichier( CONVU(pzTable ));
}

BOOL CVHFContext::HDebloqueNumEnr( PCXSTR pzTable/*=NULL*/, RECNUM llRecNum/*=HCURRENTRECNUM*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDebloqueNumEnr( CONVU(pzTable), llRecNum );
}

BOOL CVHFContext::HDernier( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDernier( CONVU(pzTable), CONVU(pzItem), nFlags );
}

BOOL CVHFContext::HDesactiveFiltre( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDesactiveFiltre( CONVU(pzTable), CONVU(pzItem ));
}

BOOL CVHFContext::HDetruitVue( PCXSTR pzSnapShot/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDetruitVue( CONVU(pzSnapShot ));
}

BOOL CVHFContext::HEcrit( PCXSTR pzTable/*=NULL*/, RECNUM llRecNum/*=HCURRENTRECNUM*/ , UINT nWriteFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[NBCARU(SMAX_TABLENAME+1)];
	_GetTableName( zTableName, pzTable );
	UpdateRecordToWDHF( zTableName );
	BOOL bResult = m_pHFContext->bHEcrit( CONVU(zTableName), llRecNum, nWriteFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HEffaceVue( PCXSTR pzSnapShot/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHEffaceVue( CONVU(pzSnapShot ));
}

BOOL CVHFContext::HEffaceVueIndex( PCXSTR pzSnapShot/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHEffaceVueIndex( CONVU(pzSnapShot ));
}

BOOL CVHFContext::HEnDehors( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	BOOL bEnDehors;
	m_pHFContext->bHEnDehors( &bEnDehors, CONVU(pzTable ));
	return bEnDehors;
}

int CVHFContext::HErreur( eHERRORPARSE eErrorParse/*=HEP_CURRENT*/ )
{
	assert( m_pHFContext != NULL );
	int nErreur;
	m_pHFContext->bHErreur( &nErreur, eErrorParse );
	return nErreur;
}

BOOL CVHFContext::HErreurBlocage( void )
{
	assert( m_pHFContext != NULL );
	BOOL bErreur;
	m_pHFContext->bHErreurBlocage( &bErreur );
	return bErreur;
}

BOOL CVHFContext::HErreurDoublon( void )
{
	assert( m_pHFContext != NULL );
	BOOL bErreur;
	m_pHFContext->bHErreurDoublon( &bErreur );
	return bErreur;
}

PXSTR CVHFContext::HErreurInfo( eHERRORINFO eErrorInfo/*=HEI_INFO*/ )
{
	assert( m_pHFContext != NULL );
	PXSTR pzErrorInfo = NULL;
	m_pHFContext->bHErreurInfo( &pzErrorInfo, eErrorInfo );
	CONVA(pzErrorInfo)
	return pzErrorInfo;
}

BOOL CVHFContext::HErreurIntegrite( void )
{
	assert( m_pHFContext != NULL );
	BOOL bErreur;
	m_pHFContext->bHErreurIntegrite( &bErreur );
	return bErreur;
}

BOOL CVHFContext::HErreurMotDePasse( void )
{
	assert( m_pHFContext != NULL );
	BOOL bErreur;
	m_pHFContext->bHErreurMotDePasse( &bErreur );
	return bErreur;
}

eHRECORDSTATE CVHFContext::HEtat( PCXSTR pzTable/*=NULL*/ , RECNUM llRecNum/*=HCURRENTRECNUM*/ )
{
	assert( m_pHFContext != NULL );
	eHRECORDSTATE eState;
	m_pHFContext->bHEtat( &eState, CONVU(pzTable), llRecNum );
	return eState;
}

BOOL CVHFContext::HExecuteVue( PCXSTR pzSnapShot, PCXSTR pzCondition )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHExecuteVue( CONVU(pzSnapShot), CONVU(pzCondition ));
}

BOOL CVHFContext::HExtraitMemo( PCXSTR pzTable, PCXSTR pzItem, PCXSTR pzFilename/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[NBCARU(SMAX_TABLENAME+1)];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHExtraitMemo( CONVU(pzTable ), CONVU(pzItem ), CONVU(pzFilename ));
	UpdateRecordToWDHF( zTableName );
	return bResult;
}
		  
BOOL CVHFContext::HFerme( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHFerme( CONVU(pzTable ));
}

BOOL CVHFContext::HFermeAnalyse( void )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHFermeAnalyse();
}

BOOL CVHFContext::HFichierExiste( PCXSTR pzTable/*=NULL*/ )
{
	BOOL bFichierExiste;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHFichierExiste( CONVU(pzTable), &bFichierExiste );
	return bFichierExiste;
}

BOOL CVHFContext::HFichierPosition( PXSTR pzTable, UINT nSize, HPOS hPosition )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHFichierPosition( CONVU(pzTable), nSize, hPosition );
}

PXSTR CVHFContext::HFiltre( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pMin, int nMin/*=HDEFAULTSIZE*/, LPCVOID pMax/*=NULL*/, int nMax/*=HDEFAULTSIZE*/, PCXSTR pzCondition/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	PXSTR pzResult = NULL;
	m_pHFContext->bHFiltre( &pzResult, CONVU(pzTable), CONVU(pzItem), pMin, nMin, pMax, nMax, CONVU(pzCondition ));
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HFiltre( PCXSTR pzTable, PCXSTR pzCondition )
{
	assert( m_pHFContext != NULL );
	PXSTR pzResult = NULL;
	m_pHFContext->bHFiltreCondition( &pzResult, CONVU(pzTable), CONVU(pzCondition ));
	CONVA(pzResult)
	return pzResult;
}

int CVHFContext::HSecurite( PCXSTR pzTable, int nSecurity )
{
	assert( m_pHFContext != NULL );
	int nOldValue = 0;
	m_pHFContext->bHSecurite( &nOldValue, CONVU(pzTable), nSecurity );
	return nOldValue;
}

BOOL CVHFContext::HGereDoublon( PCXSTR pzTable, PCXSTR pzItem, BOOL bCheckDuplicates )
{
	assert( m_pHFContext != NULL );
	BOOL bOldValue = TRUE;
	m_pHFContext->bHGereDoublon( &bOldValue, CONVU(pzTable), CONVU(pzItem), bCheckDuplicates );
	return bOldValue;
}

BOOL CVHFContext::HGereIntegrite( PCXSTR pzRelation, PCXSTR pzTable, DWORD dwRules, BOOL bCheck )
{
	assert( m_pHFContext != NULL );
	BOOL bOldValue = TRUE;
	m_pHFContext->bHGereIntegrite( &bOldValue, CONVU(pzRelation), CONVU(pzTable), dwRules, bCheck );
	return bOldValue;
}

eHMEMO CVHFContext::HGereMemo( PCXSTR pzTable, PCXSTR pzItem, eHMEMO eMemo )
{
	assert( m_pHFContext != NULL );
	eHMEMO eOldValue = HMEMOAUTO;
	m_pHFContext->bHGereMemo( &eOldValue, CONVU(pzTable), CONVU(pzItem), eMemo );
	return eOldValue;
}

BOOL CVHFContext::HGereREP( BOOL bManageREP, PCXSTR pzREPDirectory/*=NULL*/, PCXSTR pzREPFile/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	BOOL bOldValue = TRUE;
	m_pHFContext->bHGereREP( &bOldValue, bManageREP, CONVU(pzREPDirectory), CONVU(pzREPFile ));
	return bOldValue;
}

#ifndef HF_DESACTIVE_HF5
BOOL CVHFContext::HImporteHF55( PCXSTR pszTable, PCXSTR pszTableHF5, PCXSTR pszPathHF5, PCXSTR pszPasswordHF5, PCXSTR pszWDD5, PCXSTR pszWDD5Password/*=NULL*/, PCXSTR pszItemList/*=NULL*/, PCXSTR pszItemListHF5/*=NULL*/, UINT nFlags/*=HIMPNORMAL*/, IGaugeControl *piGauge/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHImporteHF55( CONVU(pszTable), CONVU(pszTableHF5), CONVU(pszPathHF5), CONVU(pszPasswordHF5), CONVU(pszWDD5), CONVU(pszWDD5Password), CONVU(pszItemList), CONVU(pszItemListHF5), nFlags, piGauge );
}
#endif //HF_DESACTIVE_HF5

#ifndef HF_DESACTIVE_IMPORTETEXTE
BOOL CVHFContext::HImporteTexte( PCXSTR pszTable , PCXSTR pszFilename , PCXSTR pszItemList/*=ALLITEMS*/, PCXSTR pszSeparator/*=DEFAULT_IMPORTSEPARATOR*/, UINT nFlags/*=HIMPNORMAL*/, IGaugeControl *piGauge/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHImporteTexte( CONVU(pszTable), CONVU(pszFilename), CONVU(pszItemList), CONVU(pszSeparator), nFlags, piGauge );
}
#endif //HF_DESACTIVE_IMPORTETEXTE

#ifndef XVER_POCKET
BOOL CVHFContext::HInfoIndex( PCXSTR pzFileDest, PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHInfoIndex( CONVU(pzFileDest), CONVU(pzTable ));
}
#endif //XVER_POCKET

PXSTR CVHFContext::HInfoMemo( PCXSTR pzTable, PCXSTR pzItem )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHInfoMemo( &pzResult, CONVU(pzTable), CONVU(pzItem ));
	CONVA(pzResult)
	return pzResult;
}

BOOL CVHFContext::HExecuteRequeteSQL( PCXSTR pzQuery, PCXSTR pszConnection, eHQUERYMODE eMode, PCXSTR pzSelect )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHExecuteRequeteSQL( CONVU(pzQuery), CONVU(pszConnection), eMode, CONVU(pzSelect ));
}

BOOL CVHFContext::HLibere( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHLibere( CONVU(pzTable ));
}

BOOL CVHFContext::HLiberePosition( HPOS hPosition )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHLiberePosition( hPosition );
}

PXSTR CVHFContext::HListeAnalyse( PCXSTR pzPath, PCXSTR pzSep/*=NULL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeAnalyse( &pzResult, CONVU(pzPath), CONVU(pzSep ));
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeCle( PCXSTR pzTable , PCXSTR pzWDD, PCXSTR pzWDDPassword/*=NULL*/, UINT nFlags/*=HLSTNORMAL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeCle( &pzResult, CONVU(pzTable ), CONVU(pzWDD), CONVU(pzWDDPassword), nFlags );
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeCle( PCXSTR pzTable , UINT nFlags/*=HLSTNORMAL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeCle( &pzResult, CONVU(pzTable ), nFlags );
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeFichier( PCXSTR pzWDD, PCXSTR pzWDDPassword/*=NULL*/, UINT nFlags/*=HLSTNORMAL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeFichier( &pzResult, CONVU(pzWDD), CONVU(pzWDDPassword), nFlags );
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeFichier( UINT nFlags/*=HLSTNORMAL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeFichier( &pzResult, nFlags );
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeLiaison( PCXSTR pzTable/*=NULL*/, PCXSTR pzWDD/*=NULL*/, PCXSTR pzWDDPassword/*=NULL*/, UINT nFlags/*=HLSTNORMAL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeLiaison( &pzResult, CONVU(pzTable), CONVU(pzWDD), CONVU(pzWDDPassword), nFlags );
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeREP( PCXSTR pzREPWDD/*=NULL*/, PCXSTR pzTable/*=NULL*/, PCXSTR pzFile/*=NULL*/, UINT nFlags/*=HREPDEFAULT*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeREP( &pzResult, CONVU(pzREPWDD), CONVU(pzTable), CONVU(pzFile), nFlags );
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeRubrique( PCXSTR pzTable , PCXSTR pzWDD, PCXSTR pzWDDPassword/*=NULL*/, UINT nFlags/*=HLSTNORMAL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeRubrique( &pzResult, CONVU(pzTable ), CONVU(pzWDD), CONVU(pzWDDPassword), nFlags );
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HListeRubrique( PCXSTR pzTable , UINT nFlags/*=HLSTNORMAL*/ )
{
	PXSTR pzResult=NULL;
	assert( m_pHFContext != NULL );
	m_pHFContext->bHListeRubrique( &pzResult, CONVU(pzTable ), nFlags );
	CONVA(pzResult)
	return pzResult;
}

BOOL CVHFContext::HLit( PCXSTR pzTable/*=NULL*/, RECNUM llRecNum/*=HCURRENTRECNUM*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHLit( CONVU(zTableName), llRecNum, nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HLitDernier( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHLitDernier( CONVU(zTableName), CONVU(pzItem), nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HLitPrecedent( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHLitPrecedent( CONVU(zTableName), CONVU(pzItem), nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HLitPremier( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHLitPremier( CONVU(zTableName), CONVU(pzItem), nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HLitRecherchePremier( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue/*=HDEFAULTSIZE*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHLitRecherchePremier( CONVU(zTableName), CONVU(pzItem), pValue, nValue, nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HLitRechercheDernier( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue/*=HDEFAULTSIZE*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHLitRechercheDernier( CONVU(zTableName), CONVU(pzItem), pValue, nValue, nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HLitSuivant( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHLitSuivant( CONVU(zTableName), CONVU(pzItem), nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

eHMODE CVHFContext::HMode( PCXSTR pzTable, eHMODE eMode, eHLOCKMETHOD eLockMethod/*=HLOCKMETHODDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	eHMODE eOldValue = HMODEMULTI;
	m_pHFContext->bHMode( &eOldValue, CONVU(pzTable), eMode, eLockMethod );
	return eOldValue;
}

BOOL CVHFContext::HModifie( PCXSTR pzTable/*=NULL*/, RECNUM llRecNum/*=HCURRENTRECNUM*/ , UINT nWriteFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	UpdateRecordToWDHF( zTableName );
	BOOL bResult = m_pHFContext->bHModifie( CONVU(zTableName), llRecNum , nWriteFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

RECNUM CVHFContext::HNbEnr( PCXSTR pzTable/*=NULL*/ , DWORD dwStates/*=HSTATEACTIVE*/ )
{
	assert( m_pHFContext != NULL );
	RECNUM llRecNum;
	m_pHFContext->bHNbEnr( &llRecNum, CONVU(pzTable ), dwStates );
	return llRecNum;
}

RECNUM CVHFContext::HNbEnr_55( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	RECNUM llRecNum;
	m_pHFContext->bHNbEnr_55( &llRecNum, CONVU(pzTable ));
	return llRecNum;
}

RECNUM CVHFContext::HNbSup_55( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	RECNUM llRecNum;
	m_pHFContext->bHNbSup_55( &llRecNum, CONVU(pzTable ));
	return llRecNum;
}

RECNUM CVHFContext::HNumEnr( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	RECNUM llRecNum;
	m_pHFContext->bHNumEnr( &llRecNum, CONVU(pzTable ));
	return llRecNum;
}

RECNUM CVHFContext::HNumEnrPosition( HPOS hPosition )
{
	assert( m_pHFContext != NULL );
	RECNUM llRecNum;
	m_pHFContext->bHNumEnrPosition( &llRecNum, hPosition );
	return llRecNum;
}

BOOL CVHFContext::HOuvre( PCXSTR pzTable/*=NULL*/, PCXSTR pzPassword/*=NULL*/, eHACCESS eAccess/*=HODEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHOuvre( CONVU(pzTable), CONVU(pzPassword), eAccess );
}

BOOL CVHFContext::HDeclare( PCXSTR pzTable, PCXSTR pzWDD, PCXSTR pzWDDPassword/*=NULL*/, PCXSTR pzAlias/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDeclare( CONVU(pzTable), CONVU(pzWDD), CONVU(pzWDDPassword), CONVU(pzAlias ));
}

BOOL CVHFContext::HDeclareExterne( PCXSTR pzFullName, PCXSTR pzAlias , PCXSTR pszPassword/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHDeclareExterne( CONVU(pzFullName), CONVU(pzAlias ), CONVU(pszPassword ));
}

BOOL CVHFContext::HOuvreAnalyse( PCXSTR pzAnalysis, PCXSTR pzPassword/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHOuvreAnalyse( CONVU(pzAnalysis), CONVU(pzPassword ));
}

BOOL CVHFContext::HPasse( PCXSTR pzTable, PCXSTR pzPassword/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHPasse( CONVU(pzTable), CONVU(pzPassword ));
}

int CVHFContext::HPositionCourante( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, eHPRECISION ePrecision/*=HPRECISIONMEDIUM*/ )
{
	assert( m_pHFContext != NULL );
	int nPos;
	m_pHFContext->bHPositionCourante( &nPos, CONVU(pzTable), CONVU(pzItem), ePrecision );
	return nPos;
}

BOOL CVHFContext::HPositionne( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nPos/*=1*/, eHPRECISION ePrecision/*=HPRECISIONMEDIUM*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHPositionne( CONVU(pzTable), CONVU(pzItem), nPos, ePrecision );
	NOUPDATEONERROR( zTableName );
	return bResult;
}
	
BOOL CVHFContext::HPrecedent( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHPrecedent( CONVU(pzTable), CONVU(pzItem), nFlags );
}

BOOL CVHFContext::HPremier( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHPremier( CONVU(pzTable), CONVU(pzItem), nFlags );
}

BOOL CVHFContext::HRaye( PCXSTR pzTable/*=NULL*/, RECNUM llRecNum/*=HCURRENTRECNUM*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHRaye( CONVU(pzTable), llRecNum );
}

BOOL CVHFContext::HRAZ( PCXSTR pzTable/*=NULL*/,PCXSTR pzItem/*=ALLITEMS*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHRAZ( CONVU(zTableName), CONVU(pzItem ));
	NOUPDATEONERROR( zTableName );
	return bResult;
}

BOOL CVHFContext::HRecherchePremier( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue/*=HDEFAULTSIZE*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHRecherchePremier( CONVU(pzTable), CONVU(pzItem), pValue, nValue, nFlags );
}

BOOL CVHFContext::HRechercheDernier( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pValue, int nValue/*=HDEFAULTSIZE*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHRechercheDernier( CONVU(pzTable), CONVU(pzItem), pValue, nValue, nFlags );
}

BOOL CVHFContext::HRecule( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, RECNUM llStep/*=1*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	_GetTableName( zTableName, pzTable );
	BOOL bResult = m_pHFContext->bHRecule( CONVU(zTableName), CONVU(pzItem), llStep, nFlags );
	NOUPDATEONERROR( zTableName );
	return bResult;
}

PXSTR CVHFContext::HRecupereEnregistrement( PCXSTR pzTable/*NULL*/, PCXSTR pzItemSep/*=NULL*/, PCXSTR pzSubItemSep/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	PXSTR pzResult = NULL;
	m_pHFContext->bHRecupereEnregistrement( &pzResult, CONVU(pzTable), CONVU(pzItemSep), CONVU(pzSubItemSep ));
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HRecupereRubrique( PCXSTR pzTable, UINT nItem, PCXSTR pzSubItemSep/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	PXSTR pzResult = NULL;
	m_pHFContext->bHRecupereRubrique( &pzResult, CONVU(pzTable), nItem, INVALID_ITEMINDEX, CONVU(pzSubItemSep ));
	CONVA(pzResult)
	return pzResult;
}

PXSTR CVHFContext::HRecupereRubrique( PCXSTR pzTable, UINT nItem, int nIndex )
{
	assert( m_pHFContext != NULL );
	PXSTR pzResult = NULL;
	m_pHFContext->bHRecupereRubrique( &pzResult, CONVU(pzTable), nItem, nIndex );
	CONVA(pzResult)
	return pzResult;
}

BOOL CVHFContext::HReindexe( PCXSTR pzTable/*=NULL*/, eHNDXMODE eNdxMode/*=HNDXNORMAL*/, IGaugeControl *piGauge/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHReindexe( CONVU(pzTable), NULL, NULL, eNdxMode, piGauge );
}

BOOL CVHFContext::HReindexe( PCXSTR pzTable, PCXSTR pzFileName, PCXSTR pzPath, eHNDXMODE eNdxMode/*=HNDXNORMAL*/, IGaugeControl *piGauge/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHReindexe( CONVU(pzTable), CONVU(pzFileName), CONVU(pzPath), eNdxMode, piGauge );
}

BOOL CVHFContext::HRetourPosition( HPOS hPosition, UINT nFlags/*=HRPDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	TCHAR zTableName[SMAX_TABLENAME+1];
	BOOL bResult = HFichierPosition( zTableName, sizeof(zTableName)/sizeof(TCHAR), hPosition );
	if( bResult )
	{
		bResult = m_pHFContext->bHRetourPosition( hPosition, nFlags );
		NOUPDATEONERROR( zTableName );
	}
	return bResult;
}

HPOS CVHFContext::HSauvePosition( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	HPOS hPosition;
	m_pHFContext->bHSauvePosition( &hPosition, CONVU(pzTable), CONVU(pzItem ));
	return hPosition;
}

BOOL CVHFContext::HStatCalcule( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=ALLITEMS*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHStatCalcule( CONVU(pzTable), CONVU(pzItem ));
}

PXSTR CVHFContext::HStatDate( PXSTR* ppzDate, PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	m_pHFContext->bHStatDate( ppzDate, CONVU(pzTable), CONVU(pzItem ));
	CONVA(*ppzDate)
	return *ppzDate;
}

PXSTR CVHFContext::HStatHeure( PXSTR* ppzTime, PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	m_pHFContext->bHStatHeure( ppzTime, CONVU(pzTable), CONVU(pzItem ));
	CONVA(*ppzTime)
	return *ppzTime;
}

RECNUM CVHFContext::HStatNbDoublon( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	RECNUM llDuplicates;
	m_pHFContext->bHStatNbDoublon( &llDuplicates, CONVU(pzTable), CONVU(pzItem ));
	return llDuplicates;
}

RECNUM CVHFContext::HStatNbEnr( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	RECNUM llNbRec;
	m_pHFContext->bHStatNbEnr( &llNbRec, CONVU(pzTable), CONVU(pzItem ));
	return llNbRec;
}

RECNUM CVHFContext::HStatNbEnrIntervalle( PCXSTR pzTable, PCXSTR pzItem, LPCVOID pMin, int nMin, LPCVOID pMax, int nMax )
{
	assert( m_pHFContext != NULL );
	RECNUM llNbRec;
	m_pHFContext->bHStatNbEnrIntervalle( &llNbRec, CONVU(pzTable), CONVU(pzItem), pMin, nMin, pMax, nMax );
	return llNbRec;
}
	
BOOL CVHFContext::HSubstRep( PCXSTR pzLogicalDir, PCXSTR pzPhysicalDir )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHSubstRep( CONVU(pzLogicalDir), CONVU(pzPhysicalDir ));
}

BOOL CVHFContext::HSuivant( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, UINT nFlags/*=HPARSEMODEDEFAULT*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHSuivant( CONVU(pzTable), CONVU(pzItem), nFlags );
}

BOOL CVHFContext::HSupprime( PCXSTR pzTable/*=NULL*/, RECNUM llRecNum/*=HCURRENTRECNUM*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHSupprime( CONVU(pzTable), llRecNum );
}

BOOL CVHFContext::HTrieVue( PCXSTR pzSnapShot/*=NULL*/, PCXSTR pzItem/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHTrieVue( CONVU(pzSnapShot), CONVU(pzItem ));
}

BOOL CVHFContext::HTrouve( PCXSTR pzTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	BOOL bHTrouve;
	m_pHFContext->bHTrouve( &bHTrouve, CONVU(pzTable ));
	return bHTrouve;
}

int CVHFContext::HVerifieIndex( PCXSTR pzTable/*=NULL*/, PCXSTR pzItem/*=NULL*/, IGaugeControl *piGauge/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	int nRes;
	m_pHFContext->bHVerifieIndex( &nRes, CONVU(pzTable), CONVU(pzItem), piGauge );
	return nRes;
}

eHDESCRIPTION CVHFContext::HVerifieStructure( PCXSTR pzTable/*=NULL*/, eHDESCRIPTION eDescriptionCheck/*=HSTRICT*/ )
{
	assert( m_pHFContext != NULL );
	eHDESCRIPTION eOldValue;
	m_pHFContext->bHVerifieStructure( &eOldValue, CONVU(pzTable), eDescriptionCheck );
	return eOldValue;
}

int	CVHFContext::HVersion( PCXSTR pzTable/*=NULL*/)
{
	assert( m_pHFContext != NULL );
	int nVersion;
	m_pHFContext->bHVersion( &nVersion, CONVU(pzTable ));
	return nVersion;
}

BOOL CVHFContext::HVersRubrique( PCXSTR pzTable, UINT nItem, PCXSTR pzValue )
{
	assert( m_pHFContext != NULL );
	BOOL bResult = m_pHFContext->bHVersRubrique( CONVU(pzTable), nItem, INVALID_ITEMINDEX, NULL, CONVU(pzValue ));
	NOUPDATEONERROR( pzTable );
	return bResult;
}

BOOL CVHFContext::HVersRubrique( PCXSTR pzTable, UINT nItem, int nIndex, PCXSTR pzValue )
{
	assert( m_pHFContext != NULL );
	BOOL bResult = m_pHFContext->bHVersRubrique( CONVU(pzTable), nItem, nIndex, NULL, CONVU(pzValue ));
	NOUPDATEONERROR( pzTable );
	return bResult;
}

BOOL CVHFContext::HVersRubrique( PCXSTR pzTable, UINT nItem, PCXSTR pzSubItemSep, PCXSTR pzValue )
{
	assert( m_pHFContext != NULL );
	BOOL bResult = m_pHFContext->bHVersRubrique( CONVU(pzTable), nItem, INVALID_ITEMINDEX, CONVU(pzSubItemSep), CONVU(pzValue ));
	NOUPDATEONERROR( pzTable );
	return bResult;
}

BOOL CVHFContext::HVueVersFichier( PCXSTR pzSnapShot/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHVueVersFichier( CONVU(pzSnapShot ));
}

BOOL CVHFContext::HConnecte(PCXSTR pzTable, PCXSTR pzUser/*=NULL*/, PCXSTR pzPassword/*=NULL*/, PCXSTR pzSource/*=NULL*/, PCXSTR pzProvider/*=NULL*/, eHACCESS eAccess/*=HOREADWRITE*/, eHTESTOPERATION eOperation/*=HCUNSPECIFIED*/, PXSTR * ppsztabParam/*=NULL*/, int nNbParam/*=0*/) 
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHConnecte( CONVU(pzTable), CONVU(pzUser), CONVU(pzPassword), CONVU(pzSource), CONVU(pzProvider), eAccess, eOperation, PCONVU(ppsztabParam), nNbParam );
}

BOOL CVHFContext::HGereTransaction( PCXSTR pzTable/*=NULL*/, BOOL bMode/*=TRUE*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHGereTransaction( CONVU(pzTable), bMode );
}

BOOL CVHFContext::HTransactionDebut( PCXSTR pzFile/*=NULL*/, PCXSTR pzFileList/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHTransactionDebut( CONVU(pzFile), CONVU(pzFileList ));
}

BOOL CVHFContext::HTransactionFin( void )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHTransactionFin();
}

BOOL CVHFContext::HTransactionAnnule( PCXSTR pszNomFichierTRS/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHTransactionAnnule( CONVU(pszNomFichierTRS ));
}

BOOL CVHFContext::HTransactionLibere( PCXSTR pszTable/*=NULL*/ )
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bHTransactionLibere( CONVU(pszTable ));
}

#ifndef HF_DESACTIVE_JNLRPL_C
BOOL CVHFContext::bGetPathJnlSave(PXSTR pszFullFileName, PCXSTR pszFilePath)
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bGetPathJnlSave( CONVU(pszFullFileName), CONVU(pszFilePath ));
}

BOOL CVHFContext::bBackupJnlSave(PCXSTR pszFullFileName, PCXSTR pszBackupPath)
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bBackupJnlSave( CONVU(pszFullFileName), CONVU(pszBackupPath ));
}

BOOL CVHFContext::bDeleteJnlSave(PCXSTR pszFullFileName) 
{
	assert( m_pHFContext != NULL );
	return m_pHFContext->bDeleteJnlSave( CONVU(pszFullFileName ));
}
#endif //HF_DESACTIVE_JNLRPL_C


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Classe gérant les association table / buffer
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constructeur
///////////////////////////////////////////////////////////////////////////////
CHFTabAssociation::CHFTabAssociation( UINT nGrowingStep/*=DEFAULTGROWINGSTEP*/ ) :
	m_nNumKeys(0),
	m_nTabSize(0),
	m_nGrowingStep(nGrowingStep),
	m_tabAssoc(NULL)
{
	assert( nGrowingStep > 0 );
}


	
///////////////////////////////////////////////////////////////////////////////
// Destructeur
///////////////////////////////////////////////////////////////////////////////
CHFTabAssociation::~CHFTabAssociation()
{
	if( m_nNumKeys > 0 )
	{
		UINT i;
		for( i = 0; i < m_nNumKeys; i++ )
			delete [] (m_tabAssoc[i].pzKey);
		free( m_tabAssoc );
	}
}



///////////////////////////////////////////////////////////////////////////////
// Rechercher le buffer associé à la table
///////////////////////////////////////////////////////////////////////////////
BOOL CHFTabAssociation::bGetAssociation( PCXSTR pzKey, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const
{
	assert( pzKey != NULL );
	UINT i;
	for( i = 0; i < m_nNumKeys; i++ )
	{
		if( STRICMP( pzKey, m_tabAssoc[i].pzKey ) == 0 )
		{
			if( ppBuffer != NULL ) *ppBuffer = m_tabAssoc[i].pBuffer;
			if( pnSize != NULL ) *pnSize = m_tabAssoc[i].nSize;
			return TRUE;
		}
	}
	// l'association cherchée n'a pas été trouvée
	if( ppBuffer != NULL ) *ppBuffer = NULL;
	if( pnSize != NULL ) *pnSize = 0;
	return FALSE;
}



///////////////////////////////////////////////////////////////////////////////
// Associer un buffer à une table
///////////////////////////////////////////////////////////////////////////////
BOOL CHFTabAssociation::bAssociate( PCXSTR pzKey, LPVOID pBuffer, XUSIZE32 nSize )
{
	assert( pzKey != NULL );
	// si l'association existe déjà, on sort en erreur
	if( bGetAssociation( pzKey, NULL, NULL ) ) return FALSE;

	// s'il ne reste plus de place dans le tableau, on l'agrandit
	if( m_nNumKeys >= m_nTabSize )
	{
		if( !_bGrow() ) return FALSE;
	}

	// ajoute la nouvelle association
	m_tabAssoc[m_nNumKeys].pzKey = new XCHAR[STRLEN(pzKey)+1];
	if( m_tabAssoc[m_nNumKeys].pzKey == NULL ) { assert(FALSE); return FALSE; }
	STRCPY( m_tabAssoc[m_nNumKeys].pzKey, pzKey );
	m_tabAssoc[m_nNumKeys].pBuffer = pBuffer;
	m_tabAssoc[m_nNumKeys].nSize = nSize;
	m_nNumKeys++;
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// Supprimer l'association table / buffer
///////////////////////////////////////////////////////////////////////////////
BOOL CHFTabAssociation::bDeleteAssociation( PCXSTR pzKey )
{
	assert( pzKey != NULL );
	UINT i;
	for( i = 0; i < m_nNumKeys; i++ )
	{
		if( STRICMP( pzKey, m_tabAssoc[i].pzKey ) == 0 ) break;
	}
	// si la table cherchée n'a pas été trouvée, on sort
	if( i == m_nNumKeys ) return FALSE;

	// libère l'association
	delete [] (m_tabAssoc[i].pzKey);
	memmove( &(m_tabAssoc[i]), &(m_tabAssoc[i+1]), (m_nNumKeys-i-1)*sizeof(m_tabAssoc[0]) );
	m_nNumKeys--;
	return TRUE;
}



///////////////////////////////////////////////////////////////////////////////
// Agrandir le tableau des associations
///////////////////////////////////////////////////////////////////////////////
BOOL CHFTabAssociation::_bGrow( void )
{
	m_nTabSize += m_nGrowingStep;
	// nouvelle allocation
	if( m_tabAssoc == NULL )
		m_tabAssoc = (stASSOC*)malloc( m_nTabSize*sizeof(stASSOC) );
	else
		m_tabAssoc = (stASSOC*)realloc( m_tabAssoc, m_nTabSize*sizeof(stASSOC) );
	// en cas de problème d'allocation
	if( m_tabAssoc == NULL ) { assert(FALSE); return FALSE; }
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Classe gérant un contexte Hyper File
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Associer une table et un buffer contenant son enregistrement en cours
///////////////////////////////////////////////////////////////////////////////
BOOL CHFContext::bAssociate( PCXSTR pzTable, LPVOID pBuffer, XUSIZE32 nSize )
{
	return m_clAssociation.bAssociate( pzTable, pBuffer, nSize );
}



///////////////////////////////////////////////////////////////////////////
// Récupérer le buffer qui contient l'enregistrement en cours
///////////////////////////////////////////////////////////////////////////
BOOL CHFContext::bGetAssociation( PCXSTR pzTable, LPVOID *ppBuffer, XUSIZE32 *pnSize ) const
{
	assert( ppBuffer != NULL );
	assert( pnSize != NULL );
	return m_clAssociation.bGetAssociation( pzTable, ppBuffer, pnSize );
}

	

///////////////////////////////////////////////////////////////////////////////
// Supprimer une association
///////////////////////////////////////////////////////////////////////////////
BOOL CHFContext::bDeleteAssociation( PCXSTR pzTable )
{
	return m_clAssociation.bDeleteAssociation( pzTable );
}
