//-------------------Réalisation de la classe <Catalogue> (fichier Catalogue.cpp)-------------------//

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
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
        cin >> choix;
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
                Sauvegarde();
                break;
            case 5:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Erreur de saisie" << endl;
                break;
        }
    } while (choix != 5);
}

void Catalogue::SauvegardeCompose(ofstream& fic, Trajet* trajet, int compteurSep, int trajetUnique = 0, char* depart = nullptr, char* arrivee = nullptr)
{
    TrajetCompose* trajetCompose = dynamic_cast<TrajetCompose*>(trajet);
    
    if (trajetCompose && trajetUnique != 1) {
        for(int i = 0; i < compteurSep; i++)
        {
            fic << SEP;
        }
        if(depart != nullptr && arrivee != nullptr)
        {
            if(strcmp(trajet->getVilleDepart(), depart) == 0 && strcmp(trajet->getVilleArrivee(), arrivee) == 0)
            {
                fic << "c" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << "\n";
            }
            else
            {
                return;
            }
        } else if (depart != nullptr) {
            if(strcmp(trajet->getVilleDepart(), depart) == 0)
            {
                fic << "c" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << "\n";
            }
        } else if (arrivee != nullptr) {
            if(strcmp(trajet->getVilleArrivee(), arrivee) == 0)
            {
                fic << "c" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << "\n";
            }
        } else {
            fic << "c" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << "\n";
        }
        Collection* listeTrajets = trajetCompose->getLesTrajets();
        Cellule* head = listeTrajets->GetHead();
        while(head)
        {
            SauvegardeCompose(fic, head->t, compteurSep + 1, 0, depart, arrivee);
            head = head->suivant;
        }
    } else if (!trajetCompose && trajetUnique != 2){
        for(int i = 0; i < compteurSep; i++)
        {
            fic << SEP;
        }
        if(depart != nullptr && arrivee != nullptr)
        {
            if(strcmp(trajet->getVilleDepart(), depart) == 0 && strcmp(trajet->getVilleArrivee(), arrivee) == 0)
            {
                fic << "s" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << SEP << trajet->getMoyenTransport() << "\n";
            }
        } else if (depart != nullptr) {
            if(strcmp(trajet->getVilleDepart(), depart) == 0)
            {
                fic << "s" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << SEP << trajet->getMoyenTransport() << "\n";
            }
        } else if (arrivee != nullptr) {
            if(strcmp(trajet->getVilleArrivee(), arrivee) == 0)
            {
                fic << "s" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << SEP << trajet->getMoyenTransport() << "\n";
            }
        } else {
            fic << "s" << SEP << trajet->getVilleDepart() << SEP << trajet->getVilleArrivee() << SEP << trajet->getMoyenTransport() << "\n";
        }
    }
}

