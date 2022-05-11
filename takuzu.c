//
// Created by Mikhaïl on 4/6/2022.
//

// todo saisie sécurisée de ligne et de colonne
#include "takuzu.h"

int nb_vies = 3;
int nb_coups_incorrects = 0;

int **creer_matrice(int taille) {
    int **matrice = (int **) malloc(taille * sizeof(int *));

    for (int i = 0; i < taille; i++) {
        matrice[i] = (int *) malloc(taille * sizeof(int));
    }
    return matrice;
}

void remplir_matrice4(int **matrice) {
    int solution[4][4] = {{1, 0, 0, 1},
                          {1, 0, 1, 0},
                          {1, 0, 1, 0},
                          {1, 0, 1, 0}};
    /*    1, 0, 0, 1
          1, 0, 1, 0
          1, 0, 1, 0
          1, 0, 1, 0*/

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrice[i][j] = solution[i][j];
        }
    }
}

void remplir_matrice8(int **matrice) {
    int solution[8][8] = {{1, 0, 1, 1, 0, 1, 0, 0},
                          {1, 0, 1, 0, 1, 0, 0, 1},
                          {0, 1, 0, 1, 1, 0, 1, 0},
                          {0, 1, 0, 1, 0, 1, 1, 0},
                          {1, 0, 1, 0, 0, 1, 0, 1},
                          {0, 1, 0, 0, 1, 0, 1, 1},
                          {0, 0, 1, 1, 0, 1, 1, 0},
                          {1, 1, 0, 0, 1, 0, 0, 1}};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrice[i][j] = solution[i][j];
        }
    }
}

