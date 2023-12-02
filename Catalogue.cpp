//-------------------Réalisation de la classe <Catalogue> (fichier Catalogue.cpp)-------------------//

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue()
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
    c = new Collection;
}

Catalogue::~Catalogue()
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    delete c;
}

void Catalogue::Afficher()
{
    c->Afficher();
    cin >> ws;
    cout << "Appuyez sur entrée pour continuer" << endl;
    cin.get();
}

void Catalogue::AjouterTrajet(Trajet* unTrajet)
{
    c->AjouterFin(unTrajet);
}

void Catalogue::Menu()
{
    int choix;
    do {
        printMenu();
        cin >> choix; // on imprime le menu et on attend une entrée 
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        switch (choix) {
            case 1:
                ajoutTrajet();
                break;
            case 2:
                Afficher();
                break;
            case 3:
                RechercherTrajet();
                break;
            case 4:
                cout << "Au revoir !" << endl;
                break;
            case 5:
                CatalogueVersFichier();
                break; // pour sortir pas besoin de vérifier le reste 
            case 6:
                FichierVersCatalogue();
                break;
            default:
                cout << "Erreur de saisie" << endl;
                break;
        }
    } while (choix != 4);
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Catalogue::printCatlogueVersFichierViceVersa()
{
    cout << "------------------------------------------" << endl;
    cout << "1. Sans critère  de sélection" << endl;
    cout << "2. Selon le type de trajets" << endl;
    cout << "3. Selon la ville de départ et d'arrivée" << endl;
    cout << "4. Selon une sélection de trajets" << endl;
    cout << "5. Retour" << endl;
    cout << "Votre choix : ";
}

void Catalogue::CatalogueVersFichier()
{
    int choix;
    do{
        printCatlogueVersFichierViceVersa();
        cin >> choix;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        switch (choix) {
            case 1:
                CatalogueVersFichierSansCriteres();
                break;
            case 2:
                CatalogueVersFichierSelonTypeTrajet();
                break;
            case 3:
                CatalogueVersFichierSelonVilles();
                break;
            case 4:
                CatalogueVersFichierSelonSelection();
                break;
            case 5:
                break;
            default:
                cout << "Erreur de saisie" << endl;
                break;
        }
    }while(choix != 5);

}

void Catalogue::CatalogueVersFichierSansCriteres()
{

}

void Catalogue::CatalogueVersFichierSelonTypeTrajet()
{

}

void Catalogue::CatalogueVersFichierSelonSelection()
{

}

void Catalogue::CatalogueVersFichierSelonVilles()
{

}



void Catalogue::FichierVersCatalogue()
{
    int choix;
    do{
        printCatlogueVersFichierViceVersa();
        cin >> choix;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        switch (choix) {
            case 1:
                FichierVersCatalogueSansCriteres();
                break;
            case 2:
                FichierVersCatalogueSelonTypeTrajet();
                break;
            case 3:
                FichierVersCatalogueSelonVilles();
                break;
            case 4:
                FichierVersCatalogueSelonSelection();
                break;
            case 5:
                break;
            default:
                cout << "Erreur de saisie" << endl;
                break;
        }
    }while(choix != 5);

}

void Catalogue::FichierVersCatalogueSansCriteres()
{

}

void Catalogue::FichierVersCatalogueSelonTypeTrajet()
{

}

void Catalogue::FichierVersCatalogueSelonSelection()
{

}

void Catalogue::FichierVersCatalogueSelonVilles()
{

}

void Catalogue::RechercherTrajet()
{
    char depart[100];
    char arrivee[100];
    cout << "------------------------------------------" << endl;
    cout << "RECHERCHE D'UN TRAJET" << endl;
    cout << "Choix de la ville de départ : " << endl;
    cin >> depart;
    cout << "Choix de la ville d'arrivée : " << endl;
    cin >> arrivee;
//    c->RechercheSimple(depart, arrivee);
    c->RechercheComplexe(depart, arrivee);
    cin >> ws;
    cout << "Appuyez sur entrée pour continuer" << endl;
    cout << "------------------------------------------" << endl;
    cin.get();
}

void Catalogue::printMenu()
{
    cout << "------------------------------------------" << endl;
    cout << "BIENVENUE DANS LE CATALOGUE DE TRAJET" << endl;
    cout << "QUE VOULEZ VOUS FAIRE ?" << endl;
    cout << "------------------------------------------" << endl;
    cout << "1. Ajouter un trajet" << endl;
    cout << "2. Afficher le catalogue" << endl;
    cout << "3. Rechercher un trajet" << endl;
    cout << "4. Quitter" << endl;
    cout << "5. Charger le fichier dans le catalogue" << endl;
    cout << "6. Charger le fcatalogue dans un fichier" << endl;
    cout << "Votre choix : ";
}

void Catalogue::ajoutTrajetSimple()
{
    char depart[100];
    char arrivee[100];
    char moyen[100];
    cout << "------------------------------------------" << endl;
    cout << "AJOUT D'UN TRAJET SIMPLE" << endl;
    cout << "Choix de la ville de départ : " << endl;
    cin >> depart;
    cout << "Choix de la ville d'arrivée : " << endl;
    cin >> arrivee;
    cout << "Choix du moyen de transport : " << endl;
    cin >> moyen;
    c->AjouterFin(new TrajetSimple(depart, arrivee, moyen));
}

void Catalogue::ajoutTrajet()
{
    int choix;
    do{
        printAjoutTrajet();
        cin >> choix;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        switch (choix) {
            case 1:
                ajoutTrajetSimple();
                break;
            case 2:
                ajoutTrajetCompose();
                break;
            case 3:
                break;
            default:
                cout << "Erreur de saisie" << endl;
                break;
        }
    }while(choix != 3);
}

void Catalogue::printAjoutTrajet()
{
    cout << "------------------------------------------" << endl;
    cout << "1. Ajouter un trajet simple" << endl;
    cout << "2. Ajouter un trajet composé" << endl;
    cout << "3. Retour" << endl;
    cout << "Votre choix : ";
}

void Catalogue::ajoutTrajetCompose()
{
    int choice = 1 ;
    char depart[100];
    char arrivee[100];
    char moyen[100];
    cout << "------------------------------------------" << endl;
    cout << "Ajout d'un trajet composé" << endl;
    cout << "Choix de la ville de départ : " << endl;
    cin >> depart;
    cout << "Choix du premier arrêt : " << endl;
    cin >> arrivee;
    cout << "Choix du moyen de transport : " << endl;
    cin >> moyen;
    Collection* listeTrajet = new Collection();
    listeTrajet->AjouterFin(new TrajetSimple(depart, arrivee, moyen));
    cout << "Choix de l'arrêt suivant : " << endl;
    strcpy(depart, arrivee);
    cin >> arrivee;
    cout << "Choix du moyen de transport : " << endl;
    cin >> moyen;
    listeTrajet->AjouterFin(new TrajetSimple(depart, arrivee, moyen));
    while(choice != 0){
        strcpy(depart, arrivee);
        cout << "Choix de l'arrêt suivant (0 pour terminer) : " << endl;
        cin >> arrivee;
        if(strcmp(arrivee, "0") == 0){
            choice = 0;
        } else {
            cout << "Choix du moyen de transport : " << endl;
            cin >> moyen;
            listeTrajet->AjouterFin(new TrajetSimple(depart, arrivee, moyen));
        }
    }
    TrajetCompose *trajetCompose = new TrajetCompose(listeTrajet);
    c->AjouterFin(trajetCompose);
}