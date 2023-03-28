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

typedef struct {
    bool tir_reussi;
    bool peut_placer;
    bool peut_tirer;
    bool placement_reussi;
    bool tour_joueur1;
    char type[10];
    char commande;
    char ligne[100];  
    int num_ligne;
    int cmd;
    int x, y;
    FILE* fichier;
    Grille grille;
    Bateau bateau1;
} Game;


#endif