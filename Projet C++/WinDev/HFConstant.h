//#6.00A	HFConstant.h	NF
// Définition des valeurs des constantes de WDHF
// Constantes à exporter pour le langage externe
// Fichier destiné à être envoyé en clientèle


#ifndef __HFCONSTANT_H
#define __HFCONSTANT_H

#define COMPONUM			7				// numéro de la composante. TODO : à mettre ailleurs
#define CONSTANTBASE		(COMPONUM*10000)// nombre de base pour les constantes de la composante

//--- Types
typedef LONGLONG			RECNUM;			// type "numéro d'enregistrement"
typedef int					HPOS;			// type "handle de position"


// ATTENTION, tailles à ne pas dépasser, on stock la taille des noms sur 1 octet
// Si plus grand, on devra modifier la structure des fichiers
#define SMAX_TABLENAME		255				// taille max du nom logique de la table
#define SMAX_LINKNAME		255				// taille max du nom d'une liaison
#define SMAX_ITEMNAME		255				// taille max du nom d'une rubrique

#define ALLTABLES			_X("*")			// chaîne désignant "toutes les tables"
#define ALLITEMS			_X("*")			// chaîne désignant "toutes les rubriques de la table"
#define ALLRELATIONS		_X("*")			// chaîne désignant "toutes les relations"
#define ALLPATH				_X("*")			// chaîne désignant "tous les chemins"
#define CURRENTDIR			_X(".")			// désigne le répertoire courant
#define HCURRENTRECNUM		((RECNUM) 0)	// enregistrement courant
#define HINVALIDRECNUM		((RECNUM)-1)	// enregistrement invalide
#define HINVALIDPOS			((int)-1)		// handle de position invalide
#define HDEFAULTSIZE		(-1)			// demande à HF de déterminer la taille du paramètre
#define	HSUCCES				0				// pas d'erreur

// Indice de rubrique tableau indéfini.
// Equivaut à l'indice 1 pour les rubriques normales.
// Pour les rubriques tableau, est utilisé pour désigner la rubrique dans sa totalité.
#define INVALID_ITEMINDEX		-1
#define UNDEFINEDITEMDATASIZE	0			// taille de la donnée non spécifiée ( SetValueSize(ptr, size) ): 
											//		pour les chaines on utilise la taille de la chaine
											//		pour les rubriques de taille fixe,  on utilise la taille fixée
											//		pour les rubriques binaires, provoque une erreur

#define HINFINITECARDINALITY	(-1)		// cardinalité N d'une liaison

// pour HGereRep, ne pas mettre à jour le HFREP.INI
#define  HREP_SANSMAJINI		3


// les séparateurs par défaut utilisés pour la fonction HImportTexte :
//		- la virgule pour les colonnes
//		- la double quote ( " ) pour les chaînes
//		- RC (Retour Chariot) pour les lignes.
#define DEFAULT_IMPORTSEPARATOR	_X(",\x07F\"\x07F")XRC

// Valeur de TimeOut par défaut
// Les TimeOut de connexion et de commande sont utilisés sur OLE DB pour déterminer la durée maximale d'une opération
// Si la valeur DEFAULTTIMEOUT est utilisée, les propriétés de TimeOut de connexion et de commande de la connexion OLE DB
// ne sont pas spécifiées par HF : ce sont donc les valeurs par défaut du provider OLE DB qui seront utilisées.
// A titre indicatif : 
// TimeOut de connexion = 15 sec 
// TimeOut de commande	= 30 sec 
#define DEFAULTTIMEOUT			-1

// Noms des providers "Accès Natif"
#define HNATIVEACCESS_AS400					_X("WinDevAS400")			// Nom du provider Accès Natif AS400
#define HNATIVEACCESS_ORACLE				_X("WinDevOracle")			// Nom du provider Accès Natif Oracle
#define HNATIVEACCESS_SQLServer				_X("WinDevSQLServer")		// Nom du provider Accès Natif SQLServer
#define HNATIVEACCESS_SQLAzure				_X("WinDevSQLAzure")		// Nom du provider Accès Natif SQLServer
#define HNATIVEACCESS_HF7					_X("WinDevHF7")				// Nom du provider HF7 (utilisé pour passer des fichiers "natifs" en HF7
#define HNATIVEACCESS_HF7_CLIENT_SERVEUR	_X("WinDevClientServeurHF") // Nom du provider HF7 client serveur
#define HNATIVEACCESS_XBase					_X("WinDevXBase")			// Nom du provider Accès Natif XBase
#define HNATIVEACCESS_MySQL					_X("WinDevMySQL")			// Nom du provider Accès Natif MySQL
#define HNATIVEACCESS_POSTGRESQL			_X("WinDevPostgreSQL")		// Nom du provider Accès Natif PostgreSQL
#define HNATIVEACCESS_Informix				_X("WinDevInformix")		// Nom du provider Accès Natif Informix
#define HNATIVEACCESS_DB2					_X("WinDevDB2")				// Nom du provider Accès Natif DB2
#define HNATIVEACCESS_Sybase				_X("WinDevSybase")			// Nom du provider Accès Natif Sybase
#define HNATIVEACCESS_Progress				_X("WinDevProgress")		// Nom du provider Accès Natif Progress
#define HNATIVEACCESS_XML					_X("WinDevXML")				// Nom du provider Accès Natif XML
#define HNATIVEACCESS_ORACLELITE			_X("WinDevOracleLite")		// Nom du provider Accès Natif Oracle Lite
#define HNATIVEACCESS_SQLServerCE			_X("WinDevSQLServerMobile")	// Nom du provider Accès Natif SQLServerCE
#define HNATIVEACCESS_SQLITE				_X("WinDevSQLite")			// Nom du provider Accès Natif SQLLite

// Type des provider
// Si rajout d'un provider, rajouter dans eNA_PROVIDEr de NAHFConstant.h (même valeur) et dans CNAHFConvertConst::eConvertePROVIDERtoeNA_PROVIDER
enum ePROVIDER { eNOTDEFINED, eHF7, eOLEDB, eORACLE, eSQLSERVER, eAS400, eXBASE, eMYSQL, eINFORMIX, eDB2, eSYBASE, ePROGRESS, eHF7_CLIENT_SERVEUR, eNXML, eORACLELITE, eSQLSERVERCE, ePOSTGRESQL, eSQLITE, eSQLAZURE };

#define HMINVAL   _X("\x00")	// hValMin utilisé dans HFiltre et HLitRecherche
#define HMAXVAL   _X("\xFF")	// hValMax utilisé dans HFiltre et HLitRecherche
#define HMAXVAL_A "\xFF"		// hValMax utilisé dans HFiltre et HLitRecherche
#define HMAXVAL_U L"\xFFFF"		// hValMax utilisé dans HFiltre et HLitRecherche


