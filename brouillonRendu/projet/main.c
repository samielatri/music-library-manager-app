/*	main.c	*/

#include "biblio.h"


void menu(void) {
	printf("Menu:\n") ;
	printf("0-Sortie\n") ; 
	printf("1-Affichage\n") ;
	printf("2-Recherche morceaux uniques\n") ;
	printf("3-Recherche morceau par titre\n") ;

	printf("Votre choix : ") ;
	
	return ; 
}

int main(int argc, const char *argv[]) {
	printf("Bonjour\n") ;

	if (argc != 3) {
		fprintf(stderr, "Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>\n", argv[0]) ; 
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>\n", argv[0]) ;
		return EXIT_FAILURE ;
	}
	
	const char *nomfic = argv[1] ;
	int nlignes = atoi(argv[2]) ;
	char titre[249] ;
	printf("Lecture :\n") ;
	Biblio *biblio = charge_n_entrees(nomfic, nlignes) ;
	
	int ch = 0 ;
	do {
		menu() ;
		int lus = scanf("%d", &ch) ;
		if (lus == 0)
			ch = 0;
		
		switch(ch) {
			case 1 : {
				printf("Affichage\n") ;
				affiche(biblio) ;
				break ;
			}

			case 2 : {
				Biblio *Bunique = uniques(biblio) ;
				affiche(Bunique) ;
				libere_biblio(Bunique) ;
				break ;
			}

			case 3 : {
					printf("Saisir le titre du morceau :\n") ;
					scanf(" %248[^\n]", titre) ;
					CellMorceau * r = rechercheParTitre(biblio, titre) ;
					if (r == NULL) {
						printf("Aucun morceau de titre : %s!!!\n", titre) ;
					} else {
						afficheMorceau(r) ;
					}
					break ;
			}

			default : {
				ch = 0 ; 
				break ;
			}
		}	

	} while (ch != 0);
	
	libere_biblio(biblio) ;
	
	printf("Au revoir\n") ;
	
	return EXIT_SUCCESS ;
}
