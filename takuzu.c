//
// Created by Mikhaïl on 4/6/2022.
//

#include "takuzu.h"

void creer_masque(int masque[16][16], int taille) {
    srand(rand());
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            masque[i][j] = rand() % 2;
        }
    }
}


void afficher_tab(int tab[16][16], int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}