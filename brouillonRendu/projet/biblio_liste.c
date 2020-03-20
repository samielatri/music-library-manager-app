/*	biblio_liste.c	*/

/* 
	Biblioth`eque permettant la construction d'une biblio (structure : liste)
	`a partir de la lecture d'un fichier et la manipulation de cette biblio (liste)
*/

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

	/* commun aux deux cas */
	nouv->num = num ;
	nouv->titre = titre ; 
	nouv->artiste = artiste ; 
	
	// cas1
	if(B->L != NULL){
		nouv->suiv = B->L ; 
		B->L = nouv ; 
		B->nE = ++ (B->nE) ;

		return ; // sortie pr'ematur'ee
	}

	// cas2 : B->L == NULL
	nouv->suiv = NULL ; 
	B->L = nouv ; 
	B -> nE = 1 ; 	

	return ; 
}

/* libere la biblio */
void libere_biblio(Biblio *B) {
    CellMorceau *temp = B->L ;
	
	while(temp != NULL) {
		CellMorceau *temp1 = temp->suiv ; 

		free(temp->artiste) ; 

		if(temp->artiste != NULL) {
			printf("Echec de la liberation memoire (biblio_liste/libere1)\n") ;
			fprintf(stderr, "Echec de la liberation memoire biblio_liste/libere1\n") ; 
			exit(EXIT_FAILURE) ; 
		}

		free(temp->titre) ;

		if(temp->titre != NULL) {
			printf("Echec de la liberation memoire (biblio_liste/libere2)\n") ;
			fprintf(stderr, "Echec de la liberation memoire biblio_liste/libere2\n") ; 
			exit(EXIT_FAILURE) ; 
		}

		free(temp) ; 

		if(temp != NULL) {
			printf("Echec de la liberation memoire (biblio_liste/libere3)\n") ;
			fprintf(stderr, "Echec de la liberation memoire biblio_liste/libere3\n") ; 
			exit(EXIT_FAILURE) ; 
		}

		temp = temp1 ; 
	}

	free(B) ;

	if(temp != NULL) {
		printf("Echec de la liberation memoire (biblio_liste/libereF)\n") ;
		fprintf(stderr, "Echec de la liberation memoire biblio_liste/libereF\n") ; 
		exit(EXIT_FAILURE) ; 
	}

	return ;
}

/* affiche un morceau (BONUS : FONCTION NON UTILISEE) */
void afficheMorceau(CellMorceau *cell) {
	printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
	return ;
}

/* affiche tous les morceaux de la biblio B */
void affiche(Biblio *B) {
	
	if (B->L == NULL) {
	   printf ("Biblio vide !\n") ;
	   return ; 
    }
	
	CellMorceau *temp = B->L ; 

	int i = 0 ; 	
	for(i = 0 ; i < (B->nE) ; i++) {
		printf("%d\t%s\t%s\n", temp->num, temp->titre, temp->artiste) ;
		temp = temp->suiv ; 
	} 

    return ; 
}

Biblio *uniques (Biblio *B) {
    
}

/* 
	Affiche tous les morceaux contenus dans une biblio dont le numero d'enregistrement est num 
	En bonus, elle affiche le nombre morceaux trouv'es ! 
*/
CellMorceau *rechercheParNum(Biblio *B, int num) {
	CellMorceau *temp = B->L ;
	int cpt = 0 ; // compteur du nombre de morceaux trouv'es
	// on n'a jamais mentionn'e le fait que num (enregistrement) soit unique ou qu'on puisse pas avoir le m^eme plusieurs fois
	while(temp != NULL) {
		if( (temp->num) == num ) {
			printf("%d\t%s\t%s\n", (temp->num), (temp->titre), (temp->artiste)) ;
			++ cpt ; 
		}
		temp = (temp->suiv) ; 
	}

	/* Bonus : affichage du nombre de morceaux trouv'es */
	if ( cpt == 0 ) {
		printf("Aucun morceau n'a 'et'e trouv'e !\n") ;
	} else {
		printf("\n%d morceau(x) trouv'e(s).\n", cpt) ;
	}

	return temp ; 
}

/* 
	Affiche tous les morceaux contenus dans une biblio dont le titre est titre 
	En bonus, elle affiche le nombre morceaux trouv'es ! 
	(retourne derniere structure parcourue)
*/
CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	CellMorceau *temp = B->L ;
	int cpt = 0 ; // compteur du nombre de morceaux trouv'es
	// on n'a jamais mentionné le fait que num (enregistrement) soit unique ou qu'on puisse pas avoir le m^eme plusieurs fois
	while(temp != NULL) {
		if( strcmp(temp->titre, titre) == 0 ) {
			printf("%d\t%s\t%s\n", (temp->num), (temp->titre), (temp->artiste)) ;
			++ cpt ; 
		}
		temp = (temp->suiv) ; 
	}

	/* Bonus : affichage du nombre de morceaux trouv'es */
	if ( cpt == 0 ) {
		printf("Aucun morceau n'a 'et'e trouv'e !\n") ;
	} else {
		printf("\n%d morceau(x) trouv'e(s).\n", cpt) ;
	}

	return temp ; 		
}
/*
	Retourne une nouvelle biblio qui contient uniquement les morceaux de l'artiste artiste
*/
Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	
}

/*
	Réalise l'insertion d'un nouveau morceau (de titre titre et dont le nom de l'interprète est artiste).
	Attention le numéro associé au morceau doit être différent de celui de tous les morceaux
	présents dans B
*/
void insereSansNum(Biblio *B, char *titre, char *artiste) {
	
}

/* Supprime le morceau de numéro num de la Biblio B */
int supprimeMorceau(Biblio *B, int num) {
	
}
































