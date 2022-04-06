#include "takuzu.h"

int main() {
    int taille;
    do {
        printf("Quelle taille de grille voulez-vous ? : \n");
        printf("1 : 4x4\t2 : 8x8\t3 : 16x16 :");
        scanf("%d", &taille);
    } while (taille < 1 || taille > 3);

    int grille[4][4] = {{1, 0, 0, 1},
                        {1, 0, 1, 0},
                        {0, 1, 1, 0},
                        {0, 1, 0, 1}};

    int **masque = (int **) malloc(taille * sizeof(int*));

    for (int i = 0; i < taille; i++) {
        masque[i] = (int *) malloc(taille * sizeof(int));
    }
    creer_masque(masque, 4);
    afficher_tab(grille, 4);
    return 0;
}
