#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stdprof.h"	
#include "type.h"
#include "grille.h"
#include "action.h"
#include "afficher.h"

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

