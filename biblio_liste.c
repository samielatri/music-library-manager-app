/*	biblio_liste.c	*/

/* 
	Biblioth`eque permettant la construction d'une biblio (structure : liste)
	`a partir de la lecture d'un fichier et la manipulation de cette biblio (liste)
*/

#include "biblio_liste.h"

/* Alloue, instancie et retourne l'adresse d'un nouveau CellMorceau */
CellMorceau *creation_Morceau(int numero, char *titre, char *artiste)  {
    CellMorceau *morceau = (CellMorceau *)malloc(sizeof(CellMorceau)) ;

    morceau->num = numero ;
    morceau->titre = titre ;
    morceau->artiste = artiste ;
    morceau->suiv = NULL ;

    return morceau ;
}

/* Alloue et retourne l'adresse d'une nouvelle Biblio */
Biblio * nouvelle_biblio(void) {
    Biblio *b = (Biblio*)malloc(sizeof(Biblio))  ;
	/*
	if (biblio == NULL) {
		printf("Echec de l'allocation memoire (biblio_liste/nouvelle_biblio)\n")  ;
		fprintf(stderr, "Echec de l'allocation memoire (biblio_liste/nouvelle_biblio)\n")  ; 
		exit(EXIT_FAILURE)  ; 
	}
	*/
    b->L = NULL ;
    b->nE = 0 ;
    return b ;
}

/* Insère le morceau dont les caractéristiques sont num, titre et artiste */
void insere(Biblio *B, int num, char *titre, char *artiste) {
    CellMorceau *c = creation_Morceau(num, titre, artiste) ;

    if (B->L == NULL) {
        B->L = c ;
    } else {
        CellMorceau *morc = B->L ;
        while (morc->suiv != NULL) {
            morc = morc->suiv ;
        }
        morc->suiv = c ;
    }

    ++ (B->nE)  ;

    return  ; 
}

/* Libère intégralement la biblio */
void libere_biblio(Biblio *B) {
    CellMorceau *courant = B->L ;
    while (courant) {
        CellMorceau *tmp = courant ;
        courant = courant->suiv ;
        free(tmp) ;
    }
    free(B) ;
}

/* Affiche un morceau */
void afficheMorceau(CellMorceau *cell) {
	printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste) ;
}

/* Affiche les morceaux contenus dans la Biblio */
void affiche(Biblio *B) {
   CellMorceau *morceau = B->L ;
    
    while (morceau) {
        afficheMorceau(morceau) ;
        morceau = morceau->suiv ;
    }

    printf("Nombre de morceaux dans la bibliotheque - %d\n\n", B->nE) ;
}

int compte_nombre_morceaux_bibli(CellMorceau *c, Biblio *B) {
    int occ = 0 ;
    char *titre = strdup(c->titre) ;
    char *artiste = strdup(c->artiste) ;
    CellMorceau *courant = B->L ;

    while (courant) {
        if ((strcmp((courant->titre), (titre)) == 0) && (strcmp((courant->artiste), (artiste)) == 0)) {
            occ++ ;
        }
        courant = courant->suiv ;
    }

    return occ ;
}

/* Retourne une nouvelle biblio contenant les morceaux de B sans doublons */
Biblio *uniques (Biblio *B) {
    Biblio *b = nouvelle_biblio() ;
    CellMorceau *courant = B->L ;

    while (courant) {
        if (compte_nombre_morceaux_bibli(courant, B) == 1) insere(b, b->nE, (courant->titre), (courant->artiste)) ;
        courant = courant->suiv ;
    }

    return b ;
}

/* Retourne une nouvelle biblio contenant les morceaux de B sans doublons */
CellMorceau * rechercheParNum(Biblio *B, int num) {
	CellMorceau *courant = B->L ;

    while (courant) {
        if (courant->num == num) {
            printf("Un morceau correspondant a pu etre trouvé.\n") ;
            return creation_Morceau(courant->num, strdup(courant->titre), strdup(courant->artiste)) ;
        }
        courant = courant->suiv ;
    }
    
    printf("Aucun morceau n'a pu etre trouvé.\n") ;
    return NULL ;
}

/* Retourne un morceau de titre titre */
CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	CellMorceau *courant = B->L ;

    while (courant) {
        if (strcmp(strdup(courant->titre), titre) == 0) {
            printf("Un morceau correspondant a pu etre trouvé.\n") ;
            return creation_Morceau(courant->num, strdup(courant->titre), strdup(courant->artiste)) ;
        }
        courant = courant->suiv ;
    }
    
    printf("Aucun morceau n'a pu etre trouvé.\n") ;
    return NULL ;
}

/* Retourne une nouvelle biblio qui contient uniquement les morceaux de l'artiste artiste */
Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	Biblio *b = nouvelle_biblio() ;
    CellMorceau *courant = B->L ;

    while (courant) {
        if (strcmp(strdup(courant->artiste), artiste) == 0) insere(b, b->nE, strdup(courant->titre), strdup(courant->artiste)) ;
        courant = courant->suiv ;
    }

    return b ;
}

/*Réalise l'insertion d'un nouveau morceau (de titre titre et dont le nom de l'interprète est artiste).
Attention le numéro associé au morceau doit être différent de celui de tous les morceaux
présents dans B */
void insereSansNum(Biblio *B, char *titre, char *artiste) {
	insere(B, B->nE, titre, artiste) ;
}

/*Supprime le morceau de numéro num de la Biblio B */
int supprimeMorceau(Biblio *B, int num) {
	CellMorceau *courant = B->L ;
	CellMorceau *temp ;

	if (num == 0) {
		B->L = B->L->suiv ;
        B->nE-- ;
		return 1 ;
	}

	while (courant) {
		if (courant->suiv->num == num) {
            CellMorceau *c = courant->suiv ;
			courant->suiv = courant->suiv->suiv ;
            free(c) ;
            B->nE-- ;

			return 1 ;
		}
		courant = courant->suiv ;
	}

	return 0 ;
}
