//
// Created by Mikhaïl on 4/6/2022.
//

#ifndef TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H
#define TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"

/*
 *
 * 1 0 0 1
 * 1 0 1 0
 * 0 1 1 0
 * 0 1 0 1
 *
 * */

typedef struct {
    int ligne;
    int colonne;
    int chiffre;
} CASE;

typedef enum {
    joueur,
    ordinateur
} UTILISATEUR;

int **creer_matrice(int taille);

void remplir_matrice4(int **matrice);

void remplir_matrice8(int **matrice);

int **creer_masque(int taille);

void afficher_tab(int *tab[16], int taille);

void afficher_grille(int *grille[16], int *masque[16], int taille);

CASE saisir_case(int taille);

int coup_valide(int *grille[16], int *masque[16], CASE case_joueur, int taille);

void coup_correct(int *grille[16], int *masque[16], CASE case_joueur, int tailles);

int verifier_haut(int *grille[16], int *masque[16], CASE case_joueur);

int verifier_bas(int *grille[16], int *masque[16], CASE case_joueur, int taille);

int verifier_droite(int *grille[16], int *masque[16], CASE case_joueur, int taille);

int verifier_gauche(int *grille[16], int *masque[16], CASE case_joueur);

int afficher_indice(int *grille[16], int *masque[16], int taille, int utilisateur);

int jouer(int *grille[16], int *masque[16], CASE case_joueur, int taille);

int **saisir_masque(int taille);

int tableau_rempli(int *masque[16], int taille);

int rejouer();

void generer_ligne(int taille, int *ligne);

int ** generer_grille(int taille);

int indice_suite_deux_cases(int *grille[16], int *masque[16], int taille);
int indice_suite_deux_cases(int *grille[16], int *masque[16], int taille, int utilisateur);

int indice_case_encadree(int *grille[16], int *masque[16], int taille, int utilisateur);

int lignes_identiques(int *grille[16], int *masque[16], int taille, int utilisateur);

// PARTIE 2

int jeu_ordinateur(int **grille, int **masque,int taille);

// PARTIE 3

void generer_ligne(int *ligne, int taille);

void generer_grille(int **grille, int taille);

#endif //TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H
