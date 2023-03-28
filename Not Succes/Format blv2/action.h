#ifndef ACTION_H
#define ACTION_H

#include "type.h"

bool placer_bateau(Grille* grille, int x, int y, char joueur);

bool coord_valide (Grille* grille, int x, int y);

bool tirer(Grille* grille, int x, int y, char joueur);

bool placer_bateau_horizontal(Grille* grille, int x1, int x2, int y, char joueur);

bool placer_bateau_vertical(Grille* grille, int x, int y1, int y2, char joueur);

bool placer_bateau_unique(Grille* grille, int x, int y, char joueur);

bool tir_joueur(Grille* grille, int x, int y, char joueur, bool peut_tirer);

void joue(bool* peut_placer, bool* peut_tirer);

void placer_bateau_ia(Grille *grille, bool* tour_joueur1);

void tirer_ia(Grille* grille, bool* tour_joueur1);

#endif