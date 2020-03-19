/*	biblio_liste.c	*/

#include "biblio_liste.h"

/* Alloue et retourne l'adresse d'une nouvelle Biblio */
Biblio *nouvelle_biblio(void) {
    Biblio *biblio = (Biblio*) malloc( sizeof(Biblio) ) ; 
	
	if (biblio == NULL) {
		printf("Echec de l'allocation memoire (biblio_liste/nouvelle_biblio)\n") ;
		fprintf(stderr, "Echec de l'allocation memoire (biblio_liste/nouvelle_biblio)\n") ; 
		exit(EXIT_FAILURE) ; 
	}

	biblio->L = NULL ; 
	biblio->nE = 0 ; 
	
	return biblio ; 
}

/*
	Insère un nouveau morceau dont les caract'eristiques sont num, titre et artiste dans une biblio. 
	Remarque : L'insertion se fait en t^ete de liste (biblio).
*/
void insere(Biblio *B, int num, char *titre, char *artiste) {
    CellMorceau *nouv = (CellMorceau*) malloc( sizeof(CellMorceau) ) ;
	
	if (nouv == NULL) {
		printf("Echec de l'allocation memoire (biblio_liste/insere)\n") ;
		fprintf(stderr, "Echec de l'allocation memoire biblio_liste/insere\n") ; 
		exit(EXIT_FAILURE) ; 
	}

	nouv->num = num ;
	nouv->titre = titre ; 
	nouv->artiste = artiste ; 
	
	if(B->L != NULL){
		nouv->suiv = B->L ; 
		B->L = nouv ; 
		B->nE = ++ (B->nE) ;

		return ; 
	}

	// cas : B->L == NULL
	nouv->suiv = NULL ; 
	B->L = nouv ; 
	B -> nE = 1 ; 	

	return ; 
}

void libere_biblio(Biblio *B)
{
    
}

void afficheMorceau(CellMorceau *cell)
{
	printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
   
}

Biblio *uniques (Biblio *B)
{
    
}

CellMorceau * rechercheParNum(Biblio *B, int num)
{
	
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	
}

Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	
}


void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	
}

int supprimeMorceau(Biblio *B, int num)
{
	
}
































