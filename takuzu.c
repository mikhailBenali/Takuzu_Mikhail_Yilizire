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

            limite_uns = taille * 2 / 3; // Le nombre maximal de valeurs affichées
            nb_uns = 0; // Variable qui compte le nombre de 1 présent dans la ligne actuelle

            for (int j = 0; j < taille; j++) {

                if (nb_uns < limite_uns &&
                    rand() % 2 == 1) { // Si la limite de 1 n'est pas atteinte et que le rand donne 1
                    masque[i][j] = 1;
                    nb_uns++;
                } else {
                    masque[i][j] = 0;
                }
            }
        } while (nb_uns < taille * 1 / 3);
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

void afficher_grille(int tab[16][16], int masque[16][16], int taille) { // Fonction qui applique le masque à la grille
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

CASE valider_case(int grille[16][16], int ligne, int colonne) {
    CASE case_joueur;
    printf("Quelle ligne ? ");
    scanf("%d", case_joueur.ligne);
    printf("Quelle colonne ? ");
    scanf("%d", case_joueur.colonne);
    return case_joueur;
}

int coup_valide(int grille[16][16], int masque[16][16], CASE case_joueur) {
    if (masque[case_joueur.ligne][case_joueur.colonne] == 1)
        // Si la valeur est déjà affichée
    {
        printf("La valeur que vous avez saisie n'est pas valide\n");
        saisir_case(grille);
    }
    /*
     * vérifier que les deux chiffres en haut et en bas soient affichés
     * vérifier que les deux chiffres en bas et en bas soient affichés
     * vérifier que les deux chiffres à droite et en bas soient affichés
     * vérifier que les deux chiffres à gauche et en bas soient affichés
     *
     *
     *
     *
     *
     */

    //if ()

    return 1; // Le coup est valide
}


int coup_correct(int grille[16][16], int masque[16][16], CASE case_joueur) {
    coup_valide(grille, masque, case_joueur);
    if (grille[case_joueur.ligne][case_joueur.colonne] == case_joueur.chiffre) {
        return 1;
    } else {
        return 0;
    }
}