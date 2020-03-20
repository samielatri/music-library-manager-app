/* biblio.c */

#include "biblio.h"

/*
    Permet de lire n entr'ees du fichier (nom_fichier) et de renvoyer une biblio cr'ee les contenant.
    Hypoth`ese : 
            format du fichier : 

                chaque ligne est une entr'ee

                format de chaque ligne : 
                  Num\tTitre\tArtitste\n
                  
                pour un fichier de trois lignes, donc : 
                    Num\tTitre\tArtitste\n
                    Num\tTitre\tArtitste\n
                    Num\tTitre\tArtitste\n

             Tout autre format est invalide ! (Erreur)
*/

Biblio *charge_n_entrees(const char *nom_fichier, int n) {
    FILE *f = fopen(nom_fichier, "r") ; // le fichier accessible en lecture uniquement

    if (f == NULL) {
        printf("Echec de l'accès en lecture du fichier (biblio/charge_n_entrees)\n") ;
		fprintf(stderr, "Echec de l'accès en lecture du fichier (biblio/charge_n_entrees)\n") ;
		exit(EXIT_FAILURE) ;  // pas les droits de lecture peut-^etre 
    }

    Biblio *biblio = nouvelle_biblio() ; // la biblio `a retourner
    
    int nbl = 0 ; // compteur de nombres de lignes lues (entr'ees lues)
    
    for(nbl = 0 ; nbl < n ; nbl ++) {
        if(end_of_file(f) == 0) { // Ce n'est pas la fin du fichier
            int num ;
            
            char *titre = (char*) malloc(sizeof(char*)) ;
            if (titre == NULL) {
		        printf("Echec de l'allocation memoire (biblio/charge_n_entrees@titre)\n") ;
		        fprintf(stderr, "Echec de l'allocation memoire (biblio/charge_n_entrees@titre)\n") ; 
		        exit(EXIT_FAILURE) ; 
            }

            char *artiste = (char*) malloc(sizeof(char*)) ;
            if (artiste == NULL) {
                printf("Echec de l'allocation memoire biblio/charge_n_entrees@artiste)\n") ;
		        fprintf(stderr, "Echec de l'allocation memoire (biblio/charge_n_entrees@artiste)\n") ;
		        exit(EXIT_FAILURE) ;  
            }

            char *retourChariot = "\n" ;
            char *tabulation = "\t" ; 
            
            int taille = TAILLEBUFF ; 

            /* 
                format du fichier : 

                    chaque ligne est une entr'ee

                    format de chaque ligne : 
                        Num\tTitre\tArtitste\n

                    pour un fichier de trois lignes, donc : 
                        Num\tTitre\tArtitste\n
                        Num\tTitre\tArtitste\n
                        Num\tTitre\tArtitste\n

                Tout autre format est invalide ! (Erreur)
            */

            parse_int(f, &num) ; // parse un entier
            
            /* consomme la tabulation */
            if ( parse_char(f, *tabulation) == 0 ) { // Consomme c et renvoie 1. Renvoie 0 si c n'est pas le caractère suivant
                printf("format fichier invalide (biblio/charge_n_entrees@tabulation1)\n") ;
		        fprintf(stderr, "format fichier invalide (biblio/charge_n_entrees@tabulation1)\n") ;
		        exit(EXIT_FAILURE) ;  
            } 

            parse_string(f, &titre, &taille, *tabulation) ;

            /* consomme la tabulation */
            if ( parse_char(f, *tabulation) == 0 ) { // Consomme c et renvoie 1. Renvoie 0 si c n'est pas le caractère suivant
                printf("format fichier invalide (biblio/charge_n_entrees@tabulation2)\n") ;
		        fprintf(stderr, "format fichier invalide (biblio/charge_n_entrees@tabulation2)\n") ;
		        exit(EXIT_FAILURE) ;  
            } 

            parse_string(f, &artiste, &taille, *retourChariot) ;

            /* consomme le retour chariot */
            if ( parse_char(f, *retourChariot) == 0 ) {
                printf("format fichier invalide (biblio/charge_n_entrees@retourChariot)\n") ;
		        fprintf(stderr, "format fichier invalide (biblio/charge_n_entrees@retourChariot)\n") ;
		        exit(EXIT_FAILURE) ; 
            }

            /* Ajout du morceau `a la biblio */
            insere(biblio, num, titre, artiste) ;  // ins`ere le morceau dans la biblio
        }
    }

    fclose(f) ; 
    
    if (f != NULL) {
        printf("Echec de fermeture du fichier (biblio/charge_n_entrees)\n") ;
		fprintf(stderr, "Echec de fermeture du fichier (biblio/charge_n_entrees)\n") ;
		exit(EXIT_FAILURE) ;       
    }

    return biblio ; 
}



