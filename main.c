#include "takuzu.h"

int main() {
    int taille;
    CASE case_joueur;
    /*
    do {
        printf("Quelle taille de grille voulez-vous ? : \n");
        printf("1 : 4x4\t2 : 8x8\t3 : 16x16 :");
        scanf("%d", &taille);
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
    }*/
    taille = 4; // Pour le début on ne propose pas la taille de la grille, on impose 4

    int grille[4][4] = {{1, 0, 0, 1},
                        {1, 0, 1, 0},
                        {0, 1, 1, 0},
                        {0, 1, 0, 1}};

    int masque[4][4];
    creer_masque(masque, taille);

    printf("Grille\n");
    afficher_tab(grille, taille);
    printf("\n");

    printf("Grille masquee\n");
    afficher_grille(grille, masque, taille);
    printf("\n");

    while (1) {
        jouer(grille, masque, case_joueur, taille);

        // S'il y a au moins une case encore non affichée dans la grille on continue
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                if (masque[i][j] == 0) {
                    afficher_tab(masque, taille);
                    jouer(grille, masque, case_joueur, taille);
                }
            }
        }
        break;
    }

    printf("Bravo vous avez resolu le Takuzu\n");
    return 0;
}
