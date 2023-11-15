// La classe CWDFenReservation pilote la fenêtre de réservation faite avec WinDev
// Elle hérite de la classe CWDDialog qui est fournie avec WinDev pour 
// le langage externe en C++
// ---------------------------------------------------------------------------


#ifndef __FENRESERVATION_H
#define __FENRESERVATION_H 

#include "WDWDial.h" 

class CWDFenReservation : public CWDDialog
{		
protected :
	CString m_sDateDebut;	//date de début
	CString m_sDateFin;		//date de fin
	int m_nNbPersonnes;		//nombre de personnes pour la réservation
	int m_nIdEmplacement;	//identifiant auto de l'emplacement

public:
	// constructeur avec comme paramêtre le nom de la fenêtre WinDev (sans l'extension! )
	// et le handle de la fenêtre mere
	CWDFenReservation(LPCSTR pszDateDebut, LPCSTR pszDateFin, int nNbPersonnes, int nIdEmplacement, HWND hWndMere= NULL);
	virtual ~CWDFenReservation(){} // destructeur virtuel pour un héritage sans soucis.

protected:
	//-------------------------------------------------------------------------------------
	//Cette méthode sert à initialiser les champs de la fenêtre
	//elle est appelée juste après la création;
	void OnInitDialog();  
	
	//-------------------------------------------------------------------------------------
	//validation de la réservation
	void OnOk();

	//------------------------------------------------------------------------------------------
	// on a annulé la réservation
	void OnCancel();

	//-------------------------------------------------------------------------------------
	//Implémente la Touche Map par defaut
	//la Touche Map associe des WDTouche renvoyés par WinDev à des méthode en C++ De al classe.
	//Par exemple, dans un code de click d'un bouton on écrit le code "WDTouche = "ClickBouton1" "
	//Dans le .Cpp de la classe on associe "ClickBouton1" à la méthode OnBouton1() et cette méthode
	//sera appellée chaque fois que le WDTouche est renvoyé.
	//IMPORTANT : Le code WLangage situé après un WDTouche dans WinDev n'est pas éxecuté (on s'arrète au WDTouche)
	DECLARE_TOUCHE_MAP(CWDFenReservation);

};


#endif //__FENRESERVATION_H
