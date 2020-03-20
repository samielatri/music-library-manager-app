/* biblio_arbrelex.c */

#include "biblio_arbrelex.h"

/* Alloue et retourne l'adresse d'une nouvelle Biblio */
Biblio *nouvelle_biblio(void) {
   Biblio *B = (Biblio *) malloc( sizeof(Biblio) ) ;
   
   B->nE = 0 ;
   B->A = NULL ;

   return B ;
}

/* Libère noeud (fonction récursive) */
void libere_noeud(Noeud *N) {
	if (N == NULL) { 
		return ; // sortie
	}

	CellMorceau *courant = N->liste_morceaux ;

	while (courant != NULL) {
		CellMorceau *temp = courant ;
		courant = courant->suiv ;
		free(temp) ;
	}

	/* appels récursifs */
	libere_noeud(N->car_suiv) ;
	libere_noeud(N->liste_car) ;

	return ; // non atteint
}

/* Libère intégralement la biblio */
void libere_biblio(Biblio *B) {
	libere_noeud(B->A) ;

    free(B) ;

	return ;
}

/* Recherche si un artiste est présent */
void recherche_artiste(Biblio *B, char *artiste) {
	int i = 0; // Indice lisant nom
	Noeud *pointeurCourant = B->A; // Pointeur courant
	Noeud *pointeurPrecedent = pointeurCourant; // Pointeur sur la valeur precedant pointeurCourant

	while ((pointeurCourant != NULL) && (artiste[i] != '\0')) {
		pointeurPrecedent = pointeurCourant;

		if (pointeurCourant->car == artiste[i]) { // On a lu le bon caractere
			pointeurCourant = pointeurCourant->car_suiv;
			i++;
		}
		else { // On tente un caractere alternatif
			pointeurCourant = pointeurCourant->liste_car;
		}
	}

	if (artiste[i] == '\0'){
		printf("La chaine %s est présente.\n", artiste);
	} else {
		printf("La chaine %s est pr'esente jusqu'au caract`ere numero %d.\n", artiste, i - 1);
		if (artiste[i-1] == pointeurPrecedent->car) {
			printf("La suite de la chaine peut etre inseree a la suite de la lettre %c.\n", pointeurPrecedent->car);
		} else {
			printf("La suite de la chaine peut etre en alternative a la lettre %c.\n", pointeurPrecedent->car);
		}
	}

	return ;
}

CellMorceau *nouvelle_cellule(int num, char *titre, char *artiste) {
	CellMorceau *nouvelleCelluleTemp = (CellMorceau *) malloc( sizeof(CellMorceau) ) ;
	nouvelleCelluleTemp->num = num ;
	nouvelleCelluleTemp->artiste = strdup(artiste) ;
	nouvelleCelluleTemp->titre = strdup(titre) ;
	nouvelleCelluleTemp->suiv = NULL ;
	return nouvelleCelluleTemp ;
}

Noeud *insere_noeud(Noeud *unNoeud, char *artiste, int i, CellMorceau *nouvelleCelluleTemp) {
	if (unNoeud == NULL) {
		unNoeud = (Noeud *) malloc( sizeof(Noeud) ) ;
		unNoeud->liste_car = NULL ;
		unNoeud->car_suiv = NULL ;
		unNoeud->liste_morceaux = NULL ;
		unNoeud->car = artiste[i] ;
	}

	if (artiste[++i] == '\0') {
		nouvelleCelluleTemp->suiv = unNoeud->liste_morceaux ;
		unNoeud->liste_morceaux = nouvelleCelluleTemp ;
	} else {
		if (artiste[i] == unNoeud->car) {
			unNoeud->car_suiv = insere_noeud(unNoeud->car_suiv, artiste, i+1, nouvelleCelluleTemp) ;
		} else {
			unNoeud->liste_car = insere_noeud(unNoeud->liste_car, artiste, i, nouvelleCelluleTemp) ;
		}
	}

	return unNoeud ;
}

/* Insère le morceau dont les caractéristiques sont num, titre et artiste */
void insere(Biblio *B, int num, char *titre, char *artiste) {
	CellMorceau *nouvelleCelluleTemp = nouvelle_cellule(num, titre, artiste) ;
	B->A = insere_noeud(B->A, artiste, 0, nouvelleCelluleTemp) ;
	++ (B->nE) ;

	return ; 
}

/* Affiche un morceau */
void afficheMorceau(CellMorceau *cell) {
	printf("|A| %8d | %-32.32s | %-32.32s |A|\n", cell->num, cell->titre, cell->artiste);
	return ; 
}

/* Affiche un noeud (fonction r'ecurisive) */
void afficheNoeud(Noeud *N) {
	if (N == NULL) {
		return ; // sortie
	}

	CellMorceau *courant = N->liste_morceaux;

	while (courant != NULL ) {
		afficheMorceau(courant) ;
		courant = courant->suiv ; 
	}

	/* Appels récursifs */
	afficheNoeud(N->liste_car) ;
	afficheNoeud(N->car_suiv) ;

	return ; // non atteint 
}

void affiche(Biblio *B) {
    afficheNoeud(B->A) ;
	return ;
}

