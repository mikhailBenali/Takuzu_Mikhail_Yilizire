#include "takuzu.h"

int main() {
    char taille; // pour éviter les bugs quand l'utilisateur saisit un caractère autre qu'un chiffre
    int i;
    char choix_masque;
    CASE case_joueur;
    int *masque[16];
    int **grille;
    do {
        printf("Quelle taille de grille voulez-vous utiliser ?\n");
        printf("1 : 4x4\n2 : 8x8\n3 : 16x16\n");
        scanf(" %c", &taille); // un espace pour éviter que la boucle s'exécute deux fois
    } while (taille != '1' && taille != '2' && taille != '3');
    do {
        printf("Que souhaitez-vous faire ? : \n");
        printf("1 : Voulez-vous saisir un masque\n2 : Utiliser un masque genere automatiquement\n");
        scanf(" %c", &choix_masque); // un espace pour éviter que la boucle s'exécute deux fois
    } while (choix_masque != '1' && choix_masque != '2');

    taille = (int) taille;
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
        printf("grille complete :\n");
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
        afficher_tab(grille, taille);

        if (choix_masque == 1) {
            saisir_masque(masque, taille);
            afficher_grille(grille, masque, taille);
        } else {
            creer_masque(masque, taille);
            afficher_grille(grille, masque, taille);
        }
        jouer(grille, masque, case_joueur, taille);
        return 0;
    }
}