#ifndef GRILLE_H
#define GRILLE_H

#include "type.h"

void init_grille(Grille *grille, int x, int y);

void free_grille(Grille *grille);

void creation_grille (Grille* grille, char* ligne);

bool est_fini(Grille* grille, char joueur);

#endif