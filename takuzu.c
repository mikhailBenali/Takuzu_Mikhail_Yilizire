// Created by Mikhaïl on 4/6/2022.
//

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
        printf("Saisissez une ligne :\n");
        fflush(stdin);
        scanf("%d", &case_joueur.ligne);
        case_joueur.ligne--;

        printf("Saisissez une colonne :\n");
        fflush(stdin);
        scanf("%d", &case_joueur.colonne);
        case_joueur.colonne--;

        printf("Saisissez un chiffre :\n");
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


int afficher_indice(int *grille[16], int *masque[16], int taille, int utilisateur) {
    char reponse_indice = 'o';
    int retour_indice;
    if (utilisateur == 0) { // Si l'utilisateur est un joueur
        do {
            printf("Voulez-vous utiliser un indice ? o\\n : \n");
            scanf(" %c", &reponse_indice);
        } while (reponse_indice != 'o' && reponse_indice != 'n');
    }

    if (reponse_indice == 'o') {
        retour_indice = indice_suite_deux_cases(grille, masque, taille, utilisateur);

        if (retour_indice == 0) { // Si aucune suite de deux cases n'est présente
            retour_indice = indice_case_encadree(grille, masque, taille, utilisateur);

            if (retour_indice == 0) { // Si aucune valeur ne peut être mise entre deux cases identiques
                retour_indice = lignes_identiques(grille, masque, taille, utilisateur);

                if (retour_indice == 0) { // Si aucune ligne n'est identique avec deux trous dedans
                    return 0;
                }
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}


int indice_suite_deux_cases(int *grille[16], int *masque[16], int taille, int utilisateur) {
    CASE case_temp = {0, 0, 0}; // Il nous faut une variable de type CASE pour les fonction de vérification
    CASE case_temp2 = {0, 0, 1};

    for (int ligne = 0; ligne < taille; ligne++) {
        for (int colonne = 0; colonne < taille; colonne++) {

            case_temp.ligne = ligne;
            case_temp.colonne = colonne;

            case_temp2.ligne = ligne;
            case_temp2.colonne = colonne;

            // On doit verifier avec case_temp et case_temp2 car il faut tester avec 1 et 0 comme chiffre

            // Vérification du haut
            if (ligne >= 2) {
                if ((verifier_haut(grille, masque, case_temp) == 0 || verifier_haut(grille, masque, case_temp2) == 0) && masque[case_temp.ligne][case_temp.colonne] == 0) { // Si la case est affichée et que deux cases adjacentes sont les mêmes
                    printf("Les deux cases en haut de la case %d %d sont deja a la valeur %d, il faut y en inserer une autre\n", case_temp.ligne + 1, case_temp.colonne + 1, grille[case_temp.ligne - 1][case_temp.colonne]);
                    if (utilisateur) { // Si c'est l'ordinateur qui joue
                        masque[case_temp.ligne][case_temp.colonne] = 1; // On affiche la valeur
                        Sleep(5000);
                    }
                    return 1;
                }
            }

            // Vérification du bas
            if (ligne < taille - 2) {
                if ((verifier_bas(grille, masque, case_temp, taille) == 0 || verifier_bas(grille, masque, case_temp2, taille) == 0) && masque[case_temp.ligne][case_temp.colonne] == 0) { // Si la case est affichée et que deux cases adjacentes sont les mêmes
                    printf("Les deux cases en bas de la case %d %d sont deja a la valeur %d, il faut y en inserer une autre\n", case_temp.ligne + 1, case_temp.colonne + 1, grille[case_temp.ligne + 1][case_temp.colonne]);
                    if (utilisateur) { // Si c'est l'ordinateur qui joue
                        masque[case_temp.ligne][case_temp.colonne] = 1; // On affiche la valeur
                        Sleep(5000);
                    }
                    return 2;
                }
            }

            // Vérification de la gauche
            if (colonne >= 2) {
                if ((verifier_gauche(grille, masque, case_temp) == 0 || verifier_gauche(grille, masque, case_temp2) == 0) && masque[case_temp.ligne][case_temp.colonne] == 0) { // Si la case est affichée et que deux cases adjacentes sont les mêmes
                    printf("Les deux cases a gauche de la case %d %d sont deja a la valeur %d, il faut y en inserer une autre.\n", case_temp.ligne + 1, case_temp.colonne + 1, grille[case_temp.ligne][case_temp.colonne - 1]);
                    if (utilisateur) { // Si c'est l'ordinateur qui joue
                        masque[case_temp.ligne][case_temp.colonne] = 1; // On affiche la valeur
                        Sleep(5000);
                    }
                    return 3;
                }
            }

            // Vérification de la droite
            if (colonne < taille - 2) {
                if ((verifier_droite(grille, masque, case_temp, taille) == 0 || verifier_droite(grille, masque, case_temp2, taille) == 0) && masque[case_temp.ligne][case_temp.colonne] == 0) { // Si la case est affichée et que deux cases adjacentes sont les mêmes
                    printf("Les deux cases a droite de la case %d %d sont deja a la valeur %d, il faut y en inserer une autre.\n", case_temp.ligne + 1, case_temp.colonne + 1, grille[case_temp.ligne][case_temp.colonne + 1]);
                    if (utilisateur) { // Si c'est l'ordinateur qui joue
                        masque[case_temp.ligne][case_temp.colonne] = 1; // On affiche la valeur
                        Sleep(5000);
                    }
                    return 4;
                }
            }
        }
    }
    return 0; // Si aucune vérification n'a aboutie
}

int indice_case_encadree(int *grille[16], int *masque[16], int taille, int utilisateur) {
    CASE case_temp = {0, 0, 0}; // Il nous faut une variable de type CASE pour les fonctions de vérification

    for (int ligne = 0; ligne < taille; ligne++) {
        for (int colonne = 0; colonne < taille; colonne++) {

            case_temp.ligne = ligne;
            case_temp.colonne = colonne;

            if (case_temp.ligne > 0 && case_temp.ligne < taille - 1) { // Si la ligne n'est pas au bord de la grille
                if (grille[case_temp.ligne - 1][case_temp.colonne] == grille[case_temp.ligne + 1][case_temp.colonne] && masque[case_temp.ligne][case_temp.colonne] == 0) { // Si la case est encadrée et non affichée
                    if (masque[case_temp.ligne - 1][case_temp.colonne] == 1 && masque[case_temp.ligne + 1][case_temp.colonne] == 1) {
                        printf("Il y a la meme valeur au dessus et en dessous de la case %d %d\nIl faut y mettre une autre valeur\n", case_temp.ligne + 1, case_temp.colonne + 1);
                        if (utilisateur) { // Si c'est l'ordinateur qui joue
                            masque[case_temp.ligne][case_temp.colonne] = 1;
                            Sleep(5000);
                        }
                        return 1;
                    }
                }
            }
            if (case_temp.colonne > 0 && case_temp.colonne < taille - 1) {
                if (grille[case_temp.ligne][case_temp.colonne - 1] == grille[case_temp.ligne][case_temp.colonne + 1] && masque[case_temp.ligne][case_temp.colonne] == 0) { // Si la case est encadrée et non affichée
                    if (masque[case_temp.ligne][case_temp.colonne - 1] == 1 && masque[case_temp.ligne][case_temp.colonne + 1] == 1) {
                        printf("Il y a la meme valeur a droite et a gauche de la case %d %d\nIl faut y mettre une autre valeur\n", case_temp.ligne + 1, case_temp.colonne + 1);
                        if (utilisateur) { // Si c'est l'ordinateur qui joue
                            masque[case_temp.ligne][case_temp.colonne] = 1;
                            Sleep(5000);
                        }
                        return 2;
                    }
                }
            }
        }
    }
    return 0;

}

int lignes_identiques(int *grille[16], int *masque[16], int taille, int utilisateur) {
    /*
     * On va parcourir chaque ligne à la recherche de la première ligne pleine et stocker son indice
     * On parcourt de nouveau à partir de là toutes les lignes
     * Pour chaque colonne, on vérifie si les nombres correspondent tous
     * S'ils correspondent sauf 2, on peut donner un indice
     */

    int indice_ligne_pleine = -1, nb_val_coincidant = 0, nb_val_diff = 0, indice_ligne_identique = -1;
    int trou_un = -1, trou_deux = -1;

    for (int i = 0; i < taille; i++) { // À chaque ligne
        int nb_val_affichees = 0;
        for (int j = 0; j < taille; j++) {
            if (masque[i][j] == 1) {
                nb_val_affichees++; // On compte le nombre de valeurs affichées sur cette ligne
            }
        }
        if (nb_val_affichees == taille) { // Si la ligne est pleine
            indice_ligne_pleine = i;
            break; // On sort de la boucle pour ne pas sélectionner une autre ligne pleine
        }
    }

    // On parcourt de nouveau la grille à la recherche d'une ligne identique
    if (indice_ligne_pleine != -1) {
        for (int i = indice_ligne_pleine + 1; i < taille; ++i) {
            nb_val_coincidant = 0;
            nb_val_diff = 0;
            for (int j = 0; j < taille; ++j) {
                if (masque[i][j] == 1 && grille[indice_ligne_pleine][j] == grille[i][j]) { // Si la valeur est affichée et est la même que dans la ligne pleine
                    nb_val_coincidant++;
                } else if (masque[i][j] == 1 && grille[indice_ligne_pleine][j] != grille[i][j]) {
                    nb_val_diff++;
                }
            }
            // Si la ligne contient taille moins deux coincidences (2 trous), on note l'indice de la ligne
            if (nb_val_coincidant == taille - 2 && nb_val_diff == 0) {
                indice_ligne_identique = i;
                break;
            }
        }
    }
    if (indice_ligne_identique != -1) {
        for (int j = 0; j < taille; ++j) { // On parcourt la ligne identique
            if (masque[indice_ligne_identique][j] == 0 && trou_un == -1) { // Si la valeur n'est pas affichée dans le masque et que l'on a l'indice d'aucun trou
                trou_un = j;
            } else if (masque[indice_ligne_identique][j] == 0 && trou_un != -1) { // Si la valeur n'est pas affichée dans le masque et que l'on a l'indice du premier trou
                trou_deux = j;
            }
        }// Ayant nos deux indices, on peut proposer un indice
        printf("La ligne %d est presque identique a la %d\nElle comporte un %d a la case %d %d et un %d a la case %d %d\nOr il ne peut pas y avoir deux lignes identiques\n", indice_ligne_pleine + 1, indice_ligne_identique + 1, grille[indice_ligne_pleine][trou_un], indice_ligne_pleine + 1,
               trou_un + 1,
               grille[indice_ligne_pleine][trou_deux], indice_ligne_pleine + 1, trou_deux + 1);
        printf("Il faut mettre les valeurs opposees dans les trous\n");

        if (utilisateur) { // Si c'est l'ordinateur qui joue
            if (masque[indice_ligne_identique][trou_un] == 0) { // On met la valeur opposée dans chaque trou
                masque[indice_ligne_identique][trou_un] = 1;
            }
            if (masque[indice_ligne_identique][trou_deux] == 0) {
                masque[indice_ligne_identique][trou_deux] = 1;
            }
            Sleep(5000);
        }
        return 1; // Deux lignes ont été trouvées (presque) égales
    }
    return 0;
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
    UTILISATEUR utilisateur = joueur;
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
            afficher_indice(grille, masque, taille, utilisateur);
        }
    }
    if (nb_vies > 0) { // Si le joueur à gagné
        printf("Bravo, vous avez resolu le Takuzu !\n");
        replay = rejouer();
    } else {
        printf("Vous avez epuise vos 3 vies\n");
        replay = rejouer();
    }
    return replay;
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

                    printf("Entrez une valeur pour la ligne %d et la colonne %d :\n", i + 1, j + 1);
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

// PARTIE 2

int jeu_ordinateur(int **grille, int **masque, int taille) {
    srand(time(NULL));
    CASE case_ordinateur;
    int retour_indice, changement_case = 0;
    do {

        afficher_grille(grille, masque, taille);

        retour_indice = afficher_indice(grille, masque, taille, 1);

        if (retour_indice == 0) {
            printf("Il n'y a pas assez d'informations pour vous donner un indice... Il faut tenter quelque chose\n");
            changement_case = 0;
            do {
                // On initialise la case de l'ordinateur aléatoirement
                case_ordinateur.ligne = rand() % taille;
                case_ordinateur.colonne = rand() % taille;
                case_ordinateur.chiffre = rand() % 2;

                if (masque[case_ordinateur.ligne][case_ordinateur.colonne] == 0) { // Si la case n'est pas affichée
                    masque[case_ordinateur.ligne][case_ordinateur.colonne] = 1;
                    changement_case = 1;
                    printf("On a change la case %d %d pour y mettre un %d\n", case_ordinateur.ligne + 1, case_ordinateur.colonne + 1, grille[case_ordinateur.ligne][case_ordinateur.colonne]);
                    Sleep(5000);
                }
            } while (changement_case == 0);
        }

    } while (tableau_rempli(masque, taille) != 1);
    printf("\nVoila votre grille remplie !\n");

}

// PARTIE 3 (non terminée)

void generer_ligne(int *ligne, int taille) { // corriger nb répétitions
    int i;
    srand(time(NULL));
    int nb_binaire = 0;
    for (i = 0; i < taille; i++) {
        ligne[i] = rand() % 2;
    }
}

int somme_1(int **grille, int taille) {
    int som_tot = 0;
    int nb0 = 0;
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (grille[i][j] == 0) { nb0++; }
            som_tot += grille[i][j];
        }
    }
    printf("som_tot=%d\n", som_tot);
    if (som_tot >= taille * taille / 2)
        return 0;
    return 1;
}

