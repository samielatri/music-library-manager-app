#ifndef _BIBLIO_LISTE_H_
#define _BIBLIO_LISTE_H_

#include "biblio.h"


struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    CellMorceau *L;
    int nE;
};

#endif
