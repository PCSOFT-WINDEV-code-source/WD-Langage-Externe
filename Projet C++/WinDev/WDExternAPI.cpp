//Interface C++ pour Langage Externe WinDev
//Implémentation de l'API C++

#include "WDExternAPI.h"
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>

// verifie qu'une chaine passée en lecture seule est bien valide
#define CHECKLPCTSTR(STR) XASSERT(!IsBadReadPtr(STR, 1))
// verifie qu'un pointeur est valide sur une taille donnée
#define CHECKPTR(_str, _lng) XASSERT(!IsBadReadPtr(_str,_lng) && !IsBadWritePtr((LPVOID)(_str),_lng))

#define DLL_WDOBJ		1
#define DLL_WDVM		0
#define VM_EXECUTETRAITEMENT	0
#define OBJ_OUVRE	1
#define OBJ_FERME	2
#define OBJ_TABLESUPPRIME	7
#define OBJ_LISTEAJOUTE	8
#define OBJ_LISTESELECT	9
#define OBJ_LISTESUPPRIME	10
#define OBJ_LISTEMODIFIE	14
#define OBJ_LISTESUPPRIMETOUT	15
#define OBJ_LISTESELECTPLUS	16
#define OBJ_LISTESELECTMOINS	17
#define OBJ_LISTEOCCURRENCE	18
#define OBJ_FENENCOURS	19
#define OBJ_TABLEAJOUTE	20
#define OBJ_TABLESUPPRIMETOUT	21
#define OBJ_TABLEOCCURRENCE	23
#define OBJ_TABLESELECT	24
#define OBJ_TABLESELECTPLUS	25
#define OBJ_TABLESELECTMOINS	26
#define OBJ_HANDLE	30
#define OBJ_ARBREAJOUTE	42
#define OBJ_ARBRESUPPRIME	44
#define OBJ_ARBRESUPPRIMETOUT	45
#define OBJ_ARBREDEROULE	46
#define OBJ_ARBRESELECT	54
#define OBJ_ARBRESELECTPLUS	55
#define OBJ_ARBRETYPEELEMENT	56
#define OBJ_TABLECHERCHE	72
#define OBJ_TABLEPOSITION	79
#define OBJ_ARBRERECUPEREIDENTIFIANT	86
#define OBJ_SABLIER	90
#define OBJ_LISTECHERCHE	93
#define OBJ_TITREENCOURS	97
#define OBJ_ECRANPREMIER	127
#define OBJ_LISTEINSERE	132
#define OBJ_TABLEINSERE	144
#define OBJ_TABLEMODIFIE	145

// construction d'une chaine vide
CTString::CTString(void):
  m_pszStr( NULL )
{
}

// constructeur à partir d'une chaine C
CTString::CTString(PCXSTR pszText)
{
	m_pszStr=NULL;
    Set(pszText);
}

//Destructeur
CTString::~CTString()
{
	if (m_pszStr!=NULL)
	{
		XVALIDSTRING(m_pszStr);
		free(m_pszStr); // libère la mémoire éventuellement allouée.
	}
}

// récup du buffer ASCIIZ
PCXSTR CTString::pszGet(void) const
{
	if (m_pszStr==NULL) return _X("");
	return m_pszStr;
}

// récupération du nombre de caractères d'une chaine
int CTString::nTaille(void)  const
{
	return (m_pszStr != NULL) ? (int)_tcslen(m_pszStr) : 0;
}

// indique si la chaine est vide
BOOL CTString::bEstVide(void) const 
{
	return (m_pszStr==NULL || m_pszStr[0]==0);
} 

//Initialisation de la chaîne dynamique à partir d'une chaine asciiz
//Allocation du buffer nécessaire et copie des caractères jusqu'au 0 inclus
//
//void CTString::Set(PCXSTR psz)
void FASTCALL CTString::Set(PCXSTR psz) // Init à partir d'une chaine ASCIIZ
{
	if (psz== NULL)  // si on passe null
	{
		Vide(); // on met la chaine a vide.
		return;
	}
	XVALIDSTRING(psz);

	// Si Affectation d'une CTString à elle même
    if ( psz == m_pszStr ) return; // OK.
	
	// on calcule la longueur de la chaine à copier en comptant le 0 final.
	// en NOMBRE DE CARACTERE.
	int nPszLen = (int)STRLEN(psz);
	
	// mise du buffer à la bonne taille
	_SetBufferSize(nPszLen);
	
	// on copie la chaine fournie (avec le 0 final)
	memcpy(m_pszStr, psz, nPszLen+1);

	XASSERT(STRCMP(m_pszStr, psz) == 0);
}

// Change la taille du buffer d'une chaîne dynamique, 
// quel que soit son contenu actuel.
//  nNewSize	IN	taille en nb de caractères.
//void CTString::_SetBufferSize(int nNewSize)
void FASTCALL CTString::_SetBufferSize(int nNewSize)
{
	// si aucune chaine n'existait
	if(m_pszStr == NULL)
	{
	    //on alloue le buffer de la taille demandée+1 pour le 0
	    m_pszStr = (PXSTR)malloc((nNewSize+1) * sizeof(TCHAR));
	}
	else
	{
	    //sinon on réalloue (augmentation ou diminution de taille)
	    m_pszStr = (PXSTR)realloc(m_pszStr, (nNewSize+1) * sizeof(TCHAR));
	}

	// si plus de mémoire, une exception à été lancée.
	//if ((m_pszStr) == NULL) throw "Plus de mémoire.";
}

// mise à la chaine NULLE.
void CTString::Vide(void) 
{
	// si on a alloué de la mémoire pour la chaine
    if(m_pszStr != NULL)
    {	
		XVALIDSTRING(m_pszStr);
		// il faut la libérer.
        free(m_pszStr);
		// le pointeur de buffer est null a présent.
		m_pszStr = NULL;
    }
	
	// n'arrivera jamais, c'est juste pour que le lecteur du
	// code n'est pas de doute sur la valeur de ce pointeur.
	XASSERT(m_pszStr == NULL);
}

// Retourne la position de la sous-chaine de caractères passé en paramètre
// à partir d'une position donnée (0 par défaut)
// renvoie la position ou -1 si elle n'est pas trouvée
//int CTString::nPos(PCXSTR psz, int nFrom) const
int FASTCALL CTString::nPos(PCXSTR psz, int nFrom) const
{
	// si la chaine est vide, on renvoie -1.
	if (bEstVide()) return -1;

	XASSERT(nFrom >= 0);
	XASSERT(nFrom <= nTaille()); // '<=' car on autorise à chercher sur le 0 de fin.
	LPTSTR p = STRSTR(m_pszStr + nFrom, psz);
	return (int)(p ? p-m_pszStr : -1);
}

// remplace toutes les occurences de 'pszMotRecherche' par pszAlaPlace
//void CTString::Remplace(PCXSTR pszMotRecherche, PCXSTR pszAlaPlace)
void FASTCALL CTString::Remplace(PCXSTR pszMotRecherche, PCXSTR pszAlaPlace)
{
	XVALIDSTRING(pszMotRecherche);
	XVALIDSTRING(pszAlaPlace);
	XASSERT(pszMotRecherche[0] != 0); // on ne peut pas rechercher ""

	// si la chaine est vide, on ne fait rien.
	if (bEstVide()) return;

	CTString clResult;
	// calcul de taille des 2 chaines
	// (pour accélérer les calculs qui vont suivre)
	DWORD dwLngRecherche = (DWORD)STRLEN(pszMotRecherche);
	DWORD dwLngAlaPlace = (DWORD)STRLEN(pszAlaPlace);

	// on calcule la taille de la chaine finale
	DWORD dwLngResultat = nTaille(); // pour l'instant comme la chaine source
	int nPosRecherche;
	nPosRecherche = nPos(pszMotRecherche, 0);
	while (nPosRecherche != -1)
	{
		// a chaque occurence trouvée
		// on ajoute la taille de le nouvelle chaine mois celle de l'ancienne
		dwLngResultat += (dwLngAlaPlace - dwLngRecherche);
		// recher de l'occurence suivante
		nPosRecherche = nPos(pszMotRecherche, nPosRecherche + dwLngRecherche);
	}
	// OK, on peut maintenant allouer un buffer de cette taille
	PXSTR pszBuf = (PXSTR)malloc( (dwLngResultat + 1) * sizeof(TCHAR));
	PXSTR pszResult = pszBuf;
	// Début de l'algo de remplacement
	PXSTR pszParsed = m_pszStr; // *this
	PXSTR pNextOccurence;
	XDBG( DWORD dwLng=0; )
	// tant que l'on trouve des occurences :
    while ((pNextOccurence = STRSTR(pszParsed, pszMotRecherche) ) != NULL)
	{
		// nombre de caractères depuis la dernière occurence
		DWORD dwDepl = (DWORD)(pNextOccurence - pszParsed);
		// on calcule la nouvelle taille prise dans le résultat
		XDBG( dwLng = dwLng + dwDepl + dwLngAlaPlace ; ) 
		// on concatène la partie depuis l'occurence d'avant
		if (dwDepl)		   MEMCPY(pszResult, pszParsed, dwDepl*sizeof(TCHAR));
		// on concatère la nouvelle chaine
		if (dwLngAlaPlace) MEMCPY(pszResult + dwDepl, pszAlaPlace, dwLngAlaPlace*sizeof(TCHAR));
		// on passe à ce qui se trouve derrière <pszCherche>
		pszParsed = pNextOccurence + dwLngRecherche;
		pszResult += (size_t)( dwDepl + dwLngAlaPlace);
	}
	// on rajoute la fin de la chaine
	STRCPY(pszResult, pszParsed);
	//  on calcule la nouvelle taille prise dans le résultat
	XDBG(dwLng = dwLng + (DWORD)STRLEN(pszParsed); )
	// vérifie que les calculs de longueur de chaine tombent juste
	XASSERT(dwLngResultat == dwLng);

	// on copie le résulat dans this
	_SetBufferSize(dwLngResultat+1);
	MEMCPY(m_pszStr, pszBuf, (dwLngResultat+1) * sizeof(TCHAR));
	free(pszBuf);
}

