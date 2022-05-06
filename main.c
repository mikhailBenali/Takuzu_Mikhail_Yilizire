#include "takuzu.h"

int main() {
    int taille, i;
    int choix_masque;
    CASE case_joueur;
    int **masque;
    int **grille;
    do {
        printf("Quelle taille de grille voulez-vous ? : \n");
        printf("1 : 4x4\n2 : 8x8\n3 : 16x16\n");
        scanf("%d", &taille);
        printf("Que souhaitez-vous faire ? : \n");
        printf("1 : Voulez-vous saisir un masque\n2 : Utiliser un masque genere automatiquement ?\n");
        scanf("%d", &choix_masque);

    } while (taille < 1 || taille > 3);

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
    if (taille == 4) {
        grille = (int **) malloc(taille * sizeof(int *)); // Initialisation du tableau 2D
        for (i = 0; i < taille; i++) {
            grille[i] = malloc(taille * sizeof(int));
        }

        int grille[16][16] = {{1, 0, 0, 1},
                            {1, 0, 1, 0},
                            {0, 1, 1, 0},
                            {0, 1, 0, 1}};

        if (choix_masque == 1) {
            masque = saisir_masque(masque, taille);
        } else {
            creer_masque(masque, taille);
        }
        jouer(grille, masque, case_joueur, taille);
        return 0;
    }
}