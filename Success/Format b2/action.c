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