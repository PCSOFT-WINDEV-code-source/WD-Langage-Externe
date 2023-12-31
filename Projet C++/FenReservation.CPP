//Encapsualtion des fontions d'un dialogue Windev dans une classe c++.
#include "Central.h"
#include "FenReservation.h"

//-------------------------------------------------------------------------------------
//Map des WDTouche
//la Touche Map associe ici des WDTouche renvoy�s par WinDev � des m�thode en C++ De la classe.
//Par exemple, dans un code de click d'un bouton on �crit le code "WDTouche = "RET" "
//On associe ici "RET" � la m�thode OnOk() et cette m�thode
//sera appell�e chaque fois que le WDTouche est renvoy�.
//IMPORTANT : Le code WLangage situ� apr�s un WDTouche dans WinDev n'est pas �xecut� (on s'arr�te au WDTouche)
START_TOUCHE_MAP(CWDFenReservation)
		{"RET", &CWDFenReservation::OnOk},
		{"ESC", &CWDFenReservation::OnCancel},
END_TOUCHE_MAP()


//-------------------------------------------------------------------------------------
//Constructeur 
CWDFenReservation::	CWDFenReservation(LPCSTR pszDateDebut, LPCSTR pszDateFin, int nNbPersonnes, 
	int nIdEmplacement, HWND hWndMere): 
	m_sDateDebut(pszDateDebut),
	m_sDateFin(pszDateFin),
	m_nNbPersonnes(nNbPersonnes),
	m_nIdEmplacement(nIdEmplacement),
	CWDDialog("Fen_R�servation",hWndMere)
{
}

//-------------------------------------------------------------------------------------
//Cette m�thode sert � initialiser les champs de la fen�tre
//elle est appel�e juste apr�s la cr�ation;
void CWDFenReservation::OnInitDialog()
{
	//on utilise la m�thode affiche de WDExternApi.h pour initialiser les champs
	Affiche("DATEDEB",m_sDateDebut);
	Affiche("DATEFIN",m_sDateFin);
	Affiche("NBPERSONNES",m_nNbPersonnes);
	Affiche("N_IDEMPLACEMENT",m_nIdEmplacement);

	nWDExecute("JourDateDeb()");
	nWDExecute("JourDateFin()");
	nWDExecute("AfficheEmplacement(%d)",m_nIdEmplacement);

	//on fait un DateDiff�rence
	nWDExecute("DateDiff�rence(DATEDEB,DATEFIN)");
	//on r�cup�re la valeur renvoy�e
	int nNbJour = nWDGetValeurRetour();

	//on controle que la date de d�but est bien inf�rieure � la date de fin
	XASSERT(nNbJour>0);

	//on affiche le nombre de jours
	CString sJour;
	if(nNbJour>1)
		sJour.Format("%d jours",nNbJour);
	else
		sJour ="1 jour";
	Affiche("NBJOURS",sJour);
	
	//On r�cup�re le prix par jour (c'est un r�el on utilise la m�thode dRecup de WDExternApi.h"
	double dPrix =  dRecup("PRIXPARJOUR");
	
	//On affiche le prix total
	Affiche("TOTAL",nNbJour * dPrix);
}

//------------------------------------------------------------------------------------------
// on a accept� la r�servation
void CWDFenReservation::OnOk()
{
	CWDDialog::OnOk();
}

//------------------------------------------------------------------------------------------
// on a annul� la r�servation
void CWDFenReservation::OnCancel()
{
	CWDDialog::OnCancel();
}