int som_lignes(int **grille, int ligne, int taille) {
    int som_l = 0;
    for (int j = 0; j < taille; j++) {
        som_l += grille[ligne][j];
        printf("grille[ligne][j]=%d\n", grille[ligne][j]);
    }
    printf("som_l=%d\n", som_l);
    if (som_l > taille / 2 || som_l < 2)
        return 0;
    return 1;
}

int som_col(int **grille, int colonne, int taille) {
    int som_c = 0;
    afficher_tab(grille, taille);
    for (int i = 0; i < taille; i++) {
        som_c += grille[i][colonne];
        printf("grille[ligne][j]=%d", grille[i][colonne]);
        printf("i=%d j=%d som_l=%d\n", i, colonne, som_c);
    }
    if (som_c > taille / 2 || som_c < 2)
        return 0;
    return 1;
}

int verification_grille(int **grille, int taille) {
    int i, l = 0;
    int ligne_valide = 1; //booleen : si la ligne est valide

    /*// Vérification des deux premières lignes
    for (i = 0; i < 2; ++i) {
        for (int j = 0; j < taille - 2; ++j) {
            if ((grille[i][j] == grille[i][j + 1] && grille[i][j + 1] == grille[i][j + 2])) {//comparaison avec les deux valeurs de droite et du haut
                ligne_valide = 0;//ligne incorrecte
            }

            while (ligne_valide == 0) { //tant que la ligne est incorrecte
                generer_ligne(grille[i], taille);//générer une nouvelle ligne
                ligne_valide = 1;
                for (int l = 0; l < taille - 2; ++l) {
                    if ((grille[i][l] == grille[i][l + 1] && grille[i][l + 1] == grille[i][l + 2])) {
                        //revérifier qu'il n'y a pas de triplon sur la ligne et la colonne
                        ligne_valide = 0;
                    }
                }
            }
        }
        // Vérification du reste
        for (i = 2; i < taille - 2; i++) {
            for (int j = 0; j < taille - 2; ++j) {
                if ((grille[i][j] == grille[i][j + 1] && grille[i][j + 1] == grille[i][j + 2])
                    || (grille[i][j] == grille[i - 1][j] && grille[i - 1][j] == grille[i - 2][j])) {//comparaison avec les deux valeurs de droite et du haut
                    ligne_valide = 0;//ligne incorrecte
                }

                while (ligne_valide == 0) { //tant que la ligne est incorrecte
                    generer_ligne(grille[i], taille);//générer une nouvelle ligne
                    ligne_valide = 1;//le remplacement de la ligne est fait
                    for (int l = 0; l < taille - 2; ++l) {
                        if ((grille[i][j] == grille[i][j + 1] && grille[i][j + 1] == grille[i][j + 2])
                            || (grille[i][j] == grille[i - 1][j] && grille[i - 1][j] == grille[i - 2][j])) {
                            //revérifier qu'il n'y a pas de triplon sur la ligne et la colonne
                            ligne_valide = 0;
                        }
                    }
                }
            }
        }
    }*/
    for (i = 0; i < 2; ++i) {
        for (int j = 0; j < taille - 2; ++j) { if (!(grille[i][j] == grille[i][j + 1] && grille[i][j + 1] == grille[i][j + 2])) { ligne_valide++; }}
    }
    if (ligne_valide != 1)
        return 0;
    else
        return 1;
}


void generer_grille(int **grille, int taille) {
    srand(time(NULL));

    int **grille_auto = (int **) malloc(taille * sizeof(int *)); //créer une grille contennant 0 ou 1
    for (int k = 0; k < taille; k++) {
        grille_auto[k] = (int *) malloc(taille * sizeof(int)); //
    }

    for (int l = 0; l < taille; ++l) {
        generer_ligne(grille_auto[l], taille);
    }

    for (int a = 0; a < taille; a++) {
        for (int b = 0; b < taille; b++) {

            while (!(somme_1(grille_auto, taille)
                     || verification_grille(grille_auto, taille)
                     || som_lignes(grille_auto, a, taille)
                     || som_col(grille, b, taille))) {//vérifier le nombre total de 1
                verification_grille(grille_auto[b], taille);
            }
        }

    }
    printf("...\n");
    afficher_tab(grille_auto, taille);
    printf("...\n");
}
