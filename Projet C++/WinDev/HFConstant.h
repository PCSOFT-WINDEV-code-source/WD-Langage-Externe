//#6.00A	HFConstant.h	NF
// D�finition des valeurs des constantes de WDHF
// Constantes � exporter pour le langage externe
// Fichier destin� � �tre envoy� en client�le


#ifndef __HFCONSTANT_H
#define __HFCONSTANT_H

#define COMPONUM			7				// num�ro de la composante. TODO : � mettre ailleurs
#define CONSTANTBASE		(COMPONUM*10000)// nombre de base pour les constantes de la composante

//--- Types
typedef LONGLONG			RECNUM;			// type "num�ro d'enregistrement"
typedef int					HPOS;			// type "handle de position"


// ATTENTION, tailles � ne pas d�passer, on stock la taille des noms sur 1 octet
// Si plus grand, on devra modifier la structure des fichiers
#define SMAX_TABLENAME		255				// taille max du nom logique de la table
#define SMAX_LINKNAME		255				// taille max du nom d'une liaison
#define SMAX_ITEMNAME		255				// taille max du nom d'une rubrique

#define ALLTABLES			_X("*")			// cha�ne d�signant "toutes les tables"
#define ALLITEMS			_X("*")			// cha�ne d�signant "toutes les rubriques de la table"
#define ALLRELATIONS		_X("*")			// cha�ne d�signant "toutes les relations"
#define ALLPATH				_X("*")			// cha�ne d�signant "tous les chemins"
#define CURRENTDIR			_X(".")			// d�signe le r�pertoire courant
#define HCURRENTRECNUM		((RECNUM) 0)	// enregistrement courant
#define HINVALIDRECNUM		((RECNUM)-1)	// enregistrement invalide
#define HINVALIDPOS			((int)-1)		// handle de position invalide
#define HDEFAULTSIZE		(-1)			// demande � HF de d�terminer la taille du param�tre
#define	HSUCCES				0				// pas d'erreur

// Indice de rubrique tableau ind�fini.
// Equivaut � l'indice 1 pour les rubriques normales.
// Pour les rubriques tableau, est utilis� pour d�signer la rubrique dans sa totalit�.
#define INVALID_ITEMINDEX		-1
#define UNDEFINEDITEMDATASIZE	0			// taille de la donn�e non sp�cifi�e ( SetValueSize(ptr, size) ): 
											//		pour les chaines on utilise la taille de la chaine
											//		pour les rubriques de taille fixe,  on utilise la taille fix�e
											//		pour les rubriques binaires, provoque une erreur

#define HINFINITECARDINALITY	(-1)		// cardinalit� N d'une liaison

// pour HGereRep, ne pas mettre � jour le HFREP.INI
#define  HREP_SANSMAJINI		3


// les s�parateurs par d�faut utilis�s pour la fonction HImportTexte :
//		- la virgule pour les colonnes
//		- la double quote ( " ) pour les cha�nes
//		- RC (Retour Chariot) pour les lignes.
#define DEFAULT_IMPORTSEPARATOR	_X(",\x07F\"\x07F")XRC

// Valeur de TimeOut par d�faut
// Les TimeOut de connexion et de commande sont utilis�s sur OLE DB pour d�terminer la dur�e maximale d'une op�ration
// Si la valeur DEFAULTTIMEOUT est utilis�e, les propri�t�s de TimeOut de connexion et de commande de la connexion OLE DB
// ne sont pas sp�cifi�es par HF : ce sont donc les valeurs par d�faut du provider OLE DB qui seront utilis�es.
// A titre indicatif : 
// TimeOut de connexion = 15 sec 
// TimeOut de commande	= 30 sec 
#define DEFAULTTIMEOUT			-1

// Noms des providers "Acc�s Natif"
#define HNATIVEACCESS_AS400					_X("WinDevAS400")			// Nom du provider Acc�s Natif AS400
#define HNATIVEACCESS_ORACLE				_X("WinDevOracle")			// Nom du provider Acc�s Natif Oracle
#define HNATIVEACCESS_SQLServer				_X("WinDevSQLServer")		// Nom du provider Acc�s Natif SQLServer
#define HNATIVEACCESS_SQLAzure				_X("WinDevSQLAzure")		// Nom du provider Acc�s Natif SQLServer
#define HNATIVEACCESS_HF7					_X("WinDevHF7")				// Nom du provider HF7 (utilis� pour passer des fichiers "natifs" en HF7
#define HNATIVEACCESS_HF7_CLIENT_SERVEUR	_X("WinDevClientServeurHF") // Nom du provider HF7 client serveur
#define HNATIVEACCESS_XBase					_X("WinDevXBase")			// Nom du provider Acc�s Natif XBase
#define HNATIVEACCESS_MySQL					_X("WinDevMySQL")			// Nom du provider Acc�s Natif MySQL
#define HNATIVEACCESS_POSTGRESQL			_X("WinDevPostgreSQL")		// Nom du provider Acc�s Natif PostgreSQL
#define HNATIVEACCESS_Informix				_X("WinDevInformix")		// Nom du provider Acc�s Natif Informix
#define HNATIVEACCESS_DB2					_X("WinDevDB2")				// Nom du provider Acc�s Natif DB2
#define HNATIVEACCESS_Sybase				_X("WinDevSybase")			// Nom du provider Acc�s Natif Sybase
#define HNATIVEACCESS_Progress				_X("WinDevProgress")		// Nom du provider Acc�s Natif Progress
#define HNATIVEACCESS_XML					_X("WinDevXML")				// Nom du provider Acc�s Natif XML
#define HNATIVEACCESS_ORACLELITE			_X("WinDevOracleLite")		// Nom du provider Acc�s Natif Oracle Lite
#define HNATIVEACCESS_SQLServerCE			_X("WinDevSQLServerMobile")	// Nom du provider Acc�s Natif SQLServerCE
#define HNATIVEACCESS_SQLITE				_X("WinDevSQLite")			// Nom du provider Acc�s Natif SQLLite

// Type des provider
// Si rajout d'un provider, rajouter dans eNA_PROVIDEr de NAHFConstant.h (m�me valeur) et dans CNAHFConvertConst::eConvertePROVIDERtoeNA_PROVIDER
enum ePROVIDER { eNOTDEFINED, eHF7, eOLEDB, eORACLE, eSQLSERVER, eAS400, eXBASE, eMYSQL, eINFORMIX, eDB2, eSYBASE, ePROGRESS, eHF7_CLIENT_SERVEUR, eNXML, eORACLELITE, eSQLSERVERCE, ePOSTGRESQL, eSQLITE, eSQLAZURE };

#define HMINVAL   _X("\x00")	// hValMin utilis� dans HFiltre et HLitRecherche
#define HMAXVAL   _X("\xFF")	// hValMax utilis� dans HFiltre et HLitRecherche
#define HMAXVAL_A "\xFF"		// hValMax utilis� dans HFiltre et HLitRecherche
#define HMAXVAL_U L"\xFFFF"		// hValMax utilis� dans HFiltre et HLitRecherche


