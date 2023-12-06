//----------------Interface de la classe <tab> (fichier tab.h)----------------//

#if !defined TAB_H
#define TAB_H

//-------------------------------------------------------- Interfaces utilisées
#include <string>

using  namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------//
// Rôle de la structure <tab>
// Description :
//------------------------------------------------------------------------//

typedef struct Tab
{
    string** table;
    int nb;
};


//-------------------------------- Autres définitions dépendantes de <Classe>

#endif // !defined CLASSE_H
