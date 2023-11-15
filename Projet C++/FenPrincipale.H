// La classe CWDFenPrincipale pilote la fenêtre principale faite avec WinDev
// Elle hérite de la classe CWDDialog qui est fournie avec WinDev pour 
// le langage externe en C++
// ---------------------------------------------------------------------------


#ifndef __FENPRINCIPALE_H
#define __FENPRINCIPALE_H 

#include "WDWDial.h" 

class CWDFenPrincipale : public CWDDialog
{		
public:
	// constructeur avec comme paramêtre le nom de la fenêtre WinDev (sans l'extension! )
	// et le handle de la fenêtre mere
	CWDFenPrincipale(HWND hWndMere= NULL);
	virtual ~CWDFenPrincipale(){} // destructeur virtuel pour un héritage sans soucis.

protected:

	//-------------------------------------------------------------------------------------
	//Implémente la Touche Map par defaut
	//la Touche Map associe des WDTouche renvoyés par WinDev à des méthode en C++ De al classe.
	//Par exemple, dans un code de click d'un bouton on écrit le code "WDTouche = "ClickBouton1" "
	//Dans le .Cpp de la classe on associe "ClickBouton1" à la méthode OnBouton1() et cette méthode
	//sera appellée chaque fois que le WDTouche est renvoyé.
	//IMPORTANT : Le code WLangage situé après un WDTouche dans WinDev n'est pas éxecuté (on s'arrète au WDTouche)
	DECLARE_TOUCHE_MAP(CWDFenPrincipale);

	//-------------------------------------------------------------------------------------
	//Cette méthode sert à initialiser les champs de la fenêtre
	//elle est appelée juste après la création;
	void OnInitDialog();  
	
	//-------------------------------------------------------------------------------------
	//action sur le bouton recherche de la fenêtre principale
	//démonstration de la récupération de valeur de champs et d'execution de code WLangage 
	//depuis une application C++
	void OnLanceRecherche();

	//-------------------------------------------------------------------------------------
	//action sur le bouton de réservation de la fenêtre principale
	void OnReservation();

};


#endif //__FENPRINCIPALE_H
