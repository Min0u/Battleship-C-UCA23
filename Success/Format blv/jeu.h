#ifndef JOUEUR_H
#define JOUEUR_H

#include "type.h"
#include <stdbool.h>

void creation_grille (Grille* grille, char* ligne);

bool placer_bateau_horizontal(Grille* grille, int x1, int x2, int y, char id);

bool placer_bateau_vertical(Grille* grille, int x, int y1, int y2, char id);

bool placer_bateau_unique(Grille* grille, int x, int y, char id);

bool tir_joueur(Grille* grille, int x, int y, char id_joueur);

void affiche(Grille* grille);

void joue(bool* peut_placer, bool* peut_tirer);

#endif