// Propriétés des objets HF
// rajout de propriétés :
//	- compléter __gtabProperty
//	- modifier les asserts dans PROP_bGetProperty et PROP_bSetProperty
typedef enum _eHPROPERTY
{
	HPROPNAME=0,               		// fichier, rubrique, liaison, connexion
	HPROPPHYSICALNAME,          	// =1 fichier
	HPROPDIRECTORY,             	// fichier
	HPROPDESCRIBEDNAME,          	// fichier
	HPROPDESCRIBEDPHYSICALNAME, 	// fichier
	HPROPDESCRIBEDDIRECTORY,    	// =5 fichier
	HPROPHUGEFILE,              	// fichier
	HPROPPASSWORDPROTECTED,     	// fichier
	HPROPNUMITEM,               	// fichier
	HPROPNUMKEY,                	// fichier
	HPROPNUMMEMO,               	// =10 fichier
	HPROPPHYSICALRECORDSIZE,    	// fichier
	HPROPTYPE,                  	// fichier, rubrique
	HPROPFORMAT,                	// fichier
	HPROPLOGMETHOD,             	// fichier
	HPROPSECURED,                	// =15 fichier
	HPROPFICCRYPTMETHOD,        	// fichier
	HPROPNDXCRYPTMETHOD,        	// fichier
	HPROPMMOCRYPTMETHOD,        	// fichier
	HPROPMMOPACKMETHOD,         	// fichier
	HPROPABBREVIATION,          	// =20 fichier
	HPROPREPLICATION,           	// fichier
	HPROPNUMARRAYELEMENT,          	// rubrique
	HPROPSIZE,                  	// rubrique
	HPROPDEFAULTVALUE,          	// rubrique
	HPROPKEYTYPE,               	// =25 rubrique
	HPROPKEYEXPRESSION,         	// rubrique
	HPROPACCENTSENSITIVE,          	// rubrique
	HPROPCASESENSITIVE,            	// rubrique
	HPROPPUNCTUATIONSENSITIVE,     	// rubrique
	HPROPPHYSICALINDICE,        	// =30 rubrique
	HPROPNUMCOMPONENT,          	// rubrique
	HPROPMEMO,                  	// rubrique
	HPROPLITERAL,               	// rubrique
	HPROPCOMPOSITEKEY,           	// rubrique
	HPROPCOMPONENT,             	// =35 rubrique
	HPROPNUMERICAL,             	// rubrique
	HPROPBINARY,                	// rubrique
	HPROPCAPTION,               	// rubrique, connexion
	HPROPSORTTYPE,             		// rubrique
	HPROPSOURCEFILE,            	// =40 liaison
	HPROPLINKEDFILE,            	// liaison
	HPROPSOURCEKEY,             	// liaison
	HPROPLINKEDKEY,             	// liaison
	HPROPSOURCECARDINALITYMIN,  	// liaison
	HPROPSOURCECARDINALITYMAX,  	// =45 liaison
	HPROPLINKEDCARDINALITYMIN,  	// liaison
	HPROPLINKEDCARDINALITYMAX,  	// liaison
	HPROPMODIFICATIONRULE,      	// liaison
	HPROPDELETIONRULE,          	// liaison
	HPROPDESCRIBEDLOGDIRECTORY,    	// =50 fichier
	HPROPTEXTITEMCOMPLETED,	    	// fichier
	HPROPCTUSERNAME,				// fichier
	HPROPCTDESCRIBEDUSERNAME,    	// fichier
	HPROPCTDESCRIBEDPASSWORD,    	// fichier
	HPROPCTDATABASE,		    	// =55 fichier
	HPROPCTDESCRIBEDDATABASE,    	// fichier
	HPROPCTDESCRIBEDCAPTION,    	// fichier
	HPROPCTACCESS,	    			// fichier
	HPROPCTDESCRIBEDACCESS,	    	// fichier
	HPROPCTOLEDBPROVIDER,	    	// =60 fichier
	HPROPCTDESCRIBEDOLEDBPROVIDER, 	// fichier
	HPROPWDD55,					 	// fichier
	HPROPNAME55,				 	// fichier
	HPROPWDD55PASSWORD,			 	// fichier
	HPROPGENERATIONNUMBER,		 	// =65 fichier
	HPROPLOGFILE,				 	// fichier
	HPROPTRANSACTIONFILE,		 	// fichier
	HPROPCONNECTIONTIMEOUT,			// connexion
	HPROPCONNECTIONCOMMANDTIMEOUT,	// connexion
	HPROPDESCRIBEDOPLOGDIRECTORY,	// =70 fichier
	HPROPINITIALITEM,				// rubrique (ItemData)
	HPROPINITIALFILE,				// rubrique (ItemData)
	HPROPYEAR,						// rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPMONTH,						// rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPDAY,						// =75 rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPHOUR,						// rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPMINUTE,					// rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPSECOND,					// rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPMILLISECOND,				// rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPDATE,						// =80 rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPTIME,						// rubrique (géré par la VM, renvoie une erreur si appelé dans HF)
	HPROPLOGDIRECTORY,    			// fichier
	HPROPLOGOPDIRECTORY,    		// fichier
	HPROPRPLDIRECTORY,    			// fichier
	HPROPRPLDESCRIBEDDIRECTORY,		// =85 fichier
	HPROPCTINITIALCATALOG,			// connexion : database
	HPROPCTEXTENDEDINFO,			// connexion : InfosEtendues
	HPROPCTOLEDBCURSOR,				// connexion : Options du curseur
	HPROPEXTENSION,					// fichier
	HPROPCTCACHESIZE,				// =90 connexion : taille du cache
	HPROPEXTENDEDINFO,				// fichier, rubrique, connexion
	HPROPNULL,						// rubrique
	HPROPCONNECTION,				// fichier
	HPROPMINIDAUTO,					// fichier
	HPROPMAXIDAUTO,					// =95 fichier
	HPROPNULLSUPPORTED,				// fichier supporte les Nulles
	HPROPCHARSET,					// fichier, alphabet associé
	HPROPFILTEREDITEM,				// fichier
	HPROPANALYSISGUID,				// fichier, GUID de l'analyse
	HPROPTABLEGUID,					// =100 fichier, GUID du fichier
	HPROPFILTERCONDITION,			// fichier
	HPROPFILTERWITHBOUNDS,			// fichier
	HPROPLOWERBOUND,				// fichier
	HPROPUPPERBOUND,				// fichier
	HPROPCRYPTMETHOD,				// =105 connexion
	HPROPACCESS,					// connexion
	HPROPSERVER,					// connexion
	HPROPSOURCE,					// connexion
	HPROPDATABASE,					// connexion
	HPROPPASSWORD,					// =110 connexion
	HPROPCURSOROPTION,				// connexion
	HPROPPROVIDER,					// connexion
	HPROPCACHESIZE,					// connexion
	HPROPUSER,						// connexion
	HPROPNBTHUMBNAIL,				// =115 rubrique
	HPROPMAXTHUMBNAILWIDTH,			// rubrique
	HPROPMAXTHUMBNAILHEIGHT,		// rubrique
	HPROPTHUMBNAIL,					// rubrique
	HPROPVISIBLEENDUSER,			// rubrique
	HPROPINFOTHUMBNAILGENERATION,	// =120 rubrique
	HPROPLOGBACKUPDIRECTORY,		// fichier
	HPROPNBDESCRIBEDTHUMBNAIL,		// rubrique
	HPROPEXECUTIONCOMPLETED,		// fichier (util pour vues ou requêtes)
	HPROPSQLCODE,					// code SQL
	HPROPINTEGERPART,				// partie entière
	HPROPDECIMALPART,				// partie décimale
	HPROPLOCALE,					// langue
	NOUVELENREGISTREMENT,			// fichier (en lecture seule)
	HPROPCOMPRESSION,				// connexion
	HPROPTAILLECLE,					// rubrique
	HPROPDESCRIBEDLOCALE,			// rubrique
	HPROPNULLALLOWED,				// rubrique
	HPROP_MAX						
}eHPROPERTY;

					 
//------------------------------------------------------------------------------------------//
//--- les constantes suivantes nécessitent une conversion (conversions à rajouter dans ConvertConst.h)
// Accès aux fichiers
typedef enum _eHACCESS
{
	HACCESS_MIN=1,
	HOREAD=HACCESS_MIN,						// accès au fichier en lecture
	HODEFAULT,								// accès au fichier par défaut (lecture/écriture si possible, sinon lecture)
	HOREADWRITE,							// accès au fichier en lecture/écriture
	HACCESS_MAX,
}eHACCESS;

// Gestion des type utilisateur des mémos binaires (précisés dans HAttacheMemo)
typedef enum _eHMEMOTYPE
{
	HMEMOTYPE_MIN=20,
	HMEMOTYPEIMG=HMEMOTYPE_MIN,				// type "IMG", fichier image
	HMEMOTYPEWAV,							// type "WAV", fichier son
	HMEMOTYPEOLE,							// type "OLE", fichier OLE
	HMEMOTYPEBIN,							// type "BIN", fichier autre binaire
	HMEMOSAVEWRITEOPENEDFILE=0x80000000,	// passer ce flag ou l'additionner à l'un des flags ci-dessous
											// pour permettre de charger un fichier ouvert en écriture par
											// une autre application
	HMEMOTYPE_MAX,
}eHMEMOTYPE;

// Méthodes de cryptage des fichiers HF
typedef enum _eHCRYPTMETHOD
{
	HCRYPTMETHOD_MIN=30,
	HCRYPTNO=HCRYPTMETHOD_MIN,				// pas de cryptage
	HCRYPTSTANDARD,							// cryptage PCSOFT
	HCRYPTRC5_12,							// cryptage RC5 12 boucles
	HCRYPTRC5_16,							// cryptage RC5 16 boucles
	HCRYPTMETHOD_MAX,
}eHCRYPTMETHOD;

// Méthodes de compression des mémo HF
typedef enum _eHPACKMETHOD
{
	HPACKMETHOD_MIN=40,
	HPACKNO=HPACKMETHOD_MIN,				// pas de compression
	HPACKLZW,								// compression LZW
	HPACKMETHOD_MAX,
}eHPACKMETHOD;