// Propri�t�s des objets HF
// rajout de propri�t�s :
//	- compl�ter __gtabProperty
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
	HPROPYEAR,						// rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPMONTH,						// rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPDAY,						// =75 rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPHOUR,						// rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPMINUTE,					// rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPSECOND,					// rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPMILLISECOND,				// rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPDATE,						// =80 rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
	HPROPTIME,						// rubrique (g�r� par la VM, renvoie une erreur si appel� dans HF)
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
	HPROPCHARSET,					// fichier, alphabet associ�
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
	HPROPEXECUTIONCOMPLETED,		// fichier (util pour vues ou requ�tes)
	HPROPSQLCODE,					// code SQL
	HPROPINTEGERPART,				// partie enti�re
	HPROPDECIMALPART,				// partie d�cimale
	HPROPLOCALE,					// langue
	NOUVELENREGISTREMENT,			// fichier (en lecture seule)
	HPROPCOMPRESSION,				// connexion
	HPROPTAILLECLE,					// rubrique
	HPROPDESCRIBEDLOCALE,			// rubrique
	HPROPNULLALLOWED,				// rubrique
	HPROP_MAX						
}eHPROPERTY;

					 
//------------------------------------------------------------------------------------------//
//--- les constantes suivantes n�cessitent une conversion (conversions � rajouter dans ConvertConst.h)
// Acc�s aux fichiers
typedef enum _eHACCESS
{
	HACCESS_MIN=1,
	HOREAD=HACCESS_MIN,						// acc�s au fichier en lecture
	HODEFAULT,								// acc�s au fichier par d�faut (lecture/�criture si possible, sinon lecture)
	HOREADWRITE,							// acc�s au fichier en lecture/�criture
	HACCESS_MAX,
}eHACCESS;

// Gestion des type utilisateur des m�mos binaires (pr�cis�s dans HAttacheMemo)
typedef enum _eHMEMOTYPE
{
	HMEMOTYPE_MIN=20,
	HMEMOTYPEIMG=HMEMOTYPE_MIN,				// type "IMG", fichier image
	HMEMOTYPEWAV,							// type "WAV", fichier son
	HMEMOTYPEOLE,							// type "OLE", fichier OLE
	HMEMOTYPEBIN,							// type "BIN", fichier autre binaire
	HMEMOSAVEWRITEOPENEDFILE=0x80000000,	// passer ce flag ou l'additionner � l'un des flags ci-dessous
											// pour permettre de charger un fichier ouvert en �criture par
											// une autre application
	HMEMOTYPE_MAX,
}eHMEMOTYPE;

// M�thodes de cryptage des fichiers HF
typedef enum _eHCRYPTMETHOD
{
	HCRYPTMETHOD_MIN=30,
	HCRYPTNO=HCRYPTMETHOD_MIN,				// pas de cryptage
	HCRYPTSTANDARD,							// cryptage PCSOFT
	HCRYPTRC5_12,							// cryptage RC5 12 boucles
	HCRYPTRC5_16,							// cryptage RC5 16 boucles
	HCRYPTMETHOD_MAX,
}eHCRYPTMETHOD;

// M�thodes de compression des m�mo HF
typedef enum _eHPACKMETHOD
{
	HPACKMETHOD_MIN=40,
	HPACKNO=HPACKMETHOD_MIN,				// pas de compression
	HPACKLZW,								// compression LZW
	HPACKMETHOD_MAX,
}eHPACKMETHOD;

// Type de fichier
// rajout de type, compl�ter CContext::vbNeedParseKey
typedef enum _eHDATATYPE
{
	HDATATYPE_MIN=50,
	HFT_SQL=HDATATYPE_MIN,					// Fichier de type SQL
	HFT_NORMAL,								// Fichier normal
	HFT_TEMP,								// Fichier temporaire
	HFT_XBASE,								// Fichier xBase
	HFT_AS400,								// Fichier AS/400
//55
	HFT_MEMORY,								// Utilis� par HyperFIle pour les vues, ce n'est un type dans l'analyse
	HFT_HF5,								// Type HyperFile WinDev 5
	HFT_QUERY,								// Requete
	HFT_OTHER,								// autre
	HFT_NATIVE,								// Acc�s natif inconnu
//60
	HFT_OLEDB,								// OLE DB
	HFT_ORACLE,								// Acc�s natif Oracle
	HFT_SQLSERVER,							// Acc�s natif SQL Server
	HFT_QUERYNATIVE,						// Requ�te sur Acc�s natif inconnu
	HFT_QUERYOLEDB,							// Requ�te sur OLE DB
//65
	HFT_QUERYORACLE,						// Requ�te sur Acc�s natif Oracle
	HFT_QUERYSQLSERVER,						// Requ�te sur Acc�s natif SQL Server
	HFT_QUERYAS400,							// Requ�te sur Fichier AS/400
	HFT_QUERYXBASE,							// Requ�te sur Acces Natif AS400
	HFT_QUERYMYSQL,							// Requ�te sur Acces Natif MYSQL
//70
	HFT_QUERYINFORMIX,						// Requ�te sur Acces Natif INFORMIX
	HFT_QUERYDB2,							// Requ�te sur Acces Natif DB2
	HFT_MYSQL,								// Acces Natif MYSQL
	HFT_INFORMIX,							// Acces Natif INFORMIX
	HFT_DB2,								// Acces Natif DB2
//75
	HFT_SYBASE,								// Acces Natif SYBASE
	HFT_QUERYSYBASE,						// Requ�te sur Acces Natif SYBASE
	HFT_PROGRESS,							// Acc�s natif Progress
	HFT_QUERYPROGRESS,						// Requ�te sur Acc�s natif Progress
	HFT_CLIENT_SERVEUR,						// Fichier sur Serveur HyperFile
//80
	HFT_QUERY_CLIENT_SERVEUR,				// Requ�te sur Serveur HyperFile
	HFT_XML,								// Acc�s natif XML
	HFT_QUERYXML,							// Requ�te sur Acc�s natif XML
	HFT_ORACLELITE,							// Acc�s natif OracleLite
	HFT_SQLSERVERCE,						// Acc�s natif SQL Server CE
//85
	HFT_QUERYORACLELITE,					// Requ�te sur Acc�s natif OracleLite
	HFT_QUERYSQLSERVERCE,					// Requ�te sur Acc�s natif SQL Server CE
	HFT_QUERYPOSTGRESQL,					// Requ�te sur Acc�s natif PostgreSQL
	HFT_POSTGRESQL,							// Acc�s Natif PostgreSQL
	HFT_SQLITE,								// Acc�s Natif SQLite
	HFT_QUERYSQLITE,						// Requ�te sur Acc�s Natif SQLite
	HFT_SQLAZURE,							// Acc�s Natif SQLAzure
	HFT_QUERYSQLAZURE,						// Requ�te sur Acc�s natif SQL Azure

	HDATATYPE_MAX,
}eHDATATYPE;


