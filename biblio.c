#include "biblio.h"

Biblio *charge_n_entrees(const char *nom_fichier, int n) {
    FILE *fichier = fopen(nom_fichier, "r")  ;
    Biblio *biblioResultat = nouvelle_biblio()  ;
    int compteurLignes = 0 ; // nb lignes a lire

    while ((end_of_file(fichier) == 0) && (compteurLignes < n)) {
        int num = 0 ; 
        int buffeurTitle, buffeurArtiste = MAXBUFF ; //256
        char *title = (char*)malloc(sizeof(char) * MAXI1) ;
        char *artist = (char*)malloc(sizeof(char) * MAXI1) ;

        parse_int(fichier, &num) ;
        parse_char(fichier, '\t') ;

        parse_string(fichier, &title, &buffeurTitle, '\t') ;
        parse_char(fichier, '\t') ;

        parse_string(fichier, &artist, &buffeurArtiste, '\n') ;
        parse_char(fichier, '\n') ;

        insere(biblioResultat, num, title, artist) ;

        ++ compteurLignes  ;
    }
    // ancienne solution : boucle for et if ...
    fclose(fichier) ;

    return biblioResultat ;
}
