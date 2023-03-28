#ifndef ACTION_H
#define ACTION_H

#include "type.h"

bool placer_bateau(Grille* grille, int x, int y, char joueur);

bool coord_valide (Grille* grille, int x, int y);

bool tirer(Grille* grille, int x, int y, char joueur);

#endif