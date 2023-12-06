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
#include "tab.h"

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

//----------------------------------------------------- Méthodes protégées

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
            FichierVersCatalogue();
            break;
        case 6:
            CatalogueVersFichier();
            break;

        default:
            cout << "Erreur de saisie" << endl;
            break;
        }
    } while (choix != 4);
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
}

void Catalogue::FichierVersCatalogue()
{
    int choix;
    do
    {
        ifstream file;
        string file_name, chaine, depart, arrivee, line;
        int nblignes, nbcolonnes, deb, fin;
        Tab *table;
        Collection *collection;
        printCatlogueVersFichierViceVersa();
        cin >> choix;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            choix = 0;
        }
        cout << "Veuillez saisir le nom du fichier celui-ci doit être au format csv" << endl;
        cin >> file_name;
        cout << "Donnez le nb de lignes de ce fichier" << endl;
        cin >> nblignes;
        cout << "Donnez le nb de colonnes max dans ce fichier" << endl;
        cin >> nbcolonnes;
        file.open(file_name.c_str());

        if (file.is_open())
        {
            switch (choix)
            {
            case 1:

                table = Catalogue::conversionDonneesVersTableauSansCritere(file, nblignes, nbcolonnes);
                collection = Catalogue::inseredansCatalogueSansCriteres(table->table, 0, 0, table->nb);
                c->Afficher();
                file.close();

                break;
            case 2:
                cout << "Saissisez 's' pour choisir de charger exclusivement les trajets simples et 'c' pour choisir de charger les trajets composés" << endl;
                cin >> chaine;
                table = Catalogue::conversionDonneesVersTableauSelonTypeTrajet(file, nblignes, nbcolonnes, chaine);
                collection = Catalogue::inseredansCatalogueSansCriteres(table->table, 0, 0, table->nb);
                c->Afficher();

                break;
            case 3:
                cout << "Saissisez la ville de depart" << endl;
                cin >> depart;
                cout << "Saissisez la ville d'arrivee" << endl;
                cin >> arrivee;

                table = Catalogue::conversionDonneesVersTableauSansCritere(file, nblignes, nbcolonnes);
                collection = Catalogue::inseredansCatalogueSansSelonVillesDepartArrivee(table->table, 0, 0, table->nb, depart, arrivee);
                c->Afficher();
                file.close();

                break;
            case 4:
                cout << "Saissisez l'indice du premier trajet" << endl;
                cin >> deb;
                cout << "Saissisez l'indice du dernier trajet" << endl;
                cin >> fin;

                table = Catalogue::conversionDonneesVersTableauSelonSelection(file, nblignes, nbcolonnes, deb, fin);
                collection = Catalogue::inseredansCatalogueSansCriteres(table->table, 0, 0, table->nb);
                c->Afficher();
                file.close();

            }
        }
        else
        {
            cout << "Nous n'avons pas réussi à ouvrir le fichier" << endl;
        }

    } while (choix != 5);
}

Tab *Catalogue::conversionDonneesVersTableauSansCritere(ifstream &file, int nblignes, int nbcolonnes)
{
    Tab *tab = new Tab;
    tab->table = new string *[nblignes];
    string line;
    int i = 0, j = 0;
    while (getline(file, line))
    {
        stringstream linestream(line);
        string cell;
        j = 0;
        tab->table[i] = new string[nbcolonnes];
        while (getline(linestream, cell, ','))
        {

            tab->table[i][j] = cell;
            j++;
        }
        i++;
    }
    tab->nb = nblignes;
    return tab;
}

Tab *Catalogue::conversionDonneesVersTableauSelonSelection(ifstream &file, int nblignes, int nbcolonnes, int debut, int fin)
{
    Tab *tab = new Tab;
    tab->table = new string *[nblignes];
    string line;
    int i = 0, j = 0, compteur = 0;

    while (getline(file, line))
    {
        if (line[0] == 's' || line[0] == 'c')
        {
            compteur++;
        }

        if (compteur >= debut && compteur <= fin)
        {
            stringstream linestream(line);
            string cell;

            j = 0;
            tab->table[i] = new string[nbcolonnes];
            while (getline(linestream, cell, ','))
            {

                tab->table[i][j] = cell;
                j++;
            }
            i++;
        }
    }

    tab->nb = i;
    return tab;
}

Tab *Catalogue::conversionDonneesVersTableauSelonTypeTrajet(ifstream &file, int nblignes, int nbcolonnes, string chaine)
{
    Tab *tab = new Tab;
    tab->table = new string *[nblignes];
    string line;
    int i = 0, j = 0;

    while (getline(file, line))
    {
        if ((line[0] == chaine[0] && chaine[0] == 's') || ((line[0] == 'c' || line[0] == ',') && chaine[0] == 'c'))
        {
            stringstream linestream(line);
            string cell;
            j = 0;
            tab->table[i] = new string[nbcolonnes];
            while (getline(linestream, cell, ','))
            {

                tab->table[i][j] = cell;
                j++;
            }
            i++;
        }
    }

    tab->nb = i;
    return tab;
}