/* renvoie nombre de morceaux */
int compte_nombre_morceaux(CellMorceau *C) {
	int cpt = 0 ;

	CellMorceau *courant = C ;
	while (courant != NULL) {
		if (strcmp(C->titre, courant->titre) == 0) {
			++ cpt ;
		}

		courant = courant->suiv ;
	}

	return cpt ;
}

/* cherche_uniques (fonction r'ecursive) */
void cherche_uniques(Noeud *N, Biblio *B) {
	if (N != NULL) {
		CellMorceau *c = N->liste_morceaux ;

		while (c != NULL) {
			if (compte_nombre_morceaux(c) == 1) {
				insere(B, c->num, strdup(c->titre), strdup(c->artiste)) ;
			}
			c = c->suiv ;
		}

		/* appels r'ecurisifs */
		cherche_uniques(N->liste_car, B) ;
		cherche_uniques(N->car_suiv, B) ;
	}

	return ; 
}

/* Retourne une nouvelle biblio contenant les morceaux de B sans doublons */
Biblio *uniques (Biblio *B) {
	Biblio *nouvelleBiblio = nouvelle_biblio() ;
	cherche_uniques(B->A, nouvelleBiblio) ;

	return nouvelleBiblio ;
}

CellMorceau *choixMorceau(CellMorceau *cell1, CellMorceau *cell2) {
	if (cell1 == NULL && cell2 == NULL) {
		return NULL ;
	}

	if (cell1 == NULL && cell2 != NULL) {
		return cell2 ;
	}

	if (cell1 != NULL && cell2 == NULL)  {
		return cell1 ;
	}

	return cell1 ;
}

CellMorceau *cherche_num(Noeud *N, int num) {
	if (N == NULL) {
		return NULL ;
	}
	
	CellMorceau *courant = N->liste_morceaux;
	while (courant) {
		if (courant->num == num) {
			CellMorceau *C = (CellMorceau *)malloc(sizeof(CellMorceau));
			C->num = courant->num;
			C->titre = strdup(courant->titre);
			C->artiste = strdup(courant->artiste);
			C->suiv = NULL;
			return C;
		}
		courant = courant->suiv;
	}

	return choixMorceau(cherche_num(N->liste_car, num), cherche_num(N->car_suiv, num));
}

CellMorceau *rechercheParNum(Biblio *B, int num) {
	return cherche_num(B->A, num) ;
}

CellMorceau *cherche_titre(Noeud *N, char *titre) {
	if (N == NULL) return NULL;

	CellMorceau *courant = N->liste_morceaux;
	while (courant) {
		if (strcmp(courant->titre, titre) == 0) {
			CellMorceau *C = (CellMorceau *)malloc(sizeof(CellMorceau));
			C->num = courant->num;
			C->titre = strdup(courant->titre);
			C->artiste = strdup(courant->artiste);
			C->suiv = NULL;
			return C;
		}
		courant = courant->suiv;
	}

	return choixMorceau(cherche_titre(N->liste_car, titre), cherche_titre(N->car_suiv, titre));
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	return cherche_titre(B->A, titre) ;
}

Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	int i = 0 ; 
	Noeud *pointeurCourant = B->A ; 
	Noeud *pointeurPrecedent = pointeurCourant ; 

	while ((pointeurCourant != NULL) && (artiste[i] != '\0')) {
		pointeurPrecedent = pointeurCourant ;

		if (pointeurCourant->car == artiste[i]) { 
			pointeurCourant = pointeurCourant->car_suiv;
			i++ ;
		}
		else { 
			pointeurCourant = pointeurCourant->liste_car ;
		}
	}

	Biblio *autreBiblio = nouvelle_biblio() ;

	if (artiste[i] == '\0') {
		CellMorceau *c = pointeurPrecedent->liste_morceaux ;
		while (c) {
			insere(autreBiblio, c->num, strdup(c->titre), strdup(c->artiste)) ;
			c = c->suiv ;
		}
	} else {
		printf("L'artiste n'a pas pu etre trouv'e dans la base de donn'ees.\n");
	}

	return autreBiblio;
}


void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	insere(B, B->nE, strdup(titre), strdup(artiste));
}


int supprime_num(Biblio *B, Noeud *N, int num) {
	
	if (N == NULL) {
		return 0 ;
	}

	CellMorceau *courant = N->liste_morceaux;
	if (courant) {
		if (courant->num == num) {
			N->liste_morceaux = courant->suiv;
			free(courant->titre);
			free(courant->artiste);
			free(courant);
			B->nE--;
			return 1;
		}

		while (courant->suiv && courant->suiv->num != num) {
			courant = courant->suiv;
		}

		if (courant->suiv != NULL) {
			CellMorceau *tmp = courant->suiv ;
			courant->suiv = tmp->suiv ;
			free(tmp->titre) ;
			free(tmp->artiste) ;
			free(tmp) ;
			B->nE-- ;
			return 1 ;
		}
	}

	return MAX(supprime_num(B, N->liste_car, num), supprime_num(B, N->car_suiv, num)) ;
	/*
		return (supprime_num(B, N->liste_car, num)>=supprime_num(B, N->car_suiv, num)?supprime_num(B, N->liste_car, num):supprime_num(B, N->car_suiv, num))
	*/
}

/* Supprime le morceau de numéro num de la Biblio B */
int supprimeMorceau(Biblio *B, int num) {
	return supprime_num(B, B->A, num) ;
}
