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
                          {0, 1, 1, 0},
                          {0, 1, 0, 1}};

    /*1, 0, 0, 1
      1, 0, 1, 0
      0, 1, 1, 0
      0, 1, 0, 1*/

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
                printf(" * ");
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
    //les règles du jeu ne sont pas respectées
    if (case_joueur.ligne > 1
        && masque[case_joueur.ligne - 1][case_joueur.colonne] == 1
        && masque[case_joueur.ligne - 2][case_joueur.colonne] == 1
        && grille[case_joueur.ligne - 1][case_joueur.colonne] == case_joueur.chiffre
        && grille[case_joueur.ligne - 2][case_joueur.colonne] == case_joueur.chiffre) {
        return 0;
    }
    //les règles du jeu sont respectées
    return 1;
}

int verifier_bas(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    //les règles du jeu ne sont pas respectées
    if (case_joueur.ligne < taille - 2
        && masque[case_joueur.ligne + 1][case_joueur.colonne] == 1
        && masque[case_joueur.ligne + 2][case_joueur.colonne] == 1
        && grille[case_joueur.ligne + 1][case_joueur.colonne] == case_joueur.chiffre
        && grille[case_joueur.ligne + 2][case_joueur.colonne] == case_joueur.chiffre) {
        return 0;
    }
    //les règles du jeu sont respectées
    return 1;
}

int verifier_droite(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    //les règles du jeu ne sont pas respectées
    if (case_joueur.colonne < taille - 2
        && masque[case_joueur.ligne][case_joueur.colonne + 1] == 1
        && masque[case_joueur.ligne][case_joueur.colonne + 2] == 1
        && grille[case_joueur.ligne][case_joueur.colonne + 1] == case_joueur.chiffre
        && grille[case_joueur.ligne][case_joueur.colonne + 2] == case_joueur.chiffre) {
        return 0;
    }
    //les règles du jeu sont respectées
    return 1;
}

int verifier_gauche(int *grille[16], int *masque[16], CASE case_joueur) {
    //les règles du jeu ne sont pas respectées
    if (case_joueur.colonne > 1
        && masque[case_joueur.ligne][case_joueur.colonne - 1] == 1
        && masque[case_joueur.ligne][case_joueur.colonne - 2] == 1
        && grille[case_joueur.ligne][case_joueur.colonne - 1] == case_joueur.chiffre
        && grille[case_joueur.ligne][case_joueur.colonne - 2] == case_joueur.chiffre) {
        return 0;
    }
    //les règles du jeu sont respectées
    return 1;

}