// Type de fichier
// rajout de type, compléter CContext::vbNeedParseKey
typedef enum _eHDATATYPE
{
	HDATATYPE_MIN=50,
	HFT_SQL=HDATATYPE_MIN,					// Fichier de type SQL
	HFT_NORMAL,								// Fichier normal
	HFT_TEMP,								// Fichier temporaire
	HFT_XBASE,								// Fichier xBase
	HFT_AS400,								// Fichier AS/400
//55
	HFT_MEMORY,								// Utilisé par HyperFIle pour les vues, ce n'est un type dans l'analyse
	HFT_HF5,								// Type HyperFile WinDev 5
	HFT_QUERY,								// Requete
	HFT_OTHER,								// autre
	HFT_NATIVE,								// Accès natif inconnu
//60
	HFT_OLEDB,								// OLE DB
	HFT_ORACLE,								// Accès natif Oracle
	HFT_SQLSERVER,							// Accès natif SQL Server
	HFT_QUERYNATIVE,						// Requête sur Accès natif inconnu
	HFT_QUERYOLEDB,							// Requête sur OLE DB
//65
	HFT_QUERYORACLE,						// Requête sur Accès natif Oracle
	HFT_QUERYSQLSERVER,						// Requête sur Accès natif SQL Server
	HFT_QUERYAS400,							// Requête sur Fichier AS/400
	HFT_QUERYXBASE,							// Requête sur Acces Natif AS400
	HFT_QUERYMYSQL,							// Requête sur Acces Natif MYSQL
//70
	HFT_QUERYINFORMIX,						// Requête sur Acces Natif INFORMIX
	HFT_QUERYDB2,							// Requête sur Acces Natif DB2
	HFT_MYSQL,								// Acces Natif MYSQL
	HFT_INFORMIX,							// Acces Natif INFORMIX
	HFT_DB2,								// Acces Natif DB2
//75
	HFT_SYBASE,								// Acces Natif SYBASE
	HFT_QUERYSYBASE,						// Requête sur Acces Natif SYBASE
	HFT_PROGRESS,							// Accès natif Progress
	HFT_QUERYPROGRESS,						// Requête sur Accès natif Progress
	HFT_CLIENT_SERVEUR,						// Fichier sur Serveur HyperFile
//80
	HFT_QUERY_CLIENT_SERVEUR,				// Requête sur Serveur HyperFile
	HFT_XML,								// Accès natif XML
	HFT_QUERYXML,							// Requête sur Accès natif XML
	HFT_ORACLELITE,							// Accès natif OracleLite
	HFT_SQLSERVERCE,						// Accès natif SQL Server CE
//85
	HFT_QUERYORACLELITE,					// Requête sur Accès natif OracleLite
	HFT_QUERYSQLSERVERCE,					// Requête sur Accès natif SQL Server CE
	HFT_QUERYPOSTGRESQL,					// Requête sur Accès natif PostgreSQL
	HFT_POSTGRESQL,							// Accès Natif PostgreSQL
	HFT_SQLITE,								// Accès Natif SQLite
	HFT_QUERYSQLITE,						// Requête sur Accès Natif SQLite
	HFT_SQLAZURE,							// Accès Natif SQLAzure
	HFT_QUERYSQLAZURE,						// Requête sur Accès natif SQL Azure

	HDATATYPE_MAX,
}eHDATATYPE;


// Type de rubrique	(valeurs compatibles 5.5)
typedef enum _eHITEMTYPE
{
	HIT_EMPTY		= 0,					// pas de type ou type inconnu
	HIT_TEXTE		= 2,					// texte
	HIT_REELTURBO	= 13,					// réel turbo
	HIT_NUMENR		= 8,					// numéro d'enregistrement
	HIT_HEURE		= 11,					// heure
	HIT_DATE8		= 14,					// date
	HIT_DATE6		= 10,					// date
	HIT_MEMOTEXTE	= 15,					// mémo texte
	HIT_MONETAIRE	= 17,					// monétaire
	HIT_MEMOBINAIRE	= 18,					// mémo binaire
	HIT_IMAGE		= 21,					// nom de fichier image
	HIT_IDAUTO		= 1,					// identifiant automatique
	HIT_I1			= 4,					// valeur entière signée sur 1 octet
	HIT_I2			= 3,					// valeur entière signée sur 2 octets
	HIT_I4			= 5,					// valeur entière signée sur 4 octets
	HIT_I8			= 19,					// valeur entière signée sur 8 octets
	HIT_R4			= 6,					// valeur réelle sur 4 octets
	HIT_R8			= 7,					// valeur réelle sur 8 octets
	HIT_UI1			= 12,					// valeur entière non signée sur 1 octet
	HIT_UI2			= 9,					// valeur entière non signée sur 2 octets
	HIT_UI4			= 22,					// valeur entière non signée sur 4 octets
	HIT_UI8			= 20,					// valeur entière non signée sur 8 octets
	HIT_CHAR		= 26,					// caractère
	HIT_BOOLEEN		= 27,					// booléen
	HIT_BINAIRE		= 23,					// chaîne binaire
	HIT_DATETIME	= 24,					// date+heure
	HIT_TIMELENGHT	= 25,					// durée
	HIT_MEMOBINAIRE4= 16,					// mémo binaire 4.0
	HIT_IDAUTO4		= 28,					// identifiant automatique sur 4 octets
	HIT_UNICODE		= 29,					// chaîne Unicode ( en 12 )
	HIT_MEMOUNICODE = 30,					// mémo contenant du texte Unicode
	HIT_DECIMAL		= 31,					// un numérique

	HIT_LAST		= HIT_DECIMAL
}eHITEMTYPE;

// types de journalisation
typedef enum _eHLOGMETHOD
{
	HLOGMETHOD_MIN=90,
	HNOLOG=HLOGMETHOD_MIN,					// pas de journalisation
	HLOGW,									// journalisation
	HLOGRW,									// journalisation
	HLOGMETHOD_MAX,
}eHLOGMETHOD;

// format de fichiers
typedef enum _eHFILEFORMAT
{
	HFILEFORMAT_MIN=100,
	HANSI=HFILEFORMAT_MIN,					// Chaines au format ANSI (windows)
	HUNICODE,								// Chaines au format UNICODE
	HFILEFORMAT_MAX,
}eHFILEFORMAT;


// Sous-type de fichier
typedef enum _eHSUBDATATYPE
{
	HSUBDATATYPE_MIN=110,
	HSDT_INVALID=HSUBDATATYPE_MIN,			// non définit
	HSDT_DBASE3,							// dBASE III
	HSDT_DBASE4,							// dBASE IV
	HSDT_FOXBASE,							// FoxBASE
	HSDT_CLIPPER5,							// Clipper 5
	HSDT_CLIPPER87,							// Clipper 87
	HSUBDATATYPE_MAX
}eHSUBDATATYPE;

//------------------------------------------------------------------------------------------//
//--- les constantes suivantes ne nécessitent pas de conversion

// constante pour la commande HDBTypeTri (valeurs compatibles 5.5)
typedef enum _eHDBSORTTYPE
{
	HDBSORTTYPE_MIN=0,
	HDBLEXICOGRAPHIC=HDBSORTTYPE_MIN,		// Tri lexicographique
	HDBASCII=1,								// Tri ascii
	HDBDONOTSETSORTTYPE=2,					// Pour juste connaître le type de tri sans le modifier
	HDBSORTTYPE_MAX,
}eHDBSORTTYPE;

// Gestion des mémos
typedef enum _eHMEMO
{
	HMEMO_MIN=1000,
	HMEMONO=HMEMO_MIN,						// les mémos ne sont pas gérés lors des lectures/modification de l'enregistrement
	HMEMOYES,								// les mémos textes sont gérés à chaque lecture/modification de l'enregistrement
	HMEMOAUTO,								// les mémos sont lus/modifiés lors de l'accès à la rubrique (fonctionnement par défaut)
	HMEMO_MAX,
}eHMEMO;

// Ordre de tri
typedef enum _eHORDER
{
	HORDER_MIN=1010,
	HINCREASING=HORDER_MIN,					// tri croissant
	HDECREASING,							// tri décroissant
	HNOTSORTED,								// pas de tri
	HORDER_MAX,
}eHORDER;

// Méthodes de blocage
typedef enum _eHLOCKMETHOD
{
	HLOCKMETHOD_MIN=1020,
	HLOCKMETHODDIRECT=HLOCKMETHOD_MIN,		// blocage direct
	HLOCKMETHODRESERVATION,					// blocage avec réservation
	HLOCKMETHOD_MAX,
}eHLOCKMETHOD;

// Méthodes d'ouverture des fichiers
typedef enum _eHMODE
{
	HMODE_MIN=1030,
	HMODEMONO=HMODE_MIN,					// mode mono-utilisateur
	HMODEMULTI,								// mode multi-utilisateur
	HMODE_MAX,
}eHMODE;

