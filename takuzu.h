//
// Created by Mikhaïl on 4/6/2022.
//

#ifndef TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H
#define TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

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

int **creer_matrice(int taille);

void remplir_matrice4(int **matrice);

void remplir_matrice8(int **matrice);

int **creer_masque(int taille);

void afficher_tab(int *tab[16], int taille);

void afficher_grille(int *grille[16], int *masque[16], int taille);

int valeur_choisie(int val);

CASE saisir_case(int taille);

int coup_valide(int *grille[16], int *masque[16], CASE case_joueur, int taille);

void coup_correct(int *grille[16], int *masque[16], CASE case_joueur, int tailles);

int verifier_haut(int *grille[16], int *masque[16], CASE case_joueur);

int verifier_bas(int *grille[16], int *masque[16], CASE case_joueur, int taille);

int verifier_droite(int *grille[16], int *masque[16], CASE case_joueur, int taille);

int verifier_gauche(int *grille[16], int *masque[16], CASE case_joueur);

int afficher_indice(int *grille[16], int *masque[16], CASE case_joueur, int taille);

int jouer(int *grille[16], int *masque[16], CASE case_joueur, int taille);

int **saisir_masque(int taille);

int tableau_rempli(int *masque[16], int taille);

int rejouer();

#endif //TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H
