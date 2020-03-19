#ifndef _BIBLIO_ARBRE_LEX_H_
#define _BIBLIO_ARBRE_LEX_H_

#include "biblio.h"

struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};


typedef struct Noeud {
    struct Noeud *liste_car;
    struct Noeud *car_suiv;
    CellMorceau *liste_morceaux;
    char car;
} Noeud;


struct Biblio {
    int nE;
    Noeud *A;
};

#endif