Collection *Catalogue::inseredansCatalogueSansCriteres(string **tableau, int abs, int colonne, int nblignes)
{
    Collection *collection = new Collection;
    for (int i = abs; i < nblignes; i++)
    {

        if (tableau[i][colonne] == "s")
        {
            collection->AjouterFin(new TrajetSimple(tableau[i][colonne + 1].c_str(), tableau[i][colonne + 2].c_str(), tableau[i][colonne + 3].c_str()));
            if (colonne == 0)
            {
                c->AjouterFin(new TrajetSimple(tableau[i][colonne + 1].c_str(), tableau[i][colonne + 2].c_str(), tableau[i][colonne + 3].c_str()));
            }
        }
        else if (tableau[i][colonne] == "c")
        { // on definit une
            collection->AjouterFin(new TrajetCompose(Catalogue::inseredansCatalogueSansCriteres(tableau, i + 1, colonne + 1, nblignes)));
            if (colonne == 0)
            {
                c->AjouterFin(new TrajetCompose(Catalogue::inseredansCatalogueSansCriteres(tableau, i + 1, colonne + 1, nblignes)));
            }
        }
        else if (tableau[i][colonne].length() > 1)
        {
            break;
        }
    }
    return collection;
}

Collection *Catalogue::inseredansCatalogueSansSelonVillesDepartArrivee(string **tableau, int abs, int colonne, int nblignes, string depart, string arrivee)
{
    Collection *collection = new Collection;
    for (int i = abs; i < nblignes; i++)
    {

        if (tableau[i][colonne] == "s")
        {
            collection->AjouterFin(new TrajetSimple(tableau[i][colonne + 1].c_str(), tableau[i][colonne + 2].c_str(), tableau[i][colonne + 3].c_str()));
            if (colonne == 0 && strcmp(depart.c_str(), tableau[i][colonne + 1].c_str()) == 0 && strcmp(arrivee.c_str(), tableau[i][colonne + 2].c_str()) == 0)
            {
                c->AjouterFin(new TrajetSimple(tableau[i][colonne + 1].c_str(), tableau[i][colonne + 2].c_str(), tableau[i][colonne + 3].c_str()));
            }
        }
        else if (tableau[i][colonne] == "c")
        {
            collection->AjouterFin(new TrajetCompose(Catalogue::inseredansCatalogueSansCriteres(tableau, i + 1, colonne + 1, nblignes)));
            if (colonne == 0 && strcmp(depart.c_str(), tableau[i][colonne + 1].c_str()) == 0 && strcmp(arrivee.c_str(), tableau[i][colonne + 2].c_str()) == 0)
            {
                c->AjouterFin(new TrajetCompose(Catalogue::inseredansCatalogueSansCriteres(tableau, i + 1, colonne + 1, nblignes)));
            }
        }
        else if (tableau[i][colonne].length() > 1)
        {
            break;
        }
    }
    return collection;
}


bool Catalogue::verifieSiExisteCatalogue(Collection *uneCollection,Collection* uneCollectionCatalogue)
{
    Cellule *current1 = uneCollection->GetHead();
    Cellule *current2 = uneCollectionCatalogue->GetHead();
    bool var;
    while (current1 != nullptr && current2!=nullptr && var)
    {   
        TrajetSimple *ptr1 = dynamic_cast<TrajetSimple *>(current1->t);
        TrajetSimple *ptr2 = dynamic_cast<TrajetSimple *>(current2->t);
        if (ptr1 != nullptr && ptr2 != nullptr) // le deux trajets sont simples
        {
            if (strcmp(current1->t->getVilleArrivee(), current1->t->getVilleArrivee()) != 0 || strcmp(current2->t->getVilleArrivee(), current2->t->getVilleArrivee()) != 0)
            {
                var = false;
            }
        }
        else if (ptr1 == nullptr and ptr2 == nullptr) // les deux sont composés
        {
            if (strcmp(current1->t->getVilleArrivee(), current1->t->getVilleArrivee()) == 0 && strcmp(current2->t->getVilleArrivee(), current2->t->getVilleArrivee()) == 0)
            {
                var = Catalogue::verifieSiExisteCatalogue(current2->t); // il faut accéder aux éléments de t qui est une collection de trajets 
            }
            else
            {
                var = false
            }
        }

        else
        {
            var = false; // si à un même niveau c'est différent on retourne un pointeur null
        }

        current1 = current1->suivant;
        current2 = current2->suivant;
    }
    return var;
}