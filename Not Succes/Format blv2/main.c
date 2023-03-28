#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>	
#include "stdprof.h"
#include "type.h"
#include "grille.h"
#include "action.h"
#include "afficher.h"

int main(int argc, char* argv[]) {
  bool peut_tirer = false;
  bool tour_joueur1 = true;
  bool peut_placer = true;
  char type[10];
  FILE* fichier;
  int num_ligne = 0;
  int cmd;
  Grille grille;
  int x1, x2, x, y1, y2, y, lignes, colonnes;
  char ligne[100];
  char commande;

  if(argc == 2 && strcmp(argv[1], "-i") == 0) {
    printf("Mode interactif : Joueur humain va jouer contre l'IA\n");
    printf("Entrez la taille de la grille (lignexcolonne): ");
    scanf("%dx%d", &lignes, &colonnes);
    init_grille(&grille, lignes, colonnes);

  	/* Placement de bateaux */
    while (peut_placer) {
      /* Humain */
      if (tour_joueur1) { 
        printf("Joueur 1, entrez la position de votre bateau (format : x:y ou x:y-x ou x1:y-x2:y) ou jouer pour commencer à jouer : ");
        if (scanf("%d-%d:%d", &x1, &x2, &y) == 3) {
          if (placer_bateau_horizontal(&grille, x1, x2, y, 'A')){
            
            tour_joueur1 = false;
          } else {
            printf("Erreur de placement\n");
            exit(2);
          }
        } else if (scanf("%d:%d-%d", &x, &y1, &y2) == 3) {
          if (placer_bateau_vertical(&grille, x, y1, y2, 'A')){
            tour_joueur1 = false;
          } else {
            printf("Erreur de placement\n");
            exit(2);
          }
        } else if (scanf("%d:%d", &x, &y) == 2) {
          if (placer_bateau_unique(&grille, x, y, 'A')){
            tour_joueur1 = false;
          } else {
            printf("Erreur de placement\n");
            exit(2);
          }
        } else if (scanf("%s", commande)==1){
          if (strcmp(commande,"jouer")==0) {
            peut_placer = false;
            tour_joueur1 = true;
            printf("Le jeu commence, vous pouvez maintenant tirer\n");
          } else if (strcmp(commande,"afficher")==0) {
            afficher_grille(&grille);
          }
        } else {
          printf("Erreur, veuillez réessayer\n");
          continue;
        }
      } else {
      /* IA */
        placer_bateau_ia(&grille, &tour_joueur1);
      }
    }

    /* Tir */
    while (peut_tirer && !est_fini(&grille, 'A' && !est_fini(&grille, 'B'))) {
      /* Humain */
      if (tour_joueur1) {
        printf("Entrez la position de tir (x:y) : ");
        if (scanf("%d:%d", &x, &y) == 2) {
          if (tirer(&grille, x, y, 'A')) {
            printf("Tir de l'Humain à la position (%d,%d)\n", x, y);
            tour_joueur1 = false;
          } else {
            printf("Erreur de tir\n");
            exit(7);
          }
        } else if (scanf("%s", commande)){
          if (strcmp(commande,"afficher")==0) {
            afficher_grille(&grille);
          } else {
            printf("Erreur, veuillez réessayer\n");
            continue;
          }
        } else {
          printf("Erreur, veuillez réessayer\n");
          continue;
        }
      } else {
        /* IA */
        tir_ia(&grille, &tour_joueur1);
      }
    }

    if (est_fini(&grille, 'A')) {
      printf("Le joueur 2 a gagné\n");
    } else if (est_fini(&grille, 'B')) {
      printf("Le joueur 1 a gagné\n");
    }

  } else {
    printf("Mode fichier : lecture de %s\n", argv[1]);

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
                if (!tir_joueur(&grille, x, y, 'A', &peut_tirer)) {
                  exit(7);
                }
                tour_joueur1 = false;
              }
            } else {
              printf("C'est au tour du joueur 2\n");
              exit(5);
            }
          }
          break; 
        /* Joueur 2 */
        case 2 :
          if (tour_joueur1 == false) {
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
                if (!tir_joueur(&grille, x, y, 'A', &peut_tirer)) {
                  exit(7);
                }
                tour_joueur1 = false;
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

    printf("Fin du fichier\n");
  }
  /* Free la grille */
  free_grille(&grille);

  return 0;
}
