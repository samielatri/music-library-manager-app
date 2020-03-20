#include "biblio_tabdyn.h"

Biblio *nouvelle_biblio(void) {
   Biblio *B = (Biblio *)malloc(sizeof(Biblio));
   B->capacite = 10;
   B->T = malloc(sizeof(CellMorceau) * 10);
   B->nE = 0;

   int i;
   for (i = 0; i < B->capacite; i++) {
      (B->T[i].artiste) = NULL;
      (B->T[i].titre) = NULL;
   }

   return B;
}

void libere_biblio(Biblio *B) {
   free(B->T);
   free(B);
}


void insere(Biblio *B, int num, char *titre, char *artiste) {
   CellMorceau *tab = B->T;
   int index = 0;

   if (B->nE == B->capacite) {
      B->T = realloc(B->T, sizeof(CellMorceau) * (B->capacite * 2));
      B->capacite = B->capacite * 2;

      for (index = B->capacite/2; index < B->capacite; index++) {
         (B->T[index].artiste) = NULL;
         (B->T[index].titre) = NULL;
      }
      insere(B, num, titre, artiste);
   }
   
   else {
      while (B->T[index].artiste != NULL) {
         index++;
      }
      B->T[index].num = num;
      B->T[index].titre = strdup(titre);
      B->T[index].artiste = strdup(artiste);
      B->nE++;
   }
}

void afficheMorceau(CellMorceau *cell) {
	if (cell->artiste != NULL) printf("*T* %8d * %-32.32s * %-32.32s *T*\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B) {
	int index = 0;
   CellMorceau *liste = B->T;
	while (index < B->capacite) {
		afficheMorceau(liste + index);
		index++;
	}
}

int compte_occurences(Biblio *B, char *titre, char *artiste) {
   int occ = 0;
   int i;
   for (i = 0; i < B->capacite; i++) {
      CellMorceau c = B->T[i];
      if (c.titre != NULL) {
         if ((strcmp(c.titre, titre) == 0) && (strcmp(c.artiste, artiste) == 0)) occ++;
      }
   }
   return occ;
}

Biblio *uniques (Biblio *B) {
   Biblio *nB = nouvelle_biblio();

   int i;
   for (i = 0; i < B->capacite; i++) {
      CellMorceau c = B->T[i];
      if (c.titre != NULL && c.artiste != NULL) {
         if (compte_occurences(B, c.titre, c.artiste) == 1) insere(nB, nB->nE, c.titre, c.artiste);
      } 
   }

   return nB;
}

CellMorceau *rechercheParNum(Biblio *B, int num) {
   CellMorceau *c = B->T;
   int i;
   for (i = 0; i < B->nE; i++) {
      if (c[i].num == num) return (c + i);
   }

   return NULL;
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
   CellMorceau *c = B->T;
   int i;
   for (i = 0; i < B->nE; i++) {
      if (strcmp(c[i].titre, titre) == 0) return (c + i);
   }

   return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
   Biblio *nB = nouvelle_biblio();
   int i;

   for (i = 0; i < B->capacite; i++) {
      CellMorceau c = B->T[i];
      if (c.artiste != NULL) {
         if (strcmp(c.artiste, artiste) == 0) insere(nB, nB->nE, strdup(c.titre), strdup(c.artiste));
      }
   }

   return nB;
}

void insereSansNum(Biblio *B, char *titre, char *artiste) {
   insere(B, B->nE, titre, artiste);
}


int supprimeMorceau(Biblio *B, int num) {
   if (B->nE == 0) return 0;

   int deleted = 0;
   int i;
   
   while (i < B->capacite && deleted == 0) {
      CellMorceau c = B->T[i];
      if (c.titre != NULL) {
         if (c.num == num) {
            B->T[i].num = 0;
            B->T[i].titre = NULL;
            B->T[i].artiste = NULL;
            B->nE--;
            deleted = 1;
         }
      }
      i++;
   }

   if (deleted == 0) return 0;
   else return 1;
}




































