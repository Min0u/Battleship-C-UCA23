#include <stdio.h> 
#include <stdlib.h>
#include "stdprof.h"
#include <string.h>
#include <stdbool.h>	
#include "type.h"
#include "grille.h"
#include "action.h"
#include "afficher.h"
#include "jeu.h"

int main(int argc, char* argv[]) {
  bool peut_tirer = false;
  bool peut_placer = true;
  bool tour_joueur1 = true;
  char type[10];
  char ligne[100];  
  int num_ligne = 0;
  int cmd;
  FILE* fichier;
  Grille grille;
  Bateau bateau1;

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

    printf("Ligne %d: commande '%s'\n", num_ligne, type);
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
        action_J1(&grille, ligne, &bateau1, &tour_joueur1, peut_placer, peut_tirer);
        break; 
      /* Joueur 2 */
      case 2 :
        action_J2(&grille, ligne, &bateau1, &tour_joueur1, peut_placer, peut_tirer);
        break;
      /* Affichage de la grille */
      case 3:
        affiche(&grille);
        break;
      /* Le jeu commence, interdiction de placer plus de bateau */
      case 4:
        joue(&peut_placer, &peut_tirer);
        break;
      default:
        printf("Commande inconnue\n");
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