// Type de rubrique	(valeurs compatibles 5.5)
typedef enum _eHITEMTYPE
{
	HIT_EMPTY		= 0,					// pas de type ou type inconnu
	HIT_TEXTE		= 2,					// texte
	HIT_REELTURBO	= 13,					// r�el turbo
	HIT_NUMENR		= 8,					// num�ro d'enregistrement
	HIT_HEURE		= 11,					// heure
	HIT_DATE8		= 14,					// date
	HIT_DATE6		= 10,					// date
	HIT_MEMOTEXTE	= 15,					// m�mo texte
	HIT_MONETAIRE	= 17,					// mon�taire
	HIT_MEMOBINAIRE	= 18,					// m�mo binaire
	HIT_IMAGE		= 21,					// nom de fichier image
	HIT_IDAUTO		= 1,					// identifiant automatique
	HIT_I1			= 4,					// valeur enti�re sign�e sur 1 octet
	HIT_I2			= 3,					// valeur enti�re sign�e sur 2 octets
	HIT_I4			= 5,					// valeur enti�re sign�e sur 4 octets
	HIT_I8			= 19,					// valeur enti�re sign�e sur 8 octets
	HIT_R4			= 6,					// valeur r�elle sur 4 octets
	HIT_R8			= 7,					// valeur r�elle sur 8 octets
	HIT_UI1			= 12,					// valeur enti�re non sign�e sur 1 octet
	HIT_UI2			= 9,					// valeur enti�re non sign�e sur 2 octets
	HIT_UI4			= 22,					// valeur enti�re non sign�e sur 4 octets
	HIT_UI8			= 20,					// valeur enti�re non sign�e sur 8 octets
	HIT_CHAR		= 26,					// caract�re
	HIT_BOOLEEN		= 27,					// bool�en
	HIT_BINAIRE		= 23,					// cha�ne binaire
	HIT_DATETIME	= 24,					// date+heure
	HIT_TIMELENGHT	= 25,					// dur�e
	HIT_MEMOBINAIRE4= 16,					// m�mo binaire 4.0
	HIT_IDAUTO4		= 28,					// identifiant automatique sur 4 octets
	HIT_UNICODE		= 29,					// cha�ne Unicode ( en 12 )
	HIT_MEMOUNICODE = 30,					// m�mo contenant du texte Unicode
	HIT_DECIMAL		= 31,					// un num�rique

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
	HSDT_INVALID=HSUBDATATYPE_MIN,			// non d�finit
	HSDT_DBASE3,							// dBASE III
	HSDT_DBASE4,							// dBASE IV
	HSDT_FOXBASE,							// FoxBASE
	HSDT_CLIPPER5,							// Clipper 5
	HSDT_CLIPPER87,							// Clipper 87
	HSUBDATATYPE_MAX
}eHSUBDATATYPE;

//------------------------------------------------------------------------------------------//
//--- les constantes suivantes ne n�cessitent pas de conversion

// constante pour la commande HDBTypeTri (valeurs compatibles 5.5)
typedef enum _eHDBSORTTYPE
{
	HDBSORTTYPE_MIN=0,
	HDBLEXICOGRAPHIC=HDBSORTTYPE_MIN,		// Tri lexicographique
	HDBASCII=1,								// Tri ascii
	HDBDONOTSETSORTTYPE=2,					// Pour juste conna�tre le type de tri sans le modifier
	HDBSORTTYPE_MAX,
}eHDBSORTTYPE;

// Gestion des m�mos
typedef enum _eHMEMO
{
	HMEMO_MIN=1000,
	HMEMONO=HMEMO_MIN,						// les m�mos ne sont pas g�r�s lors des lectures/modification de l'enregistrement
	HMEMOYES,								// les m�mos textes sont g�r�s � chaque lecture/modification de l'enregistrement
	HMEMOAUTO,								// les m�mos sont lus/modifi�s lors de l'acc�s � la rubrique (fonctionnement par d�faut)
	HMEMO_MAX,
}eHMEMO;

// Ordre de tri
typedef enum _eHORDER
{
	HORDER_MIN=1010,
	HINCREASING=HORDER_MIN,					// tri croissant
	HDECREASING,							// tri d�croissant
	HNOTSORTED,								// pas de tri
	HORDER_MAX,
}eHORDER;

// M�thodes de blocage
typedef enum _eHLOCKMETHOD
{
	HLOCKMETHOD_MIN=1020,
	HLOCKMETHODDIRECT=HLOCKMETHOD_MIN,		// blocage direct
	HLOCKMETHODRESERVATION,					// blocage avec r�servation
	HLOCKMETHOD_MAX,
}eHLOCKMETHOD;

// M�thodes d'ouverture des fichiers
typedef enum _eHMODE
{
	HMODE_MIN=1030,
	HMODEMONO=HMODE_MIN,					// mode mono-utilisateur
	HMODEMULTI,								// mode multi-utilisateur
	HMODE_MAX,
}eHMODE;

// Pr�cision pour la m�thode HPosition/HPositionne
typedef enum _eHPRECISION
{
	HPRECISION_MIN=1040,
	HPRECISIONLOW=HPRECISION_MIN,			// faible pr�cision
	HPRECISIONMEDIUM,						// moyenne pr�cision
	HPRECISIONHIGH,							// haute pr�cision
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
	HEI_FILE,								// table concern�e par l'erreur
	HEI_ITEM,								// rubrique concern�e
	HEI_WDD,								// WDD concern�
	HEI_FIC,								// .FIC concern�
	HEI_NDX,								// .NDX concern�
	HEI_MMO,								// .MMO concern�
	HEI_LINK,								// liaison concern�e
	HEI_SYSTEMERRORCODE,					// num�ro d'erreur syst�me
	HEI_SYSTEMERRORMESSAGE,					// message d'erreur syst�me
	HEI_RECNUM,								// num�ro de l'enregistrement
	HEI_INFO,								// message d'erreur + message syst�me
	HEI_DEBUG,								// infos de debug interne PCSOFT
	HEI_BASECODE,							// code d'erreur renvoy� par le SGBD acc�d� en natif ou via OLEDB
	HEI_NATIVECODE,							// code d'erreur renvoy� par la dll d'acc�s natif ou OLEDB
	HEI_ADOCODE,							// code d'erreur renvoy� par ADO pour la dll OLEDB
	HEI_BASEMESSAGE,						// message d'erreur renvoy� par le SGBD acc�d� en natif ou via OLEDB
	HEI_NATIVEMESSAGE,						// message d'erreur renvoy� par la dll d'acc�s natif ou OLEDB
	HEI_ADOMESSAGE,							// message d'erreur renvoy� par ADO pour la dll OLEDB
	HEI_FULLERROR,							// dump complet de l'erreur
	HEI_INFOCLIENT,							// Acc�s natifs : infos sur la couche client utilis�e par l'acc�s natif (typiquement = num�ro de version du client)
	HEI_INFOSERVEUR,						// Acc�s natifs : infos sur le serveur utilis� par l'acc�s natif (typiquement = num�ro de version du serveur)
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
	HEP_SUBERRFIRST,						// premi�re sous-erreur
	HEP_SUBERRLAST,							// derni�re sous-erreur
	HEP_SUBERRNEXT,							// sous-erreur suivante
	HEP_SUBERRPREVIOUS,						// sous-erreur pr�c�dente
	HEP_MAX,
}eHERRORPARSE;

