/* DEPARTEMENT */
#pragma pack(1)
typedef struct _stDEPARTEMENT
{
	char	departement[30+1];	/* Département */
	char	codedep[2+1];	/* Code du département */
} stDEPARTEMENT, *pstDEPARTEMENT;
#pragma pack()

/* VILLE */
#pragma pack(1)
typedef struct _stVILLE
{
	char	codepostal[5+1];	/* Code Postal */
	char	ville[30+1];	/* Ville */
} stVILLE, *pstVILLE;
#pragma pack()

/* ADRESSE */
#pragma pack(1)
typedef struct _stADRESSE
{
	long	adcleunik;	/* ID Adresse */
	char	nom[30+1];	/* Nom */
	char	societe[30+1];	/* Société */
	char	adresse1[30+1];	/* Adresse */
	char	adresse2[30+1];	/* (suite) */
	char	codepostal[5+1];	/* Code Postal */
	char	ville[30+1];	/* Ville */
	char	pays[40+1];	/* Pays */
	char	tel[20+1];	/* Téléphone */
	#if defined(__BORLANDC__) && (__BORLANDC__ < 0x550)
	DWORD	email_HIGH;	/* EMail (high __int64 DWORD) */
	DWORD	email_LOW;	/* EMail (low __int64 DWORD) */
	#else
	__int64	email;	/* EMail */
	#endif
} stADRESSE, *pstADRESSE;
#pragma pack()

