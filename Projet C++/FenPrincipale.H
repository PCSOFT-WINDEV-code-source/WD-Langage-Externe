// La classe CWDFenPrincipale pilote la fen�tre principale faite avec WinDev
// Elle h�rite de la classe CWDDialog qui est fournie avec WinDev pour 
// le langage externe en C++
// ---------------------------------------------------------------------------


#ifndef __FENPRINCIPALE_H
#define __FENPRINCIPALE_H 

#include "WDWDial.h" 

class CWDFenPrincipale : public CWDDialog
{		
public:
	// constructeur avec comme param�tre le nom de la fen�tre WinDev (sans l'extension! )
	// et le handle de la fen�tre mere
	CWDFenPrincipale(HWND hWndMere= NULL);
	virtual ~CWDFenPrincipale(){} // destructeur virtuel pour un h�ritage sans soucis.

protected:

	//-------------------------------------------------------------------------------------
	//Impl�mente la Touche Map par defaut
	//la Touche Map associe des WDTouche renvoy�s par WinDev � des m�thode en C++ De al classe.
	//Par exemple, dans un code de click d'un bouton on �crit le code "WDTouche = "ClickBouton1" "
	//Dans le .Cpp de la classe on associe "ClickBouton1" � la m�thode OnBouton1() et cette m�thode
	//sera appell�e chaque fois que le WDTouche est renvoy�.
	//IMPORTANT : Le code WLangage situ� apr�s un WDTouche dans WinDev n'est pas �xecut� (on s'arr�te au WDTouche)
	DECLARE_TOUCHE_MAP(CWDFenPrincipale);

	//-------------------------------------------------------------------------------------
	//Cette m�thode sert � initialiser les champs de la fen�tre
	//elle est appel�e juste apr�s la cr�ation;
	void OnInitDialog();  
	
	//-------------------------------------------------------------------------------------
	//action sur le bouton recherche de la fen�tre principale
	//d�monstration de la r�cup�ration de valeur de champs et d'execution de code WLangage 
	//depuis une application C++
	void OnLanceRecherche();

	//-------------------------------------------------------------------------------------
	//action sur le bouton de r�servation de la fen�tre principale
	void OnReservation();

};


#endif //__FENPRINCIPALE_H
