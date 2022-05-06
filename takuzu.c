//
// Created by Mikhaïl on 4/6/2022.
//

#include "takuzu.h"

int nb_vies = 3;

void creer_masque(int *masque[16], int taille) {
    int limite_uns, i, j; // Le nombre maximum de valeurs affichées par ligne
    // Il faut qu'il n'y ait pas trop de 1 ou de 0 dans chaque ligne
    srand(time(NULL));

    masque = (int **) malloc(taille * sizeof(int *)); // Initialisation du tableau 2D
    for (i = 0; i < taille; i++) {
        masque[i] = malloc(taille * sizeof(int));
    }
    for (i = 0; i < taille; i++) {
        int nb_uns;

        do { // On veut au moins une valeur affichée par ligne

            limite_uns = taille * 2 / 3; // Le nombre maximal de valeurs affichées
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
}


void afficher_tab(int tab[16][16], int taille) { // Fonction de test pour afficher un tableau
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void afficher_grille(int grille[16][16], int *masque[16], int taille) { // Fonction qui applique le masque à la grille
    printf("afficher_grille : ok\n");
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (masque[i][j] == 1) {
                printf("%d ", grille[i][j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
}

CASE saisir_case() {
    CASE case_joueur;
    do {
        printf("Quelle ligne ?\n");
        scanf("%d", &case_joueur.ligne);
        case_joueur.ligne--;
        printf("Quelle colonne ?\n");
        scanf("%d", &case_joueur.colonne);
        case_joueur.colonne--;
        printf("Quel chiffre ?\n");
        scanf("%d", &case_joueur.chiffre);

    } while (case_joueur.colonne < 0 || case_joueur.colonne > 3
             || case_joueur.ligne < 0 || case_joueur.ligne > 3
             || (case_joueur.chiffre != 0 && case_joueur.chiffre != 1));
    return case_joueur;
}

int verifier_haut(int grille[16][16], int *masque[16], CASE case_joueur) {
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


int verifier_bas(int grille[16][16], int *masque[16], CASE case_joueur) {
    if (masque[case_joueur.ligne + 1][case_joueur.colonne] == 1 &&
        masque[case_joueur.ligne + 2][case_joueur.colonne] == 1) {

        if (grille[case_joueur.ligne + 1][case_joueur.colonne] == case_joueur.chiffre &&
            grille[case_joueur.ligne + 2][case_joueur.colonne] == case_joueur.chiffre) {
            return 0;
        }
    }
    return 1;
}

int verifier_droite(int grille[16][16], int *masque[16], CASE case_joueur) {
    if (masque[case_joueur.ligne][case_joueur.colonne + 1] == 1 &&
        masque[case_joueur.ligne][case_joueur.colonne + 2] == 1) {

        if (grille[case_joueur.ligne][case_joueur.colonne + 1] == case_joueur.chiffre &&
            grille[case_joueur.ligne][case_joueur.colonne + 2] == case_joueur.chiffre) {
            return 0;
        }
    }

    return 1;
}

int verifier_gauche(int grille[16][16], int *masque[16], CASE case_joueur) {

    if (masque[case_joueur.ligne][case_joueur.colonne - 1] == 1 &&
        masque[case_joueur.ligne][case_joueur.colonne - 2] == 1) {

        if (grille[case_joueur.ligne][case_joueur.colonne - 1] == case_joueur.chiffre &&
            grille[case_joueur.ligne][case_joueur.colonne - 2] == case_joueur.chiffre) {
            return 0;
        }

    }
    return 1; // vérification pas effectuée

}

int coup_valide(int grille[16][16], int *masque[16], CASE case_joueur, int taille) {
    if (masque[case_joueur.ligne][case_joueur.colonne] == 1)
        // Si la valeur est déjà affichée
    {
        printf("La valeur que vous avez saisie n'est pas valide\n");
        saisir_case();
    }

    int nb_verif = 0;
    int verif_ok = 0;
    // vérifier que les deux chiffres (haut/bas/gauche/droite) set en bas soient affichés

    // Vérification du haut

    if (case_joueur.ligne >= 2) {
        nb_verif++;
        if (verifier_haut(grille, masque, case_joueur)) {
            verif_ok++;
        }
    }

    // Vérification du bas
    if (case_joueur.ligne <= taille - 2) {
        nb_verif++;
        if (verifier_bas(grille, masque, case_joueur)) {
            verif_ok++;
        }
    }

    // Vérification de la gauche
    if (case_joueur.colonne >= 2) {
        nb_verif++;
        if (verifier_gauche(grille, masque, case_joueur)) {
            verif_ok++;
        }
    }
    // Vérification de la droite
    if (case_joueur.colonne < taille - 2) {
        nb_verif++;
        if (verifier_droite(grille, masque, case_joueur)) {
            verif_ok++;
        }
    }

    if (verif_ok ==
        nb_verif) { // S'il y a autant de vérifications validées que le nombre de vérifications, elles sont toutes validées
        return 1;
    } else {
        return 0; // Le coup est invalide
    }
}

/*int afficher_indice(int grille[4][4], int masque[4][4], CASE case_joueur, int taille) {

}*/ // todo Finir les indices


void coup_correct(int grille[16][16], int *masque[16], CASE case_joueur, int taille) {

    if (coup_valide(grille, masque, case_joueur, taille)) { // Si le coup est valide
        if (grille[case_joueur.ligne][case_joueur.colonne] ==
            case_joueur.chiffre) { // Lorsque le joueur mets le bon chiffre
            masque[case_joueur.ligne][case_joueur.colonne] = 1; // On modifie le masque pour afficher cette valeur
            printf("Votre coup est correct !\n");
        } else { // Si le coup n'est pas correct
            printf("Coup valide mais incorrect\n");
        }
    } else { // Si le coup n'est pas valide
        printf("Ce coup n'est pas valide\n");
        nb_vies--;
    }
}

void jouer(int grille[4][4], int masque[4][4], CASE case_joueur, int taille) {

    int rejouer = 1;
    while (nb_vies > 0 && rejouer == 1) {
        printf("Vous avez %d vies\n", nb_vies);
        afficher_grille(grille, masque, taille);
        case_joueur = saisir_case();
        coup_correct(grille, masque, case_joueur, taille);


        int nb_val_afficheees = 0;
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                printf("masque : ok%d", masque[i][j] );
                if (masque[i][j] == 1) {
                    nb_val_afficheees++;
                }
            }
        }

        if (nb_val_afficheees == 16) { // Si toutes les valeurs du masque sont affichées
            rejouer = 0; // Plus besoin de rejouer
        }
    }

    if (nb_vies > 0) { // Si le joueur à gagné


        printf("Bravo vous avez resolu le Takuzu ! \n");
    } else {
        printf("Ah zut, c'est dommage d'avoir perdu si vite ☺");
    }
}

int **saisir_masque(int *masque[16], int taille) {
    int i, j;
    masque = (int **) malloc(taille * sizeof(int *)); // Initialisation du tableau 2D
    for (i = 0; i < taille; i++) {
        masque[i] = malloc(taille * sizeof(int));
    }
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            do {
                printf("Entrez une valeur :\n");
                scanf("%d", &masque[i][j]);
            } while (masque[i][j] != 1 && masque[i][j] != 0);
        }
    }
    return masque;
}