//___________________________________________________________________________
//
//  		Méthodes de modification du contenu des champs	
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur nouvelle valeur
	void AfficheEx(LPCTSTR pszNom, LPCTSTR pszValeur) 
	{ 
		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);

		CTString clTemp(pszValeur);
		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "

		WDLEVERIFY(nWDExecute(_T("%s=\"%s\""), pszNom, (PCXSTR)clTemp));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur nouvelle valeur
	void Affiche(LPCTSTR pszNom, LPCTSTR pszValeur) 
	{ 
		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);

		WDLEVERIFY(nWDEmpile(pszValeur,WDTYPE_TSTR));
		WDLEVERIFY(nWDEcritPropElem(pszNom,-1));

	}

	////////////////////////////////////////////////////////////////
	// NOM	 :			Affiche
	// EFFET :			modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  LPCTSTR pszValeur nouvelle valeur
	 void Affiche(LPCTSTR pszNom, int nIndice, LPCTSTR pszValeur)
	{ 
 		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);

		WDLEVERIFY(nWDEmpile(pszValeur,WDTYPE_TSTR));
		WDLEVERIFY(nWDEcritPropElemInd(pszNom,nIndice,-1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	 :			Affiche
	// EFFET :			modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  LPCTSTR pszValeur nouvelle valeur
	void Affiche(LPCTSTR pszNom, int nIndice1, int nIndice2, LPCTSTR pszValeur)
	{ 
 		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);

		WDLEVERIFY(nWDEmpile(pszValeur,WDTYPE_TSTR));
		WDLEVERIFY(nWDEcritPropElemInd2(pszNom,nIndice1,nIndice2,-1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur nouvelle valeur
	//	int nLong		 longueur de la  chaine passée en paramètre
	void Affiche(LPCTSTR pszNom, LPTSTR pszValeur, int nLong) 
	{ 
 		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);
		XASSERT(nLong >= 0);
		UNUSED(nLong);
 
		Affiche(pszNom, pszValeur);
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nValeur		 nouvelle valeur
 	void AfficheEx(LPCTSTR pszNom, int nValeur)
	{ 
 		XVALIDSTRING(pszNom);

		WDLEVERIFY(nWDExecute(_T("%s=%d"), pszNom, nValeur));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nValeur		 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nValeur)
	{ 
 		XVALIDSTRING(pszNom);

		WDLEVERIFY(nWDEmpile(&nValeur,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElem(pszNom,-1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  int lValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nIndice, int nValeur)
	{ 
 		XVALIDSTRING(pszNom);
		XASSERT(nIndice>0);

		WDLEVERIFY(nWDEmpile(&nValeur,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElemInd(pszNom,nIndice,-1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  int lValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nIndice1, int nIndice2, int nValeur)
	{ 
 		XVALIDSTRING(pszNom);
		XASSERT(nIndice1>0);
		XASSERT(nIndice2>0);

		WDLEVERIFY(nWDEmpile(&nValeur,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElemInd2(pszNom,nIndice1,nIndice2,-1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  DWORD dwValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, DWORD dwValeur)
	{ 
 		XVALIDSTRING(pszNom);
		WDLEVERIFY(nWDExecute(_T("%s=0x%x"), pszNom, dwValeur));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  DWORD dwValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nIndice, DWORD dwValeur)
	{ 
 		XVALIDSTRING(pszNom);
		XASSERT(nIndice>0);
		WDLEVERIFY(nWDExecute(_T("%s[%d]=0x%x"), pszNom, nIndice, dwValeur));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  double dValeur	 nouvelle valeur
 	void AfficheEx(LPCTSTR pszNom, double dValeur)
	{ 
 		XVALIDSTRING(pszNom);
		// verif la configuration local, doit etre en "C" pour que la convertion réel -> chaine
		// soit correcte pour le langage externe
		XASSERT(strcmp(setlocale(LC_NUMERIC, NULL), "C")==0);
		WDLEVERIFY(nWDExecute(_T("%s=%g"), pszNom, dValeur));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  double dValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, double dValeur)
	{ 
 		XVALIDSTRING(pszNom);
		WDLEVERIFY(nWDEmpile(&dValeur,WDTYPE_DOUBLE));
		WDLEVERIFY(nWDEcritPropElem(pszNom,-1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 AfficheInterrupteur
	// EFFET     :		 modifie le contenu d'un champ interrupteur 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  BOOL * pbValeur	 tableau de états de chaque interupteur (commence à 0)
	//  int nNbOptions   taille du tableau 
	void AfficheInterrupteur(LPCTSTR pszNom, const BOOL * const pbValeur, int nNbOptions)
	{
 		XVALIDSTRING(pszNom);
		CHECKPTROK(pbValeur, sizeof(BOOL)*nNbOptions);
		XASSERT(nNbOptions >= 0);
 
		// pour charque interrupteur
		for(int i=0; i<nNbOptions; i++)
		{
			// on change la valeur de l'interupteur numéro 'i'
			WDLEVERIFY(nWDEmpile(pbValeur+i,WDTYPE_BOOL));
			WDLEVERIFY(nWDEcritPropElemInd(pszNom,i+1,-1));
		}
	}      

//___________________________________________________________________________
//
//  		Méthodes de lecture du contenu des champs	
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    int nRecupEx(LPCTSTR pszNom) 
	{  
 		XVALIDSTRING(pszNom);
 
		WDLEVERIFY(nWDExecuteEx(pszNom));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    int nRecup(LPCTSTR pszNom) 
	{  
 		XVALIDSTRING(pszNom);
 
		WDLEVERIFY(nWDLitPropElem(pszNom,-1));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ numérique indicé
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ indicé
	int nRecup(LPCTSTR pszNom, int nIndice) 
	{ 
		XVALIDSTRING(pszNom);
		XASSERT(nIndice>0);
		
		WDLEVERIFY(nWDLitPropElemInd(pszNom,nIndice,-1));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ numérique indicé
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ indicé
	int nRecup(LPCTSTR pszNom, int nIndice1, int nIndice2) 
	{ 
		XVALIDSTRING(pszNom);
		XASSERT(nIndice1>0);
		XASSERT(nIndice2>0);
		
		WDLEVERIFY(nWDLitPropElemInd2(pszNom,nIndice1,nIndice2,-1));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 dRecup
	// EFFET     :		 récupère le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    double dRecupEx(LPCTSTR pszNom)
	{  
 		XVALIDSTRING(pszNom);
 
		XASSERT(strcmp(setlocale(LC_NUMERIC, NULL), "C")==0);
		WDLEVERIFY(nWDExecuteEx(pszNom));
		return dWDGetValeurRetour();
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 dRecup
	// EFFET     :		 récupère le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    double dRecup(LPCTSTR pszNom)
	{  
 		XVALIDSTRING(pszNom);
 
		WDLEVERIFY(nWDLitPropElem(pszNom,-1));
		return dWDGetValeurRetour();
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szRecupEx(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);
 
		WDLEVERIFY(nWDExecuteEx(pszNom));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szRecup(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);
 
		WDLEVERIFY(nWDLitPropElem(pszNom,-1));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ 
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szRecup(LPCTSTR pszNom, int nIndice) 
	{ 
		XVALIDSTRING(pszNom);
		XASSERT(nIndice>0);

		WDLEVERIFY(nWDLitPropElemInd(pszNom,nIndice,-1));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ 
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szRecup(LPCTSTR pszNom, int nIndice1, int nIndice2) 
	{ 
		XVALIDSTRING(pszNom);
		XASSERT(nIndice1>0);
		XASSERT(nIndice2>0);
		
		WDLEVERIFY(nWDLitPropElemInd2(pszNom,nIndice1,nIndice2,-1));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ texte
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
 	// REMARQUE  :		 la longueur est limitée à 64 Ko en 16bit 
	void RecupTexteLongEx(LPCTSTR pszNom, LPTSTR pszDest, int nMax) 
	{  
		XVALIDSTRING(pszNom);
		CHECKPTROK(pszDest,nMax);
		XASSERT(nMax>=0);

		// appel au langage externe
		WDLEVERIFY(nWDExecuteEx(pszNom));

 		// copie du résulat dans le buffer, et des 0 sont ajouté dans
		// l'espace restant à la fin de la chaine.
		STRNCPY(pszDest, WDLEVERIFYVALEURSTR(pszWDGetValeurRetour()), nMax-1);
		// terminaison de la chaine 
		// (ne sert que si le resultat doit être tronqué)
		pszDest[nMax-1]=0; 
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ texte
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
 	// REMARQUE  :		 la longueur est limitée à 64 Ko en 16bit 
	void RecupTexteLong(LPCTSTR pszNom, LPTSTR pszDest, int nMax) 
	{  
		XVALIDSTRING(pszNom);
		CHECKPTROK(pszDest,nMax);
		XASSERT(nMax>=0);

		// appel au langage externe
		WDLEVERIFY(nWDLitPropElem(pszNom,-1));

 		// copie du résulat dans le buffer, et des 0 sont ajouté dans
		// l'espace restant à la fin de la chaine.
		STRNCPY(pszDest, WDLEVERIFYVALEURSTR(pszWDGetValeurRetour()), nMax-1);
		// terminaison de la chaine 
		// (ne sert que si le resultat doit être tronqué)
		pszDest[nMax-1]=0; 
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice du champ indicé, ou indice dans la liste
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
	void RecupTexteLong(LPCTSTR pszNom, int nIndice, LPTSTR pszDest, int nMax)
	{
		XVALIDSTRING(pszNom);
		XASSERT(nIndice>0);
		CHECKPTROK(pszDest,nMax);
		XASSERT(nMax>=0);

		// appel au langage externe
		WDLEVERIFY(nWDLitPropElemInd(pszNom,nIndice,-1));

 		// copie du résulat dans le buffer, et des 0 sont ajouté dans
		// l'espace restant à la fin de la chaine.
		STRNCPY(pszDest, WDLEVERIFYVALEURSTR(pszWDGetValeurRetour()), nMax-1);
		// terminaison de la chaine 
		// (ne sert que si le resultat doit être tronqué)
		pszDest[nMax-1]=0; 
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice du champ indicé, ou indice dans la liste
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
	void RecupTexteLong(LPCTSTR pszNom, int nIndice1, int nIndice2, LPTSTR pszDest, int nMax)
	{
		XVALIDSTRING(pszNom);
		XASSERT(nIndice1>0);
		XASSERT(nIndice2>0);
		CHECKPTROK(pszDest,nMax);
		XASSERT(nMax>=0);

		// appel au langage externe
		WDLEVERIFY(nWDLitPropElemInd2(pszNom,nIndice1,nIndice2,-1));

 		// copie du résulat dans le buffer, et des 0 sont ajouté dans
		// l'espace restant à la fin de la chaine.
		STRNCPY(pszDest, WDLEVERIFYVALEURSTR(pszWDGetValeurRetour()), nMax-1);
		// terminaison de la chaine 
		// (ne sert que si le resultat doit être tronqué)
		pszDest[nMax-1]=0; 
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère l'état d'un champ interrupteur
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	BOOL bRecupEx(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);
 
		WDLEVERIFY(nWDExecuteEx(pszNom));
		return WDLEVERIFYVALEURINT(bWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère l'état d'un champ interrupteur
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	BOOL bRecup(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);
 
		WDLEVERIFY(nWDLitPropElem(pszNom,-1));
		return WDLEVERIFYVALEURINT(bWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère l'état d'un champ interrupteur
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ indicé
 	BOOL bRecup(LPCTSTR pszNom, int nIndice) 
	{ 
		XVALIDSTRING(pszNom);
		XASSERT(nIndice>0);
 
		WDLEVERIFY(nWDLitPropElemInd(pszNom,nIndice,-1));
		return WDLEVERIFYVALEURINT(bWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère l'état d'un champ interrupteur
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ indicé
 	BOOL bRecup(LPCTSTR pszNom, int nIndice1, int nIndice2) 
	{ 
		XVALIDSTRING(pszNom);
		XASSERT(nIndice1>0);
		XASSERT(nIndice2>0);
 
		WDLEVERIFY(nWDLitPropElemInd2(pszNom,nIndice1,nIndice2,-1));
		return WDLEVERIFYVALEURINT(bWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupInterrupteur
	// EFFET     :		 récupère le contenu d'un champ interrupteurs
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  BOOL * pbValeur	 tableau des boolééens qui sera remplit des valeur de
	//					 chaque interrupteur.NB: Le premier a l'indice 0.
	// int nNbOptions	 taille du tableau.
	void RecupInterrupteur(LPCTSTR pszNom, BOOL *pbValeur, int nNbOptions)
	{
		// vérification, en _DEBUG, des paramètre reçus
		XVALIDSTRING(pszNom);	
		// pour chaque interrupteur
		for(int i=0; i<nNbOptions; i++)
		{
			// on récupère la valuer de l'interrupteur numéro 'i'
			WDLEVERIFY(nWDLitPropElemInd(pszNom,i+1,-1));
			pbValeur[i]=WDLEVERIFYVALEURINT(bWDGetValeurRetour());
		}
	}
	
//___________________________________________________________________________
//
//  		Méthodes pour les listes
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeRecup
	// EFFET     :		 récupère le contenu d'un champ Liste/combo
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPTSTR szRes		 buffer pour récupérer le contenu sous forme d'une chaine 
	//					 NULL est valide si on ne veut rien récupérer.
	//	int	* pnSelected renvoie le numéro d'ordre sélectionné ou -1 si la combo est
	//				     en saisie et qu'il ne s'agit d'aucune valeur de la liste
	//					 NULL est valide si on ne veut rien récupérer.
	void ListeRecup(LPCTSTR pszNom, LPTSTR szRes, int *pnSelected) 
	{
		XVALIDSTRING(pszNom);
		// récupération du numéro d'ordre dans la liste.
//		WDLEVERIFY(nWDExecute(_T("ListeSelect(\"%s\")"), pszNom));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESELECT, 0, 1));
		int nSelected = WDLEVERIFYVALEURINT(nWDGetValeurRetour());
		if (szRes!= NULL) // si on veut récupérer la chaine sélectionnée
		{
			CHECKPTROK(szRes, 1);
			// récupère la sélection sous forme de chaine
			if (nSelected>0)
			{
//				WDLEVERIFY(nWDExecute(_T("%s[%d]"), pszNom, nSelected));
				WDLEVERIFY(nWDLitPropElemInd(pszNom,nSelected,1));
				STRCPY(szRes, WDLEVERIFYVALEURSTR(pszWDGetValeurRetour()));
			}
			else
			{
//				WDLEVERIFY(nWDExecute(_T("%s"), pszNom));
				WDLEVERIFY(nWDLitPropElem(pszNom,1));
				if (wWDGetTypeValeurRetour()==WDTYPE_TSTR)
					STRCPY(szRes, WDLEVERIFYVALEURSTR(pszWDGetValeurRetour()));
				else
					*szRes=0;
			}
			
		}   
		if (pnSelected != NULL)
		{
			CHECKPTROK(pnSelected, sizeof(int));
			*pnSelected=nSelected;
		}
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSupprime
	// EFFET     :		 supprime un élément d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice de l'élément à supprimer
	//					 -1 signifie le ou les élément sélectionnés
	void ListeSupprime(LPCTSTR pszNom, int nIndice) 
	{
		XVALIDSTRING(pszNom);	
		XASSERT((nIndice==-1) || (nIndice >= 0));

		nWDEmpile(pszNom,WDTYPE_TSTR);
		if (nIndice==-1) 
//			WDLEVERIFY(nWDExecute(_T("ListeSupprime(\"%s\")"), pszNom, nIndice));
			WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESUPPRIME, 0, 1));
		else 
		{
			nWDEmpile(&nIndice,WDTYPE_INT);
//			WDLEVERIFY(nWDExecute(_T("ListeSupprime(\"%s\",%d)"), pszNom, nIndice));
			WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESUPPRIME, 1, 2));
		}
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szListeRecup
	// EFFET     :		 récupère le contenu d'un champ Liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 -la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	//					 -renvoie chaine vide si pas d'element selectionne
	LPCTSTR szListeRecup(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);

		// ligne selectionne
//		WDLEVERIFY(nWDExecute(_T("ListeSelect(\"%s\")"), pszNom));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESELECT, 0, 1));
		if (WDLEVERIFYVALEURINT(nWDGetValeurRetour())==-1)
		{
			// pas de selection ou valeur saisie
//			WDLEVERIFY(nWDExecuteEx(pszNom));
			WDLEVERIFY(nWDLitPropElem(pszNom,1));
			if (wWDGetTypeValeurRetour()==WDTYPE_TSTR)
				return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
			return _X("");
		}

//		WDLEVERIFY(nWDExecute(_T("%s[%d]"), pszNom, nWDGetValeurRetour()));
		WDLEVERIFY(nWDLitPropElemInd(pszNom,nWDGetValeurRetour(),1));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSupprimeTout
	// EFFET     :		 supprime tous les éléments d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ListeSupprimeTout(LPCTSTR pszNom) 
	{
		XVALIDSTRING(pszNom);  
//		WDLEVERIFY(nWDExecute(_T("ListeSupprimeTout(\"%s\")"), pszNom));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESUPPRIMETOUT, 0, 1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSupprimeTout
	// EFFET     :		 supprime tous les éléments d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ListeSupprimeTout(LPCTSTR pszNom, BOOL bVideCache) 
	{
		XVALIDSTRING(pszNom);  
//		WDLEVERIFY(nWDExecute(_T("ListeSupprimeTout(\"%s\", %d)"), pszNom, bVideCache));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(&bVideCache,WDTYPE_BOOL);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESUPPRIMETOUT, 1, 2));
	}
	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeAjoute
	// EFFET     :		 ajoute un élément à la fin d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dan la liste	
 	void ListeAjoute(LPCTSTR pszNom,LPCTSTR pszValeur) 
	{ 
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszValeur);	
		// utilisation methode rapide
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTEAJOUTE, 1, 2));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeInsere
	// EFFET     :		 insere un élément à une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dan la liste
	//	int nIndice		 indice d'insertion
 	void ListeInsere(LPCTSTR pszNom, LPCTSTR pszValeur, int nIndice)
	{ 
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszValeur);	

//		CTString clTemp(pszValeur);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//		WDLEVERIFY(nWDExecute(_T("ListeInsere(\"%s\",\"%s\",%d)"), pszNom, clTemp, nIndice));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		nWDEmpile(&nIndice,WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTEINSERE, 1, 3));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeModifie
	// EFFET     :		 modifie un élément d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dan la liste
	//	int nIndice		 indice d'insertion
 	void ListeModifie(LPCTSTR pszNom, LPCTSTR pszValeur, int nIndice)
	{ 
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszValeur);	
		XASSERT(nIndice>0);

//		CTString clTemp(pszValeur);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//		WDLEVERIFY(nWDExecute(_T("ListeModifie(\"%s\",\"%s\",%d)"), pszNom, clTemp, nIndice));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		nWDEmpile(&nIndice,WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTEMODIFIE, 1, 3));
	}

	void ListeModifie(LPCTSTR pszNom, int nIndice, LPCTSTR pszValeur)
	{
		ListeModifie(pszNom, pszValeur, nIndice);
	}
	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSelect
	// EFFET     :		 sélectionne un élément d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice de l'élément à sélectionner
 	void ListeSelect(LPCTSTR pszNom,int nIndice) 
	{
		XVALIDSTRING(pszNom);

//		WDLEVERIFY(nWDExecute(_T("ListeSelectPlus(\"%s\",%d)"), pszNom, nIndice));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(&nIndice,WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESELECTPLUS, 0, 2));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeDeselectionneTous
	// EFFET     :		 désélectionne tous les élements d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void ListeDeselectionneTous(LPCTSTR pszNom) 
	{
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("ListeSelectMoins(\"%s\")"), pszNom));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESELECTMOINS, 0, 1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSelectionneTous
	// EFFET     :		 Sélectionne tous les élements d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void ListeSelectionneTous(LPCTSTR pszNom) 
	{
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("ListeSelectPlus(\"%s\")"), pszNom));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESELECTPLUS, 1, 1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeSelect 
	// EFFET     :		 renvoie l'élement sélectionné dans une liste
	//					 ou -1 si rien n'est sélectionné
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nRang		 <optionnel> (1 par defaut) rang de la sélection
	//					 dans le cas de liste multi sélections 
 	int nListeSelect(LPCTSTR pszNom, int nRang)
	{
		XVALIDSTRING(pszNom);
		XASSERT(nRang>0);
//		WDLEVERIFY(nWDExecute(_T("ListeSelect(\"%s\",%d)"), pszNom, nRang));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(&nRang,WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTESELECT, 1, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}
	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeCherche
	// EFFET     :		 recherche l'indice d'un elément dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ liste WinDev
	//  LPCTSTR pszChaineCherchee	chaine recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nListeCherche(LPCTSTR pszNom, LPCTSTR pszChaineCherchee)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszChaineCherchee);	
		// utilisation methode rapide
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszChaineCherchee,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTECHERCHE, 0, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeCherche
	// EFFET     :		 recherche l'indice d'un elément dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ liste WinDev
	//  LPCTSTR nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nListeCherche(LPCTSTR pszNom, int nValCherchee)
	{
		XVALIDSTRING(pszNom);	
		// utilisation methode rapide
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(&nValCherchee,WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTECHERCHE, 0, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeCherche
	// EFFET     :		 recherche l'indice d'un elément dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ liste WinDev
	//  LPCTSTR nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nListeCherche(LPCTSTR pszNom, WDINT64 nValCherchee)
	{
		XVALIDSTRING(pszNom);	
		// utilisation methode rapide
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(&nValCherchee,WDTYPE_INT64);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTECHERCHE, 0, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeOccurrence
	// EFFET     :		 donne le nombre d'éléments dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom		nom du champ liste WinDev
 	int nListeOccurrence(LPCTSTR pszNom)
	{
		XVALIDSTRING(pszNom);	
		// utilisation methode rapide
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_LISTEOCCURRENCE, 0, 1));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	//___________________________________________________________________________
//
//  		Procédures pour les Arbres
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreSupprimeTout
	// EFFET     :		 supprime tous les éléments d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    void ArbreSupprimeTout(LPCTSTR pszNom)
	{
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("ArbreSupprimeTout(\"%s\")"), pszNom));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBRESUPPRIMETOUT, 0, 1));
	}
	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreAjoute
	// EFFET     :		 ajoute un élément à un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dan la liste
 	void ArbreAjoute(LPCTSTR pszNom, LPCTSTR pszValeur, LPCTSTR pszImageEnr/*=NULL*/, LPCTSTR pszImageDer/*=NULL*/, LPCTSTR pszId/*=NULL*/, int nTri/*=0*/)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszValeur);	

		// determine le numero de syntax
		int nSyntax;
		if (pszImageEnr==NULL)
			nSyntax=(pszImageDer==NULL) ? 4 : 7; 
		else
			nSyntax=(pszImageDer==NULL) ? 14 : 10; 

		// empile les parametres
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(pszValeur, WDTYPE_TSTR);

		if (pszImageEnr==NULL)
			nWDEmpile(&pszImageEnr, WDTYPE_INT);
		else
			nWDEmpile(pszImageEnr, WDTYPE_TSTR);
		if (pszImageDer==NULL)
			nWDEmpile(&pszImageDer, WDTYPE_INT);
		else
			nWDEmpile(pszImageDer, WDTYPE_TSTR);
		if (pszId==NULL)
			nWDEmpile(&pszId, WDTYPE_INT);
		else
			nWDEmpile(pszId, WDTYPE_TSTR);
		nWDEmpile(&nTri, WDTYPE_INT);

		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBREAJOUTE, nSyntax, 6));			
	}

 	void ArbreAjouteDWord(LPCTSTR pszNom, LPCTSTR pszValeur, LPCTSTR pszImageEnr/*=NULL*/, LPCTSTR pszImageDer/*=NULL*/, DWORD dwId/*=NULL*/, int nTri/*=0*/)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszValeur);	

		// determine le numero de syntax
		int nSyntax;
		if (pszImageEnr==NULL)
			nSyntax=(pszImageDer==NULL) ? 4 : 7; 
		else
			nSyntax=(pszImageDer==NULL) ? 14 : 10; 

		// empile les parametres
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(pszValeur, WDTYPE_TSTR);

		if (pszImageEnr==NULL)
			nWDEmpile(&pszImageEnr, WDTYPE_INT);
		else
			nWDEmpile(pszImageEnr, WDTYPE_TSTR);
		if (pszImageDer==NULL)
			nWDEmpile(&pszImageDer, WDTYPE_INT);
		else
			nWDEmpile(pszImageDer, WDTYPE_TSTR);
		nWDEmpile(&dwId, WDTYPE_INT);
		nWDEmpile(&nTri, WDTYPE_INT);

		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBREAJOUTE, nSyntax, 6));			
	}


	////////////////////////////////////////////////////////////////
	// NOM	     :		 pszArbreRecupereIdentifiant
	// EFFET     :		 recup l'id d'un un élément d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur dont on veux l'identifiant
	LPCTSTR szArbreRecupereIdentifiant(LPCTSTR pszNom, LPCTSTR	pszValeur)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszValeur);	
		
//		CTString clTemp(pszValeur);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		WDLEVERIFY(nWDExecute(_X("ArbreRecupereIdentifiant(\"%s\", \"%s\")"), pszNom, clTemp));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBRERECUPEREIDENTIFIANT, 0, 2));

		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreDeroule
	// EFFET     :		 recup l'id d'un un élément d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur que l'on vex derouler
	void ArbreDeroule(LPCTSTR pszNom, LPCTSTR pszValeur)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszValeur);	
		
//		CTString clTemp(pszValeur);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		WDLEVERIFY(nWDExecute(_X("ArbreDeroule(\"%s\", \"%s\")"), pszNom, clTemp));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBREDEROULE, 0, 2));
	}

    
	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreSelect
	// EFFET     :		 sélectionne un élément d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur a selectionner
 	void ArbreSelect(LPCTSTR pszNom, LPCTSTR pszValeur) 
	{
		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);	

//		CTString clTemp(pszValeur);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		WDLEVERIFY(nWDExecute(_T("ArbreSelectPlus(\"%s\",\"%s\")"), pszNom, clTemp));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBRESELECTPLUS, 0, 2));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szArbreRecup
	// EFFET     :		 récupère le contenu d'un champ Arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 -la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	//					 -renvoie chaine vide si pas d'element selectionne
	LPCTSTR szArbreRecup(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);

//		WDLEVERIFY(nWDExecute(_T("ArbreSelect(\"%s\")"), pszNom));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBRESELECT, 0, 1));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nArbreTypeElement
	// EFFET     :		 récupère le type d'un element de l' Arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur a tester
	int nArbreTypeElement(LPCTSTR pszNom, LPCTSTR pszValeur)
	{
		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);	

//		CTString clTemp(pszValeur);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		WDLEVERIFY(nWDExecute(_T("ArbreTypeElement(\"%s\",\"%s\")"), pszNom, clTemp));
		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBRETYPEELEMENT, 0, 2));

		return WDLEVERIFYVALEURINT(nWDGetValeurRetour()); 
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreSupprime
	// EFFET     :		 supprime un elem de l'arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur a tester
	void ArbreSupprime(LPCTSTR pszNom, LPCTSTR pszValeur)
	{
		XVALIDSTRING(pszNom);
		XVALIDSTRING(pszValeur);	

		nWDEmpile(pszNom,WDTYPE_TSTR);
		nWDEmpile(pszValeur,WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ARBRESUPPRIME, 0, 2));
	}


//___________________________________________________________________________
//
//  		Classe pour ajouter/supprimer les elements d'une table 
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableAjoute
	// EFFET     :		 ajoute une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPCTSTR pszLigne	 ligne à ajouter, 
	//					 les colonnes sont séparées par des TAB ('\t')
	void TableAjoute(LPCTSTR pszNom, LPCTSTR pszLigne) 
	{  
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszLigne);			
		// utilisation methode rapide
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(pszLigne, WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLEAJOUTE, 1, 2));			
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableInsere
	// EFFET     :		 insère une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPCTSTR pszLigne	 ligne à insérer, 
	//					 les colonnes sont séparées par des TAB ('\t')
	//  int    nIndice   indice de ligne pour l'insertion, 
	//					 si nIndice n'est pas précisé, l'insertion se fait à la ligne courante
	void TableInsere(LPCTSTR pszNom, LPCTSTR pszLigne,int nIndice/*=-1*/)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszLigne);	
//		CTString clTemp(pszLigne);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		WDLEVERIFY(nWDExecute(_T("TableInsere(\"%s\",\"%s\",%d)"), pszNom, clTemp, nIndice));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(pszLigne, WDTYPE_TSTR);
		nWDEmpile(&nIndice, WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLEINSERE, 2, 3));			
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableModifie
	// EFFET     :		 modifie une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPCTSTR pszLigne	 ligne à insérer, 
	//					 les colonnes sont séparées par des TAB ('\t')
	//  int    nIndice   indice de ligne pour l'insertion, 
	//					 si nIndice n'est pas précisé, la modification se fait à la ligne courante
	void TableModifie(LPCTSTR pszNom, LPCTSTR pszLigne,int nIndice/*=-1*/)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszLigne);	
//		CTString clTemp(pszLigne);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		//@@@ A modif lors du changement de nom
//		WDLEVERIFY(nWDExecute(_T("TableModifie(\"%s\",\"%s\",%d)"), pszNom, clTemp, nIndice));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(pszLigne, WDTYPE_TSTR);
		nWDEmpile(&nIndice, WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLEMODIFIE, 1, 3));			
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableSelect 
	// EFFET     :		 renvoie l'élement sélectionné dans une table
	//					 ou -1 si la table est vide
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nRang		 <optionnel> (1 par defaut) rang de la sélection
	//					 dans le cas de liste multi sélections 
 	int nTableSelect(LPCTSTR pszNom, int nRang/*=-1*/) 
	{  
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TableSelect(\"%s\",%d)"),pszNom, nRang));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(&nRang, WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESELECT, 1, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour()); 
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSelect 
	// EFFET     :		 Fixer la ligne sélectionnée dans une table
	//					 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	nIndice		 numéro de la ligne à sélectionner (commence à 1)
 	void TableSelect(LPCTSTR pszNom, int nIndice) 
	{  
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TableSelectPlus(\"%s\",%d)"), pszNom, nIndice));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(&nIndice, WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESELECTPLUS, 1, 2));
	}

	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSelectPlus
	// EFFET     :		 selectionne tout ou une ligne de plus
	// PARAMETRES:
	//	LPCTSTR pszNom				nom de al table
	//  LPCTSTR nValCherchee		indice de ligne (si -1 on selectionne tout)
	void TableSelectPlus(LPCTSTR pszNom, int nIndice)
	{
		XVALIDSTRING(pszNom);	
		nWDEmpile(pszNom, WDTYPE_TSTR);
		if(nIndice>0)
		{
//			WDLEVERIFY(nWDExecute(_T("TableSelectPlus(\"%s\",%d)"), pszNom, nIndice));
			nWDEmpile(&nIndice, WDTYPE_INT);
			WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESELECTPLUS, 1, 2));
		}
		else
		{
//			WDLEVERIFY(nWDExecute(_T("TableSelectPlus(\"%s\")"), pszNom));
			WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESELECTPLUS, 0, 1));
		}
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableDeselectionneTous
	// EFFET     :		 désélectionne tous les élements d'une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void TableDeselectionneTous(LPCTSTR pszNom) 
	{
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TableSelectMoins(\"%s\")"), pszNom));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESELECTMOINS, 0, 1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTablePosition 
	// EFFET     :		 renvoie la position de la 1ere ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	int nTablePosition(LPCTSTR pszNom) 
	{  
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TablePosition(\"%s\")"), pszNom));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLEPOSITION, 0, 1));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour()); 
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TablePositoin 
	// EFFET     :		 Fixer la position de la 1ere ligne dans une table
	//					 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	nIndice		 numéro de la ligne qui devient la 1ere (commence à 1)
 	void TablePosition(LPCTSTR pszNom, int nIndice) 
	{  
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TablePosition(\"%s\",%d)"), pszNom, nIndice));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(&nIndice, WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLEPOSITION, 1, 2));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSupprime
	// EFFET     :		 supprime une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	int	   nIndice	 numéro de la ligne à surprimer 
	//					 (-1) signifie l'élément en cours
 	void TableSupprime(LPCTSTR pszNom,  int nIndice) 
	{  
		XVALIDSTRING(pszNom);	 
		nWDEmpile(pszNom, WDTYPE_TSTR);
		if (nIndice == -1)
		{
//			WDLEVERIFY(nWDExecute(_T("TableSupprime(\"%s\")"), pszNom));
			WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESUPPRIME, 0, 1));
		}
		else
		{
//			WDLEVERIFY(nWDExecute(_T("TableSupprime(\"%s\",%d)"), pszNom, nIndice));
			nWDEmpile(&nIndice, WDTYPE_INT);
			WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESUPPRIME, 1, 2));
		}
	}


	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSupprimeTout
	// EFFET     :		 supprime toutes les lignes dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
  	void TableSupprimeTout(LPCTSTR pszNom) 
	{  
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TableSupprimeTout(\"%s\")"), pszNom));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLESUPPRIMETOUT, 0, 1));
 	}


	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableOccurrence
	// EFFET     :		 donne le nombre d'éléments dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom		nom du champ table WinDev
 	int nTableOccurrence(LPCTSTR pszNom)
	{
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TableOccurrence(\"%s\")"),pszNom));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLEOCCURRENCE, 0, 1));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableCherche
	// EFFET     :		 recherche l'indice d'un elément dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ colonne
	//  LPCTSTR pszChaineCherchee	chaine recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nTableCherche(LPCTSTR pszNom, LPCTSTR pszChaineCherchee)
	{
		XVALIDSTRING(pszNom);	
		XVALIDSTRING(pszChaineCherchee);	
//		CTString clTemp(pszChaineCherchee);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		WDLEVERIFY(nWDExecute(_T("TableCherche(\"%s\",\"%s\")"), pszNom, clTemp));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(pszChaineCherchee, WDTYPE_TSTR);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLECHERCHE, 0, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableCherche
	// EFFET     :		 recherche l'indice d'un elément dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ colonne
	//  LPCTSTR nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nTableCherche(LPCTSTR pszNom, int nValCherchee)
	{
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TableCherche(\"%s\",\"%d\")"), pszNom, nValCherchee));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(&nValCherchee, WDTYPE_INT);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLECHERCHE, 0, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableCherche
	// EFFET     :		 recherche l'indice d'un elément dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ colonne
	//  LPCTSTR nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nTableCherche(LPCTSTR pszNom, WDINT64 nValCherchee)
	{
		XVALIDSTRING(pszNom);	
//		WDLEVERIFY(nWDExecute(_T("TableCherche(\"%s\",%I64d)"), pszNom, nValCherchee));
		nWDEmpile(pszNom, WDTYPE_TSTR);
		nWDEmpile(&nValCherchee, WDTYPE_INT64);
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TABLECHERCHE, 0, 2));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

