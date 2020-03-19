#ifndef _BIBLIO_LISTE_H_
#define _BIBLIO_LISTE_H_

#include "biblio.h"


struct CellMorceau {
    struct CellMorceau *suiv ;
    int num ;   /* Num'ero d'enregistrement du morceau */
    char *titre ;   /* Titre du morceau */
    char *artiste ; /* Nom de l'artiste qui interpr`ete le morceau */
} ;

/*  typedef struct CellMorceau CellMorceau ; // dans biblio.h   */

struct Biblio {
    CellMorceau *L ;    /* Liste chain'ee des morceaux */
    int nE ;    /* Nombre de morceaux dans la liste */
} ;

/*  typedef struct Biblio Biblio ; // dans biblio.h  */

#endif /* _BIBLIO_LISTE_H_ */