void Catalogue::Sauvegarde()
{
    choixSauvegarde();
    int choix;
    cin >> choix;
    ofstream fic;
    int index = 0;
    fic.open("FichierEntreeSortie.csv");
    switch (choix) {
        case 1: // sans critère de séléction
            if(fic.is_open())
            {
                Cellule* head = c->GetHead();
                Cellule* tail = c->GetTail();
                do
                {
                    if(index)
                    {
                        head = head->suivant;
                    }
                    else
                    {
                        index = 1;
                    }
                    SauvegardeCompose(fic, head->t, 0);
                }
                while(head->t != tail->t);     
                fic.close();
                cout << "Fichier modifié" << endl;
            } else {
                cout << "Erreur d'ouverture du fichier" << endl;
            }
            break;
        case 2: // Selon le type de trajet
            cout << "------------------------------------------" << endl;
            cout << "TRAJET SIMPLE OU COMPOSE ?" << endl;
            cout << "1. Trajet simple" << endl;
            cout << "2. Trajet compose" << endl;
            int choix;
            cin >> choix;
            if(choix != 1 && choix != 2)
            {
                cout << "Erreur de saisie" << endl;
                break;
            }
            if(fic.is_open())
            {
                Cellule* head = c->GetHead();
                Cellule* tail = c->GetTail();
                do
                {
                    if(index)
                    {
                        head = head->suivant;
                    }
                    else
                    {
                        index = 1;
                    }
                    SauvegardeCompose(fic, head->t, 0, choix);
                }
                while(head->t != tail->t);
                fic.close();
                cout << "Fichier modifié" << endl;
            }
            break;
        case 3: // Selon la ville de départ/arrivée
            cout << "------------------------------------------" << endl;
            cout << "CHOISIR UN DEPART, UNE ARRIVEE OU LES DEUX" << endl;
            cout << "1. Depart" << endl;
            cout << "2. Arrivee" << endl;
            cout << "3. Depart/Arrivee" << endl;
            int choixDepArr;
            cin >> choixDepArr;
            char* selectionDepart, * selectionArrivee;
            selectionDepart = new char[100];
            selectionArrivee = new char[100];
            switch (choixDepArr)
            {
            case 1:
                cout << "Veuillez saisir un depart" << endl;
                cin >> selectionDepart;
                if(fic.is_open() && selectionDepart)
                {
                    Cellule* head = c->GetHead();
                    Cellule* tail = c->GetTail();
                    index = 0;
                    do
                    {
                        if(index)
                        {
                            head = head->suivant;
                        }
                        else
                        {
                            index = 1;
                        }
                        SauvegardeCompose(fic, head->t, 0, 0, selectionDepart);
                    }
                    while(head->t != tail->t);
                    fic.close();
                    cout << "Fichier modifié" << endl;
                }
                break;
            case 2:
                cout << "Veuillez saisir une arrivée" << endl;
                cin >> selectionArrivee;
                if(fic.is_open() && selectionArrivee)
                {
                    Cellule* head = c->GetHead();
                    Cellule* tail = c->GetTail();
                    index = 0;
                    do
                    {
                        if(index)
                        {
                            head = head->suivant;
                        }
                        else
                        {
                            index = 1;
                        }
                        SauvegardeCompose(fic, head->t, 0, 0, nullptr, selectionArrivee);
                    }
                    while(head->t != tail->t);
                    fic.close();
                    cout << "Fichier modifié" << endl;
                }
                break;
            case 3:
                cout << "Veuillez saisir un depart" << endl;
                cin >> selectionDepart;
                cout << "Veuillez saisir une arrivée" << endl;
                cin >> selectionArrivee;
                if(fic.is_open() && selectionDepart && selectionArrivee)
                {
                    index = 0;
                    Cellule* head = c->GetHead();
                    Cellule* tail = c->GetTail();
                    do
                    {
                        if(index)
                        {
                            head = head->suivant;
                        }
                        else
                        {
                            index = 1;
                        }
                        SauvegardeCompose(fic, head->t, 0, 0, selectionDepart, selectionArrivee);
                    }
                    while(head->t != tail->t);
                    fic.close();
                    cout << "Fichier modifié" << endl;
                }
                break;
            default:
                cout << "Erreur de saisie" << endl;
                break;
            }
            break;
        case 4: // selon un intervalle de trajet avec n le premier trajet et m le dernier
            int n, m;
            cout << "------------------------------------------" << endl;
            cout << "INDICE DU PREMIER/DERNIER TRAJET ?" << endl;
            cout << "1. Veuillez saisir l'indice du premier trajet" << endl;
            cin >> n;
            cout << "2. Veuillez saisir l'indice du dernier trajet" << endl;
            cin >> m;
            if(m <= n)
            {
                cout << "Le dernier trajet doit etre inferieur à la position du premier et doit avoir un ecart d'au moins 1 trajet" << endl;
                break;
            } else {
                if(fic.is_open())
                {
                    Cellule* head = c->GetHead();
                    Cellule* tail = c->GetTail();
                    int skip = 0;
                    int compteur = 0;
                    for(int i = 1; i < n; i++)
                    {
                        if(head->t == tail->t)
                        {
                            cout << "L'indice du premier trajet est supérieur au nombre de trajet" << endl;
                            skip = 1;
                            break;
                        }
                        compteur++;
                        head = head->suivant;
                    }
                    if(!skip)
                    {
                        do
                        {
                            compteur++;
                            if(index)
                            {
                                head = head->suivant;
                            }
                            else
                            {
                                index = 1;
                            }
                            SauvegardeCompose(fic, head->t, 0);
                        }
                        while(head->t != tail->t && compteur <= m);     
                    }
                    fic.close();
                } else {
                    cout << "Erreur d'ouverture du fichier" << endl;
                }
                break;
            }
        default:
            cout << "Erreur de saisie" << endl;
            if(fic.is_open())
            {
                fic.close();
            }
            break;
    }
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

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
    //c->RechercheSimple(depart, arrivee);
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
    cout << "4. Sauvegarder le catalogue courant dans un fichier" << endl;
    cout << "5. Quitter" << endl;
    cout << "Votre choix : ";
}

void Catalogue::choixSauvegarde()
{
    cout << "------------------------------------------" << endl;
    cout << "CHOIX DU TYPE DE SAUVEGARDE" << endl;
    cout << "1. Sans critère de sélection" << endl;
    cout << "2. Selon le type de trajet" << endl;
    cout << "3. Selon la ville de départ et / ou la ville d'arrivée" << endl;
    cout << "4. Selon une sélection de trajets" << endl;
    cout << "5. Quitter" << endl;
    cout << "Votre choix :";
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