// Type de l'enregistrement dont on veut r�cup�rer la valeur apr�s un conflit
// de modification
typedef enum _eHRECTYPE_MODIFYCONFLICT
{
	HRECTYPE_MIN=2010,
	HRECREAD=HRECTYPE_MIN,				// enregistrement lu avant le HModifie
	HRECFILE,							// enregistrement dans le fichier
	HRECUSER,							// valeurs de l'utilisateur
	HRECTYPE_MAX,
}eHRECTYPE_MODIFYCONFLICT;

// R�gles d'int�grit�
typedef enum _eHINTEGRITYRULE
{
	HIR_MIN=2020,
	HIR_INTEGRITYNONE=HIR_MIN,			// pas de r�gle de suppression/modification
	HIR_INTEGRITYRESTRICT,				// suppression/modification interdite si enregistrement reli�
	HIR_INTEGRITYCASCADE,				// suppression/modification en cascade
	HIR_INTEGRITYDEFAULT,				// affectation de la valeur par d�faut � l'enreg reli�
	HIR_MAX,
}eHINTEGRITYRULE;

// types de r�plicat
typedef enum _eHREPLICAT
{
	HREPLICAT_MIN=2050,
	HNOREPLICAT=HREPLICAT_MIN,			// pas de r�plication
	HMASTERREPLICAT,					// r�plicat maitre
	HCONSUMERREPLICAT,					// r�plicat abonn�
	HREPLICATED,						// fichier r�pliqu� mais on ne sais pas si ma�tre ou abonn�
	HREPLICAT_MAX,
}eHREPLICAT;

// types de r�plicat
typedef enum _eHKEYTYPE
{
	HKEYTYPE_MIN=2060,
	HNOTAKEY=HKEYTYPE_MIN,				// pas cl�
	HUNIQUEKEY,							// cl� unique
	HDUPLICATESKEY,						// cl� avec doublon
	HKEYTYPE_MAX,
}eHKEYTYPE;

// type du contenu des rubriques texte
typedef enum _eHCONTENTTYPE
{
	HCONTENTTYPE_MIN=2070,
	HNORMALCONTENT=HCONTENTTYPE_MIN,	// pas de contenu sp�cifique
	HRTFCONTENT,						// texte RTF
	HCONTENTTYPE_MAX,
}eHCONTENTTYPE;


// 2080 est utilis� plus loin


//------------------------------------------------------------------------------------------//
//--- les constantes de type flags (qui s'additionnent).
// Constantes de type UINT ou DWORD (entier non sign� sur 32 bits)
// Les bits utilis�s doivent �tre cons�cutif pour que CHECKFLAGS_IMPL fonctionne.

// Modes d'importation des fichiers pour la fonction HImporteTexte et HImporteHF55
typedef enum _eHIMPORTMODE
{
	HIMPORTMODE_MAX			= 0x00000001,
	HIMPCREATION			= HIMPORTMODE_MAX,	// Cr�ation du fichier o� les enregistrements sont ajout�s (si le fichier ".Fic" existe d�j�, il est �cras�)
	HIMPOEM2ANSI			= 0x00000002,		// (HImporteTexte uniquement) Conversion OEM vers ANSI des cha�nes import�es
	HIMPTESTDUPLICATES		= 0x00000004,		// Test des doublons lors de l'importation
	HIMPTESTINTEGRITY		= 0x00000008,		// Test de l'int�grit� lors de l'importation
	HIMPNODELIMITER			= 0x00000010,		// (HImporteTexte uniquement) Les d�limiteurs de cha�nes ne sont pas pris en compte
	HDEFAULTVAL				= 0x00000020,		// Initialiser les rubriques non affect�es � leurs valeurs par d�faut
	HIMPIGNOREINVALIDLINE	= 0x00000040,		// (HImporteTexte uniquement) Les lignes de structure invalides sont ignor�es (sinon erreur et arr�t de l'importation)
	HIMPIGNOREITEM			= 0x00000080,		// (HImportHF5 uniquement) Les rubriques n'ayant pas d'�quivalence dans un des deux fichiers sont ignor�es
	HIMPCONVERSION			= 0x00000100,		// (HImportHF5 uniquement) Tronquage/Conversion des rubriques de type diff�rents
	HIMPNOSPACE				= 0x00000200,		// (HImportHF5 uniquement) Suppression des espaces de fin de cha�ne
	HIMPNORMAL				= 0x00000400,		// Ajout des enregistrements import�s au fichier (.FIC) existant (valeur par d�faut)
	HCOPYAUTOID				= 0x00000800,		// Copier l'ID auto
	HCOPYRECORDDEFAULT		= 0x00001000,		// Valeur par d�faut de flags de HCopieEnreg
	HIMPBREAKABLE			= 0x00002000,		// importation interruptible par ESC
	HIMPIGNOREEMPTYITEM		= 0x00004000,		// importation des rubriques non pr�cis�e dans le fichier texte � la valeur par d�faut ou non (selon hValDefaut)
	HIMPIGNOREFIRSTLINE		= 0x00008000,		// ignore la premi�re ligne
//	0x40000000,									// r�serv� pour usage interne
//	0x80000000,									// r�serv� pour usage interne
	HIMPORTMODE_MIN			= HIMPIGNOREEMPTYITEM,
}eHIMPORTMODE;

// Modes d'exportation des fichiers pour la fonction HExportXML
typedef enum _eHEXPORTMODE
{
	HEXPORTMODE_MAX			= 0x00000001,
	HEXPCREATION			= HEXPORTMODE_MAX,	// Cr�ation du fichier XML o� les enregistrements sont ajout�s (si le fichier ".xml" existe d�j�, il est �cras�)
	HEXPNORMAL				= 0x00000002,		// mode par d�faut
	HEXPBREAKABLE			= 0x00000004,		// exportation interruptible par ESC
	HEXPWITHOUTXSL			= 0x00000008,		// ne pas g�n�rer de XSL avec le XML
	HEXPORTMODE_MIN			= HEXPWITHOUTXSL,
}eHEXPORTMODE;


