//Encapsulation des fonctions d'un dialogue Windev dans une classe c++.
#include "Central.h"
#include "FenPrincipale.h"
#include "FenReservation.h"

//-------------------------------------------------------------------------------------
//Map des WDTouche
//la Touche Map associe ici des WDTouche renvoy�s par WinDev � des m�thode en C++ de la classe.
//Par exemple, dans un code de clic d'un bouton on �crit le code "WDTouche = "LanceRecherche" "
//On associe ici "LanceRecherche" � la m�thode OnLanceRecherche() et cette m�thode
//sera appell�e chaque fois que le WDTouche est renvoy�.
//IMPORTANT : Le code WLangage situ� apr�s un WDTouche dans WinDev n'est pas execut� (on s'arr�te au WDTouche)
START_TOUCHE_MAP(CWDFenPrincipale)
		{"LanceRecherche", &CWDFenPrincipale::OnLanceRecherche},
		{"Reservation", &CWDFenPrincipale::OnReservation},
END_TOUCHE_MAP()


//-------------------------------------------------------------------------------------
//Constructeur 
CWDFenPrincipale::CWDFenPrincipale(HWND hWndMere) : CWDDialog("Fen_Principale",hWndMere)
{
}

//-------------------------------------------------------------------------------------
//Cette m�thode sert � initialiser les champs de la fen�tre
//elle est appel�e juste apr�s la cr�ation;
void CWDFenPrincipale::OnInitDialog()
{
	nWDExecute("DATEDEB=Datesys()");
	nWDExecute("DATEFIN=EntierVersDate(DateVersEntier(DATEDEB)+7)");

	CWDDialog::OnInitDialog();
}

//------------------------------------------------------------------------------------------
// m�thode appel�e lors du clic sur le bouton recherche
// on y v�rifie les dates et on appelle une m�thode WinDev qui fait la recherche dans la base HyperFileSQL
void CWDFenPrincipale::OnLanceRecherche()
{
	//Nous allons acc�der aux champs de la fen�tre WinDev de deux fa�ons diff�rentes afin d'explorer les deux possibilit�s:
	//- en utilisant nWDExecute qui permet de taper directement du code WLangage au sein de l'application C++
	//- en Utilisant les fonctions fournies dans ExterneApi.h qui permettent entre autre d'afficher des informations ou de 
	//  r�cup�rer ces informations dans des champs

	//1- V�rification des dates :
	//on fait un DateDiff�rence
	nWDExecute("DateDiff�rence(DATEDEB,DATEFIN)");
	//on r�cup�re la valeur renvoy�e
	int nDif = nWDGetValeurRetour();
	//si la date de fin n'est pas strictement sup�rieur � la date de d�but on affiche un message d'erreur
	if(nDif<1)
	{
		AfxMessageBox("La date de Fin n'est pas correcte");
		//On met la date de debut +1 jour dans la date de fin
		nWDExecute("DATEFIN=EntierVersDate(DateVersEntier(DATEDEB)+7)");
		//on s'arr�te l�
		return;
	}


	//2- Lancer la recherche dans HyperFile
	//on r�cup�re la valeur des champs afin de les passer en param�tre � la fonction
	//pour cela on utilise les m�thodes de WDExterneApi.h

	int nNbPersonnes = nRecup("NBPERSONNE");
	int nTypeEmplacement = nRecup("TYPE_EMPLACEMENT");
	CString sDateDebut = szRecup("DATEDEB");
	CString sDateFin = szRecup("DATEFIN");

	//on appelle directement la proc�dure locale de la fen�tre
	int nErreur = nWDExecute("RechercheDispo(%d,%d,\"%s\",\"%s\")",nNbPersonnes,nTypeEmplacement,sDateDebut,sDateFin);

	//on traite les cas d'erreurs que peut renvoyer la fonction
	if(nErreur!=WDERREUR_OK)
	{
		//on est dans un cas d'erreur (ils sont tous list�s dans WDExtern.h)
		//-- On peut faire un traitement particulier ici ---
		AfxMessageBox("Erreur");
	}
}

//-------------------------------------------------------------------------------------
//action sur le bouton de r�servation de la fen�tre principale
void CWDFenPrincipale::OnReservation()
{
	//on regarde si une ligne est bien s�lectionn�e dans la table
	int nLigneSelection = nTableSelect("TABLE_EMPLACEMENT");
	if(nLigneSelection<1)
	{
		AfxMessageBox("Vous devez choisir un emplacement disponible dans le tableau");
		return;
	}

	int nIDEmplacement = nRecup("N_IDEMPLACEMENT");

	//on r�cup�re les autres param�tres
	CString sDebut = szRecup("DATEDEB");
	CString sFin = szRecup("DATEFIN");
	int nNbPers = nRecup("NBPERSONNE");
	//et on cr�e la fen�tre � ouvrir
	CWDFenReservation clReservation(sDebut,sFin,nNbPers,nIDEmplacement,GetSafeHwnd());

	//si on a effectu� la r�servation
	if(clReservation.DoModal()==IDOK)
	{
		//on affiche un message de confirmation
		AfxMessageBox("La r�servation a �t� faite");
	}
}
