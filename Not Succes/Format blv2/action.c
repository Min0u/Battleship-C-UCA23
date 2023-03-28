#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stdprof.h"	
#include "type.h"
#include "action.h"

/* Place un bateau sur la grille */
bool placer_bateau(Grille* grille, int x, int y, char joueur) {
  if (y < 0 || y >= grille->ligne || x < 0 || x >= grille->colonne) {
    return false;
  }

  if (grille->cases[y][x].etat_c != MER) {
    return false;
  }

  grille->cases[y][x].etat_c = (joueur == 'A') ? BATEAU_A : BATEAU_B;
  return true;
}

bool coord_valide (Grille* grille, int x, int y) {
  if (y < 0 || y >= grille->ligne || x < 0 || x >= grille->colonne) {
    return false;
  }

  if (grille->cases[y][x].etat_c == MER || grille->cases[y][x].etat_c == BATEAU_A || grille->cases[y][x].etat_c == BATEAU_B) {
    return true;
  }

  return false;
}

/* Tire sur une case de la grille */
bool tirer(Grille* grille, int x, int y, char joueur) {
  Etat etat_1;

  if (y < 0 || y >= grille->ligne || x < 0 || x >= grille->colonne) {
    return false;
  }

  etat_1 = grille->cases[y][x].etat_c;

  if (etat_1 == BATEAU_A || etat_1 == BATEAU_B) {
    grille->cases[y][x].etat_c = TOUCHE;
    return true;
  } 
  else if (etat_1 == MER) {
    grille->cases[y][x].etat_c = RATE;
    return false;
  } 
  else {
    return false;
  }
}

/* Pour main : Case 1 et Case 2 */
bool placer_bateau_horizontal(Grille* grille, int x1, int x2, int y, char joueur) {
    int i;

    int taille = abs(x2 - x1) + 1;
    printf("Placement d'un bateau horizontal de taille %d de la position (%d,%d) à la position (%d,%d) par le joueur %c\n", taille, x1, y, x2, y,joueur);
    for (i = x1; i <= x2; i++) {
        if(!placer_bateau(grille, i, y,joueur)){
            printf("Erreur lors du placement du bateau\n");
            return false;
        }
    }
    return true;
}

bool placer_bateau_vertical(Grille* grille, int x, int y1, int y2, char joueur) {
    int j;

    int taille = abs(y2 - y1) + 1;
    printf("Placement d'un bateau vertical de taille %d de la position (%d,%d) à la position (%d,%d) par le joueur %c\n", taille, x, y1, x, y2,joueur);
    for (j = y1; j <= y2; j++) {
        if(!placer_bateau(grille, x, j,joueur)){
            printf("Erreur lors du placement du bateau\n");
            return false;
        }
    }
    return true;
}

bool placer_bateau_unique(Grille* grille, int x, int y, char joueur) {
    printf("Placement d'un bateau à la position (%d,%d) par le joueur %c\n", x, y,joueur);
    return placer_bateau(grille, x, y,joueur);
}

/* lecture de fichier : Tir pour main */
bool tir_joueur(Grille* grille, int x, int y, char joueur, bool peut_tirer) {
    if (peut_tirer) {
        printf("Tir du joueur %c à la position (%d,%d)\n", joueur, x, y);
        if (!coord_valide(grille, x, y)) {
            printf("Erreur lors du tir\n");
            return false;
        } else {
            tirer(grille, x, y, joueur);
            return true;
        }
    } else {
        printf("Le jeu n'a pas commence, pas possible de tirer.\n");
        return false;
    }
}


/* Pour main : Case 4 */
void joue(bool* peut_placer, bool* peut_tirer) {
    printf("Le jeu commence, interdiction de placer plus de bateau\n");
    *peut_placer = false;
    *peut_tirer = true;
}

/* IA : PLace un bateau */
void placer_bateau_ia(Grille *grille, bool* tour_joueur1) {
    int x, y, x1, x2, y1, y2;
    int random = rand() % 3;
    if (random == 0) {
        x = rand() % grille->ligne - 1;
        y = rand() % grille->colonne - 1;
        if (!placer_bateau_unique(grille, x, y, 'B')) {
            printf("Erreur de placement\n");
            exit(2);
        }
    } else if (random == 1) {
        x1 = rand() % grille->ligne - 1;
        x2 = rand() % grille->ligne - 1;
        y = rand() % grille->colonne - 1;
        if (!placer_bateau_horizontal(grille, x1, x2, y, 'B')) {
            printf("Erreur de placement\n");
            exit(2);
        }
    } else {
        x = rand() % grille->ligne - 1;
        y1 = rand() % grille->colonne - 1;
        y2 = rand() % grille->colonne - 1;
        if (!placer_bateau_vertical(grille, x, y1, y2, 'B')) {
            printf("Erreur de placement\n");
            exit(2);
        }
    }
    *tour_joueur1 = true;
}

/* IA : Tir */
void tir_ia(Grille* grille, bool* tour_joueur1) {
  int x = rand() % grille->colonne;
  int y = rand() % grille->ligne;
  bool peut_tirer = true;
  while (peut_tirer) {
    if (tir_joueur(grille, x, y, 'B', &peut_tirer)) {
      *tour_joueur1 = true;
    } else {
      exit(7);
    }
  }
}


