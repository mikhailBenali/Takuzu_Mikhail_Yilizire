#include "takuzu.h"

int main() {
    int taille;
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
    taille = 8; // Pour le début on ne propose pas la taille de la grille, on impose 4

    int grille[16][16] = {{1, 0, 0, 1},
                          {1, 0, 1, 0},
                          {0, 1, 1, 0},
                          {0, 1, 0, 1}};

    int masque[16][16];
    for (int i = 0; i < taille; i++) {
        for (int j = 0; i < taille; i++) {
            masque[i][j] = 0;
        }
    }
    creer_masque(masque, taille);
    printf("Masque\n");
    afficher_tab(masque, taille);
    printf("\n");

    printf("Grille\n");
    afficher_tab(grille, taille);
    printf("\n");

    printf("Grille masquee\n");
    afficher_grille(grille, taille, masque);
    printf("\n");
    return 0;
}
