#ifndef _BIBLIO_TAB_DYN_H_
#define _BIBLIO_TAB_DYN_H_

#include "biblio.h"

struct CellMorceau{
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    int nE;
    int capacite;
    CellMorceau *T;    
};

#endif
