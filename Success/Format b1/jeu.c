#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stdprof.h"	
#include "type.h"
#include "grille.h"
#include "action.h"
#include "afficher.h"
#include "jeu.h"

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

/* Pour main : Case 1 */
void action_J1 (Grille* grille, char* ligne, Bateau* bateau1, bool* tour_joueur1, bool peut_placer, bool peut_tirer){    
  int x, y;
  char commande;
  bool placement_reussi, tir_reussi;

  if (*tour_joueur1) {
    /* S'il rencontre ce type de ligne : J1 P (ou T) 1:2 */
    if (sscanf(ligne, " %*s %c %d:%d", &commande, &x, &y) == 3){
      /* Placement d'un bateau A*/
      if (commande == 'P') {
        if (peut_placer){
          printf("Placement d'un bateau à la position (%d,%d) par le joueur 1\n", x, y);
          placement_reussi = placer_bateau(grille, x, y, 'A');
          /* Taille bateau */
          bateau1->debut.x = x;
          bateau1->debut.y = y;
          bateau1->fin.x = x;
          bateau1->fin.y = y;
          bateau1->taille = abs(bateau1->fin.x - bateau1->debut.x) + abs(bateau1->fin.y - bateau1->debut.y) + 1;
          printf("Taille du bateau : %d\n", bateau1->taille);
          if (!placement_reussi) {
            printf("Erreur lors du placement du bateau\n");
            exit(2);
          }
          *tour_joueur1 = false;
        }
        else {
          printf("Le jeu a commence, plus possible de placer de bateau.\n");
          exit(4);
        }
      }
      /* Tire sur la grille */
      else {
        if (peut_tirer){
          printf("Tir du joueur 1 à la position (%d,%d)\n", x, y);
          tir_reussi = coord_valide(grille, x, y);
          if (!tir_reussi) {
            printf("Erreur lors du tir\n");
            exit(7);
          }
          else {
            tirer(grille, x, y, 'A');
          }
          *tour_joueur1 = false;
        }
        else {
          printf("Le jeu n'a pas commence, pas possible de tirer.\n");
          exit(6);
        }
      }
    }
  }
  else {
    printf("C'est au tour du joueur 2\n");
    exit(5);
  }
}

/* Pour main : Case 2 */
void action_J2 (Grille* grille, char* ligne, Bateau* bateau1, bool* tour_joueur1, bool peut_placer, bool peut_tirer){
    int x, y;
    char commande;
    bool placement_reussi, tir_reussi;

  if (!*tour_joueur1) {
    /* S'il rencontre ce type de ligne : J1 P (ou T) 1:2 */
    if (sscanf(ligne, " %*s %c %d:%d", &commande, &x, &y) == 3){
      /* Placement d'un bateau A*/
      if (commande == 'P') {
        if (peut_placer){
          printf("Placement d'un bateau à la position (%d,%d) par le joueur 1\n", x, y);
          placement_reussi = placer_bateau(grille, x, y, 'B');
          /* Taille bateau */
          bateau1->debut.x = x;
          bateau1->debut.y = y;
          bateau1->fin.x = x;
          bateau1->fin.y = y;
          bateau1->taille = abs(bateau1->fin.x - bateau1->debut.x) + abs(bateau1->fin.y - bateau1->debut.y) + 1;
          printf("Taille du bateau : %d\n", bateau1->taille);
          if (!placement_reussi) {
            printf("Erreur lors du placement du bateau\n");
            exit(2);
          }
          *tour_joueur1 = true;
        }
        else {
          printf("Le jeu a commence, plus possible de placer de bateau.\n");
          exit(4);
        }
      }
      /* Tire sur la grille */
      else {
        if (peut_tirer){
          printf("Tir du joueur 2 à la position (%d,%d)\n", x, y);
          tir_reussi = coord_valide(grille, x, y);
          if (!tir_reussi) {
            printf("Erreur lors du tir\n");
            exit(7);
          }
          else {
            tirer(grille, x, y, 'B');
          }
          *tour_joueur1 = true;
        }
        else {
          printf("Le jeu n'a pas commence, pas possible de tirer.\n");
          exit(6);
        }
      }
    }
  }
  else {
    printf("C'est au tour du joueur 1\n");
    exit(5);
  }
}

/* Pour main : Case 3 */  
void affiche(Grille* grille) {
    printf("Affichage de la grille\n");
    afficher_grille(grille);
}

/* Pour main : Case 4 */
void joue(bool* peut_placer, bool* peut_tirer) {
    printf("Le jeu commence, interdiction de placer plus de bateau\n");
    *peut_placer = false;
    *peut_tirer = true;
}
