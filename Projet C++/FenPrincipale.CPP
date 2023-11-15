//Encapsulation des fonctions d'un dialogue Windev dans une classe c++.
#include "Central.h"
#include "FenPrincipale.h"
#include "FenReservation.h"

//-------------------------------------------------------------------------------------
//Map des WDTouche
//la Touche Map associe ici des WDTouche renvoyés par WinDev à des méthode en C++ de la classe.
//Par exemple, dans un code de clic d'un bouton on écrit le code "WDTouche = "LanceRecherche" "
//On associe ici "LanceRecherche" à la méthode OnLanceRecherche() et cette méthode
//sera appellée chaque fois que le WDTouche est renvoyé.
//IMPORTANT : Le code WLangage situé après un WDTouche dans WinDev n'est pas executé (on s'arrête au WDTouche)
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
//Cette méthode sert à initialiser les champs de la fenêtre
//elle est appelée juste après la création;
void CWDFenPrincipale::OnInitDialog()
{
	nWDExecute("DATEDEB=Datesys()");
	nWDExecute("DATEFIN=EntierVersDate(DateVersEntier(DATEDEB)+7)");

	CWDDialog::OnInitDialog();
}

//------------------------------------------------------------------------------------------
// méthode appelée lors du clic sur le bouton recherche
// on y vérifie les dates et on appelle une méthode WinDev qui fait la recherche dans la base HyperFileSQL
void CWDFenPrincipale::OnLanceRecherche()
{
	//Nous allons accéder aux champs de la fenêtre WinDev de deux façons différentes afin d'explorer les deux possibilités:
	//- en utilisant nWDExecute qui permet de taper directement du code WLangage au sein de l'application C++
	//- en Utilisant les fonctions fournies dans ExterneApi.h qui permettent entre autre d'afficher des informations ou de 
	//  récupérer ces informations dans des champs

	//1- Vérification des dates :
	//on fait un DateDifférence
	nWDExecute("DateDifférence(DATEDEB,DATEFIN)");
	//on récupère la valeur renvoyée
	int nDif = nWDGetValeurRetour();
	//si la date de fin n'est pas strictement supérieur à la date de début on affiche un message d'erreur
	if(nDif<1)
	{
		AfxMessageBox("La date de Fin n'est pas correcte");
		//On met la date de debut +1 jour dans la date de fin
		nWDExecute("DATEFIN=EntierVersDate(DateVersEntier(DATEDEB)+7)");
		//on s'arrète là
		return;
	}


	//2- Lancer la recherche dans HyperFile
	//on récupère la valeur des champs afin de les passer en paramêtre à la fonction
	//pour cela on utilise les méthodes de WDExterneApi.h

	int nNbPersonnes = nRecup("NBPERSONNE");
	int nTypeEmplacement = nRecup("TYPE_EMPLACEMENT");
	CString sDateDebut = szRecup("DATEDEB");
	CString sDateFin = szRecup("DATEFIN");

	//on appelle directement la procédure locale de la fenêtre
	int nErreur = nWDExecute("RechercheDispo(%d,%d,\"%s\",\"%s\")",nNbPersonnes,nTypeEmplacement,sDateDebut,sDateFin);

	//on traite les cas d'erreurs que peut renvoyer la fonction
	if(nErreur!=WDERREUR_OK)
	{
		//on est dans un cas d'erreur (ils sont tous listés dans WDExtern.h)
		//-- On peut faire un traitement particulier ici ---
		AfxMessageBox("Erreur");
	}
}

//-------------------------------------------------------------------------------------
//action sur le bouton de réservation de la fenêtre principale
void CWDFenPrincipale::OnReservation()
{
	//on regarde si une ligne est bien sélectionnée dans la table
	int nLigneSelection = nTableSelect("TABLE_EMPLACEMENT");
	if(nLigneSelection<1)
	{
		AfxMessageBox("Vous devez choisir un emplacement disponible dans le tableau");
		return;
	}

	int nIDEmplacement = nRecup("N_IDEMPLACEMENT");

	//on récupère les autres paramêtres
	CString sDebut = szRecup("DATEDEB");
	CString sFin = szRecup("DATEFIN");
	int nNbPers = nRecup("NBPERSONNE");
	//et on crée la fenêtre à ouvrir
	CWDFenReservation clReservation(sDebut,sFin,nNbPers,nIDEmplacement,GetSafeHwnd());

	//si on a effectué la réservation
	if(clReservation.DoModal()==IDOK)
	{
		//on affiche un message de confirmation
		AfxMessageBox("La réservation a été faite");
	}
}