// Précision pour la méthode HPosition/HPositionne
typedef enum _eHPRECISION
{
	HPRECISION_MIN=1040,
	HPRECISIONLOW=HPRECISION_MIN,			// faible précision
	HPRECISIONMEDIUM,						// moyenne précision
	HPRECISIONHIGH,							// haute précision
	HPRECISION_MAX,
}eHPRECISION;

// Types de langage externe
typedef enum _eHEXLANGTYPE
{
	HEXLANG_MIN=1050,
	HEXLANG_C=HEXLANG_MIN,					// langage C/C++
	HEXLANG_MAX,
}eHEXLANGTYPE;

// Informations concernant une erreur
typedef enum _eHERRORINFO
{
	HEI_MIN=1070,
	HEI_MESSAGE=HEI_MIN,					// message d'erreur
	HEI_FILE,								// table concernée par l'erreur
	HEI_ITEM,								// rubrique concernée
	HEI_WDD,								// WDD concerné
	HEI_FIC,								// .FIC concerné
	HEI_NDX,								// .NDX concerné
	HEI_MMO,								// .MMO concerné
	HEI_LINK,								// liaison concernée
	HEI_SYSTEMERRORCODE,					// numéro d'erreur système
	HEI_SYSTEMERRORMESSAGE,					// message d'erreur système
	HEI_RECNUM,								// numéro de l'enregistrement
	HEI_INFO,								// message d'erreur + message système
	HEI_DEBUG,								// infos de debug interne PCSOFT
	HEI_BASECODE,							// code d'erreur renvoyé par le SGBD accédé en natif ou via OLEDB
	HEI_NATIVECODE,							// code d'erreur renvoyé par la dll d'accès natif ou OLEDB
	HEI_ADOCODE,							// code d'erreur renvoyé par ADO pour la dll OLEDB
	HEI_BASEMESSAGE,						// message d'erreur renvoyé par le SGBD accédé en natif ou via OLEDB
	HEI_NATIVEMESSAGE,						// message d'erreur renvoyé par la dll d'accès natif ou OLEDB
	HEI_ADOMESSAGE,							// message d'erreur renvoyé par ADO pour la dll OLEDB
	HEI_FULLERROR,							// dump complet de l'erreur
	HEI_INFOCLIENT,							// Accès natifs : infos sur la couche client utilisée par l'accès natif (typiquement = numéro de version du client)
	HEI_INFOSERVEUR,						// Accès natifs : infos sur le serveur utilisé par l'accès natif (typiquement = numéro de version du serveur)
	HEI_LOCKINFO,							// client/serveur HF : info sur l'erreur de blocage
	HEI_SERVEUR,							// nom du serveur HF C/S
	HEI_MAX,
}eHERRORINFO;

// Parcours des erreurs
typedef enum _eHERRORPARSE
{
	HEP_MIN=2000,
	HEP_CURRENT=HEP_MIN,					// erreur en cours
	HEP_MAIN,								// erreur principale
	HEP_SUBERRFIRST,						// première sous-erreur
	HEP_SUBERRLAST,							// dernière sous-erreur
	HEP_SUBERRNEXT,							// sous-erreur suivante
	HEP_SUBERRPREVIOUS,						// sous-erreur précédente
	HEP_MAX,
}eHERRORPARSE;

// Type de l'enregistrement dont on veut récupérer la valeur après un conflit
// de modification
typedef enum _eHRECTYPE_MODIFYCONFLICT
{
	HRECTYPE_MIN=2010,
	HRECREAD=HRECTYPE_MIN,				// enregistrement lu avant le HModifie
	HRECFILE,							// enregistrement dans le fichier
	HRECUSER,							// valeurs de l'utilisateur
	HRECTYPE_MAX,
}eHRECTYPE_MODIFYCONFLICT;

// Règles d'intégrité
typedef enum _eHINTEGRITYRULE
{
	HIR_MIN=2020,
	HIR_INTEGRITYNONE=HIR_MIN,			// pas de règle de suppression/modification
	HIR_INTEGRITYRESTRICT,				// suppression/modification interdite si enregistrement relié
	HIR_INTEGRITYCASCADE,				// suppression/modification en cascade
	HIR_INTEGRITYDEFAULT,				// affectation de la valeur par défaut à l'enreg relié
	HIR_MAX,
}eHINTEGRITYRULE;

// types de réplicat
typedef enum _eHREPLICAT
{
	HREPLICAT_MIN=2050,
	HNOREPLICAT=HREPLICAT_MIN,			// pas de réplication
	HMASTERREPLICAT,					// réplicat maitre
	HCONSUMERREPLICAT,					// réplicat abonné
	HREPLICATED,						// fichier répliqué mais on ne sais pas si maître ou abonné
	HREPLICAT_MAX,
}eHREPLICAT;

// types de réplicat
typedef enum _eHKEYTYPE
{
	HKEYTYPE_MIN=2060,
	HNOTAKEY=HKEYTYPE_MIN,				// pas clé
	HUNIQUEKEY,							// clé unique
	HDUPLICATESKEY,						// clé avec doublon
	HKEYTYPE_MAX,
}eHKEYTYPE;

// type du contenu des rubriques texte
typedef enum _eHCONTENTTYPE
{
	HCONTENTTYPE_MIN=2070,
	HNORMALCONTENT=HCONTENTTYPE_MIN,	// pas de contenu spécifique
	HRTFCONTENT,						// texte RTF
	HCONTENTTYPE_MAX,
}eHCONTENTTYPE;


// 2080 est utilisé plus loin


//------------------------------------------------------------------------------------------//
//--- les constantes de type flags (qui s'additionnent).
// Constantes de type UINT ou DWORD (entier non signé sur 32 bits)
// Les bits utilisés doivent être consécutif pour que CHECKFLAGS_IMPL fonctionne.

// Modes d'importation des fichiers pour la fonction HImporteTexte et HImporteHF55
typedef enum _eHIMPORTMODE
{
	HIMPORTMODE_MAX			= 0x00000001,
	HIMPCREATION			= HIMPORTMODE_MAX,	// Création du fichier où les enregistrements sont ajoutés (si le fichier ".Fic" existe déjà, il est écrasé)
	HIMPOEM2ANSI			= 0x00000002,		// (HImporteTexte uniquement) Conversion OEM vers ANSI des chaînes importées
	HIMPTESTDUPLICATES		= 0x00000004,		// Test des doublons lors de l'importation
	HIMPTESTINTEGRITY		= 0x00000008,		// Test de l'intégrité lors de l'importation
	HIMPNODELIMITER			= 0x00000010,		// (HImporteTexte uniquement) Les délimiteurs de chaînes ne sont pas pris en compte
	HDEFAULTVAL				= 0x00000020,		// Initialiser les rubriques non affectées à leurs valeurs par défaut
	HIMPIGNOREINVALIDLINE	= 0x00000040,		// (HImporteTexte uniquement) Les lignes de structure invalides sont ignorées (sinon erreur et arrêt de l'importation)
	HIMPIGNOREITEM			= 0x00000080,		// (HImportHF5 uniquement) Les rubriques n'ayant pas d'équivalence dans un des deux fichiers sont ignorées
	HIMPCONVERSION			= 0x00000100,		// (HImportHF5 uniquement) Tronquage/Conversion des rubriques de type différents
	HIMPNOSPACE				= 0x00000200,		// (HImportHF5 uniquement) Suppression des espaces de fin de chaîne
	HIMPNORMAL				= 0x00000400,		// Ajout des enregistrements importés au fichier (.FIC) existant (valeur par défaut)
	HCOPYAUTOID				= 0x00000800,		// Copier l'ID auto
	HCOPYRECORDDEFAULT		= 0x00001000,		// Valeur par défaut de flags de HCopieEnreg
	HIMPBREAKABLE			= 0x00002000,		// importation interruptible par ESC
	HIMPIGNOREEMPTYITEM		= 0x00004000,		// importation des rubriques non précisée dans le fichier texte à la valeur par défaut ou non (selon hValDefaut)
	HIMPIGNOREFIRSTLINE		= 0x00008000,		// ignore la première ligne
//	0x40000000,									// réservé pour usage interne
//	0x80000000,									// réservé pour usage interne
	HIMPORTMODE_MIN			= HIMPIGNOREEMPTYITEM,
}eHIMPORTMODE;

// Modes d'exportation des fichiers pour la fonction HExportXML
typedef enum _eHEXPORTMODE
{
	HEXPORTMODE_MAX			= 0x00000001,
	HEXPCREATION			= HEXPORTMODE_MAX,	// Création du fichier XML où les enregistrements sont ajoutés (si le fichier ".xml" existe déjà, il est écrasé)
	HEXPNORMAL				= 0x00000002,		// mode par défaut
	HEXPBREAKABLE			= 0x00000004,		// exportation interruptible par ESC
	HEXPWITHOUTXSL			= 0x00000008,		// ne pas générer de XSL avec le XML
	HEXPORTMODE_MIN			= HEXPWITHOUTXSL,
}eHEXPORTMODE;


