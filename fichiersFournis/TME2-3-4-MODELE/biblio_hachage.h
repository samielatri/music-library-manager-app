#ifndef _BIBLIO_HACHAGE_H_
#define _BIBLIO_HACHAGE_H_

#include "biblio.h"
#include <math.h>

#define TAILLE_TABLE 60000
#define A 0.6180339887498949


typedef struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
    unsigned int cle;
} CellMorceau;


struct Biblio {
    int nE;
    int m;
    CellMorceau **T;    
};


#endif
