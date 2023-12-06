//----------------Interface de la classe <Catalogue> (fichier Catalogue.h)----------------//

#if !defined CATALOGUE_H
#define CATALOGUE_H

//-------------------------------------------------------- Interfaces utilisées
#include "Collection.h"
#include "tab.h"

//------------------------------------------------------------- Constantes
const char SEP = ';';
//------------------------------------------------------------------ Types
#include <string>
using namespace std;
//------------------------------------------------------------------------//
// Rôle de la classe <Catalogue>
// Description :
//------------------------------------------------------------------------//

class Catalogue
{
    //----------------------------------------------------------------- PUBLIC
public:
    //-----------------------------------------------------------------Méthodes publiques

    void Afficher();
    // Mode d'emploi : Affiche le contenu du catalogue
    // Contrat :

    void AjouterTrajet(Trajet *unTrajet);
    // Mode d'emploi : Ajoute un trajet au catalogue
    // Contrat :

    void Menu();

    void RechercherTrajet();

    void SauvegardeRecursif(ofstream&, Trajet*, int, int, char*, char*);

    void Sauvegarde();

//---------------------------------------------------------------Surcharge d'opérateurs

    //-----------------------------------------------------Constructeurs - Destructeur
    Catalogue(Catalogue const &unCatalogue);
    // Mode d'emploi (constructeur de copie) :
    // Contrat :

    Catalogue();
    // Mode d'emploi (Constructeur par défaut) :
    // Contrat :

    virtual ~Catalogue();
    // Mode d'emploi :
    // Contrat :

    //------------------------------------------------------------------ PRIVE
protected:
    //-----------------------------------------------------------Méthodes protégées
    // type méthode ( liste des paramètres );
    // Mode d'emploi :
    // Contrat :

    void printMenu();
    // Mode d'emploi : Affiche le menu du catalogue
    // Contrat : Aucun

    void printAjoutTrajet();
    // Mode d'emploi : Affiche le menu d'ajout de trajet
    // Contrat : Aucun

    void ajoutTrajet();
    // Mode d'emploi : Menu d'ajout de trajet
    // Contrat : Aucun

    void ajoutTrajetSimple();
    // Mode d'emploi : Ajoute un trajet simple au catalogue
    // Contrat

    void ajoutTrajetCompose();
    // Mode d'emploi : Ajoute un trajet composé au catalogue
    // Contrat : Aucun

    void printCatlogueVersFichierViceVersa();
    // Mode d'emploi : Affiche le menu de chargement du fichier vers le catalogue et vice versa
    // Contrat : Aucun

    void FichierVersCatalogue();
    // Mode d'emploi : Gère le menu du chargement des données depuis le fichier vers le catalogue
    // Contrat : Le nb de lignes et de colonnes fournies dans l'entrée doivent être conformes à celles du fichier, Le debut et la fin doivent être restreints dans ce la plage existante  en commençant à 1

    void CatalogueVersFichier();
    // Mode d'emploi : Gère le menu du chargement des données depuis le catalogue vers le fichier
    // Contrat : Aucun

    Tab* conversionDonneesVersTableauSelonSelection(ifstream &file, int nblignes, int nbcolonnes, int debut, int fin);
    // Mode d'emploi : Charge les données depuis le fichier et les range dans tableau selon une sélection de trajets
    // Contrat : Le nb de lignes et de colonnes fourni doivent être conformes à ceux du fichier, le debut et la fin doivent être restreints dans ce la plage existante  en commençant à 1

    Tab* conversionDonneesVersTableauSansCritere(ifstream &file, int nblignes, int nbcolonnes);
    // Mode d'emploi : Charge les données depuis le fichier et les range dans tableau dans leur intégralité 
    // Contrat : Le nb de lignes et de colonnes fourni doivent être conformes à ceux du fichier

    Tab* conversionDonneesVersTableauSelonTypeTrajet(ifstream &file, int nblignes, int nbcolonnes, string chaine);
    // Mode d'emploi : Charge les données depuis le fichier et les range dans tableau selon le type de trajet
    // Contrat : Le nb de lignes et de colonnes fourni doivent être conformes à ceux du fichier

    Collection* inseredansCatalogueSansCriteres(string** tableau, int abs, int colonne, int nblignes);
    // Mode d'emploi : Charge dans le catalogue les chemins en les créant depuis le tableau pris en entrée sans aucun critère de sélection
    // Contrat : Le nb de lignes et de colonnes fourni doivent être conformes à ceux du tableau

    Collection* inseredansCatalogueSansSelonVillesDepartArrivee(string **tableau, int abs, int colonne, int nblignes, string depart, string arrivee);
    // Mode d'emploi : Charge dans le catalogue les chemins en les créant depuis le tableau pris en entrée en spécifiant la ville de départ et la ville et celle d'arrivée
    // Contrat : Le nb de lignes et de colonnes fourni doivent être conformes à ceux du tableau 

    bool verifieSiExisteCatalogue(Trajet *unTrajet);
    // Mode d'emploi : Vérifie si le trajet en paramètre existe ou pas dans le catalogue
    // Contrat : Aucun

    void choixSauvegarde();

    //-------------------------------------------------------------Attributs protégés
    Collection *c;
};

//-------------------------------- Autres définitions dépendantes de <Classe>

#endif // !defined CLASSE_H
