#include "takuzu.h"

int main() {
    int taille;
    int i;
    int choix_masque;
    CASE case_joueur;
    int **masque;
    int **grille;

    do {
        printf("Quelle taille de grille voulez-vous utiliser ?\n");
        printf("1 : 4x4\n2 : 8x8\n3 : 16x16\n");
        scanf(" %d", &taille); // un espace pour éviter que la boucle s'exécute deux fois
    } while (taille != 1 && taille != 2 && taille != 3);
    do {
        printf("Que souhaitez-vous faire ? : \n");
        printf("1 : Voulez-vous saisir un masque\n2 : Utiliser un masque genere automatiquement\n");
        scanf(" %d", &choix_masque); // un espace pour éviter que la boucle s'exécute deux fois
    } while (choix_masque != 1 && choix_masque != 2);

    switch (taille) {
        case 1:
            taille = 4;
            break;
        case 2:
            taille = 8;
            break;
        case 3:
            taille = 16;
            break;
        default:
            taille = 4;
            break;
    }
    if (taille == 4) { // Si la taille est égale à 4 on utilise une grille préfaite
        grille = (int **) malloc(taille * sizeof(int *)); // Initialisation du tableau 2D
        for (i = 0; i < taille; i++) {
            grille[i] = malloc(taille * sizeof(int));
        }

        grille[0][0] = 1;
        grille[0][1] = 0;
        grille[0][2] = 0;
        grille[0][3] = 1;
        grille[1][0] = 1;
        grille[1][1] = 0;
        grille[1][2] = 1;
        grille[1][3] = 0;
        grille[2][0] = 0;
        grille[2][1] = 1;
        grille[2][2] = 1;
        grille[2][3] = 0;
        grille[3][0] = 0;
        grille[3][1] = 1;
        grille[3][2] = 0;
        grille[3][3] = 1;

        /*1, 0, 0, 1
          1, 0, 1, 0
          0, 1, 1, 0
          0, 1, 0, 1*/

        if (choix_masque == 1) {
            masque = saisir_masque(taille);
            afficher_tab(masque, taille);
        } else {
            do {
                masque = creer_masque(taille);
            } while (masque_plein(masque, taille) == 1); // Tant que le masque saisi est plein
        }
        jouer(grille, masque, case_joueur, taille);
        return 0;
    }

}