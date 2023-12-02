//-------------------Réalisation de la classe <Catalogue> (fichier Catalogue.cpp)-------------------//

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

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
    c = new Collection; // on ajoute dans la collection
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

void Catalogue::AjouterTrajet(Trajet *unTrajet)
{
    c->AjouterFin(unTrajet);
}

void Catalogue::Menu()
{
    int choix;
    do
    {
        printMenu();
        cin >> choix; // on imprime le menu et on attend une entrée
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        switch (choix)
        {
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
        case 6:
            CatalogueVersFichier();
            break; // pour sortir pas besoin de vérifier le reste
        case 5:
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
    do
    {
        printCatlogueVersFichierViceVersa();
        cin >> choix;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        switch (choix)
        {
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
    } while (choix != 5);
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
    do
    {
        printCatlogueVersFichierViceVersa();
        cin >> choix;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        string line;
        ifstream file;
        string file_name;
        int nblignes, nbcolonnes;
        switch (choix)
        {
        case 1:
            cout << "Donnez le nb de lignes de ce fichier" << endl;
            cin >> nblignes;
            cout << "Donnez le nb de colonnes max dans ce fichier" << endl;
            cin >> nbcolonnes;
            cout << "Veuillez saisir le nom du fichier celui-ci doit être au format csv" << endl;
            cin >> file_name;
            cout << file_name << endl;
            file.open(file_name.c_str());
            if (file.is_open())
            {
                Catalogue::FichierVersCatalogueSansCriteres(file, nblignes, nbcolonnes);
                file.close();
            }
            else
                cout << "Nous n'avons pas réussi à ouvrir le fichier" << endl;
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
    } while (choix != 5);
}

void Catalogue::FichierVersCatalogueSansCriteres(ifstream &file, int nblignes, int nbcolonnes)
{
    string **table = Catalogue::conversionDonneesVersTableau(file, nblignes, nbcolonnes);
    Collection *collection = Catalogue::rec2(table, 0, 0, nblignes);

    Cellule *current = collection->GetHead();
    while (current != nullptr)
    {
        if (Catalogue::verifieSiExisteCatalogue(current->t))
        {
            c->AjouterFin(current->t);
        }

        current = current->suivant;
    }
    c->Afficher();
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
    do
    {
        printAjoutTrajet();
        cin >> choix;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        switch (choix)
        {
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
    } while (choix != 3);
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
    int choice = 1;
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
    Collection *listeTrajet = new Collection();
    listeTrajet->AjouterFin(new TrajetSimple(depart, arrivee, moyen));
    cout << "Choix de l'arrêt suivant : " << endl;
    strcpy(depart, arrivee);
    cin >> arrivee;
    cout << "Choix du moyen de transport : " << endl;
    cin >> moyen;
    listeTrajet->AjouterFin(new TrajetSimple(depart, arrivee, moyen));
    while (choice != 0)
    {
        strcpy(depart, arrivee);
        cout << "Choix de l'arrêt suivant (0 pour terminer) : " << endl;
        cin >> arrivee;
        if (strcmp(arrivee, "0") == 0)
        {
            choice = 0;
        }
        else
        {
            cout << "Choix du moyen de transport : " << endl;
            cin >> moyen;
            listeTrajet->AjouterFin(new TrajetSimple(depart, arrivee, moyen));
        }
    }
    TrajetCompose *trajetCompose = new TrajetCompose(listeTrajet);
    c->AjouterFin(trajetCompose);
}

string **Catalogue::conversionDonneesVersTableau(ifstream &file, int nblignes, int nbcolonnes)
{
    string **table = new string *[nblignes];
    string line;
    int i = 0, j = 0;
    while (getline(file, line))
    {
        stringstream linestream(line);
        string cell;
        j = 0;
        table[i] = new string[nbcolonnes];
        while (getline(linestream, cell, ','))
        {

            table[i][j] = cell;
            j++;
        }
        i++;
    }

    return table;
}

Collection *Catalogue::rec2(string **tableau, int abs, int colonne, int nblignes)
{
    Collection *collection = new Collection;
    for (int i = abs; i < nblignes; i++)
    {

        if (tableau[i][colonne] == "s")
        {
            collection->AjouterFin(new TrajetSimple(tableau[i][colonne + 1].c_str(), tableau[i][colonne + 2].c_str(), tableau[i][colonne + 3].c_str()));
        }
        else if (tableau[i][colonne] == "c")
        { // on definit une
            collection->AjouterFin(new TrajetCompose(Catalogue::rec2(tableau, i + 1, colonne + 1, nblignes)));
        }
        else if (tableau[i][colonne].length() > 1)
        {
            break;
        }
    }
    return collection;
}

bool Catalogue::verifieSiExisteCatalogue(Trajet *unTrajet)
{
    return true;
}