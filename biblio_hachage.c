/* biblio_hachage.c */

#include "biblio_hachage.h"

/* renvoie cl'e */
int getKey(char *artiste) {
	int cpt = 0 ;
	int i = 0 ;

	for (i = 0  ; i < strlen(artiste)  ; i++) {
		char c = artiste[i] ;
		cpt += (int) c ;
	}

	return cpt  ;
}

/* renvoie hash */
unsigned int getHash(unsigned int cle, int m) {
	return floor(m * (cle * A - floor(cle * A)))  ;
}

/* Alloue et retourne l'adresse d'une nouvelle Biblio */
Biblio *nouvelle_biblio(void) {
   Biblio *B = (Biblio *) malloc(sizeof(Biblio))  ;
   
   B->nE = 0  ;
   B->m = TAILLE_TABLE  ;
   B->T = (CellMorceau **) malloc( sizeof(CellMorceau *) * (B->m) )  ;
   
   return B  ;
}

void libere_biblio(Biblio *B) {
    int i = 0  ;

	for (i = 0  ; i < B->m  ; i++) {
		CellMorceau * courant = B->T[i] ;
		while (courant != NULL) {
			CellMorceau *tmp =  courant ;
			courant =  courant->suiv ;
			free(tmp) ;
		}
	}

	free(B->T) ;
	free(B) ;

	return ; 
}


void insere(Biblio *B, int num, char *titre, char *artiste) {
	int keyF = getKey(artiste) ;
	int hashF = getHash(keyF, B->m) ;

	CellMorceau *cellule = (CellMorceau *)malloc(sizeof(CellMorceau)) ;
	cellule->num = num ;
	cellule->cle = keyF ;
	cellule->artiste = strdup(artiste) ;
	cellule->titre = strdup(titre) ;
	cellule->suiv = B->T[hashF] ;
	B->T[hashF] = cellule ;

    B->nE++ ;

	return ; 
}

void afficheMorceau(CellMorceau *cell) {
	printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste) ;
}

void affiche(Biblio *B)
{
    int i ;
	for (int i = 0 ; i < B->m ; i++) {
		CellMorceau * courant = B->T[i] ;
		while ( courant) {
			afficheMorceau( courant) ;
			 courant =  courant->suiv ;
		}
	}
	printf("\nNombre de morceaux - %d\n", B->nE) ;
}

Biblio *uniques (Biblio *B)
{
	Biblio *nB = nouvelle_biblio() ;

    int i ;
	for (i = 0 ; i < B->m ; i++) {
		CellMorceau * courant = B->T[i] ;
		if ( courant) {
			while ( courant) {
				int occ = 0 ;
				CellMorceau *alt = B->T[i] ;
				while (alt) {
					if ((strcmp(alt->titre,  courant->titre) == 0) && (strcmp(alt->artiste,  courant->artiste) == 0)) occ++ ;
					alt = alt->suiv ;
				}
				if (occ == 1) insere(nB, nB->nE,  courant->titre,  courant->artiste) ;
				 courant =  courant->suiv ;
			}
		}
	}

	return nB ;
}

CellMorceau *rechercheParNum(Biblio *B, int num) {
	int i = 0 ;
	for (i = 0 ; i < B->m ; i++) {
		CellMorceau * courant = B->T[i] ;
		while ( courant) {
			if ( courant->num == num) {
				return  courant ;
			}
			 courant =  courant->suiv ;
		}
	}

	return NULL ;
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	int i = 0 ;
	for (i = 0 ; i < B->m ; i++) {
		CellMorceau * courant = B->T[i] ;
		while ( courant) {
			if (strcmp(titre,  courant->titre) == 0) {
				CellMorceau *c = (CellMorceau *)malloc(sizeof(CellMorceau)) ;
				c->num =  courant->num ;
				return  courant ;
			}
			 courant =  courant->suiv ;
		}
	}

	return NULL ;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	Biblio *nB = nouvelle_biblio() ;

	unsigned int keyF = getKey(artiste) ;
	unsigned int hash = getHash(keyF, B->m) ;

	CellMorceau * courant = B->T[hash] ;
	while ( courant) {
		insere(nB,  courant->num,  courant->titre,  courant->artiste) ;
		 courant =  courant->suiv ;
	}

	return nB ;
}

void insereSansNum(Biblio *B, char *titre, char *artiste) {
	insere(B, B->nE, titre, artiste) ;
}


int supprimeMorceau(Biblio *B, int num) {
	int i ;
	for (i = 0 ; i < B->m ; i++) {
		CellMorceau * courant = B->T[i] ;
		
		if ( courant) {
			if ( courant->num == num) {
				B->T[i] =  courant->suiv ;
				free( courant->titre) ;
				free( courant->artiste) ;
				free( courant) ;
				B->nE-- ;
				return 1 ;
			}

			while ( courant->suiv &&  courant->suiv->num != num) {
				 courant =  courant->suiv ;
			}

			if ( courant->suiv != NULL) {
				CellMorceau *tmp =  courant->suiv ;
				 courant->suiv = tmp->suiv ;
				free(tmp->titre) ;
				free(tmp->artiste) ;
				free(tmp) ;
				B->nE-- ;
				return 1 ;
			}
		}
	}
	return 0  ;
}


