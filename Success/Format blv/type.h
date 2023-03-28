#ifndef TYPE_H
#define TYPE_H

#include <stdbool.h>

/* Enum */
typedef enum {
  MER,
  BATEAU_A,
  BATEAU_B,
  RATE,
  TOUCHE
} Etat;

typedef enum { 
  Projet, 
  J1, 
  J2, 
  Afficher, 
  Jouer 
} Commande;

/* Struct */ 
typedef struct {
  int x; 
  int y; 
} Coordonnee;

typedef struct {
  Etat etat_c;
  struct Bateau *bateau;
} Case;

typedef struct {
  int ligne;
  int colonne;
  Case **cases;
  bool initialisee; 
} Grille;

typedef struct {
  Coordonnee debut; 
  Coordonnee fin; 
  int cases_touchees;
  Etat etat_b;
  char joueur;
  int taille;
} Bateau;

#endif