// Options pour la réindexation (HReindexe)
typedef enum _eHNDXMODE
{
	HNDXMODE_MAX			= 0x00000001,
	HNDXCOMPACT				= HNDXMODE_MAX,		// réindexation avec compactage
	HNDXNOSTAT				= 0x00000002,		// réindexation sans calcul de stat
	HNDXNORMAL				= 0x00000004,		// réindexation classique (avec stat et sans compactage)
	HNDXSILENT				= 0x00000008,		// aucun affichage pendant la réindexation
	HNDXDELETE				= 0x00000010,		// réindexation avec suppression des enregistrements endommagés
	HNDXMINIMAL				= 0x00000020,		// réindexation ne prenant en compte que les clés corrompues
	HNDXCHECKMEMO			= 0x00000040,		// vérification des mémos
	//						  0x00000080,		// réservé par HCHANGECHARSET (changer l'alphabet courant par l'alphabet du ChangeAlphabet courant)
	HNDXNOCHECKFIC			= 0x00000100,		// ne pas faire de vérification du FIC
	HNDXFTX					= 0x00000200,		// reindexation du fulltext ( pas le ndx )
	HNDXTRYHOT				= 0x00000400,		// effectue une réindexation à chaud si possible
	HNDXFORCEHOT			= 0x00000800,		// effectue une réindexation à chaud, lance une erreur si pas possible
						   // 0x80000000,		// Réservé usage interne, ne pas utiliser
	HNDXMODE_MIN			= HNDXCHECKMEMO,
}eHNDXMODE;

// option pour l'optimisation planifiée
#define HOPTSTAT				0x00000001
#define HOPTINDEX				0x00000002

// type de liste à créer par HListeRubrique
typedef enum _eHLSTMODE
{
	// 0x00000001								// Réservé
	HLSTMODE_MAX			= 0x00000002,
	HLSTITEM				= HLSTMODE_MAX,		// liste les rubriques non clé
	HLSTKEY					= 0x00000004,		// liste les clés
	HLSTCOMPOSITEKEY		= 0x00000008,		// liste les clés composée
	HLSTMEMO				= 0x00000010,		// liste les mémo
	HLSTALL					= 0x00000020,		// dépend de la fonction qui l'utilise
												// HListeRubrique	: == HLSTITEM+HLSTKEY+HLSTCOMPOSITEKEY+HLSTMEMO
												// HListeCle		: == HLSTKEY+HLSTCOMPOSITEKEY == HLSTNORMAL
												// HListeFichier	: liste les fichiers déclarés en dynamique
	HLSTSORTED				= 0x00000040,		// liste triée
	HLSTDETAIL				= 0x00000080,		// liste détaillée
	HLSTNORMAL				= 0x00000100,		// valeur par défaut pour HListeXXX, liste par ordre physique (compatibilité 5.5)
	HLSTTABLE				= 0x00000200,		// Natif : Lister les tables (valeur par défaut)
	HLSTVIEW				= 0x00000400,		// Natif : Lister les Vues
	HLSTSYSTABLE			= 0x00000800,		// Natif : Lister les tables système
	HLSTSTOREDPROCEDURE		= 0x00001000,		// Natif : Lister les procédures stockées
	HLSTDETAILPLUS			= 0x00002000,		// liste détaillée ++ (partie entière et décimale renvoyée)
	HLSTLOGICALORDER		= 0x00004000,		// trié dans l'ordre logique
	HLSTITEMORIGINE			= 0x00008000,		// Lister les rubriques du fichier d'origine (option valide uniquement sur un fichierJNL)
	HLSTOPENED				= 0x00010000,		// Lister les connexions ouvertes
	HLSTSTOREDCOLLECTION	= 0x00020000,
	HLSTQUERY				= 0x00040000,		
	HLSTDETAILGUID			= 0x00080000,		// rajoute l'info du GUID des rubrique
	//						= 0x80000000,		// réservé usage interne
	HLSTMODE_MIN			= HLSTOPENED,
}eHLSTMODE;

// Options de blocages/ajout/modif
typedef enum _eHPARSEMODE
{
	//						  0x00000001		// Réservé usage interne, ne pas utiliser
	//						  0x00000002		// Réservé usage interne, ne pas utiliser
	//						  0x00000004		// Réservé usage interne, ne pas utiliser
	HPARSEMODE_MAX			= 0x00000008,
	HLOCKNO					= HPARSEMODE_MAX,	// pas de blocage
	HLOCKWRITE				= 0x00000010,		// blocage en écriture
	HLOCKREADWRITE			= 0x00000020,		// blocage en lecture/écriture
	HAFFECTBROWSE			= 0x00000040,		// L'écriture affecte les parcours (fonctionnement de HyperFile 5)
	HPARSEMODEDEFAULT		= 0x00000080,		// Valeur par défaut (différente signification selon les fonctions)
	HSETIDAUTO				= 0x00000100,		// Force l'identifiant auto à la valeur actuelle lors de l'ajout/mofif de l'enregistrement
	HRECALCULATEIDAUTO		= 0x00000200,		// Calcule un identifiant auto pour HEcrit
	HFORCEIDAUTO			= 0x00000400,		// Si l'identifiant auto de l'enregistrement est supérieur à celui du fichier, on n'augmente pas celui du fichier
	HDISTINCT				= 0x00000800,		// HLitSuivant... en sautant les doublons
	HGENERIC				= 0x00001000,		// HLitRechercheXXX... générique
	HNOREFRESH				= 0x00002000,		// Ne pas rafraichir les enregistrements (OLEDB : rafraichissement entraine perte de toutes les positions sauvegardées)
	HKEEPFILTER				= 0x00004000,		// Tenir compte du filtre même si le parcours ou la recherche ne se fait pas sur la clé renvoyée par HFiltre
	HIGNOREDUPLICATES		= 0x00008000,		// Ignorer les doublons même si branché par HGèreDoublon
	HIGNOREINTEGRITY		= 0x00010000,		// Ignorer l'intégrité même si branchée par HGèreIntégrité
	HCHECKDUPLICATES		= 0x00020000,		// Tester les doublons même si débranché par HGèreDoublon
	HCHECKINTEGRITY			= 0x00040000,		// Tester l'intégrité même si débranchée par HGèreIntégrité
	HIDENTICAL				= 0x00080000,		// HLitRechercheXXX... à l'identique
	HSQLFETCH				= 0x00100000,		// Parcours avec SQLFetch (ne pas mettre en cache les enregistrements)
	HLIMITPARSING			= 0x00200000,		// Positionne HEnDehors à Vrai si on sort de la recherche (optimise les accès natifs)
	// 						  0x00400000,		// Réservé usage interne, ne pas utiliser
	// 						  0x00800000,		// Réservé usage interne, ne pas utiliser
	// 						  0x01000000,		// Réservé usage interne, ne pas utiliser
	// 						  0x02000000,		// Réservé usage interne, ne pas utiliser
	// 						  0x04000000,		// Réservé usage interne, ne pas utiliser
	// 						  0x08000000,		// Réservé usage interne, ne pas utiliser
	// 						  0x10000000,		// Réservé usage interne, ne pas utiliser
	// 						  0x20000000,		// Réservé usage interne, ne pas utiliser
	// 						  0x40000000,		// Réservé usage interne, ne pas utiliser
	// 						  0x80000000,		// Réservé usage interne, ne pas utiliser
	HPARSEMODE_MIN			= HLIMITPARSING,
}eHPARSEMODE;

// Gestion des description
typedef enum _eHDESCRIPTION
{
	HDESCRIPTION_MIN=2080,
	HSTRICT=HIDENTICAL,			// les structures des fichiers HF7 doivent être identiques entre le fichier physique et l'analyse
	HCOMPATIBLE,				// les structures des fichiers HF7 peuvent être un peu différentes entre le fichier physique et l'analyse
	HNOCHECK,					// les structures des fichiers HF7 peuvent être complètement différentes entre le fichier physique et l'analyse
	HDESCRIPTION_MAX,
}eHDESCRIPTION;