int **creer_masque(int taille) {
    int limite_uns, i, j; // Le nombre maximum de valeurs affichées par ligne
    // Il faut qu'il n'y ait pas trop de 1 ou de 0 dans chaque ligne
    srand(time(NULL));

    limite_uns = taille * 2 / 3; // Le nombre maximal de valeurs affichées

    int **masque;

    masque = (int **) malloc(taille * sizeof(int *)); // Initialisation du tableau 2D
    for (i = 0; i < taille; i++) {
        masque[i] = malloc(taille * sizeof(int));
    }
    for (i = 0; i < taille; i++) {
        int nb_uns;

        do { // On veut au moins une valeur affichée par ligne

            nb_uns = 0; // Variable qui compte le nombre de 1 présent dans la ligne actuelle
            for (j = 0; j < taille; j++) {

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
    return masque;
}


void afficher_tab(int *tab[16], int taille) { // Fonction de test pour afficher un tableau
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void afficher_grille(int *grille[16], int *masque[16], int taille) { // Fonction qui applique le masque à la grille
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (masque[i][j] == 1) {
                printf(" %d ", grille[i][j]);
            } else {
                printf(" - ");
            }
        }
        printf("\n");
    }
}

CASE saisir_case(int taille) {
    CASE case_joueur;
    do {
        printf("Quelle ligne ?\n");
        fflush(stdin);
        scanf("%d", &case_joueur.ligne);
        case_joueur.ligne--;

        printf("Quelle colonne ?\n");
        fflush(stdin);
        scanf("%d", &case_joueur.colonne);
        case_joueur.colonne--;

        printf("Quel chiffre ?\n");
        fflush(stdin);
        scanf("%d", &case_joueur.chiffre);

    } while (case_joueur.colonne < 0 || case_joueur.colonne > taille - 1
             || case_joueur.ligne < 0 || case_joueur.ligne > taille - 1
             || (case_joueur.chiffre != 0 && case_joueur.chiffre != 1));
    return case_joueur;
}

int verifier_haut(int *grille[16], int *masque[16], CASE case_joueur) {
    if (masque[case_joueur.ligne - 1][case_joueur.colonne] == 1 &&
        masque[case_joueur.ligne - 2][case_joueur.colonne] == 1) {  // Si Les cases sont affichées


        if (grille[case_joueur.ligne - 1][case_joueur.colonne] == case_joueur.chiffre &&
            grille[case_joueur.ligne - 2][case_joueur.colonne] ==
            case_joueur.chiffre) {  // Et sont les mêmes que le chiffre utilisateur
            return 0; // Le test est invalide
        }
    }
    return 1;
}


int verifier_bas(int *grille[16], int *masque[16], CASE case_joueur) {
    if (masque[case_joueur.ligne + 1][case_joueur.colonne] == 1 &&
        masque[case_joueur.ligne + 2][case_joueur.colonne] == 1) {

        if (grille[case_joueur.ligne + 1][case_joueur.colonne] == case_joueur.chiffre &&
            grille[case_joueur.ligne + 2][case_joueur.colonne] == case_joueur.chiffre) {
            return 0;
        }
    }
    return 1;
}

int verifier_droite(int *grille[16], int *masque[16], CASE case_joueur) {
    if (masque[case_joueur.ligne][case_joueur.colonne + 1] == 1 &&
        masque[case_joueur.ligne][case_joueur.colonne + 2] == 1) {

        if (grille[case_joueur.ligne][case_joueur.colonne + 1] == case_joueur.chiffre &&
            grille[case_joueur.ligne][case_joueur.colonne + 2] == case_joueur.chiffre) {
            return 0;
        }
    }

    return 1;
}

int verifier_gauche(int *grille[16], int *masque[16], CASE case_joueur) {

    if (masque[case_joueur.ligne][case_joueur.colonne - 1] == 1 &&
        masque[case_joueur.ligne][case_joueur.colonne - 2] == 1) {

        if (grille[case_joueur.ligne][case_joueur.colonne - 1] == case_joueur.chiffre &&
            grille[case_joueur.ligne][case_joueur.colonne - 2] == case_joueur.chiffre) {
            return 0;
        }

    }
    return 1; // vérification effectuée

}

int coup_valide(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    if (masque[case_joueur.ligne][case_joueur.colonne] == 1)
        // Si la valeur est déjà affichée
    {
        printf("La valeur que vous avez saisie est deja affichee\n");
        case_joueur = saisir_case(taille);
    }

    int nb_verif = 0;
    int verif_ok = 0;
    // vérifier que les deux chiffres (haut/bas/gauche/droite) set en bas soient affichés

    // Vérification du haut

    if (case_joueur.ligne >= 2) {
        nb_verif++;
        if (verifier_haut(grille, masque, case_joueur)) {
            verif_ok++;
        } //en cas de coup invalide : donner un indice à l'utilisateur
        else
            printf("Les deux cases du haut sont deja des %d\n", case_joueur.chiffre);
    }

    // Vérification du bas
    if (case_joueur.ligne < taille - 2) {
        nb_verif++;
        if (verifier_bas(grille, masque, case_joueur)) {
            verif_ok++;
        } else
            printf("Les deux cases du bas sont deja des %d\n", case_joueur.chiffre);
    }

    // Vérification de la gauche
    if (case_joueur.colonne >= 2) {
        nb_verif++;
        if (verifier_gauche(grille, masque, case_joueur)) {
            verif_ok++;
        } else
            printf("Les deux cases de gauche sont deja des %d\n", case_joueur.chiffre);
    }
    // Vérification de la droite
    if (case_joueur.colonne < taille - 2) {
        nb_verif++;
        if (verifier_droite(grille, masque, case_joueur)) {
            verif_ok++;

        } else {
            printf("Les deux cases de droite sont deja des %d\n", case_joueur.chiffre);
        }
    }

    if (verif_ok ==
        nb_verif) { // S'il y a autant de vérifications validées que le nombre de vérifications, elles sont toutes validées
        return 1;
    } else {
        return 0; // Le coup est invalide
    }
}

int afficher_indice(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    char reponse_indice;
    printf("Voulez-vous un indice ? o\\n : \n");
    scanf(" %c", &reponse_indice);

    if (reponse_indice == 'o') {

        // Les deux premiers indices sont déjà implémentés dans coup_valide
        if (case_joueur.ligne > 0 && case_joueur.ligne < taille) { // Si la ligne n'est pas au bord de la grille
            if (grille[case_joueur.ligne - 1][case_joueur.colonne] == grille[case_joueur.ligne + 1][case_joueur.colonne]) { // On compare les lignes du dessus et du dessous
                printf("Il y a la meme valeur au dessus et en dessous\n");
            }
        }
        if (case_joueur.colonne > 0 && case_joueur.colonne < taille) {
            if (grille[case_joueur.ligne][case_joueur.colonne - 1] == grille[case_joueur.ligne][case_joueur.colonne + 1]) {
                printf("Il y a la meme valeur a droite et a gauche\n");
            }
        }
    }
}

void coup_correct(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    if (coup_valide(grille, masque, case_joueur, taille)) { // Si le coup est valide
        if (grille[case_joueur.ligne][case_joueur.colonne] == case_joueur.chiffre) { // Lorsque le joueur mets le bon chiffre
            masque[case_joueur.ligne][case_joueur.colonne] = 1; // On modifie le masque pour afficher cette valeur
            printf("Votre coup est correct !\n");
        }
        if (grille[case_joueur.ligne][case_joueur.colonne] != case_joueur.chiffre) { // Si le coup n'est pas correct
            printf("Coup valide mais incorrect !\n");
            nb_coups_incorrects++;
        }
    } else { // Si le coup n'est pas valide
        printf("Ce coup n'est pas valide\n");
        nb_vies--;
    }
}

int jouer(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    char choix_rejouer;
    while (nb_vies > 0 && tableau_rempli(grille, masque, taille) == 0) {
        printf("Vous avez %d vies\n", nb_vies);
        afficher_grille(grille, masque, taille);
        case_joueur = saisir_case(taille);
        coup_correct(grille, masque, case_joueur, taille);
        if (nb_coups_incorrects == 3) {
            nb_coups_incorrects = 0;
            afficher_indice(grille, masque, case_joueur, taille);
        }
    }

    if (nb_vies > 0) { // Si le joueur à gagné
        printf("Bravo, vous avez resolu le Takuzu !\n");
    }
    while (nb_vies == 0) {

        do {
            printf("Vous avez epuise vos 3 vies\n");
            printf("Souhaitez-vous rejouer ? :\no : oui\nn : non\n");
            fflush(stdin);
            scanf(" %c", choix_rejouer);
        } while (choix_rejouer != 'o' && choix_rejouer != 'n'); // todo corriger la saisie sécurisée
    }
    if (choix_rejouer == 'o')
        return 1;
    return 0;
}

int **saisir_masque(int taille) {
    int i, j, **masque;
    int nb_val_affichees;
    masque = (int **) malloc(taille * sizeof(int *)); // Initialisation du tableau 2D
    for (i = 0; i < taille; i++) {
        masque[i] = malloc(taille * sizeof(int));
    }
    do {
        nb_val_affichees = 0;
        for (i = 0; i < taille; i++) {
            for (j = 0; j < taille; j++) {
                do {
                    printf("Entrez une valeur pour la ligne %d et colonne %d:\n", i + 1, j + 1);
                    scanf("%d", &masque[i][j]);
                    if (masque[i][j] == 1) {
                        nb_val_affichees++;
                    }
                } while (masque[i][j] != 1 && masque[i][j] != 0);
            }
        }
        if (nb_val_affichees == 16) {
            printf("Votre masque est rempli uniquement de 1\nRessaisissez votre masque\n");
        }
    } while (nb_val_affichees == 16);
    return masque;
}

int tableau_rempli(int *masque[16], int taille) {
    int nb_val_affichees = 0;
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (masque[i][j] == 1) {
                nb_val_affichees++;
            }
        }
    }

    if (nb_val_affichees == taille * taille) {
        return 1;
    } else {
        return 0;
    }
}