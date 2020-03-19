/* parser.h */

#ifndef parser_h
#define parser_h

#include <stdio.h>

/*
 Cette bibliothèque contient quelques parsers qui permettent
 de lire un fichier selon un format avec des caract`ere de d'elimitation.
 Chaque fonction renvoie 1 si elle a r'eussi `a parser et 0 sinon.
 */

/* Renvoie 1 s'il n'y a plus de caractere `a lire, 0 sinon */
int end_of_file(FILE *f);

/* Parse un entier */
int parse_int(FILE *f, int *n);

/* Consomme c et renvoie 1. Renvoie 0 si c n'est pas le caractère suivant */
int parse_char(FILE *f, char c);

/*
 Parse une cha^ine de caract`eres jusqu'`a rencontrer le caract`ere delim.
 *buffer est allou'e par malloc s'il vaut NULL. Dans le cas contraire, il peut
^etre r'eallou'e par realloc.
 La taille du buffer allou'e est stock'ee dans taille_buffer par la fonction.
 Le caract`ere delim n'est pas consomm'e
 */
int parse_string(FILE *f, char **buffer, int *taille_buffer, char delim);

#endif /* parser_h */