// Différents états que peut prendre un enregistrement
typedef enum _eHRECORDSTATE
{
	HRECORDSTATE_MIN		= 0x00000001,
	HSTATEACTIVE			= HRECORDSTATE_MIN,	// enregistrement actif
	HSTATECROSSED			= 0x00000002,		// enregistrement rayé
	HSTATEDELETED			= 0x00000004,		// enregistrement supprimé
	HSTATEALLSTATES			= 0x00000008,		// tous les états autres que _55
	HSTATEACTIVE_55			= 0x00000010,		// pour le nombre d'enregistrements actifs en mode 55 (usage interne HF)
	HSTATEDELETED_55		= 0x00000020,		// pour le nombre d'enregistrements supprimés en mode 55 (usage interne HF)
	HSTATEINVALID			= 0x00000040,		// état invalide
	HSTATE_NOWAIT			= 0x80000000,		// pour vues et requêtes, non bloquant, renvoie ce qu'on a au moment de l'appel
	HRECORDSTATE_MAX		= HSTATE_NOWAIT,
}eHRECORDSTATE;

// Type d'erreur nécessitant une assistance automatique de HF
// (affichage d'une fenêtre ou appel d'une procédure)
typedef enum _eHERRORASSISTED
{
	HEA_LOCK				= 0x00000001,		// blocage
	HEA_MODIFY				= 0x00000002,		// conflit de modification
	HEA_DUPLICATES			= 0x00000004,		// doublon
	HEA_INTEGRITY			= 0x00000008,  		// integrité
	HEA_PASSWORD			= 0x00000010,		// mot de passe
	HEA_ALL					= 0x00000020,		// toutes les erreurs
	HEA_REINDEXE			= 0x00000080,		// réindexation en cours
	HEA_NEEDITEMVALUE		= 0x00000100,		// valeur de rubrique obligatoire
	HEA_DATABASE_LOCK		= 0x00000200,		// blocage d'une base de données
	HEA_DECONNEXION			= 0x00000400,		// perte de la connexion avec le serveur HF C/S
	HEA_INVALID				= 0x00000040,		// erreur inconnue (pas d'assistance)
}eHERRORASSISTED;

// Mode d'exécution du snapshot
typedef enum _eHVIEWMODE
{
	HVIEWDEFAULT			= 0x00000000,		// valeur par défaut
	// 0x00000001,								// Réservé
	HVIEWPOSTPONED			= 0x00000002,		// vue exécutée en différé
	HVIEWLOCKING			= 0x00000004,		// enregistrement bloqués dans la source
	HVIEWDISTINCT			= 0x00000008,		// suppression des doublons lors de l'extraction
	HVIEWEXCLUSIVE			= 0x00000010,		// ouverture du fichier en exclusif pour optimiser la création
	HVIEWADD				= 0x00000020,		// un prochain HExecuteVue complètera la vue actuelle
	HVIEWBREAKABLE			= 0x00000040,		// traitement interruptible
	HVIEWUNION				= 0x00000080,
	HVIEWUNIONEX			= 0x00000100,
	HVIEWINTERSECTION		= 0x00000200,
	HVIEWSUBTRACTION		= 0x00000400,
	HVIEWJOIN				= 0x00000800,
	HVIEWWAITTHREAD			= 0x00001000,		// INTERNE : on attend la fin du thread pour rendre la main
	HVIEWMODIFYFILE			= 0x00002000,		// INTERNE : les modifications sont directement reportées dans les fichiers
	//	__HVIEWFOREXIST		= 0x00010000,		// Réservé usage interne, ne pas utiliser
	//                        0x00020000 réservé pour HCHECKDUPLICATES
	//                        0x00040000 réservé pour HCHECKINTEGRITY
	//	__HVIEWCS			= 0x00080000,		// Réservé usage interne, ne pas utiliser
	HVIEWYIELD				= 0x00100000,		// Inutilisé pour le moment. Même valeur que HQUERYYIELD si on veut brancher hTemporise sur HVueVersFichier
	//                        0x00200000 reservé par la constante HWITHTRANSACTION
	//						  0x00400000		// Réservé usage interne, ne pas utiliser
}eHVIEWMODE;

// Mode d'exécution de la requête
typedef enum _eHQUERYMODE
{
	HQUERYDEFAULT			=  0x00000000,					// valeur par défaut
	// 0x00000001,											// Réservé usage interne, ne pas utiliser
	HQUERYBREAKABLE			=  0x00000002,					// traitement interruptible
	HQUERYNATIVE			=  0x00000004,					// Requête sur l'accès natif ne devant pas être "corrigée" par HF
	HQUERYDYNAMICBROWSE		=  0x00000008,					// Requête dynamique si possible (sans vue)
	HQUERYNOTCORRECTEDONHF	=  0x00000010,					// Requête sur HF ne devant pas être "corrigée"
	HQUERYNOBIND			=  0x00000020,					// Pas de bind sur l'exécution de la requête
	HQUERYUNICODE			=  0x00000040,					// la chaine utilisé dans HExecuteRequeteSQL a été fourni en Unicode par l'utilisateur
	HQUERYMODIFYFILE		=/*0x00002000*/HVIEWMODIFYFILE,	// Les modifs sont reportées dans les fichiers
	// __HQUERYFOREXIST		=  0x00010000,					// Réservé usage interne, ne pas utiliser
	//                         0x00020000 réservé pour HCHECKDUPLICATES
	//                         0x00040000 réservé pour HCHECKINTEGRITY	
	// __HQUERYCS			=  0x00080000					// Réservé usage interne, ne pas utiliser			
	HQUERYYIELD				=/*0x00100000*/HVIEWYIELD,		// Temporisation pour requête UPDATE et DELETE pour laisser la main aux autres applications
	HWITHTRANSACTION		=  0x00200000,					// Une transaction est démarrée pour la requête (UPDATE/DELETE)
	// __HQUERYOPTIMIZ		=  0x08000000,					// Réservé usage interne, ne pas utiliser
	// __HQUERYINITTABLE	=  0x10000000,					// Réservé usage interne, ne pas utiliser
	// __HQUERYDUPLIQUE		=  0x20000000,					// Réservé usage interne, ne pas utiliser
	// __HQUERYPREPARE		=  0x40000000,					// Réservé usage interne, ne pas utiliser
	// __HQUERYMINIMAL		=  0x80000000,					// Réservé usage interne, ne pas utiliser
}eHQUERYMODE;


// options de la HListeREP
typedef enum _eHREP
{
	HREPEXISTING			= 0x00000001,		// récupérer uniquement les affectations dont le fichier existe
	HREPDEFAULT				= 0x00000000,		// valeur par défaut (0 pour compatibilité 5)
}eHREP;

// options de la HSauvePosition
typedef enum _eHSAUVEPOSITION
{
	HSPSAVEITEMSVALUE		= 0x00000001,
	HSPNOFILTER				= 0x00000002,		// ne pas sauver le filtre ( optimisation champ table pour Accès natifs )
}eHSAUVEPOSITION;

// options de la HRetourPosition
typedef enum _eHRETOURPOSITION
{
	HRETOURPOSITION_MAX		= 0x00000001,
	HRPHF5					= HRETOURPOSITION_MAX,	// HRetourPosition à la HF5 (relit l'enreg même s'il est supprimé, modifié)
	HRPKEEP					= 0x00000002,		// ne pas libérer la position
	HRPDEFAULT				= 0x00000004,		// valeur par défaut
	HRPFILTER				= 0x00000008,		// retauration du filtre posé au moment du HSauvePosition
	// 0x01000000,	// Réservé usage interne, ne pas utiliser ( __HRPTABLEMODE )
	// 0x02000000,	// Réservé usage interne, ne pas utiliser
	// 0x10000000,	// Réservé usage interne, ne pas utiliser
	// 0x20000000,	// Réservé usage interne, ne pas utiliser ( __HPARSEINTEGRITY )
	// 0x40000000,	// Réservé usage interne, ne pas utiliser
	// 0x80000000,	// Réservé usage interne, ne pas utiliser
	HRETOURPOSITION_MIN		= HRPFILTER,
}eHRETOURPOSITION;

// Différentes règles d'intégrité
typedef enum _eHRULE
{
	HRULE_MAX				= 0x00000001,
	HCARDINALITY			= HRULE_MAX,		// règle sur les cardinalités
	HONUPDATE				= 0x00000002,		// règle sur une modification
	HONDELETE				= 0x00000004,		// règle sur une suppression
	HALLRULES				= 0x00000008,		// toutes les règles
	HRULE_MIN				= HALLRULES,
}eHRULE;

// Options de HRegenereFichier
typedef enum _eHREGENEREFICHIER
{
	HSTRUCTURE				= 0x00000001,		// régénèrer la structure du fichier (HCreation)
	HDATA					= 0x00000002,		// Rejouer l'intégralité du journal
}eHREGENEREFICHIER;