//___________________________________________________________________________
//
//  		Méthodes de changement d'etat (grisé/invisible/etc..) 
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampGrise
	// EFFET     :		 Grise un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
  	void ChampGrise(LPCTSTR pszNom) 
	{  
		XVALIDSTRING(pszNom);
#ifdef PROPETATMODE55
		int nGrise = 4+0x4000;
#else
		int nGrise = 4;
#endif
		WDLEVERIFY(nWDEmpile(&nGrise,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElem(pszNom,22));
//		WDLEVERIFY(nWDExecute(_T("%s..Etat=Grise"), pszNom));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampGrise
	// EFFET     :		 Grise un champ indicé
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampGrise(LPCTSTR pszNom, int nIndice)
	{  
		XVALIDSTRING(pszNom);	
#ifdef PROPETATMODE55
		int nGrise = 4+0x4000;
#else
		int nGrise = 4;
#endif
		WDLEVERIFY(nWDEmpile(&nGrise,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElemInd(pszNom,nIndice,22));
//		WDLEVERIFY(nWDExecute(_T("%s[%d]..Etat=Grise"), pszNom, nIndice));
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampActif
	// EFFET     :		 Rend Actif (=EnSaisie) un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ChampActif(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);	
#ifdef PROPETATMODE55
		int nActif = 0+0x4000;
#else
		int nActif = 0;
#endif
		WDLEVERIFY(nWDEmpile(&nActif,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElem(pszNom,22));
//		WDLEVERIFY(nWDExecute(_T("%s..Etat=Actif"), pszNom));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampActif
	// EFFET     :		 Rend Actif (=EnSaisie) un champ indicé
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampActif(LPCTSTR pszNom, int nIndice) 
	{  
		XVALIDSTRING(pszNom);	
#ifdef PROPETATMODE55
		int nActif = 0+0x4000;
#else
		int nActif = 0;
#endif
		WDLEVERIFY(nWDEmpile(&nActif,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElemInd(pszNom,nIndice,22));
//		WDLEVERIFY(nWDExecute(_T("%s[%d]..Etat=Actif"), pszNom, nIndice));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInactif
	// EFFET     :		 Rend InActif (=Pas de Saise) un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void ChampInactif(LPCTSTR pszNom) 
	{  
		XVALIDSTRING(pszNom);	
#ifdef PROPETATMODE55
		int nLectureSeule = 1+0x4000;
#else
		int nLectureSeule = 1;
#endif
		WDLEVERIFY(nWDEmpile(&nLectureSeule,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElem(pszNom,22));
//		WDLEVERIFY(nWDExecute(_T("%s..Etat=LectureSeule"), pszNom));
	}	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInactif
	// EFFET     :		 Rend InActif (=Pas de Saise) un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
 	void ChampInactif(LPCTSTR pszNom,int nIndice) 
	{  
		XVALIDSTRING(pszNom);	
#ifdef PROPETATMODE55
		int nLectureSeule = 1+0x4000;
#else
		int nLectureSeule = 1;
#endif
		WDLEVERIFY(nWDEmpile(&nLectureSeule,WDTYPE_INT));
		WDLEVERIFY(nWDEcritPropElemInd(pszNom,nIndice,22));
//		WDLEVERIFY(nWDExecute(_T("%s[%d]..Etat=LectureSeule"), pszNom, nIndice));
	}	


	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampVisible 
	// EFFET     :		 Rend Visible un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ChampVisible(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);	
		BOOL bVisible = TRUE;
		WDLEVERIFY(nWDEmpile(&bVisible,WDTYPE_BOOL));
		WDLEVERIFY(nWDEcritPropElem(pszNom,73));
//		WDLEVERIFY(nWDExecute(_T("%s..Visible=Vrai"), pszNom));
	}


	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampVisible 
	// EFFET     :		 Rend Visible un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampVisible(LPCTSTR pszNom,int nIndice) 
	{ 
		XVALIDSTRING(pszNom);	
		BOOL bVisible = TRUE;
		WDLEVERIFY(nWDEmpile(&bVisible,WDTYPE_BOOL));
		WDLEVERIFY(nWDEcritPropElemInd(pszNom,nIndice,73));
//		WDLEVERIFY(nWDExecute(_T("%s[%d]..Visible=Vrai"), pszNom, nIndice));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampVisible 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	BOOL bChampVisible(LPCTSTR pszNom) 
	{ 
		XVALIDSTRING(pszNom);	
		WDLEVERIFY(nWDLitPropElem(pszNom,73));
		return WDLEVERIFYVALEURINT(bWDGetValeurRetour());
//		WDLEVERIFY(nWDExecute(_T("%s..Visible=Vrai"), pszNom));
	}


	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInvisible
	// EFFET     :		 Rend invisible un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ChampInvisible(LPCTSTR pszNom) 
	{  
		XVALIDSTRING(pszNom);	
		BOOL bVisible = FALSE;
		WDLEVERIFY(nWDEmpile(&bVisible,WDTYPE_BOOL));
		WDLEVERIFY(nWDEcritPropElem(pszNom,73));
//		WDLEVERIFY(nWDExecute(_T("%s..Visible=Faux"), pszNom));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInvisible
	// EFFET     :		 Rend invisible un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampInvisible(LPCTSTR pszNom, int nIndice)
	{  
		XVALIDSTRING(pszNom);	
		BOOL bVisible = FALSE;
		WDLEVERIFY(nWDEmpile(&bVisible,WDTYPE_BOOL));
		WDLEVERIFY(nWDEcritPropElemInd(pszNom,nIndice,73));
//		WDLEVERIFY(nWDExecute(_T("%s[%d]..Visible=Faux"), pszNom, nIndice));
	}

//___________________________________________________________________________
//
//  		Méthodes Jauge
//___________________________________________________________________________
    
    ////////////////////////////////////////////////////////////////
	// NOM	     :		 Jauge
	// EFFET     :		 Affiche une jauge dans la barre de message de la fenetre en cours
	// PARAMETRES:
	//	DWORD dwVal		valeur courante
	// 	DWORD dwMax		valeur maximum
	//	LPCTSTR pszMessage	message affiche a droite de la jauge 
	//						ou NULL pour aucun message (valeur par defaut)
	void Jauge(DWORD dwVal, DWORD dwMax, LPCTSTR pszMessage)
	{
		XASSERT(dwVal <= dwMax);
		if (pszMessage==NULL)
			WDLEVERIFY(nWDExecute(_T("Jauge(%u,%u)"), dwVal, dwMax));
		else
		{
			CTString clTemp(pszMessage);
			clTemp.Remplace(_X("\""), _X("\"\""));	// double les "

			WDLEVERIFY(nWDExecute(_T("Jauge(%u,%u,\"%s\")"), dwVal, dwMax, (PCXSTR)clTemp));
		}
	}
 	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 FinJauge
	// EFFET     :		 Supprime la jauge de la barre de message
	void FinJauge()
	{
		WDLEVERIFY(nWDExecuteEx(_T("Jauge()")));
	}


//___________________________________________________________________________
//
//  		Méthodes diverses 
//___________________________________________________________________________

 	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChangePlan
	// EFFET     :		 change de plan dans la fenetre en cours
	// PARAMETRES:
	//	UINT nPlan		 numéro du plan à activer
	void ChangePlan(UINT nPlan)
	{
		WDLEVERIFY(nWDExecute(_T("MaFenetre..plan=%d"), nPlan));
	}	   

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RepriseSaisie
	// EFFET     :		 Donne le focus a un champ
	// PARAMETRES:
	//	LPCSTR pszNom	 nom du champ WinDev
	void RepriseSaisie(LPCTSTR pszNom) 
	{  
		XVALIDSTRING(pszNom);	
		WDLEVERIFY(nWDExecute(_X("RepriseSaisie(\"%s\")"), pszNom));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RepriseSaisie
	// EFFET     :		 Donne le focus a un champ
	// PARAMETRES:
	//	LPCSTR pszNom	 nom du champ WinDev
	//  int nId			 indice du champ, ou 
	//					 -1 (defaut) pour un champ non indicé
	void RepriseSaisie(LPCTSTR pszNom, int nId ) 
	{  
		XVALIDSTRING(pszNom);	
		// test la valeur par defaut (-1)
		if(nId != -1)
			WDLEVERIFY(nWDExecute(_X("RepriseSaisie(\"%s\",%d)"), pszNom, nId));
		else
			WDLEVERIFY(nWDExecute(_X("RepriseSaisie(\"%s\")"), pszNom));
	}

//	////////////////////////////////////////////////////////////////
//	// NOM	     :		 ExecuteWL
//	// EFFET     :		 Execute une procedure en WLangage
//	// PARAMETRES:
//	//	LPCTSTR pszNomProc	 nom de la procédure
//	void ExecuteWL(LPCTSTR pszNomProc) 
//	{  
//		XVALIDSTRING(pszNomProc);	
//		if (!g_bExtern6)
//			ExecuteWL_5_(pszNomProc);
//		else
//		{
//			XASSERT(strchr(pszNomProc, '.')==NULL);	// pas d'exec de code de champ
//			WDLEVERIFY(nWDExecute(_T("Execute(\"%s\", %d)"), pszNomProc, 10));	//@@@@
//		}
//	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ExecuteWL
	// EFFET     :		 Execute un traitement WL (procédure par défaut)
	// PARAMETRES:
	//	LPCTSTR pszNomTraitement	nom du traitement
	//	int nTraitement				indice du traitement (voir enum eID_FEN_TRAITEMENT)
	void ExecuteWL(LPCTSTR pszNomTraitement, int nTraitement/*=-1*/)
	{  
		XVALIDSTRING(pszNomTraitement);	
		// exécution d'une procédure par défaut
		if(nTraitement==-1) nTraitement=10;	//TRT_BASE_procedure
//		WDLEVERIFY(nWDExecute(_T("ExecuteTraitement(\"%s\", %d)"), pszNomTraitement, nTraitement));
		WDLEVERIFY(nWDEmpile(pszNomTraitement, WDTYPE_TSTR));
		WDLEVERIFY(nWDEmpile(&nTraitement, WDTYPE_INT));
		WDLEVERIFY(nWDAppelle(DLL_WDVM, VM_EXECUTETRAITEMENT, 0, 2));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Sablier
	// EFFET     :		 Activation/Desactivation du sablier
	// PARAMETRES:
	//	BOOL bActive	TRUE pour activer et FALSE pour désactiver
	//
	void Sablier(BOOL bActive)
	{
//		WDLEVERIFY(nWDExecute(_T("Sablier(%d)"), bActive ? TRUE : FALSE));
		WDLEVERIFY(nWDEmpile(&bActive, WDTYPE_BOOL));
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_SABLIER, 1, 1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TitreEnCours
	// EFFET     :		 Change le titre de la fenêtre en cours
	// PARAMETRES:
	//	LPCTSTR pszTitre	 nouveau titre
	void TitreEnCours(LPCTSTR pszTitre) 
	{  
		XVALIDSTRING(pszTitre);	
//		CTString clTemp(pszTitre);
//		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
//
//		WDLEVERIFY(nWDExecute(_T("TitreEnCours(\"%s\")"), clTemp));
		WDLEVERIFY(nWDEmpile(pszTitre, WDTYPE_TSTR));
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_TITREENCOURS, 0, 1));
	}


	////////////////////////////////////////////////////////////////
	// NOM	     :		 Ouvre
	// EFFET     :		 Ouverture d'une fenêtre
	// PARAMETRES:
	//	LPCTSTR pszNom	nom de la fenêtre
	//	HWND hWndMere	handle de la fenêtre mère
	void Ouvre(LPCTSTR pszNom, HWND hWndMere/*=NULL*/)
	{
		XVALIDSTRING(pszNom);
		nWDSetParentNext(hWndMere);
//		WDLEVERIFY(nWDExecute("Ouvre(\"%s\")", pszNom));
		WDLEVERIFY(nWDEmpile(pszNom, WDTYPE_TSTR));
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_OUVRE, 0, 1));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Ferme
	// EFFET     :		 Fermeture d'une fenêtre
	// PARAMETRES:
	void Ferme()
	{
//		nWDExecuteEx(_T("Ferme()"));
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_FERME, 0, 0));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Handle
	// EFFET     :		 Récupération du handle d'une fenêtre
	//					 ou d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	nom de la fenêtre
	HWND Handle(LPCTSTR pszNom)
	{
		XVALIDSTRING(pszNom);
		// utilisation methode rapide
		nWDEmpile(pszNom,WDTYPE_TSTR);

		//si erreur (pas le champ)
		//if (nWDExecute(_T("Handle(\"%s\")"), pszNom)!=WDERREUR_OK)
		if (nWDAppelle(DLL_WDOBJ, OBJ_HANDLE, 1, 1)!=WDERREUR_OK)
		{
			WDRepriseErreur();
			return NULL;
		}
		return (HWND)WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Handle
	// EFFET     :		 Récupération du handle d'une fenêtre en cours
	// Renvoie le handle de la fenêtre WinDev en cours ou NULL si aucune fenêtre WinDev ouverte
	HWND Handle()
	{
//		WDLEVERIFY(nWDExecuteEx(_T("Handle()")));
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_HANDLE, 0, 0));
		return (HWND)WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Premier
	// EFFET     :		 Indique quel champ aura le focus dès que la fenêtre sera en saisie
	// PARAMETRES:
	//    pszNomChamp : nom du champ qui doit prendre le focus
	void Premier(LPCTSTR pszNomChamp)
	{
		XVALIDSTRING(pszNomChamp);	
//		WDLEVERIFY(nWDExecute(_T("EcranPremier(\"%s\")"), pszNomChamp));
		WDLEVERIFY(nWDEmpile(pszNomChamp, WDTYPE_TSTR));
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_ECRANPREMIER, 0, 1));
	}      

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bChampExiste
	// EFFET     :		 test si le champ wd existe
	// PARAMETRES:
	//    pszNomChamp : nom du champ dont on veut tester l'existence
	// 
	BOOL bChampExiste(LPCTSTR pszNomChamp)
	{
		HWND hWnd=Handle(pszNomChamp);
		return hWnd!=NULL;
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bChampModifie
	// EFFET     :		 test si le champ wd a ete modifie
	// PARAMETRES:
	//    pszNomChamp : nom du champ dont on veut tester
	// 
	BOOL bChampModifie(PCXSTR pszNomChamp)
	{
//		WDLEVERIFY(nWDExecute(_T("%s..Modifie"), pszNomChamp));
		WDLEVERIFY(nWDLitPropElem(pszNomChamp,24));
		return WDLEVERIFYVALEURINT(bWDGetValeurRetour());
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 SetPropriete
	// EFFET     :		 fixe 
	// PARAMETRES:
	//    pszNomChamp : nom du champ dont on veut tester
	//	  pszNomProp
	//    pszValeur
	void SetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp, PCXSTR pszValeur)
	{
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszNomProp);
		XVALIDSTRING(pszValeur);

		CTString clTemp(pszValeur);
		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
		WDLEVERIFY(nWDExecute(_T("%s..%s=\"%s\""), pszNomChamp, pszNomProp, (PCXSTR)clTemp));
	}

	void SetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp, int nValeur)
	{
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszNomProp);

		WDLEVERIFY(nWDExecute(_T("%s..%s=%d"), pszNomChamp, pszNomProp, nValeur));
	}
	void SetPropriete(PCXSTR pszNomChamp, int nIndice, PCXSTR pszNomProp, int nValeur)
	{
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszNomProp);

		WDLEVERIFY(nWDExecute(_T("%s[%d]..%s=%d"), pszNomChamp, nIndice, pszNomProp, nValeur));
	}
	void SetPropriete(PCXSTR pszNomChamp, int nIndice, PCXSTR pszNomProp, PCXSTR pszValeur)
	{
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszNomProp);
		XVALIDSTRING(pszValeur);

		CTString clTemp(pszValeur);
		clTemp.Remplace(_X("\""), _X("\"\""));	// double les "
		WDLEVERIFY(nWDExecute(_T("%s[%d]..%s=\"%s\""), pszNomChamp, nIndice, pszNomProp, (PCXSTR)clTemp));
	}

	void SetBulle(PCXSTR pszNomChamp,PCXSTR pszBulle)
	{
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszBulle);

		WDLEVERIFY(nWDEmpile(pszBulle,WDTYPE_TSTR));
		WDLEVERIFY(nWDEcritPropElem(pszNomChamp,4));
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szGetPropriete
	// EFFET     :		 Recup la valeur d'une prop
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szGetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp) 
	{ 
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszNomProp);
 
		WDLEVERIFY(nWDExecute(_X("%s..%s"), pszNomChamp, pszNomProp));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}	

	int nGetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp)
	{ 
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszNomProp);
 
		WDLEVERIFY(nWDExecute(_X("%s..%s"), pszNomChamp, pszNomProp));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}	
	int nGetPropriete(PCXSTR pszNomChamp, int nIndice, PCXSTR pszNomProp)
	{ 
		XVALIDSTRING(pszNomChamp);
		XVALIDSTRING(pszNomProp);
 
		WDLEVERIFY(nWDExecute(_X("%s[%d]..%s"), pszNomChamp, nIndice, pszNomProp));
		return WDLEVERIFYVALEURINT(nWDGetValeurRetour());
	}	