int coup_valide(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    if (masque[case_joueur.ligne][case_joueur.colonne] == 1)
        // Si la valeur est déjà affichée
    {
        printf("La valeur que vous avez saisie est deja affichee\n");
        afficher_grille(grille, masque, taille);
        case_joueur = saisir_case(taille);
    }

    int nb_verif = 0;
    int verif_ok = 0;
    // vérifier si les deux chiffres (haut/bas/gauche/droite) sont affichés

    // Vérification du haut

    if (case_joueur.ligne >= 2) {
        nb_verif++;
        if (verifier_haut(grille, masque, case_joueur)) {
            verif_ok++;
        }
    }

    // Vérification du bas
    if (case_joueur.ligne < taille - 2) {
        nb_verif++;
        if (verifier_bas(grille, masque, case_joueur, taille)) {
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
        if (verifier_droite(grille, masque, case_joueur, taille)) {
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


int afficher_indice(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    char reponse_indice;
    int retour_indice;
    printf("Voulez-vous un indice ? o\\n : \n");
    scanf(" %c", &reponse_indice);

    if (reponse_indice == 'o') {

        retour_indice = indice_suite_deux_cases(grille, masque, taille);

        if (retour_indice == 0) { // Si aucune suite de deux cases n'est présente
            retour_indice = indice_case_encadree(grille, masque, taille);

            if (retour_indice == 0) { // Si aucune valeur ne peut être mise entre deux cases identiques
                retour_indice = indice_lignes_identiques(grille, masque, taille);

                if (retour_indice == 0) { // Si aucune ligne n'est identique avec deux trous dedans
                    printf("Nous ne pouvons plus vous donner d'indice...");
                    return 0;
                }
            }
        }
        return 1;
    }
}

int indice_suite_deux_cases(int *grille[16], int *masque[16], int taille) {
    CASE case_temp = {0, 0, 0}; // Il nous faut une variable de type CASE pour les fonction de vérification

    for (int ligne = 0; ligne < taille; ligne++) {
        for (int colonne = 0; colonne < taille; colonne++) {

            case_temp.ligne = ligne;
            case_temp.colonne = colonne;

            // Vérification du haut
            if (ligne >= 2) {
                if (verifier_haut(grille, masque, case_temp)) {
                    printf("Les deux cases du haut sont déjà à cette valeur, il faut y inserer une autre.\n");
                    return 1;
                }
            }

            // Vérification du bas
            if (ligne < taille - 2) {
                if (verifier_bas(grille, masque, case_temp, taille)) {
                    printf("Les deux cases du bas sont déjà à cette valeur, il faut y inserer une autre.\n");
                    return 2;
                }
            }

            // Vérification de la gauche
            if (colonne >= 2) {
                if (verifier_gauche(grille, masque, case_temp)) {
                    printf("Les deux cases de la gauche sont déjà à cette valeur, il faut y inserer une autre.\n");
                    return 3;
                }
            }

            // Vérification de la droite
            if (colonne < taille - 2) {
                if (verifier_droite(grille, masque, case_temp, taille)) {
                    printf("Les deux cases de la droite sont déjà à cette valeur, il faut y inserer une autre.\n");
                    return 4;
                }
            }
        }
    }
    return 0; // Si aucune vérification n'a aboutie
}

int indice_case_encadree(int *grille[16], int *masque[16], int taille) {
    CASE case_temp = {0, 0, 0}; // Il nous faut une variable de type CASE pour les fonctions de vérification

    for (int ligne = 0; ligne < taille; ligne++) {
        for (int colonne = 0; colonne < taille; colonne++) {

            case_temp.ligne = ligne;
            case_temp.colonne = colonne;

            if (case_temp.ligne > 0 && case_temp.ligne < taille) { // Si la ligne n'est pas au bord de la grille
                if (grille[case_temp.ligne - 1][case_temp.colonne] ==
                    grille[case_temp.ligne + 1][case_temp.colonne]) { // On compare les lignes du dessus et du dessous
                    printf("Il y a la meme valeur au dessus et en dessous\nVous devez mettre l'autre valeur\n");
                    return 1;
                }
            }
            if (case_temp.colonne > 0 && case_temp.colonne < taille) {
                if (grille[case_temp.ligne][case_temp.colonne - 1] ==
                    grille[case_temp.ligne][case_temp.colonne + 1]) {
                    printf("Il y a la meme valeur a droite et a gauche\nVous devez mettre l'autre valeur\n");
                    return 2;
                }
            }
        }
    }
    return 0;

}

int indice_lignes_identiques(int *grille[16], int *masque[16], int taille) {
    int *ligne = (int *) malloc(taille * sizeof(int));
    int nb_val_affichees = 0;
    for (int i = 0; i < taille; i++) { // À chaque ligne

        for (int j = 0; j < taille; j++) {
            if (masque[i][j] == 1) {
                nb_val_affichees++; // On compte le nombre de valeurs affichées sur cette ligne
            }
        }
        if (nb_val_affichees == taille) { // Si la ligne est pleine
            for (int val = 0; val < taille; val++) {
                ligne[val] = grille[i][val]; // On copie la ligne de la grille
            }
        }
        // todo à compléter
    }
}


void coup_correct(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    if (coup_valide(grille, masque, case_joueur, taille)) { // Si le coup est valide
        if (grille[case_joueur.ligne][case_joueur.colonne] == case_joueur.chiffre) { // Lorsque le joueur mets le bon chiffre
            masque[case_joueur.ligne][case_joueur.colonne] = 1; // On modifie le masque pour afficher cette valeur
            printf("Votre coup est correct !\n");
            nb_coups_incorrects = 0;
        }
        if (grille[case_joueur.ligne][case_joueur.colonne] != case_joueur.chiffre) { // Si le coup n'est pas correct
            printf("Votre coup n'est pas correct !\n");
            nb_coups_incorrects++;
        }
    } else { // Si le coup n'est pas valide
        printf("Vous ne respectez pas les regles du jeu\n");
        nb_vies--;
    }
}

int jouer(int *grille[16], int *masque[16], CASE case_joueur, int taille) {
    int replay = 0; // rejouer est déjà un nom de fonction
    nb_vies = 3;
    while (nb_vies > 0 && tableau_rempli(masque, taille) == 0) {
        if (nb_vies == 1) {
            printf("Vous avez %d vie\n", nb_vies);
        } else {
            printf("Vous avez %d vies\n", nb_vies);
        }
        afficher_grille(grille, masque, taille); // afficher la grille à compléter à chaque fois que l'utilisateur saisit une valeur
        case_joueur = saisir_case(taille);
        coup_correct(grille, masque, case_joueur, taille);
        if (nb_coups_incorrects == 3) {
            nb_coups_incorrects = 0;
            afficher_indice(grille, masque, case_joueur, taille);
        }
    }
    if (nb_vies > 0) { // Si le joueur à gagné
        printf("Bravo, vous avez resolu le Takuzu !\n");
        replay = rejouer();
    } else {
        printf("Vous avez epuise vos 3 vies\n");
        replay = rejouer();
    }
}

int **saisir_masque(int taille) {
    int i, j, **masque;
    char saisie_case;
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
                    fflush(stdin);
                    scanf(" %c", &saisie_case);
                } while ((int) saisie_case < '0' || (int) saisie_case > '1');
                masque[i][j] = (int) saisie_case - '0'; // On convertit le chiffre en code ascii et on lui retire 48 (code du '0') afin d'obtenir le nombre en int
                if (masque[i][j] == 1) {
                    nb_val_affichees++;
                }
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

int rejouer() {
    char choix_rejouer = 'n'; // Valeur par défaut
    do {
        printf("Souhaitez-vous rejouer ? :\no : oui\nn : non\n");
        fflush(stdin);
        scanf(" %c", &choix_rejouer);
    } while (choix_rejouer != 'o' && choix_rejouer != 'n');
    if (choix_rejouer == 'o') {
        return 1;
    } else {
        return 0;
    }
}

// PARTIE 3

int exces_repetitions(int *tab, int taille) {
    int i, bool_repetition = 0; //la ligne ne contient pas trois fois la même valeur
    printf("exces_repetitions\n");
    i = 0;
    while (i < taille - 2 && bool_repetition == 0) {
        if (tab[i] == tab[i + 1] && (tab[i + 1] == tab[i + 2])) { bool_repetition = 1; }
        else { i++; }
    }
    i = 1;
    while (i < taille - 3 && bool_repetition == 0) {
        if (tab[i] == tab[i + 1] && (tab[i + 1] == tab[i + 2])) { bool_repetition = 1; }
        else { i++; }
    }
    printf("bool_repetition=%d\n", bool_repetition);
    return bool_repetition;
}

void generer_ligne(int taille, int *ligne) { //corriger nb répétitions
    int i;
    srand(time(NULL));
    int nb_binaire = 0;
    for (i = 0; i < taille; i++) {
        ligne[i] = (int *) malloc(taille * sizeof(int)); //prévoir de l'espace mémoire pour la ligne
    }
    if (taille == 4); // une ligne : un nombre binaire entre 0 et 15
    {
        // le nombre binaire de chaque ligne : maximum 15/4

        do {
            nb_binaire = 0;
            for (i = 0; i < taille; i++) {
                ligne[i] = rand() % 2;
                printf("valeur = %d\n", ligne[i]);

                if (ligne[i] == 1) {
                    nb_binaire++;
                    printf("nb_binaire=%d\n", nb_binaire);
                }
            }
        } while (nb_binaire > 15 / 4 || exces_repetitions(ligne, taille)); //éviter qu'un même chiffre s'affiche 3 fois de suite ou que le nombre binaire dépasse 15/4
        printf("nb_binaire=%d\n", nb_binaire);

        if (taille == 8) // une ligne : un nombre binaire entre 0 et 255/8
        {// le nombre binaire de chaque ligne : maximum 255/8
            do {
                nb_binaire = 0;
                for (i = 0; i < taille; i++) {
                    ligne[i] = rand() % 2;
                    printf("valeur = %d\n", ligne[i]);

                    if (ligne[i] == 1) {
                        nb_binaire++;
                        printf("nb_binaire=%d\n", nb_binaire);
                    }
                }
            } while (nb_binaire > 255 / 8 || exces_repetitions(ligne, taille)); //éviter qu'un même chiffre s'affiche 3 fois de suite ou que le nombre binaire dépasse 15/4
        }
    }
    for (int i = 0; i < taille; i++) {
        printf("%d ", ligne[i]);
    }
    printf("\n");
}

int **generer_grille(int taille) {
    int i, **grille = (int **) malloc(taille * sizeof(int *)); //prévoir de l'espace mémoire
    for (i = 0; i < taille; i++) {
        grille[i] = (int *) malloc(taille * sizeof(int)); //prévoir de l'espace mémoire
    }

    for (i = 0; i < taille; i++) {
        generer_ligne(taille, grille[i]);
    }
    printf("grille generee automatiquement\n");
    afficher_tab(grille, taille);

    return grille;
}