// Types de trigger
typedef enum _eHTRIGGERTYPE
{
	HTRIGGERBEFORE			= 0x00000001,		// pour que la procédure W-Langage soit exécutée avant la fonction Hyper File
	HTRIGGERAFTER			= 0x00000002,		// pour que la procédure W-Langage soit exécutée après la fonction Hyper File
}eHTRIGGERTYPE;

// Types d'opération de test (HConnecteOLEDB)
typedef enum _eHTESTOPERATION
{
	HCUNSPECIFIED			= 0x00000000,
	HCHCREATIONSIINEXISTANT	= 0x00000001,
	HCHOUVRE				= 0x00000004,
}eHTESTOPERATION;

// Types d'opération de transaction (SQLTransaction)
typedef enum _eSQLTRANSACTIONOP
{
	SQLTRANSACTIONBEGIN		= 0x00000001,		// Compatibilité HF5
	SQLTRANSACTIONCOMMIT	= 0x00000002,		// Compatibilité HF5
	SQLTRANSACTIONROLLBACK	= 0x00000003,		// Compatibilité HF5
}eSQLTRANSACTIONOP;

// Options du curseur ADO
typedef enum _eADOCURSOROPTIONS
{
	HSERVERCURSOR			= 0x00000001,		// Curseur serveur
	HCLIENTCURSOR			= 0x00000002,		// Curseur client
	HDYNAMICCURSOR			= 0x00000004,		// Curseur dynamique	(à utiliser avec HSERVERCURSOR)
	HOPENKEYSETCURSOR		= 0x00000008,		// Curseur OpenKeyset	(à utiliser avec HSERVERCURSOR)
	HSTATICCURSOR			= 0x00000010,		// Curseur statique
	HLOCKREADONLY			= 0x00000020,		// Accès aux enregistrements en lecture seule
	HLOCKPESSIMISTIC		= 0x00000040,		// Blocage pessimiste de l'enregistrement lu (bloqué dès qu'il est lu)
	HLOCKOPTIMISTIC			= 0x00000080,		// Blocage optimiste de l'enregistrement lu (bloqué uniquement au moment de la mise à jour)
	HFORWARDONLYCURSOR		= 0x00000100,		// Curseur ForwardOnly
}eADOCURSOROPTIONS;

// Mode d'exécution de la requête
typedef enum _eHCREATEMODE
{
	HDELAYEDOPENING		= 0x00000001,		// ouverture différée si le fichier existe lors du HCréationSiInexistant
	HCHANGECHARSET		= 0x00000080,		// changer l'alphabet courant par l'alphabet du ChangeAlphabet courant
	HNOLINK				= 0x00000100,		// mise à jour des règles d'intégrité lors de la création du fichier
	//					  0x00800000,		// Réservé usage interne, ne pas utiliser
	//					  0x04000000,		// Réservé usage interne, ne pas utiliser
	//					  0x10000000,		// Réservé usage interne, ne pas utiliser
	//					  0x20000000,		// Réservé usage interne, ne pas utiliser
	//					  0x40000000,		/  Réservé usage interne, ne pas utiliser
	//					  0x80000000,		/  Réservé usage interne, ne pas utiliser
}eHCREATEMODE;

// Mode d'exécution de la requête
// Utilisé pour HChangeRepJNL + HJournalRecree
typedef enum _eHCHANGEREPJNL
{
	HJOURNALOP			= 0x00000001,		// Changer l'emplacement du fichier journal des opérations
	HJOURNALID			= 0x00000002,		// Changer l'emplacement du fichier journal d'identification des fichiers
	HJOURNALFICHIERJNL	= 0x00000004,		// fichier JNL
	HJOURNALUSERS		= 0x00000008,		// Pour HJournalRecree ( en C/S ) : fichier des utilisateurs
}eHCHANGEREPJNL;


// Constantes pour  HGèreServeur
// (live) = appliqué en live par HGereServeur sans avoir à redémarrer le serveur
// (restart) = nécessite un redémarrage du serveur pour être pris en compte
typedef enum _eHSERVERMANAGMENT
{
	HLOGLEVEL			= 0x00000001,		// (live) Niveau des logs du serveur
	HMAXLOGSIZE			= 0x00000002,		// (live) Taille d'un fichier de log
	HLOGPATH			= 0x00000008,		// (live) Chemin des fichiers de log
	HNDXFILECACHESIZE	= 0x00000010,		// (live) Taille du cache des fichiers d'index
	HACTIVITYSTATPERIOD	= 0x00000020,		// (live) Période d'échantillonage des statistiques d'activité
	HMAXACTIVITYSTATSIZE= 0x00000040,		// (live) Taille maxi du fichier des statistiques d'activité
	//--------------------------------------------------------------------------------------------------
	// HLB_ -> répartition de charge, paramétrage très avancé
	// Les coef servent à faire varier l'importance de chaque compteur dans la formule de calcul de la charge
	// engendrée par un utilisateur sur le serveur
	HLB_COEFFNETSEND	= 0x00000050,		// (live) Coef. pour nombre d'octets/s envoyés sur le réseau
	HLB_COEFFNETRECV	= 0x00000051,		// (live) Coef. pour nombre d'octets/s reçus sur le réseau
	HLB_COEFFDISKBYTE	= 0x00000052,		// (live) Coef. pour nombre d'octets/s lus ou écrits sur disque
	HLB_COEFFDISKACCESS	= 0x00000053,		// (live) Coef. pour nombre d'accès/s au disque
	HLB_COEFFCLIENTCALL	= 0x00000054,		// (live) Coef. pour nombre d'appels/s du client
	HLB_MAXWAIT			= 0x00000055,		// (live) Temps d'attente max (ms) pour une tâche effectué par la répartition de charge sur le serveur
	HLB_ENABLE			= 0x00000056,		// (live) Activation/désactivation de la répartition de charge
	//--------------------------------------------------------------------------------------------------
	HACTIVITYSTATPATH	= 0x00000080,		// (live) Chemin du fichier des statistiques d'activité
	HDATABASEPATH		= 0x00000100,		// (restart) Chemin des bases de données
	HSERVERPORT			= 0x00000200,		// (restart) Port du serveur
	HMODE2GB			= 0x00000400,		// (restart) Fichiers systèmes en mode >2Go
	HJNLPATH			= 0x00000800,		// (restart) Chemin des journaux
	HJNLBACKUPPATH		= 0x00001000,		// (restart) Chemin des backup des journaux
	HDAEMONUSER			= 0x00002000,		// (restart) Nom du user qui lance le serveur sous Linux
	HDEBUGGER_PORT		= 0x00004000,		// (live) Port utilisé par le debuggeur (procédures stockée)
}eHSERVERMANAGMENT;

// pour HInfoLog
typedef enum _eHINFOLOG
{
	H_INFOLOG_MAP		= 0x00000001
} eHINFOLOG;


// Localisation des fichiers pour HChangeLocalisation et HDeclare
typedef enum _eHLOCATION
{
	HLOCWDL					= 0x00000001,		// chercher les fichiers dans la WDL puis sur disque
	HLOCDISK				= 0x00000002,		// chercher les fichiers uniquement sur disque
}eHLOCATION;

#define HRPCPAGESIZE_INTERNET	100
#define HRPCPAGESIZE_NETWORK	100000


// type d'info demandé à HInfoServeur
#define SERVER_VI				0x00000001	
#define SERVER_VERSION			0x00000002
#define SERVER_OS				0x00000004
#define SERVER_CPU				0x00000008
#define SERVER_NAME				0x00000010
#define SERVER_LOGICAL_NAME		0x00000020
#define SERVER_DATE_TIME		0x00000040
#define SERVER_VERSION_DETAIL	0x00000080
#define SERVER_DISK_SIZE		0x00000100
#define SERVER_DISK_FREE		0x00000200
#define SERVER_INFO_CLUSTER		0x00000400
#define SERVER_HOSTNAME			0x00000800
#define SERVER_MEMORY_USAGE		0x80000000

#define SERVER_ALL				0x0000007F


typedef enum _eHCOPIE_FICHIER_MODE
{
	NDX_COPY,								// HCopieFichier copie l'index
	NDX_WITHOUT,							// HCopieFichier ne copie pas l'index
	NDX_REINDEX,							// HCopieFichier ne copie pas l'index et recrée l'index (réindexation)
}eHCOPIE_FICHIER_MODE;

#define HCOPIE_FICHIER_DONT_OVERRIDE	0x00000100

// mode pour la fonction HInfoFichier
#define 	HINFOFICHIER_TAILLE_FIC		0x00000001  // HInfoFichier renvoie la taille du FIC
#define 	HINFOFICHIER_TAILLE_NDX		0x00000002  // HInfoFichier renvoie la taille de l'index
#define 	HINFOFICHIER_TAILLE_MMO		0x00000004  // HInfoFichier renvoie la taille du fichier des mémo
#define 	HINFOFICHIER_TAILLE_FTX		0x00000008  // HInfoFichier renvoie la taille du fichier des ftx

