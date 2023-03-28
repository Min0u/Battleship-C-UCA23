#ifndef JOUEUR_H
#define JOUEUR_H

#include "type.h"
#include <stdbool.h>

void creation_grille (Grille* grille, char* ligne);

void action_J1 (Grille* grille, char* ligne, Bateau* bateau1, bool* tour_joueur1, bool peut_placer, bool peut_tirer);

void action_J2 (Grille* grille, char* ligne, Bateau* bateau1, bool* tour_joueur1, bool peut_placer, bool peut_tirer);

void affiche(Grille* grille);

void joue(bool* peut_placer, bool* peut_tirer);

#endif