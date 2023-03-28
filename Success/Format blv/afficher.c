#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>	
#include "stdprof.h"
#include "type.h"
#include "afficher.h"

/* Affiche une grille */
void afficher_grille(Grille *grille) {
  int lignes = grille->ligne;
  int colonnes = grille->colonne;
  int dc, dl, n, m;

  /* Numéros de colonnes */
  printf("    ");
  m = 0;
  for (dc = 0; dc < colonnes; dc++) {
    printf("  %d   ", m);
    m++;
  }
  puts("");

  /* Sépare lignes */
  printf("   +"); 
  for (dc = 0; dc < colonnes; dc++) {
    printf("-----+");
  }
  puts("");

  /* Affiche la grille */
  n = 0;
  for (dl = 0; dl < lignes; dl++) {
    printf("%d  ", n);
    for (dc = 0; dc < colonnes; dc++) {
      Etat etat_2 = grille->cases[dl][dc].etat_c;
      if (etat_2 == MER) { 
        printf("|  ~  ");
      } 
      else if (etat_2 == RATE) { 
        printf("|  O  ");
      } 
      else if (etat_2 == BATEAU_A) {
        printf("|  A  ");
      } 
      else if (etat_2 == BATEAU_B) {
        printf("|  B  ");
      } 
      else if (etat_2 == TOUCHE) {
        printf("|  X  ");
      } 
    } 
    printf("|");
    puts("");
  /* Sépare lignes */
  printf("   +"); 
  for (dc = 0; dc < colonnes; dc++) {
    printf("-----+");
  }
  puts("");
  n++;
  }
}
