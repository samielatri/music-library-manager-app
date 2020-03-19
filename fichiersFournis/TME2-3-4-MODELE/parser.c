/* parser.c */

#include "parser.h"

int end_of_file(FILE *f) {
  int c = fgetc(f);
  ungetc(c, f);
  return (c == EOF);
}

int parse_int(FILE *f, int *n) {
  int lus = fscanf(f, "%d", n);
  return (lus > 0);
}

int parse_char(FILE *f, char c) {
  return (fgetc(f) == c);
}

int parse_string(FILE *f, char **buffer, int *taille_buffer, char delim) {
  size_t cap;
  size_t lus = getdelim(buffer, &cap, delim, f);
  if((*buffer)[lus - 1] != delim) {
    return 0;
  }
  *taille_buffer = (int)cap;
  (*buffer)[lus - 1] = '\0';
  ungetc(delim, f);
  return 1;
}
