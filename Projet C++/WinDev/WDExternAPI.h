//Interface C++ pour Langage Externe WinDev
// définition des prototypes

#ifndef __WDEXTERNAPI_H
#define __WDEXTERNAPI_H

#include <string.h>
#include <assert.h>

#ifndef __cplusplus
#error "Ce module ne peut pas être inclus depuis un .C, seuls les .CPP sont supportés."
#endif //__cplusplus

#include "WDExtern.h"

#define pszBool2OuiNon(_a) ((_a) ? _X("1") : _X("0"))

#include <tchar.h>
#define UNUSED(x)	x;
#define MEMCPY		memcpy
#define STRCMP		_tcscmp
#define STRICMP		_tcsicmp
#define STRCPY		_tcscpy
#define STRNCPY		_tcsncpy
#define STRSTR		_tcsstr
#define STRLEN		_tcslen
#define LTOA		_ltot
#define I64TOA		_i64tot
#define _X(txt)		__T(txt)
#define PXSTR		LPTSTR
#define PCXSTR		LPCTSTR
#define FASTCALL __fastcall

class CTString
{
	//Données membre:
protected:
	PXSTR m_pszStr;	// pointeur sur la chaine allouée

	//Méthodes:
public:

	//constructeur/destructeur
	CTString(void);				// construction d'une chaine vide
	CTString(PCXSTR pszText);	// constructeur à partir d'une chaine ASCIZZ
	~CTString();				// destructeur (libération du buffer de chaine)

	// récup du buffer ASCIIZ
	PCXSTR pszGet(void) const;
	operator const PCXSTR () const { return pszGet(); }

	// gestion de la taille.
	int  nTaille(void) const; // récupération du nombre de caractère d'une chaine
	BOOL bEstVide(void) const;	  // indique si la chaine est vide
	void Vide(void);		  // mise à la chaine NULLE (libère le buffer).

	int FASTCALL nPos(PCXSTR psz, int nFrom=0) const; // position de la chaine <psz> (ou -1)
	void FASTCALL Set(PCXSTR pszNew); // Init à partir d'une chaine ASCIIZ
	const CTString& operator = (PCXSTR psz) {Set(psz); return *this;}		// CTString A = "hello";
	// remplace toutes les occurences de 'pszMotRecherche' par pszAlaPlace
	void FASTCALL Remplace(PCXSTR pszMotRecherche, PCXSTR pszAlaPlace);
protected:
	// méthode pour l'implémentation
	// changer la taille du buffer
	void FASTCALL _SetBufferSize(int nNewSize);
};

#define XVALIDECHAMP(champ)	XASSERT( !IsBadStringPtr(champ,(UINT)-1) && bChampExiste(champ) )


#ifdef _DEBUG
	#define XASSERT(exp)				assert(exp)
	#define XASSERTC(exp,com)			XASSERT(exp)
	#define CHECKPTROK(ptr,size)		XASSERT(!IsBadReadPtr(ptr,size) && !IsBadWritePtr((LPVOID)(ptr),size))
	#define XVALIDSTRING(pzStr)			XASSERT(!IsBadStringPtr(pzStr,(UINT)-1))		
	#define XDBG(act)					act

	#define WDLEVERIFY(_exp) do { int _nres=_exp; XASSERTC(_nres==WDERREUR_OK, pszWDGetLastError()); } while (wWDGetTypeValeurRetour() * 0)
	#define WDLEVERIFYVALEURINT(_exp) ( XASSERT((wWDGetTypeValeurRetour()!=WDTYPE_TSTR) && (wWDGetTypeValeurRetour()!=WDTYPE_VOID)), _exp )
	#define WDLEVERIFYVALEURSTR(_exp) ( XASSERT((wWDGetTypeValeurRetour()==WDTYPE_ASTR) || (wWDGetTypeValeurRetour()==WDTYPE_WSTR)), _exp )
