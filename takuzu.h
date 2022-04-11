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

void creer_masque(int masque[16][16], int taille);

void afficher_tab(int tab[16][16], int taille);

void afficher_grille(int tab[16][16], int taille, int masque[16][16]);

        int coup_valide(int grille[16][16], int ligne, int colonne);

int coup_correct(int grille[16][16], int ligne, int colonne);

#endif //TAKUZU_MIKHAIL_YILIZIRE_TAKUZU_H