//___________________________________________________________________________
//
//  		Méthodes Init et ouverture
//___________________________________________________________________________

	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 bOuvreBibli
	// EFFET     :		 Ouvre une bibliotheque (wdl)
	// PARAMETRES:
	//	LPCTSTR pszBibli  Nom de la bibliothèque	 ( avec /EXE en plus, si la wdl est intégrée à l'exécutable)
	// Retourne FALSE en cas d'erreur (dans ce cas voir la valeur de WDEntier)
	BOOL bOuvreBibli(LPCTSTR pszBibli)
	{
		XVALIDSTRING(pszBibli);	
		return nWDOuvreWDL(pszBibli)==WDERREUR_OK;
	}

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Fenetre
	// EFFET     :		 Permet de savoir si une fenêtre WinDev est actuellement ouverte
	// PARAMETRES:
	//    phWnd : en sortie contient le handle de la fenêtre ou NULL si aucune fenêtre
	// Renvoie le nom de la fenêtre WinDev actuellement ouverte, ou NULL sinon
	LPCTSTR szFenetre(HWND* phWnd)
	{
		// Si le pointeur n'est pas nul
		if (phWnd!=NULL)
		{
			CHECKPTROK(phWnd,sizeof(HWND));
			// recup la handle de la fen en cours
			*phWnd=Handle();
		}

		// puis son nom
//		WDLEVERIFY(nWDExecuteEx(_T("FenEnCours()")));
		WDLEVERIFY(nWDAppelle(DLL_WDOBJ, OBJ_FENENCOURS, 0, 0));
		return WDLEVERIFYVALEURSTR(pszWDGetValeurRetour());
	}


	//___________________________________________________________________________
	//
	//  		Classe pour ajouter/supprimer les elements d'une table 
	//___________________________________________________________________________

	// granularité d'allocation pour la classe CStringBuffer 
	const int CStringBuffer::m_nGrow = 256; 


	// constructeur
	CStringBuffer::CStringBuffer() 
	{	
		m_pszBuffer= (LPTSTR)malloc(m_nGrow); // allocation du buffer
		m_nTailleCur=0;	// on indique 0 comme taille actuelle.
		if (m_pszBuffer != NULL)
		{
			m_pszBuffer[0] = 0;   // mis à la chaine vide
			m_nTailleMax= (int)m_nGrow;
		}
	}
	// destructeur
	CStringBuffer::~CStringBuffer() 
	{ 
		if (m_pszBuffer) free(m_pszBuffer);
	}
	// ajoute une chaine
	void CStringBuffer::Add(LPCTSTR pstr) 
	{
		// ajoute un a un les caratère de pstr jusqu'a rencontrer '\0'
		while (*pstr) AddInternal(*pstr++); 
		MetZeroTerminal();
	}  
 	// ajoute la représentation décimale d'un entier 
	void CStringBuffer::Add(long l)
	{
		TCHAR szBuf[16];	// buffer pour stoquer l'entiersou forme de chaine
		LTOA(l, szBuf, 10); // convertion en base 10
		Add(szBuf); // ajout de la chaine dans le buffer
	}
	//ajoute la représentation décimale d'un entier sur 64bit
	void CStringBuffer::Add(WDINT64 l64)
	{
		TCHAR szBuf[50+1];
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x550)
		ltoa(l64,szBuf,10);
#else
		I64TOA(l64,szBuf,10);
#endif
		Add(szBuf);
	}

	// ajout d'un caractère sans mise du zero terminal
	void CStringBuffer::AddInternal(TCHAR c)  
	{
		// si le buffer est plein
		if (m_nTailleCur+1 >= m_nTailleMax)
		{
			// on demande plus de mémoire
			LPTSTR pszBiggerBuf = (LPTSTR)realloc(m_pszBuffer , m_nTailleMax+m_nGrow);
			// si il n'y a plus de mémoire 
			if (pszBiggerBuf == NULL) return; // on abandonne
			// mise en place d'un buffer plus grand.
			m_pszBuffer = pszBiggerBuf; 
		    m_nTailleMax += m_nGrow;
		}
		// ajout d'un caractère
		CHECKPTROK(m_pszBuffer, m_nTailleCur+1 );
		m_pszBuffer[m_nTailleCur++] = c;
	}
	// constructeur
	CWDTable::CWDTable(LPCTSTR pszNom) 
	{
		CHECKLPCTSTR(pszNom);	
		XASSERT(STRLEN(pszNom) <= nsMaxNomChamp);
		
		// copie le nom.
		STRCPY(m_szNom, pszNom);
 	}