// Options pour la r�indexation (HReindexe)
typedef enum _eHNDXMODE
{
	HNDXMODE_MAX			= 0x00000001,
	HNDXCOMPACT				= HNDXMODE_MAX,		// r�indexation avec compactage
	HNDXNOSTAT				= 0x00000002,		// r�indexation sans calcul de stat
	HNDXNORMAL				= 0x00000004,		// r�indexation classique (avec stat et sans compactage)
	HNDXSILENT				= 0x00000008,		// aucun affichage pendant la r�indexation
	HNDXDELETE				= 0x00000010,		// r�indexation avec suppression des enregistrements endommag�s
	HNDXMINIMAL				= 0x00000020,		// r�indexation ne prenant en compte que les cl�s corrompues
	HNDXCHECKMEMO			= 0x00000040,		// v�rification des m�mos
	//						  0x00000080,		// r�serv� par HCHANGECHARSET (changer l'alphabet courant par l'alphabet du ChangeAlphabet courant)
	HNDXNOCHECKFIC			= 0x00000100,		// ne pas faire de v�rification du FIC
	HNDXFTX					= 0x00000200,		// reindexation du fulltext ( pas le ndx )
	HNDXTRYHOT				= 0x00000400,		// effectue une r�indexation � chaud si possible
	HNDXFORCEHOT			= 0x00000800,		// effectue une r�indexation � chaud, lance une erreur si pas possible
						   // 0x80000000,		// R�serv� usage interne, ne pas utiliser
	HNDXMODE_MIN			= HNDXCHECKMEMO,
}eHNDXMODE;

// option pour l'optimisation planifi�e
#define HOPTSTAT				0x00000001
#define HOPTINDEX				0x00000002

// type de liste � cr�er par HListeRubrique
typedef enum _eHLSTMODE
{
	// 0x00000001								// R�serv�
	HLSTMODE_MAX			= 0x00000002,
	HLSTITEM				= HLSTMODE_MAX,		// liste les rubriques non cl�
	HLSTKEY					= 0x00000004,		// liste les cl�s
	HLSTCOMPOSITEKEY		= 0x00000008,		// liste les cl�s compos�e
	HLSTMEMO				= 0x00000010,		// liste les m�mo
	HLSTALL					= 0x00000020,		// d�pend de la fonction qui l'utilise
												// HListeRubrique	: == HLSTITEM+HLSTKEY+HLSTCOMPOSITEKEY+HLSTMEMO
												// HListeCle		: == HLSTKEY+HLSTCOMPOSITEKEY == HLSTNORMAL
												// HListeFichier	: liste les fichiers d�clar�s en dynamique
	HLSTSORTED				= 0x00000040,		// liste tri�e
	HLSTDETAIL				= 0x00000080,		// liste d�taill�e
	HLSTNORMAL				= 0x00000100,		// valeur par d�faut pour HListeXXX, liste par ordre physique (compatibilit� 5.5)
	HLSTTABLE				= 0x00000200,		// Natif : Lister les tables (valeur par d�faut)
	HLSTVIEW				= 0x00000400,		// Natif : Lister les Vues
	HLSTSYSTABLE			= 0x00000800,		// Natif : Lister les tables syst�me
	HLSTSTOREDPROCEDURE		= 0x00001000,		// Natif : Lister les proc�dures stock�es
	HLSTDETAILPLUS			= 0x00002000,		// liste d�taill�e ++ (partie enti�re et d�cimale renvoy�e)
	HLSTLOGICALORDER		= 0x00004000,		// tri� dans l'ordre logique
	HLSTITEMORIGINE			= 0x00008000,		// Lister les rubriques du fichier d'origine (option valide uniquement sur un fichierJNL)
	HLSTOPENED				= 0x00010000,		// Lister les connexions ouvertes
	HLSTSTOREDCOLLECTION	= 0x00020000,
	HLSTQUERY				= 0x00040000,		
	HLSTDETAILGUID			= 0x00080000,		// rajoute l'info du GUID des rubrique
	//						= 0x80000000,		// r�serv� usage interne
	HLSTMODE_MIN			= HLSTOPENED,
}eHLSTMODE;

// Options de blocages/ajout/modif
typedef enum _eHPARSEMODE
{
	//						  0x00000001		// R�serv� usage interne, ne pas utiliser
	//						  0x00000002		// R�serv� usage interne, ne pas utiliser
	//						  0x00000004		// R�serv� usage interne, ne pas utiliser
	HPARSEMODE_MAX			= 0x00000008,
	HLOCKNO					= HPARSEMODE_MAX,	// pas de blocage
	HLOCKWRITE				= 0x00000010,		// blocage en �criture
	HLOCKREADWRITE			= 0x00000020,		// blocage en lecture/�criture
	HAFFECTBROWSE			= 0x00000040,		// L'�criture affecte les parcours (fonctionnement de HyperFile 5)
	HPARSEMODEDEFAULT		= 0x00000080,		// Valeur par d�faut (diff�rente signification selon les fonctions)
	HSETIDAUTO				= 0x00000100,		// Force l'identifiant auto � la valeur actuelle lors de l'ajout/mofif de l'enregistrement
	HRECALCULATEIDAUTO		= 0x00000200,		// Calcule un identifiant auto pour HEcrit
	HFORCEIDAUTO			= 0x00000400,		// Si l'identifiant auto de l'enregistrement est sup�rieur � celui du fichier, on n'augmente pas celui du fichier
	HDISTINCT				= 0x00000800,		// HLitSuivant... en sautant les doublons
	HGENERIC				= 0x00001000,		// HLitRechercheXXX... g�n�rique
	HNOREFRESH				= 0x00002000,		// Ne pas rafraichir les enregistrements (OLEDB : rafraichissement entraine perte de toutes les positions sauvegard�es)
	HKEEPFILTER				= 0x00004000,		// Tenir compte du filtre m�me si le parcours ou la recherche ne se fait pas sur la cl� renvoy�e par HFiltre
	HIGNOREDUPLICATES		= 0x00008000,		// Ignorer les doublons m�me si branch� par HG�reDoublon
	HIGNOREINTEGRITY		= 0x00010000,		// Ignorer l'int�grit� m�me si branch�e par HG�reInt�grit�
	HCHECKDUPLICATES		= 0x00020000,		// Tester les doublons m�me si d�branch� par HG�reDoublon
	HCHECKINTEGRITY			= 0x00040000,		// Tester l'int�grit� m�me si d�branch�e par HG�reInt�grit�
	HIDENTICAL				= 0x00080000,		// HLitRechercheXXX... � l'identique
	HSQLFETCH				= 0x00100000,		// Parcours avec SQLFetch (ne pas mettre en cache les enregistrements)
	HLIMITPARSING			= 0x00200000,		// Positionne HEnDehors � Vrai si on sort de la recherche (optimise les acc�s natifs)
	// 						  0x00400000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x00800000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x01000000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x02000000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x04000000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x08000000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x10000000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x20000000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x40000000,		// R�serv� usage interne, ne pas utiliser
	// 						  0x80000000,		// R�serv� usage interne, ne pas utiliser
	HPARSEMODE_MIN			= HLIMITPARSING,
}eHPARSEMODE;

