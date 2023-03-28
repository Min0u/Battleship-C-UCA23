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

  grille->ligne = x;
  grille->colonne = y;
  grille->cases = malloc_prof(x * sizeof(Case*));

  if (grille->cases == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire pour les cases de la grille");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < x; i++) {
    grille->cases[i] = malloc_prof(y * sizeof(Case));
    if (grille->cases[i] == NULL) {
      fprintf(stderr, "Erreur d'allocation de mémoire pour la ligne %d de la grille", i);
      exit(EXIT_FAILURE);
    }
    for (j = 0; j < y; j++) {
      grille->cases[i][j].bateau = NULL;
      grille->cases[i][j].etat_c = MER;
    }
  }
}

/* Free la grille */
void free_grille(Grille *grille) {
  int i, j;
  bool initialisee = grille->initialisee;

  if (initialisee) { 
    for (i = 0; i < grille->ligne; i++) {
      for (j = 0; j < grille->colonne; j++) {
        if (grille->cases[i][j].bateau != NULL) {
          free_prof(grille->cases[i][j].bateau);
        }
      }
      free_prof(grille->cases[i]);
    }
    free_prof(grille->cases);
    initialisee = false;
  }
}

/* Pour main : Case 0 */ 
void creation_grille (Grille* grille, char* ligne) {
    int lignes, colonnes;
    if (sscanf(ligne, "%*s %d x %d", &lignes, &colonnes) == 2) {
        printf("Initialisation de la grille de %d lignes et %d colonnes\n", lignes, colonnes);
        init_grille(grille, lignes, colonnes);
    } else {
        printf("Erreur lors de la lecture de la taille de la grille\n");
        exit(1);
    }
}

/* Soit  */
bool est_fini(Grille* grille, char joueur) {
    int i, j;

    for (i = 0; i < grille->ligne; i++) {
        for (j = 0; j < grille->colonne; j++) {
            if (grille->cases[i][j].bateau != NULL && grille->cases[i][j].etat_c == (joueur == 'A') ? BATEAU_A : BATEAU_B && grille->cases[i][j].etat_c != TOUCHE) {
                return false;
            }
        }
    }
    return true;
}