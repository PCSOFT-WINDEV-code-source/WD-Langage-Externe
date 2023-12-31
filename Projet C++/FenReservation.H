// La classe CWDFenReservation pilote la fen�tre de r�servation faite avec WinDev
// Elle h�rite de la classe CWDDialog qui est fournie avec WinDev pour 
// le langage externe en C++
// ---------------------------------------------------------------------------


#ifndef __FENRESERVATION_H
#define __FENRESERVATION_H 

#include "WDWDial.h" 

class CWDFenReservation : public CWDDialog
{		
protected :
	CString m_sDateDebut;	//date de d�but
	CString m_sDateFin;		//date de fin
	int m_nNbPersonnes;		//nombre de personnes pour la r�servation
	int m_nIdEmplacement;	//identifiant auto de l'emplacement

public:
	// constructeur avec comme param�tre le nom de la fen�tre WinDev (sans l'extension! )
	// et le handle de la fen�tre mere
	CWDFenReservation(LPCSTR pszDateDebut, LPCSTR pszDateFin, int nNbPersonnes, int nIdEmplacement, HWND hWndMere= NULL);
	virtual ~CWDFenReservation(){} // destructeur virtuel pour un h�ritage sans soucis.

protected:
	//-------------------------------------------------------------------------------------
	//Cette m�thode sert � initialiser les champs de la fen�tre
	//elle est appel�e juste apr�s la cr�ation;
	void OnInitDialog();  
	
	//-------------------------------------------------------------------------------------
	//validation de la r�servation
	void OnOk();

	//------------------------------------------------------------------------------------------
	// on a annul� la r�servation
	void OnCancel();

	//-------------------------------------------------------------------------------------
	//Impl�mente la Touche Map par defaut
	//la Touche Map associe des WDTouche renvoy�s par WinDev � des m�thode en C++ De al classe.
	//Par exemple, dans un code de click d'un bouton on �crit le code "WDTouche = "ClickBouton1" "
	//Dans le .Cpp de la classe on associe "ClickBouton1" � la m�thode OnBouton1() et cette m�thode
	//sera appell�e chaque fois que le WDTouche est renvoy�.
	//IMPORTANT : Le code WLangage situ� apr�s un WDTouche dans WinDev n'est pas �xecut� (on s'arr�te au WDTouche)
	DECLARE_TOUCHE_MAP(CWDFenReservation);

};


#endif //__FENRESERVATION_H
