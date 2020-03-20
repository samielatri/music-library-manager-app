/* main.c */

/* Teste les biblioth`eques */

#include "biblio.h"

void menu(void) {
	printf("Menu :\n") ;

	printf("0-Sortie\n") ;
	printf("1-Affichage\n") ;
	printf("2-Recherche et affichage des morceaux uniques\n") ;
	printf("3-Recherche et affichage des morceaux par titre\n") ;
	printf("4-Recherche et affichage des morceaux par numero\n") ;
	printf("5-Recherche et affichage des morceaux par artiste\n") ;
	printf("6-Ajouter un morceau\n") ;
	printf("7-Suppression morceau\n") ;

	printf("\n") ; 
	
	printf("Votre choix : ") ;
	
	return ; 
}

int main(int argc, const char *argv[]) {
	printf("Bonjour\n") ;

	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return EXIT_FAILURE ; // 1 
	}
	
	const char *nomfic = argv[1] ;
	int nlignes = atoi(argv[2]) ;
	char titre[249] ;
	char artiste[249] ;
	int num = 0 ;

	printf("Lecture :\n") ;

	Biblio *biblio = charge_n_entrees(nomfic, nlignes) ;

	affiche(biblio) ; 

	printf("\n") ;

	int ch = 1 ;

	do {
		menu() ;

		int lus = scanf("%d", &ch) ;
		
		if (lus == 0){
			ch = 0 ;
		}

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
					printf("Veuillez saisir le titre du morceau :\n") ;
					scanf("%248[^\n]", titre) ;
					CellMorceau * r = rechercheParTitre(biblio, titre) ;
					if (r == NULL) {
						printf("Aucun morceau de titre : %s!!!\n", titre) ;
					} else {
						afficheMorceau(r) ;
					}
					break ;
				}
			case 4 : {
					printf("Veuillez saisir le num'ero du morceau :\n") ;
					scanf("%d[^\n]", &num) ;
					CellMorceau * r = rechercheParNum(biblio, num) ;
					if (r == NULL) {
						printf("Aucun morceau de numero : %d !!!\n", num) ;
					} else {
						afficheMorceau(r) ;
					}
					break ;
				}
			case 5 :
				{
					printf("Saisir le nom de l'artiste :\n");
					scanf(" %248[^\n]", artiste);
					Biblio * r = extraireMorceauxDe(biblio, artiste);
					affiche(r);
					libere_biblio(r);
					break;
				}
			case 6 : {
					printf("Veuillez saisir le titre du morceau :\n") ;
					scanf(" %248[^\n]", titre) ;

					printf("Maintenant, veuillez saisir le nom de l'artiste :\n") ;
					scanf(" %248[^\n]", artiste) ;
					
					insereSansNum(biblio, titre, artiste) ;

					printf("Insertion effectu'ee.\n") ;

					break ;
				}

			case 7 : {
					printf("Veuillez saisir le num'ero du morceau :\n") ;
					scanf("%d[^\n]", &num) ;

					if (supprimeMorceau(biblio, num) == 1) {
						printf("Le morceau a 'et'e supprim'e avec succ`es.\n") ;
					} else {
						printf("Aucune action n'a 'et'e 'effectu'ee. Aucun morceau n'a 'et'e supprim'e.\n") ;
					}

					break ;
				}

			default : {
				ch = 0;
				break;
			}
		}
		
	} while (ch != 0);
	
	libere_biblio(biblio);

	printf("Au revoir\n") ;
	
	return EXIT_SUCCESS ;
}