// Gestion des description
typedef enum _eHDESCRIPTION
{
	HDESCRIPTION_MIN=2080,
	HSTRICT=HIDENTICAL,			// les structures des fichiers HF7 doivent �tre identiques entre le fichier physique et l'analyse
	HCOMPATIBLE,				// les structures des fichiers HF7 peuvent �tre un peu diff�rentes entre le fichier physique et l'analyse
	HNOCHECK,					// les structures des fichiers HF7 peuvent �tre compl�tement diff�rentes entre le fichier physique et l'analyse
	HDESCRIPTION_MAX,
}eHDESCRIPTION;


// Diff�rents �tats que peut prendre un enregistrement
typedef enum _eHRECORDSTATE
{
	HRECORDSTATE_MIN		= 0x00000001,
	HSTATEACTIVE			= HRECORDSTATE_MIN,	// enregistrement actif
	HSTATECROSSED			= 0x00000002,		// enregistrement ray�
	HSTATEDELETED			= 0x00000004,		// enregistrement supprim�
	HSTATEALLSTATES			= 0x00000008,		// tous les �tats autres que _55
	HSTATEACTIVE_55			= 0x00000010,		// pour le nombre d'enregistrements actifs en mode 55 (usage interne HF)
	HSTATEDELETED_55		= 0x00000020,		// pour le nombre d'enregistrements supprim�s en mode 55 (usage interne HF)
	HSTATEINVALID			= 0x00000040,		// �tat invalide
	HSTATE_NOWAIT			= 0x80000000,		// pour vues et requ�tes, non bloquant, renvoie ce qu'on a au moment de l'appel
	HRECORDSTATE_MAX		= HSTATE_NOWAIT,
}eHRECORDSTATE;

// Type d'erreur n�cessitant une assistance automatique de HF
// (affichage d'une fen�tre ou appel d'une proc�dure)
typedef enum _eHERRORASSISTED
{
	HEA_LOCK				= 0x00000001,		// blocage
	HEA_MODIFY				= 0x00000002,		// conflit de modification
	HEA_DUPLICATES			= 0x00000004,		// doublon
	HEA_INTEGRITY			= 0x00000008,  		// integrit�
	HEA_PASSWORD			= 0x00000010,		// mot de passe
	HEA_ALL					= 0x00000020,		// toutes les erreurs
	HEA_REINDEXE			= 0x00000080,		// r�indexation en cours
	HEA_NEEDITEMVALUE		= 0x00000100,		// valeur de rubrique obligatoire
	HEA_DATABASE_LOCK		= 0x00000200,		// blocage d'une base de donn�es
	HEA_DECONNEXION			= 0x00000400,		// perte de la connexion avec le serveur HF C/S
	HEA_INVALID				= 0x00000040,		// erreur inconnue (pas d'assistance)
}eHERRORASSISTED;

// Mode d'ex�cution du snapshot
typedef enum _eHVIEWMODE
{
	HVIEWDEFAULT			= 0x00000000,		// valeur par d�faut
	// 0x00000001,								// R�serv�
	HVIEWPOSTPONED			= 0x00000002,		// vue ex�cut�e en diff�r�
	HVIEWLOCKING			= 0x00000004,		// enregistrement bloqu�s dans la source
	HVIEWDISTINCT			= 0x00000008,		// suppression des doublons lors de l'extraction
	HVIEWEXCLUSIVE			= 0x00000010,		// ouverture du fichier en exclusif pour optimiser la cr�ation
	HVIEWADD				= 0x00000020,		// un prochain HExecuteVue compl�tera la vue actuelle
	HVIEWBREAKABLE			= 0x00000040,		// traitement interruptible
	HVIEWUNION				= 0x00000080,
	HVIEWUNIONEX			= 0x00000100,
	HVIEWINTERSECTION		= 0x00000200,
	HVIEWSUBTRACTION		= 0x00000400,
	HVIEWJOIN				= 0x00000800,
	HVIEWWAITTHREAD			= 0x00001000,		// INTERNE : on attend la fin du thread pour rendre la main
	HVIEWMODIFYFILE			= 0x00002000,		// INTERNE : les modifications sont directement report�es dans les fichiers
	//	__HVIEWFOREXIST		= 0x00010000,		// R�serv� usage interne, ne pas utiliser
	//                        0x00020000 r�serv� pour HCHECKDUPLICATES
	//                        0x00040000 r�serv� pour HCHECKINTEGRITY
	//	__HVIEWCS			= 0x00080000,		// R�serv� usage interne, ne pas utiliser
	HVIEWYIELD				= 0x00100000,		// Inutilis� pour le moment. M�me valeur que HQUERYYIELD si on veut brancher hTemporise sur HVueVersFichier
	//                        0x00200000 reserv� par la constante HWITHTRANSACTION
	//						  0x00400000		// R�serv� usage interne, ne pas utiliser
}eHVIEWMODE;

// Mode d'ex�cution de la requ�te
typedef enum _eHQUERYMODE
{
	HQUERYDEFAULT			=  0x00000000,					// valeur par d�faut
	// 0x00000001,											// R�serv� usage interne, ne pas utiliser
	HQUERYBREAKABLE			=  0x00000002,					// traitement interruptible
	HQUERYNATIVE			=  0x00000004,					// Requ�te sur l'acc�s natif ne devant pas �tre "corrig�e" par HF
	HQUERYDYNAMICBROWSE		=  0x00000008,					// Requ�te dynamique si possible (sans vue)
	HQUERYNOTCORRECTEDONHF	=  0x00000010,					// Requ�te sur HF ne devant pas �tre "corrig�e"
	HQUERYNOBIND			=  0x00000020,					// Pas de bind sur l'ex�cution de la requ�te
	HQUERYUNICODE			=  0x00000040,					// la chaine utilis� dans HExecuteRequeteSQL a �t� fourni en Unicode par l'utilisateur
	HQUERYMODIFYFILE		=/*0x00002000*/HVIEWMODIFYFILE,	// Les modifs sont report�es dans les fichiers
	// __HQUERYFOREXIST		=  0x00010000,					// R�serv� usage interne, ne pas utiliser
	//                         0x00020000 r�serv� pour HCHECKDUPLICATES
	//                         0x00040000 r�serv� pour HCHECKINTEGRITY	
	// __HQUERYCS			=  0x00080000					// R�serv� usage interne, ne pas utiliser			
	HQUERYYIELD				=/*0x00100000*/HVIEWYIELD,		// Temporisation pour requ�te UPDATE et DELETE pour laisser la main aux autres applications
	HWITHTRANSACTION		=  0x00200000,					// Une transaction est d�marr�e pour la requ�te (UPDATE/DELETE)
	// __HQUERYOPTIMIZ		=  0x08000000,					// R�serv� usage interne, ne pas utiliser
	// __HQUERYINITTABLE	=  0x10000000,					// R�serv� usage interne, ne pas utiliser
	// __HQUERYDUPLIQUE		=  0x20000000,					// R�serv� usage interne, ne pas utiliser
	// __HQUERYPREPARE		=  0x40000000,					// R�serv� usage interne, ne pas utiliser
	// __HQUERYMINIMAL		=  0x80000000,					// R�serv� usage interne, ne pas utiliser
}eHQUERYMODE;