#define 	HINFOFICHIER_TAILLE_TOTAL	0x0000FFFF  // HInfoFichier renvoie la somme des tailles du FIC,NDX,et MMO


//////////////////////////////////////////////////////////////////////////
//	PARAMETRES DU CACHE
//////////////////////////////////////////////////////////////////////////

// paramètres par défaut des pages du cache client
#ifdef UNDER_CE
	#define	CS_DEFAULT_MINIMAL_SEND			1
	#define	CS_DEFAULT_MAXIMAL_PREPARED		1
	#define	CS_DEFAULT_PAGE_SIZE			10
#else // #ifdef UNDER_CE
	#define	CS_DEFAULT_MINIMAL_SEND			1
	#define	CS_DEFAULT_MAXIMAL_PREPARED		50
	#define	CS_DEFAULT_PAGE_SIZE			1000
#endif // #else // #ifdef UNDER_CE

#define PARAM_CACHE_SIZE	1

//////////////////////////////////////////////////////////////////////////
//	Gestion des droits
//////////////////////////////////////////////////////////////////////////
#define HRIGHTS_ALL						_X("ALL#")

#define	HRIGHTS_CREATE_DB				_X("A#")
#define	HRIGHTS_DELETE_DB				_X("B#")
#define	HRIGHTS_CONNECTION				_X("C#")
#define	HRIGHTS_ENCRYPTED_CONNECTION	_X("D#")
#define	HRIGHTS_CREATE_FILE				_X("E#")
#define	HRIGHTS_READ					_X("F#")
#define	HRIGHTS_INSERT					_X("G#")
#define	HRIGHTS_UPDATE					_X("H#")
#define	HRIGHTS_DELETE					_X("I#")
#define	HRIGHTS_DELETE_FILE				_X("J#")
#define	HRIGHTS_AUTO_MODIF				_X("K#")
#define	HRIGHTS_MAINTENANCE				_X("L#")
#define	HRIGHTS_CHANGE_LINK				_X("M#")
#define	HRIGHTS_LOCK					_X("N#")
#define	HRIGHTS_MANAGE_DUPLICATE		_X("O#")
#define	HRIGHTS_BECOME_OWNER			_X("P#")
#define	HRIGHTS_CHANGE_RIGHTS			_X("Q#")
#define	HRIGHTS_MANAGE_USERS			_X("R#")
#define HRIGHTS_STOP_SERVER				_X("S#")
#define HRIGHTS_CHANGE_PASSWORD			_X("T#")
#define HRIGHTS_CLIENT_DISCONNECT		_X("U#")
#define HRIGHTS_SEND_MESSAGE_TO_CLIENT	_X("V#")
#define HRIGHTS_NO_DATABASE_ACCESS		_X("W#")
#define HRIGHTS_MANAGE_INTEGRITY		_X("X#")
#define HRIGHTS_SEE_USERS				_X("Y#")
#define HRIGHTS_MANAGE_SERVER			_X("Z#")
#define HRIGHTS_PRIORITY				_X("AA#")
#define HRIGHTS_MANAGE_PROC				_X("AB#")
#define HRIGHTS_EXECUTE_PROC			_X("AC#")
#define HRIGHTS_DEBUG					_X("AD#")
#define HRIGHTS_BACKUP					_X("AE#")
#define HRIGHTS_TRIGGER					_X("AF#")
#define HRIGHTS_MANAGE_TASK				_X("AG#")
#define HRIGHTS_READ_LOG				_X("AH#")

#define HRIGHTS_ALL_FILE		       HRIGHTS_READ HRIGHTS_INSERT HRIGHTS_UPDATE HRIGHTS_DELETE HRIGHTS_DELETE_FILE HRIGHTS_AUTO_MODIF HRIGHTS_MAINTENANCE HRIGHTS_CHANGE_LINK HRIGHTS_LOCK HRIGHTS_MANAGE_DUPLICATE HRIGHTS_BECOME_OWNER HRIGHTS_CHANGE_RIGHTS  					
#define HRIGHTS_ALL_DATABASE		   HRIGHTS_ALL_FILE HRIGHTS_DELETE_DB HRIGHTS_CONNECTION HRIGHTS_ENCRYPTED_CONNECTION HRIGHTS_CREATE_FILE HRIGHTS_NO_DATABASE_ACCESS HRIGHTS_MANAGE_INTEGRITY HRIGHTS_MANAGE_PROC HRIGHTS_EXECUTE_PROC HRIGHTS_DEBUG HRIGHTS_BACKUP HRIGHTS_TRIGGER
#define HRIGHTS_ALL_SERVER			   HRIGHTS_CREATE_DB HRIGHTS_CHANGE_RIGHTS HRIGHTS_MANAGE_USERS HRIGHTS_STOP_SERVER	HRIGHTS_CHANGE_PASSWORD HRIGHTS_CLIENT_DISCONNECT HRIGHTS_SEND_MESSAGE_TO_CLIENT HRIGHTS_SEE_USERS HRIGHTS_MANAGE_SERVER HRIGHTS_PRIORITY HRIGHTS_MANAGE_TASK HRIGHTS_READ_LOG

#define	HRIGHTS_ALLOWED					_X("O")
#define	HRIGHTS_DENY					_X("N")
#define	HRIGHTS_NOT_DEFINED				_X("H")

// type des éléments sur lesquels s'applique les droits
typedef enum _eOBJECT_TYPE
{
	H_SERVER_OBJECT					= 0x00000001,		
	H_DATABASE_OBJECT				= 0x00000002,		
	H_FILE_OBJECT					= 0x00000004,
}eOBJECT_TYPE;

// type de droits et format de la chaine renvoyé par HInfoDroit
typedef enum _eRIGHTS_FORMAT
{
	HRIGHTS_DEFAULT			=	0x00000000,
	HRIGHTS_DETAIL			=	0x00000001,
	HRIGHTS_EFFECTIVE		=	0x00000002,
} eRIGHTS_FORMAT;

// méta informations
#define	HMETA_OWNER				_X("A#")
#define	HMETA_CREATOR			_X("B#")
#define	HMETA_DATE				_X("C#")
#define	HMETA_APP				_X("D#")
#define	HMETA_COMPUTER			_X("E#")
#define	HMETA_NOTES				_X("F#")	

// résultat de HEtatServeur
#define H_SERVER_NO_ACCESS		0x00000000
#define H_SERVER_STARTED		0x00000001
#define H_SERVER_STOPPED		0x00000002

// type d'action que le serveur demande aux client d'effectuer
	// 0x00000000 -> 0xFFFF0000 : réservé utilisateur
#define	H_ACTION_MESSAGE			0x40000000
#define	H_ACTION_CLOSE_CONNEXION	0x40000001
#define H_ACTION_ASSISTANCE_AUTO	0x40000002

// étendu de la suppression pour les ordres HSupprimeBaseDeDonnées et HSupprimeFichier
#define H_KEEP_TRS				0x00000001
#define H_REMOVE_JNL			0x00000002
#define H_DELETE_LINK			0x00000004

// valeur pour la variable HCS.TailleTrame
// taille limite du buffer pour un appel à l'API send
// Une valeur trop élevé peut poser problème à certain OS, ou provider WinSock
// une Valeur trop faible peut dégrader les performance
#define HTRAME_INTERNET				(9*1048576)
#define HTRAME_INTRANET				(11*1048576)
#define HTRAME_WIFI					(12*1024)
#define HTRAME_GPRS					(1*1024)
#define HTRAME_ACTIVESYNC			(10*1024)

// le 30/8/2006 : on utilise différentes valeurs par défaut car certain OS (PPC) sont trés sensible
#ifdef UNDER_CE
	#define HTRAME_DEFAUT						HTRAME_ACTIVESYNC
#else
	#define HTRAME_DEFAUT						HTRAME_INTRANET	
#endif

// Type de sortie pour HRécupèreEnregistrement
#define HUNICODE_OUTPUT			0x00000001

// Type de sauvegarde planifiée
#define		HSVG_FULL		0x00000000		/* Sauvegarde complète */
#define		HSVG_DIFF		0x00000001		/* Sauvegarde différentielle */
#define		HSVG_INTERNAL	0x00000002		/* sauvegarde pour traitement interne : reindexation, modif-auto, calcul stat */

#define		HSVG_DIFF_S			1
#define		HSVG_INTERNAL_S		2

#endif //#ifndef __HFCONSTANT_H



