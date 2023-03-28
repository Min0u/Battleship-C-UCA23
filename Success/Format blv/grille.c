#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>	
#include "stdprof.h"
#include "type.h"
#include "grille.h"

/* Initialise une grille */
void init_grille(Grille *grille, int x, int y) {
  int i, j;

  grille->ligne = y;
  grille->colonne = x;
  grille->cases = malloc_prof(y * sizeof(Case*));

  if (grille->cases == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire pour les cases de la grille");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < y; i++) {
    grille->cases[i] = malloc_prof(x * sizeof(Case));
    if (grille->cases[i] == NULL) {
      fprintf(stderr, "Erreur d'allocation de mémoire pour la ligne %d de la grille", i);
      exit(EXIT_FAILURE);
    }
    for (j = 0; j < x; j++) {
      grille->cases[i][j].bateau = NULL;
      grille->cases[i][j].etat_c = MER;
    }
  }

  grille->initialisee = true;  
}

/* Free la grille */
void free_grille(Grille *grille) {
  int i, j;

  if (grille->initialisee) { 
    for (i = 0; i < grille->ligne; i++) {
      for (j = 0; j < grille->colonne; j++) {
        if (grille->cases[i][j].bateau != NULL) {
          free_prof(grille->cases[i][j].bateau);
        }
      }
      free_prof(grille->cases[i]);
    }
    free_prof(grille->cases);
    grille->initialisee = false;
  }
}
