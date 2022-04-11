//
// Created by Mikhaïl on 4/6/2022.
//

#include "takuzu.h"

void creer_masque(int masque[16][16], int taille) {
    int limite_uns; // Le nombre maximum de valeurs affichées par ligne
    // Il faut qu'il n'y ait pas trop de 1 ou de 0 dans chaque ligne
    srand(time(NULL));
    for (int i = 0; i < taille; i++) {
        int nb_uns;

        do { // On veut au moins une valeur affichée par ligne

            limite_uns = taille / 2 + 1; // Le nombre maximal de valeurs affichées est taille/2 + 1
            nb_uns = 0; // Variable qui compte le nombre de 1 présents dans la ligne actuelle

            for (int j = 0; j < taille; j++) {

                if (nb_uns < limite_uns && rand() % 2 == 1) { // Si la limite de 1 n'est pas atteinte et que le rand donne 1
                    masque[i][j] = 1;
                    nb_uns++;
                } else {
                    masque[i][j] = 0;
                }
            }
        } while (nb_uns < taille / 2);
    }
}


void afficher_tab(int tab[16][16], int taille) { // Fonction de test pour afficher un tableau
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void afficher_grille(int tab[16][16], int taille, int masque[16][16]) { // Fonction qui applique lee masque à la grille
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (masque[i][j] == 1) {
                printf("%d ", tab[i][j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
}

int coup_valide(int grille[16][16], int ligne, int colonne) {

}