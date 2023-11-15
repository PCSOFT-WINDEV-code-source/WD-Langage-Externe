//Encapsualtion des fontions d'un dialogue Windev dans une classe c++.
#include "Central.h"
#include "FenReservation.h"

//-------------------------------------------------------------------------------------
//Map des WDTouche
//la Touche Map associe ici des WDTouche renvoyés par WinDev à des méthode en C++ De la classe.
//Par exemple, dans un code de click d'un bouton on écrit le code "WDTouche = "RET" "
//On associe ici "RET" à la méthode OnOk() et cette méthode
//sera appellée chaque fois que le WDTouche est renvoyé.
//IMPORTANT : Le code WLangage situé après un WDTouche dans WinDev n'est pas éxecuté (on s'arrète au WDTouche)
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
	CWDDialog("Fen_Réservation",hWndMere)
{
}

//-------------------------------------------------------------------------------------
//Cette méthode sert à initialiser les champs de la fenêtre
//elle est appelée juste après la création;
void CWDFenReservation::OnInitDialog()
{
	//on utilise la méthode affiche de WDExternApi.h pour initialiser les champs
	Affiche("DATEDEB",m_sDateDebut);
	Affiche("DATEFIN",m_sDateFin);
	Affiche("NBPERSONNES",m_nNbPersonnes);
	Affiche("N_IDEMPLACEMENT",m_nIdEmplacement);

	nWDExecute("JourDateDeb()");
	nWDExecute("JourDateFin()");
	nWDExecute("AfficheEmplacement(%d)",m_nIdEmplacement);

	//on fait un DateDifférence
	nWDExecute("DateDifférence(DATEDEB,DATEFIN)");
	//on récupère la valeur renvoyée
	int nNbJour = nWDGetValeurRetour();

	//on controle que la date de début est bien inférieure à la date de fin
	XASSERT(nNbJour>0);

	//on affiche le nombre de jours
	CString sJour;
	if(nNbJour>1)
		sJour.Format("%d jours",nNbJour);
	else
		sJour ="1 jour";
	Affiche("NBJOURS",sJour);
	
	//On récupère le prix par jour (c'est un réel on utilise la méthode dRecup de WDExternApi.h"
	double dPrix =  dRecup("PRIXPARJOUR");
	
	//On affiche le prix total
	Affiche("TOTAL",nNbJour * dPrix);
}

//------------------------------------------------------------------------------------------
// on a accepté la réservation
void CWDFenReservation::OnOk()
{
	CWDDialog::OnOk();
}

//------------------------------------------------------------------------------------------
// on a annulé la réservation
void CWDFenReservation::OnCancel()
{
	CWDDialog::OnCancel();
}