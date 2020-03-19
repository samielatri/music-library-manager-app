#ifndef _BIBLIO_H_
#define _BIBLIO_H_

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CellMorceau CellMorceau;

typedef struct Biblio Biblio;

/* Alloue et retourne l'adresse d'une nouvelle Biblio */
Biblio *nouvelle_biblio(void);

/* Charge au plus n morceaux par lecture du fichier nom_fichier */
Biblio *charge_n_entrees(const char *nom_fichier, int n);

/*Libère intégralement la biblio */
void libere_biblio(Biblio *B);

/* Insère le morceau dont les caractéristiques sont num, titre et artiste*/
void insere(Biblio *B, int num, char *titre, char *artiste);

/*Affiche les morceaux contenus dans la Biblio */
void affiche(Biblio *B);

/*Affiche un morceau */
void afficheMorceau(CellMorceau *);

/* Retourne une nouvelle biblio contenant les morceaux de B sans doublons */
Biblio *uniques(Biblio *B);

/* Retourne le seul morceau de numéro num */
CellMorceau * rechercheParNum(Biblio *B, int num);

/* Retourne un morceau de titre titre */
CellMorceau *rechercheParTitre(Biblio *B, char * titre);

/* Retourne une nouvelle biblio qui contient uniquement les morceaux de l'artiste artiste */
Biblio *extraireMorceauxDe(Biblio *B, char * artiste);

/* Réalise l'insertion d'un nouveau morceau (de titre titre et dont le nom de l'interprète est artiste).
   Attention le numéro associé au morceau doit être différent de celui de tous les morceaux 
   présents dans B */
void insereSansNum(Biblio *B, char *titre, char *artiste);

/* Supprime le morceau de numéro num de la Biblio B */
int supprimeMorceau(Biblio *B, int num);

#endif
