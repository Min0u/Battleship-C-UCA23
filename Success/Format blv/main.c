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

int main(int argc, char* argv[]) {
  bool peut_tirer = false;
  bool tour_joueur1 = true;
  bool peut_placer = true;
  char type[10];
  FILE* fichier;
  int num_ligne = 0;
  int cmd;
  Grille grille;
  int x1, x2, x, y1, y2, y;
  char ligne[100];
  char commande;

  /* Vérifie le nombre d'arguments */
  if (argc != 2) {
    return 1;
  }

  /* Ouvre le fichier */
  fichier = fopen(argv[1], "r");
  if (fichier == NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    exit(0);
    return 1;
  }

  /* Lit le fichier */
  while (fgets(ligne, sizeof ligne, fichier) != NULL) {
    num_ligne++;

    if (sscanf(ligne, "#%*[^\n]") == 1) {
      continue;
    }

    if (sscanf(ligne, "%9s", type) != 1) {
      continue;
    }

    printf("Ligne %d: Commande '%s'\n", num_ligne, type);
    cmd = -1;

    /* Premier mot de la ligne possible */
    if (strcmp(type, "Projet") == 0) {
      cmd = 0;
    }
    else if (strcmp(type, "J1") == 0) {
      cmd = 1;
    }
    else if (strcmp(type, "J2") == 0) {
      cmd = 2;
    }    
    else if (strcmp(type, "Afficher") == 0) {
      cmd = 3;
    }
    else if (strcmp(type, "Jouer") == 0) {
      cmd = 4;
    }

    switch (cmd) {
      /* Initialisation de la grille */
      case 0:
        creation_grille(&grille, ligne);
        break;
      /* Joueur 1 */
      case 1:
        if (tour_joueur1 == true) {
          /* S'il rencontre ce type de ligne : J1 P 3:2-5 */
          if (sscanf(ligne, "%*s %c %d:%d-%d", &commande, &x, &y1, &y2) == 4){
            if (peut_placer == true) {
              if(!placer_bateau_vertical(&grille, x, y1, y2, 'A')){
                exit(2);
              }
              tour_joueur1 = false;
            }
            else {
              printf("Le jeu a commence, plus possible de placer de bateau.\n");
              exit(4);
            }
          }
          /* S'il rencontre ce type de ligne : J1 P 1-2:3 */
          else if (sscanf(ligne, "%*s %c %d-%d:%d", &commande, &x1, &x2, &y) == 4){
            if (peut_placer == true) {
              if(!placer_bateau_horizontal(&grille, x1, x2, y, 'A')){
                exit(2);
              }
              tour_joueur1 = false;
            }
            else {
              printf("Le jeu a commence, plus possible de placer de bateau.\n");
              exit(4);
            }
          }
           /* S'il rencontre ce type de ligne : J1 P (ou T) 1:2 */
          else if (sscanf(ligne, "%*s %c %d:%d", &commande, &x, &y) == 3){
            /* Placement d'un bateau A */
            if (commande == 'P') {
              if (peut_placer == true){
                if(!placer_bateau_unique(&grille, x, y, 'A')){
                  exit(2);
                }
                tour_joueur1 = false;
              }
            }
            /* Tire sur la grille */
            else {
              if (!tir_joueur(&grille, x, y, 'A')) {
                exit(7);
              }
              tour_joueur1 = false;
            }
          }
        }
        else {
          printf("C'est au tour du joueur 2\n");
          exit(5);
        }
        break; 
      /* Joueur 2 */
      case 2 :
        if (tour_joueur1 == false) {
          /* S'il rencontre ce type de ligne : J1 P 3:2-5 */
          if (sscanf(ligne, "%*s %c %d:%d-%d", &commande, &x, &y1, &y2) == 4){
            if (peut_placer == true) {
              if(!placer_bateau_vertical(&grille, x, y1, y2, 'B')){
                exit(2);
              }
              tour_joueur1 = true;
            }
            else {
              printf("Le jeu a commence, plus possible de placer de bateau.\n");
              exit(4);
            }
          }
          /* S'il rencontre ce type de ligne : J1 P 1-2:3 */
          else if (sscanf(ligne, "%*s %c %d-%d:%d", &commande, &x1, &x2, &y) == 4){
            if (peut_placer == true) {
              if(!placer_bateau_horizontal(&grille, x1, x2, y, 'B')){
                exit(2);
              }
              tour_joueur1 = true;
            }
            else {
              printf("Le jeu a commence, plus possible de placer de bateau.\n");
              exit(4);
            }
          }
           /* S'il rencontre ce type de ligne : J1 P (ou T) 1:2 */
          else if (sscanf(ligne, "%*s %c %d:%d", &commande, &x, &y) == 3){
            /* Placement d'un bateau A */
            if (commande == 'P') {
              if (peut_placer == true){
                if(!placer_bateau_unique(&grille, x, y, 'B')){
                  exit(2);
                }
                tour_joueur1 = true;
              }
            }
            /* Tire sur la grille */
            else {
              if (!tir_joueur(&grille, x, y, 'B')) {
                exit(7);
              }
              tour_joueur1 = true;
            }
          }
        }
        else {
          printf("C'est au tour du joueur 1\n");
          exit(5);
        }
        break; 
      /* Affichage de la grille */
      case 3:
        affiche(&grille);
        break;
      /* Le jeu commence, interdiction de placer plus de bateau */
      case 4:
        joue(&peut_placer,&peut_tirer);
        break;
      default:
        printf("commande inconnue\n");
        exit(3);
        break;
      }
    }

  /* Ferme le fichier */
  fclose(fichier);

  /* Free la grille */
  free_grille(&grille);

  return 0;
}