// options de la HListeREP
typedef enum _eHREP
{
	HREPEXISTING			= 0x00000001,		// r�cup�rer uniquement les affectations dont le fichier existe
	HREPDEFAULT				= 0x00000000,		// valeur par d�faut (0 pour compatibilit� 5)
}eHREP;

// options de la HSauvePosition
typedef enum _eHSAUVEPOSITION
{
	HSPSAVEITEMSVALUE		= 0x00000001,
	HSPNOFILTER				= 0x00000002,		// ne pas sauver le filtre ( optimisation champ table pour Acc�s natifs )
}eHSAUVEPOSITION;

// options de la HRetourPosition
typedef enum _eHRETOURPOSITION
{
	HRETOURPOSITION_MAX		= 0x00000001,
	HRPHF5					= HRETOURPOSITION_MAX,	// HRetourPosition � la HF5 (relit l'enreg m�me s'il est supprim�, modifi�)
	HRPKEEP					= 0x00000002,		// ne pas lib�rer la position
	HRPDEFAULT				= 0x00000004,		// valeur par d�faut
	HRPFILTER				= 0x00000008,		// retauration du filtre pos� au moment du HSauvePosition
	// 0x01000000,	// R�serv� usage interne, ne pas utiliser ( __HRPTABLEMODE )
	// 0x02000000,	// R�serv� usage interne, ne pas utiliser
	// 0x10000000,	// R�serv� usage interne, ne pas utiliser
	// 0x20000000,	// R�serv� usage interne, ne pas utiliser ( __HPARSEINTEGRITY )
	// 0x40000000,	// R�serv� usage interne, ne pas utiliser
	// 0x80000000,	// R�serv� usage interne, ne pas utiliser
	HRETOURPOSITION_MIN		= HRPFILTER,
}eHRETOURPOSITION;

// Diff�rentes r�gles d'int�grit�
typedef enum _eHRULE
{
	HRULE_MAX				= 0x00000001,
	HCARDINALITY			= HRULE_MAX,		// r�gle sur les cardinalit�s
	HONUPDATE				= 0x00000002,		// r�gle sur une modification
	HONDELETE				= 0x00000004,		// r�gle sur une suppression
	HALLRULES				= 0x00000008,		// toutes les r�gles
	HRULE_MIN				= HALLRULES,
}eHRULE;

// Options de HRegenereFichier
typedef enum _eHREGENEREFICHIER
{
	HSTRUCTURE				= 0x00000001,		// r�g�n�rer la structure du fichier (HCreation)
	HDATA					= 0x00000002,		// Rejouer l'int�gralit� du journal
}eHREGENEREFICHIER;

// Types de trigger
typedef enum _eHTRIGGERTYPE
{
	HTRIGGERBEFORE			= 0x00000001,		// pour que la proc�dure W-Langage soit ex�cut�e avant la fonction Hyper File
	HTRIGGERAFTER			= 0x00000002,		// pour que la proc�dure W-Langage soit ex�cut�e apr�s la fonction Hyper File
}eHTRIGGERTYPE;

// Types d'op�ration de test (HConnecteOLEDB)
typedef enum _eHTESTOPERATION
{
	HCUNSPECIFIED			= 0x00000000,
	HCHCREATIONSIINEXISTANT	= 0x00000001,
	HCHOUVRE				= 0x00000004,
}eHTESTOPERATION;

// Types d'op�ration de transaction (SQLTransaction)
typedef enum _eSQLTRANSACTIONOP
{
	SQLTRANSACTIONBEGIN		= 0x00000001,		// Compatibilit� HF5
	SQLTRANSACTIONCOMMIT	= 0x00000002,		// Compatibilit� HF5
	SQLTRANSACTIONROLLBACK	= 0x00000003,		// Compatibilit� HF5
}eSQLTRANSACTIONOP;

// Options du curseur ADO
typedef enum _eADOCURSOROPTIONS
{
	HSERVERCURSOR			= 0x00000001,		// Curseur serveur
	HCLIENTCURSOR			= 0x00000002,		// Curseur client
	HDYNAMICCURSOR			= 0x00000004,		// Curseur dynamique	(� utiliser avec HSERVERCURSOR)
	HOPENKEYSETCURSOR		= 0x00000008,		// Curseur OpenKeyset	(� utiliser avec HSERVERCURSOR)
	HSTATICCURSOR			= 0x00000010,		// Curseur statique
	HLOCKREADONLY			= 0x00000020,		// Acc�s aux enregistrements en lecture seule
	HLOCKPESSIMISTIC		= 0x00000040,		// Blocage pessimiste de l'enregistrement lu (bloqu� d�s qu'il est lu)
	HLOCKOPTIMISTIC			= 0x00000080,		// Blocage optimiste de l'enregistrement lu (bloqu� uniquement au moment de la mise � jour)
	HFORWARDONLYCURSOR		= 0x00000100,		// Curseur ForwardOnly
}eADOCURSOROPTIONS;

// Mode d'ex�cution de la requ�te
typedef enum _eHCREATEMODE
{
	HDELAYEDOPENING		= 0x00000001,		// ouverture diff�r�e si le fichier existe lors du HCr�ationSiInexistant
	HCHANGECHARSET		= 0x00000080,		// changer l'alphabet courant par l'alphabet du ChangeAlphabet courant
	HNOLINK				= 0x00000100,		// mise � jour des r�gles d'int�grit� lors de la cr�ation du fichier
	//					  0x00800000,		// R�serv� usage interne, ne pas utiliser
	//					  0x04000000,		// R�serv� usage interne, ne pas utiliser
	//					  0x10000000,		// R�serv� usage interne, ne pas utiliser
	//					  0x20000000,		// R�serv� usage interne, ne pas utiliser
	//					  0x40000000,		/  R�serv� usage interne, ne pas utiliser
	//					  0x80000000,		/  R�serv� usage interne, ne pas utiliser
}eHCREATEMODE;

// Mode d'ex�cution de la requ�te
// Utilis� pour HChangeRepJNL + HJournalRecree
typedef enum _eHCHANGEREPJNL
{
	HJOURNALOP			= 0x00000001,		// Changer l'emplacement du fichier journal des op�rations
	HJOURNALID			= 0x00000002,		// Changer l'emplacement du fichier journal d'identification des fichiers
	HJOURNALFICHIERJNL	= 0x00000004,		// fichier JNL
	HJOURNALUSERS		= 0x00000008,		// Pour HJournalRecree ( en C/S ) : fichier des utilisateurs
}eHCHANGEREPJNL;