#else
	#define XASSERT(exp)
	#define XASSERTC(exp,com)
	#define CHECKPTROK(ptr,size)
	#define XVALIDSTRING(s)
	#define XDBG(act)
	#define WDLEVERIFY(_exp) _exp
	#define WDLEVERIFYVALEURINT(_exp) ( _exp )
	#define WDLEVERIFYVALEURSTR(_exp) ( _exp )
#endif

//___________________________________________________________________________
//
//  		Procédures de modification du contenu des champs	
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur nouvelle valeur
	void AfficheEx(LPCTSTR pszNom, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur nouvelle valeur
	void Affiche(LPCTSTR pszNom, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	 :			Affiche
	// EFFET :			modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	nom du champ WinDev
	//	int    nIndice	indice du champ (commence à 1)
	//  LPCTSTR pszValeur nouvelle valeur
	void Affiche(LPCTSTR pszNom, int nIndice, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	 :			Affiche
	// EFFET :			modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  LPCTSTR pszValeur nouvelle valeur
	void Affiche(LPCTSTR pszNom, int nIndice1, int nIndice2, LPCTSTR pszValeur);

	// pour compatibilite
	void Affiche(LPCTSTR pszNom, LPCTSTR pszValeur, int nLong);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nValeur		 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nValeur);  

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  int nValeur		 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nIndice, int nValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  int lValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nIndice1, int nIndice2, int nValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  double dValeur	 nouvelle valeur
 	void AfficheEx(LPCTSTR pszNom, double dValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  double dValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, double dValeur);  

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nValeur		 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, DWORD dwValeur);  

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Affiche
	// EFFET     :		 modifie le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int    nIndice		 indice du champ (commence à 1)
	//  long lValeur	 nouvelle valeur
 	void Affiche(LPCTSTR pszNom, int nIndice, DWORD dwValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 AfficheInterrupteur
	// EFFET     :		 modifie le contenu d'un champ interrupteur 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  BOOL * pbValeur	 tableau de états de chaque interupteur (commence à 0)
	//  int nNbOptions   taille du tableau 
	void AfficheInterrupteur(LPCTSTR pszNom, const BOOL * const pbValeur, int nNbOptions);

//___________________________________________________________________________
//
//  		Procédures de lecture du contenu des champs	
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 dRecup
	// EFFET     :		 récupère le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    double dRecupEx(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 dRecup
	// EFFET     :		 récupère le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    double dRecup(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ numérique 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    int nRecupEx(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    int nRecup(LPCTSTR pszNom); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ avec indice
	int nRecup(LPCTSTR pszNom, int nIndice);

	// NOM	     :		 nRecup
	// EFFET     :		 récupère le contenu d'un champ numérique indicé
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ indicé
	int nRecup(LPCTSTR pszNom, int nIndice1, int nIndice2);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szRecupEx(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ texte
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ avec indice
	LPCTSTR szRecup(LPCTSTR pszNom);	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ avec indice
	LPCTSTR szRecup(LPCTSTR pszNom, int nIndice);	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szRecup
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ 
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szRecup(LPCTSTR pszNom, int nIndice1, int nIndice2);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ texte
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
 	// REMARQUE  :		 la longueur est limitée à 64 Ko en 16bit 
	void RecupTexteLongEx(LPCTSTR pszNom, LPTSTR pszDest, int nMax);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ texte
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
	void RecupTexteLong(LPCTSTR pszNom, LPTSTR pszDest, int nMax); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice du champ avec indice
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
 	// REMARQUE  :		 la longueur est limitée à 64 Ko  
	void RecupTexteLong(LPCTSTR pszNom, int nIndice, LPTSTR pszDest, int nMax); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupTexteLong
	// EFFET     :		 récupère le contenu d'un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice du champ indicé, ou indice dans la liste
	//  LPTSTR lszDest	 buffer pour contenir la valeur récupérée
	//	int nMax		 taille maxi de la chaine (en comptant le 0 final)
	void RecupTexteLong(LPCTSTR pszNom, int nIndice1, int nIndice2, LPTSTR pszDest, int nMax);
		
	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère l'état d'un champ interrupteur
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	BOOL bRecupEx(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	BOOL bRecup(LPCTSTR pszNom);  

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère le contenu d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ
 	BOOL bRecup(LPCTSTR pszNom, int nIndice); 
		
	////////////////////////////////////////////////////////////////
	// NOM	     :		 bRecup
	// EFFET     :		 récupère l'état d'un champ interrupteur
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	   nIndice		 indice du champ indicé
 	BOOL bRecup(LPCTSTR pszNom, int nIndice1, int nIndice2);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupCombo
	// EFFET     :		 récupère le contenu d'un champ interrupteurs
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  BOOL * pbValeur	 tableau des boolééens qui sera remplit des valeur de
	//					 chaque interrupteur.NB: Le premier a l'indice 0.
	// int nNbOptions	 taille du tableau.
	void RecupInterrupteur(LPCTSTR pszNom, BOOL *pbValeur, int nNbOptions);
	
//___________________________________________________________________________
//
//  		Procédures pour les listes
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RecupCombo
	// EFFET     :		 récupère le contenu d'un champ Liste/combo
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPTSTR szRes		 buffer pour récupérer le contenu sous forme d'une chaine 
	//					 NULL est valide si on ne veut rien récupérer.
	//	int	* pnSelected renvoie le numéro d'ordre sélectionné ou -1 si la combo est
	//				     en saisie et qu'il ne s'agit d'aucune valeur de la liste
	//					 NULL est valide si on ne veut rien récupérer.
	void ListeRecup(LPCTSTR pszNom, LPTSTR szRes, int *pnSelected);

	#define RecupCombo ListeRecup

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szListeRecup
	// EFFET     :		 récupère le contenu d'un champ Liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 -la longueur est limitée à 200 caractères
	//					 -la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	//					 -renvoie chaine vide si pas d'element selectionne
	LPCTSTR szListeRecup(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSupprime
	// EFFET     :		 supprime un élément d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice de l'élément à supprimer
	//					 -1 signifie le ou les élément sélectionnés
	void ListeSupprime(LPCTSTR pszNom, int nIndice=-1);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSupprimeTout
	// EFFET     :		 supprime tous les éléments d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    void ListeSupprimeTout(LPCTSTR pszNom);
	void ListeSupprimeTout(LPCTSTR pszNom, BOOL bVideCache) ;

	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeAjoute
	// EFFET     :		 ajoute un élément à la fin d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dan la liste
 	void ListeAjoute(LPCTSTR pszNom, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeInsere
	// EFFET     :		 ajoute un élément à la fin d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dan la liste
	//	int nIndice		 indice d'insertion
 	void ListeInsere(LPCTSTR pszNom, LPCTSTR pszValeur, int nIndice);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeModifie
	// EFFET     :		 modifie un élément d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dan la liste
	//	int nIndice		 indice d'insertion
 	void ListeModifie(LPCTSTR pszNom, LPCTSTR pszValeur, int nIndice);

	// pour compatibilite
	void ListeModifie(LPCTSTR pszNom, int nIndice, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSelect
	// EFFET     :		 sélectionne un élément d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//	int nIndice		 indice de l'élément à sélectionner	(commence à 1)
 	void ListeSelect(LPCTSTR pszNom, int nIndice);  

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeDeselectionneTous
	// EFFET     :		 désélectionne tous les élements d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void ListeDeselectionneTous(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ListeSelectionneTous
	// EFFET     :		 Sélectionne tous les élements d'une liste
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void ListeSelectionneTous(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeSelect 
	// EFFET     :		 renvoie l'élement sélectionné dans une liste
	//					 ou -1 si rien n'est sélectionné
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nRang		 rang de la sélection dans le cas de liste
	//					 multi sélections (1 pour le premier)
 	int nListeSelect(LPCTSTR pszNom, int nRang=1);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeCherche
	// EFFET     :		 recherche l'indice d'un elément dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ liste WinDev
	//  LPCTSTR pszChaineCherchee	chaine recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nListeCherche(LPCTSTR pszNom, LPCTSTR pszChaineCherchee);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeCherche
	// EFFET     :		 recherche l'indice d'un elément dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ liste WinDev
	//  int nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nListeCherche(LPCTSTR pszNom, int nValCherchee);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeCherche
	// EFFET     :		 recherche l'indice d'un elément dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ liste WinDev
	//  LPCTSTR nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nListeCherche(LPCTSTR pszNom, WDINT64 nValCherchee);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nListeOccurrence
	// EFFET     :		 donne le nombre d'éléments dans une liste
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ liste WinDev
 	int nListeOccurrence(LPCTSTR pszNom);

//___________________________________________________________________________
//
//  		Procédures pour les Arbres
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreSupprimeTout
	// EFFET     :		 supprime tous les éléments d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
    void ArbreSupprimeTout(LPCTSTR pszNom);
	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreAjoute
	// EFFET     :		 ajoute un élément à un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur à ajouter dans l'arbre
	//	int nTri		 Type de tri pour l'insertion (0-> alpha, 0x2000-> Dernier, 0x1000-> Premier, 0x4000-> Accepte doublon)
 	void ArbreAjoute(LPCTSTR pszNom, LPCTSTR pszValeur, LPCTSTR pszImageEnr=NULL, LPCTSTR pszImageDer=NULL, LPCTSTR pszId=NULL, int nTri=0);
	void ArbreAjouteDWord(LPCTSTR pszNom, LPCTSTR pszValeur, LPCTSTR pszImageEnr=NULL, LPCTSTR pszImageDer=NULL, DWORD dwId=NULL, int nTri=0);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 pszArbreRecupereIdentifiant
	// EFFET     :		 recup l'id d'un un élément d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur dont on veux l'identifiant
	LPCTSTR szArbreRecupereIdentifiant(LPCTSTR pszNom, LPCTSTR	pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreDeroule
	// EFFET     :		 recup l'id d'un un élément d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur que l'on vex derouler
	void ArbreDeroule(LPCTSTR pszNom, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreSelect
	// EFFET     :		 sélectionne un élément d'un arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur a selectionner
 	void ArbreSelect(LPCTSTR pszNom, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szArbreRecup
	// EFFET     :		 récupère le contenu d'un champ Arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 -la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	//					 -renvoie chaine vide si pas d'element selectionne
	LPCTSTR szArbreRecup(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nArbreTypeElement
	// EFFET     :		 récupère le type d'un element de l' Arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur a tester
	int nArbreTypeElement(LPCTSTR pszNom, LPCTSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ArbreSupprime
	// EFFET     :		 supprime un elem de l'arbre
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  LPCTSTR pszValeur valeur a tester
	void ArbreSupprime(LPCTSTR pszNom, LPCTSTR pszValeur);

//___________________________________________________________________________
//
//  	 Procédures pour les tables
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableAjoute
	// EFFET     :		 ajoute une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPCTSTR pszLigne	 ligne à ajouter, 
	//					 les colonnes sont séparées par des TAB ('\t')
	void TableAjoute(LPCTSTR pszNom, LPCTSTR pszLigne); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableInsere
	// EFFET     :		 insère une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPCTSTR pszLigne	 ligne à insérer, 
	//					 les colonnes sont séparées par des TAB ('\t')
	//  int    nIndice   indice de ligne pour l'insertion, 
	//					 si nIndice n'est pas précisé, l'insertion se fait à la ligne courante
	void TableInsere(LPCTSTR pszNom, LPCTSTR pszLigne, int nIndice=-1); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableModifie
	// EFFET     :		 modifie une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	LPCTSTR pszLigne	 ligne à insérer, 
	//					 les colonnes sont séparées par des TAB ('\t')
	//  int    nIndice   indice de ligne pour l'insertion, 
	//					 si nIndice n'est pas précisé, la modification se fait à la ligne courante
	void TableModifie(LPCTSTR pszNom, LPCTSTR pszLigne,int nIndice=-1);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableSelect 
	// EFFET     :		 renvoie l'élement sélectionné dans une table
	//					 ou -1 si la table est vide
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nRang		 <optionnel> (1 par defaut) rang de la sélection
	//					 dans le cas de liste multi sélections 
 	int nTableSelect(LPCTSTR pszNom, int nRang=1);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSelect 
	// EFFET     :		 Fixer la ligne sélectionnée dans une table
	//					 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	nIndice		 numéro de la ligne à sélectionner (commence à 1)
 	void TableSelect(LPCTSTR pszNom, int nIndice);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTablePosition 
	// EFFET     :		 renvoie la position de la 1ere ligne dans une table
	//
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	int nTablePosition(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TablePositoin 
	// EFFET     :		 Fixer la position de la 1ere ligne dans une table
	//					 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int	nIndice		 numéro de la ligne qui devient la 1ere (commence à 1)
	void TablePosition(LPCTSTR pszNom, int nIndice); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSupprime
	// EFFET     :		 supprime une ligne dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// 	int	   nIndice	 numéro de la ligne à surprimer 
	//					 (-1) signifie l'élément en cours
 	void TableSupprime(LPCTSTR pszNom, int nIndice = -1);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSupprime
	// EFFET     :		 supprime toutes les lignes dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
  	void TableSupprimeTout(LPCTSTR pszNom); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableOccurrence
	// EFFET     :		 donne le nombre d'éléments dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom		nom du champ table WinDev
 	int nTableOccurrence(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableCherche
	// EFFET     :		 recherche l'indice d'un elément dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ colonne
	//  LPCTSTR pszChaineCherchee	chaine recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nTableCherche(LPCTSTR pszNom, LPCTSTR pszChaineCherchee);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableCherche
	// EFFET     :		 recherche l'indice d'un elément dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ colonne
	//  LPCTSTR nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nTableCherche(LPCTSTR pszNom, int nValCherchee);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 nTableCherche
	// EFFET     :		 recherche l'indice d'un elément dans une table
	// PARAMETRES:
	//	LPCTSTR pszNom				nom du champ colonne
	//  LPCTSTR nValCherchee			valeur recherchée
	// RETOUR
	//	l'indice de l'élément récherché ou -1 si pas trouvé
	int nTableCherche(LPCTSTR pszNom, WDINT64 nValCherchee);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableSelectPlus
	// EFFET     :		 selectionne tout ou une ligne de plus
	// PARAMETRES:
	//	LPCTSTR pszNom				nom de al table
	//  LPCTSTR nValCherchee		indice de ligne (si -1 on selectionne tout)
	void TableSelectPlus(LPCTSTR pszNom, int nIndice=-1);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 TableDeselectionneTous
	// EFFET     :		 désélectionne tous les élements d'une table
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void TableDeselectionneTous(LPCTSTR pszNom);


//___________________________________________________________________________
//
//  		Procédures de changement d'etat (grisé/invisible/etc..) 
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampGrise
	// EFFET     :		 Grise un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
  	void ChampGrise(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampGrise
	// EFFET     :		 Grise un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampGrise(LPCTSTR pszNom, int nIndice);  

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampActif	
	// EFFET     :		 Rend Actif (=EnSaisie) un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ChampActif(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampActif
	// EFFET     :		 Rend Actif (=EnSaisie) un champ avec indice
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampActif(LPCTSTR pszNom, int nIndice);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInactif
	// EFFET     :		 Rend InActif (=Pas de Saise) un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
 	void ChampInactif(LPCTSTR pszNom);	

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInactif
	// EFFET     :		 Rend InActif (=Pas de Saise) un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
 	void ChampInactif(LPCTSTR pszNom,int nIndice); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampVisible 
	// EFFET     :		 Rend Visible un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ChampVisible(LPCTSTR pszNom); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampVisible 
	// EFFET     :		 Rend Visible un champ 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampVisible(LPCTSTR pszNom,int nIndice); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampVisible 
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	BOOL bChampVisible(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInvisible
	// EFFET     :		 Rend invisible un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	void ChampInvisible(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChampInvisible
	// EFFET     :		 Rend invisible un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	//  int nIndice			 indice du champ
	void ChampInvisible(LPCTSTR pszNom, int nIndice);

	////////////////////////////////////////////////////////////////
	// renseigne la bulle sur le champ
	//	pszNomChamp : nom du champ
	//	pszBulle : contenu de la bulle
	void SetBulle(PCXSTR pszNomChamp,PCXSTR pszBulle);


//___________________________________________________________________________
//
//  	Procédures des gestion de la Jauge dans la barre d'état
//___________________________________________________________________________
    
    ////////////////////////////////////////////////////////////////
	// NOM	     :		 Jauge
	// EFFET     :		 Affiche une jauge dans la barre de message de la fenetre en cours
	// PARAMETRES:
	//	DWORD dwVal		valeur courante
	// 	DWORD dwMax		valeur maximum
	//	LPCTSTR pszMessage	message affiche a droite de la jauge 
	//						ou NULL pour aucun message (valeur par defaut)
	void Jauge(DWORD dwVal, DWORD dwMax, LPCTSTR pszMessage = NULL);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 FinJauge
	// EFFET     :		 Supprime la jauge de la barre de message
	void FinJauge();


//___________________________________________________________________________
//
//  		Procédures diverses 
//___________________________________________________________________________

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ChangePlan
	// EFFET     :		 change de plan dans la fenetre en cours
	// PARAMETRES:
	//	UINT nPlan		 numéro du plan à activer
	void ChangePlan( UINT nPlan );

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RepriseSaisie
	// EFFET     :		 Donne le focus a un champ
	// PARAMETRES:
	//	LPCSTR pszNom	 nom du champ WinDev
	void RepriseSaisie(LPCTSTR pszNom); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 RepriseSaisie
	// EFFET     :		 Donne le focus a un champ
	// PARAMETRES:
	//	LPCSTR pszNom	 nom du champ WinDev
	//  int nId			 indice du champ, ou 
	//					 -1 (defaut) pour un champ non indicé
	void RepriseSaisie(LPCSTR pszNom, int nId );


//	////////////////////////////////////////////////////////////////
//	// NOM	     :		 ExecuteWL
//	// EFFET     :		 Execute une procedure en WLangage
//	// PARAMETRES:
//	//	LPCTSTR pszNomProc	 nom de la procédure / nom du champ
//	void ExecuteWL(LPCTSTR pszNomProc);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 ExecuteWL
	// EFFET     :		 Execute un traitement WL (procédure par défaut)
	// PARAMETRES:
	//	LPCTSTR pszNomTraitement	nom du traitement
	//	int nTraitement				indice du traitement (voir enum eID_FEN_TRAITEMENT)
	void ExecuteWL(LPCTSTR pszNomTraitement, int nTraitement=-1);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Sablier
	// EFFET     :		 Activation/Desactivation du sablier
	// PARAMETRES:
	//	BOOL bActive	TRUE pour activer et FALSE pour désactiver
	//
	void Sablier(BOOL bActive);
	
	////////////////////////////////////////////////////////////////
	// NOM	     :		 TitreEnCours
	// EFFET     :		 Change le titre de la fenêtre en cours
	// PARAMETRES:
	//	LPCTSTR pszTitre	 nouveau titre
	void TitreEnCours(LPCTSTR pszTitre);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Nation
	// EFFET     :		 Change la langue
	// PARAMETRES:
	//	int nNumLangue	numéro de la langue
	void Nation(int nNumLangue);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Ouvre
	// EFFET     :		 Ouverture d'une fenêtre
	// PARAMETRES:
	//	LPCTSTR pszNom	nom de la fenêtre
	//	HWND hWndMere	handle de la fenêtre mère
	void Ouvre(LPCTSTR pszNom, HWND hWndMere=NULL);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Ferme
	// EFFET     :		 Fermeture d'une fenêtre
	// PARAMETRES:
	void Ferme();

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Handle
	// EFFET     :		 Récupération du handle d'une fenêtre
	//					 ou d'un champ
	// PARAMETRES:
	//	LPCTSTR pszNom	nom de la fenêtre
	HWND Handle(LPCTSTR pszNom);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Handle
	// EFFET     :		 Récupération du handle d'une fenêtre en cours
	// Renvoie le handle de la fenêtre WinDev en cours ou NULL si aucune fenêtre WinDev ouverte
	HWND Handle();

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Premier
	// EFFET     :		 Indique quel champ aura le focus dès que la fenêtre sera en saisie
	// PARAMETRES:
	//    pszNomChamp : nom du champ qui doit prendre le focus
	void  Premier(PCXSTR pszNomChamp);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bChampExiste
	// EFFET     :		 test si le champ wd existe
	// PARAMETRES:
	//    pszNomChamp : nom du champ dont on veut tester l'existence
	// 
	BOOL bChampExiste(PCXSTR pszNomChamp); 

	////////////////////////////////////////////////////////////////
	// NOM	     :		 bChampModifie
	// EFFET     :		 test si le champ wd a ete modifie
	// PARAMETRES:
	//    pszNomChamp : nom du champ dont on veut tester
	// 
	BOOL bChampModifie(PCXSTR pszNomChamp);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 SetPropriete
	// EFFET     :		 fixe 
	// PARAMETRES:
	//    pszNomChamp : nom du champ dont on veut tester
	//	  pszNomProp
	//    pszValeur
	void SetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp, PCXSTR pszValeur);
	void SetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp, int nValeur);
	void SetPropriete(PCXSTR pszNomChamp, int nIndice, PCXSTR pszNomProp, int nValeur);
	void SetPropriete(PCXSTR pszNomChamp, int nIndice, PCXSTR pszNomProp, PCXSTR pszValeur);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 szGetPropriete
	// EFFET     :		 Recup la valeur d'une prop
	// PARAMETRES:
	//	LPCTSTR pszNom	 nom du champ WinDev
	// REMARQUE  :		 la valeur renvoyé n'est valide que jusqu'au
	//					  prochain appel d'un fonction de l'API
	LPCTSTR szGetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp);
	int nGetPropriete(PCXSTR pszNomChamp, PCXSTR pszNomProp);
	int nGetPropriete(PCXSTR pszNomChamp, int nIndice, PCXSTR pszNomProp);

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
	BOOL bOuvreBibli(LPCTSTR pszBibli);

	////////////////////////////////////////////////////////////////
	// NOM	     :		 Fenetre
	// EFFET     :		 Permet de savoir si une fenêtre WinDev est actuellement ouverte
	// PARAMETRES:
	//    phWnd : en sortie contient le handle de la fenêtre ou NULL si aucune fenêtre
	// Renvoie le nom de la fenêtre WinDev actuellement ouverte, ou NULL sinon
	LPCTSTR szFenetre(HWND* phWnd = NULL);


///////////////////////////////////////////////////////////////////////////////
// Macros de remplacement des fonctions gXXXXX du WL

// fonction gImage
#define GIMAGE_FIC(img) _X("\033BN"##img"[]")
#define GIMAGE_NUM(nimg, num) _X("\033B"##nimg"["##num"]")

// fonction gCadrage
#define GCADRAGE(cad, ch) _X("\033C"##cad"(\036"##ch"\036)")
#define DEBUT_GCADRAGE(cad) _X("\033C"##cad"V(\036")
#define FIN_GCADRAGE() _X("\036)")
#define FIN_GCADRAGEPOSX(x1,x2) _X("\036,"##x1","##x2")")

// fonction gFond
#define GFOND(couleur) _X("\033F"##couleur)
#define GFONDRVB(r,v,b) _X("\033FRVB("##r","##v","##b")")

// fonction gStylo
#define GSTYLO(couleur) _X("\033T"##couleur)
#define GSTYLORVB(r,v,b) _X("\033TRVB("##r","##v","##b")")

// fonction gLien
#define GLIEN(szval) _X("\033K"##szval"\033K")

// fonction gRectangle
#define GRECTANGLE(l,t,r,b,cofond,cobord) _X("\033R("##l","##t","##r","##b","##cofond","##cobord")")

// fonction gCoord
#define GCOORD(x,y) _X("\033X"##x"\033Y"##y)
#define GCOORDX(x) _X("\033X"##x)
#define GCOORDY(y) _X("\033Y"##y)


//___________________________________________________________________________
//
//  		Classe pour ajouter/supprimer les elements d'une table 
//___________________________________________________________________________

// taille limite en caractères d'un nom de champ WinDev.
static const int nsMaxNomChamp = 30;

	// classe qui gère une buffer pour concaténer des chaines 
	// (utilisé par CWDTable, voir plus bas)
	class CStringBuffer
	{
	public:
		CStringBuffer(); 
 		~CStringBuffer();

		LPCTSTR pszGetBuffer() {return m_pszBuffer;}
		// ajoute 1 caractère
		void Add(TCHAR c) {AddInternal(c);MetZeroTerminal();}  
		// ajoute une chaine
		void Add(LPCTSTR pstr); 
 		// ajoute la représentation décimale d'un entier 
		void Add(long l);
		//ajoute la représentation décimale d'un entier sur 64bit
		void Add(WDINT64 l64);
 		// vide le buffer
		void MetAVide() {m_nTailleCur = 0;MetZeroTerminal();}

	protected:
		// ajoute un caractère (sans mettre le 0 terminal)
		void AddInternal(TCHAR c);  
 		void MetZeroTerminal() {m_pszBuffer[m_nTailleCur] = 0;}
		LPTSTR m_pszBuffer; // pointeur sur le buffer
		int m_nTailleCur;  // taille actuelle de la chaine contenue (=strlen(m_pszBuffer))
		int m_nTailleMax;  // taille maximum (dernière taille allouées)
		static const int m_nGrow; // granularité d'allocation
	};



	// classe permettant de rajouter/insérer/modifier facilement des colonnes dans une table
	// exemple :
	//	CWDTable clTable("TABLE1"); 
	//	clTable.TableColonneAjoute(34000);			// Code Postal
	//	clTable.TableColonneAjoute("Montpellier");	// ville
	//	clTable.TableColonneAjoute();				// -> saute une colonne
	//	clTable.TableColonneAjoute("France");		// Pays
	//	clTable.TableFinAjoute();	// -> ajoute effectivement toute la ligne

	class CWDTable
	{
	public:
		CWDTable(LPCTSTR pszNom);
	 	// pour ajouter des colonnes
		inline void TableColonneAjoute(LPCTSTR pszCol) { m_clLigne.Add(pszCol);m_clLigne.Add(_X('\t'));}
		inline void TableColonneAjoute(long nCol) {  m_clLigne.Add(nCol);m_clLigne.Add(_X('\t')); }
		inline void TableColonneAjoute64(WDINT64 lCol64) {  m_clLigne.Add(lCol64);m_clLigne.Add(_X('\t')); }
		inline void TableColonneAjoute() { m_clLigne.Add(_X('\t')); }
		// finalise l'ajout des colonnes en ajoutant la ligne créé
		// par les "TableColonneAjoute" appéles précédemment.		
		inline void TableFinAjoute() {  ::TableAjoute( m_szNom, m_clLigne.pszGetBuffer() ); m_clLigne.MetAVide();}
		//Insére les les colonne à l'indiuce donné
		inline void TableFinInsere(int nIndice) {  ::TableInsere( m_szNom, m_clLigne.pszGetBuffer(), nIndice ); m_clLigne.MetAVide();}
 		//Modifie la migne d'indice donné
		inline void TableFinModifie(int nIndice) {  ::TableModifie( m_szNom, m_clLigne.pszGetBuffer(),nIndice ); m_clLigne.MetAVide();}

	protected:
		TCHAR m_szNom[nsMaxNomChamp+1]; // nom de la table
		CStringBuffer m_clLigne;// buffer de travail pour créer des lignes.
	};

#endif //!__WDEXTERNAPI_H
