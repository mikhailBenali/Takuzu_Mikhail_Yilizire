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

void creer_masque(int masque[16][16], int taille);

void afficher_tab(int tab[16][16], int taille);

void afficher_grille(int tab[16][16], int masque[16][16], int taille);

int valeur_choisie(int val);

CASE saisir_case(int grille[16][16]);

int coup_valide(int grille[16][16], int masque[16][16], CASE case_joueur, int taille);

int coup_correct(int grille[16][16], int masque[16][16], CASE case_joueur, int tailles);

int verifier_haut(int grille[16][16], int masque[16][16], CASE case_joueur);

int verifier_bas(int grille[16][16], int masque[16], CASE case_joueur);

int verifier_droite(int grille[16][16], int masque[16], CASE case_joueur);

int verifier_gauche(int grille[16][16], int masque[16], CASE case_joueur);

#endif //TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H