// Constantes pour  HG�reServeur
// (live) = appliqu� en live par HGereServeur sans avoir � red�marrer le serveur
// (restart) = n�cessite un red�marrage du serveur pour �tre pris en compte
typedef enum _eHSERVERMANAGMENT
{
	HLOGLEVEL			= 0x00000001,		// (live) Niveau des logs du serveur
	HMAXLOGSIZE			= 0x00000002,		// (live) Taille d'un fichier de log
	HLOGPATH			= 0x00000008,		// (live) Chemin des fichiers de log
	HNDXFILECACHESIZE	= 0x00000010,		// (live) Taille du cache des fichiers d'index
	HACTIVITYSTATPERIOD	= 0x00000020,		// (live) P�riode d'�chantillonage des statistiques d'activit�
	HMAXACTIVITYSTATSIZE= 0x00000040,		// (live) Taille maxi du fichier des statistiques d'activit�
	//--------------------------------------------------------------------------------------------------
	// HLB_ -> r�partition de charge, param�trage tr�s avanc�
	// Les coef servent � faire varier l'importance de chaque compteur dans la formule de calcul de la charge
	// engendr�e par un utilisateur sur le serveur
	HLB_COEFFNETSEND	= 0x00000050,		// (live) Coef. pour nombre d'octets/s envoy�s sur le r�seau
	HLB_COEFFNETRECV	= 0x00000051,		// (live) Coef. pour nombre d'octets/s re�us sur le r�seau
	HLB_COEFFDISKBYTE	= 0x00000052,		// (live) Coef. pour nombre d'octets/s lus ou �crits sur disque
	HLB_COEFFDISKACCESS	= 0x00000053,		// (live) Coef. pour nombre d'acc�s/s au disque
	HLB_COEFFCLIENTCALL	= 0x00000054,		// (live) Coef. pour nombre d'appels/s du client
	HLB_MAXWAIT			= 0x00000055,		// (live) Temps d'attente max (ms) pour une t�che effectu� par la r�partition de charge sur le serveur
	HLB_ENABLE			= 0x00000056,		// (live) Activation/d�sactivation de la r�partition de charge
	//--------------------------------------------------------------------------------------------------
	HACTIVITYSTATPATH	= 0x00000080,		// (live) Chemin du fichier des statistiques d'activit�
	HDATABASEPATH		= 0x00000100,		// (restart) Chemin des bases de donn�es
	HSERVERPORT			= 0x00000200,		// (restart) Port du serveur
	HMODE2GB			= 0x00000400,		// (restart) Fichiers syst�mes en mode >2Go
	HJNLPATH			= 0x00000800,		// (restart) Chemin des journaux
	HJNLBACKUPPATH		= 0x00001000,		// (restart) Chemin des backup des journaux
	HDAEMONUSER			= 0x00002000,		// (restart) Nom du user qui lance le serveur sous Linux
	HDEBUGGER_PORT		= 0x00004000,		// (live) Port utilis� par le debuggeur (proc�dures stock�e)
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


// type d'info demand� � HInfoServeur
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
	NDX_REINDEX,							// HCopieFichier ne copie pas l'index et recr�e l'index (r�indexation)
}eHCOPIE_FICHIER_MODE;

#define HCOPIE_FICHIER_DONT_OVERRIDE	0x00000100

// mode pour la fonction HInfoFichier
#define 	HINFOFICHIER_TAILLE_FIC		0x00000001  // HInfoFichier renvoie la taille du FIC
#define 	HINFOFICHIER_TAILLE_NDX		0x00000002  // HInfoFichier renvoie la taille de l'index
#define 	HINFOFICHIER_TAILLE_MMO		0x00000004  // HInfoFichier renvoie la taille du fichier des m�mo
#define 	HINFOFICHIER_TAILLE_FTX		0x00000008  // HInfoFichier renvoie la taille du fichier des ftx

#define 	HINFOFICHIER_TAILLE_TOTAL	0x0000FFFF  // HInfoFichier renvoie la somme des tailles du FIC,NDX,et MMO


//////////////////////////////////////////////////////////////////////////
//	PARAMETRES DU CACHE
//////////////////////////////////////////////////////////////////////////

// param�tres par d�faut des pages du cache client
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

// type des �l�ments sur lesquels s'applique les droits
typedef enum _eOBJECT_TYPE
{
	H_SERVER_OBJECT					= 0x00000001,		
	H_DATABASE_OBJECT				= 0x00000002,		
	H_FILE_OBJECT					= 0x00000004,
}eOBJECT_TYPE;

// type de droits et format de la chaine renvoy� par HInfoDroit
typedef enum _eRIGHTS_FORMAT
{
	HRIGHTS_DEFAULT			=	0x00000000,
	HRIGHTS_DETAIL			=	0x00000001,
	HRIGHTS_EFFECTIVE		=	0x00000002,
} eRIGHTS_FORMAT;

// m�ta informations
#define	HMETA_OWNER				_X("A#")
#define	HMETA_CREATOR			_X("B#")
#define	HMETA_DATE				_X("C#")
#define	HMETA_APP				_X("D#")
#define	HMETA_COMPUTER			_X("E#")
#define	HMETA_NOTES				_X("F#")	

// r�sultat de HEtatServeur
#define H_SERVER_NO_ACCESS		0x00000000
#define H_SERVER_STARTED		0x00000001
#define H_SERVER_STOPPED		0x00000002

// type d'action que le serveur demande aux client d'effectuer
	// 0x00000000 -> 0xFFFF0000 : r�serv� utilisateur
#define	H_ACTION_MESSAGE			0x40000000
#define	H_ACTION_CLOSE_CONNEXION	0x40000001
#define H_ACTION_ASSISTANCE_AUTO	0x40000002

// �tendu de la suppression pour les ordres HSupprimeBaseDeDonn�es et HSupprimeFichier
#define H_KEEP_TRS				0x00000001
#define H_REMOVE_JNL			0x00000002
#define H_DELETE_LINK			0x00000004

// valeur pour la variable HCS.TailleTrame
// taille limite du buffer pour un appel � l'API send
// Une valeur trop �lev� peut poser probl�me � certain OS, ou provider WinSock
// une Valeur trop faible peut d�grader les performance
#define HTRAME_INTERNET				(9*1048576)
#define HTRAME_INTRANET				(11*1048576)
#define HTRAME_WIFI					(12*1024)
#define HTRAME_GPRS					(1*1024)
#define HTRAME_ACTIVESYNC			(10*1024)

// le 30/8/2006 : on utilise diff�rentes valeurs par d�faut car certain OS (PPC) sont tr�s sensible
#ifdef UNDER_CE
	#define HTRAME_DEFAUT						HTRAME_ACTIVESYNC
#else
	#define HTRAME_DEFAUT						HTRAME_INTRANET	
#endif

// Type de sortie pour HR�cup�reEnregistrement
#define HUNICODE_OUTPUT			0x00000001

// Type de sauvegarde planifi�e
#define		HSVG_FULL		0x00000000		/* Sauvegarde compl�te */
#define		HSVG_DIFF		0x00000001		/* Sauvegarde diff�rentielle */
#define		HSVG_INTERNAL	0x00000002		/* sauvegarde pour traitement interne : reindexation, modif-auto, calcul stat */

#define		HSVG_DIFF_S			1
#define		HSVG_INTERNAL_S		2

#endif //#ifndef __HFCONSTANT_H



