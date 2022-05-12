#include "takuzu.h"

int main() {
    char taille_char, choix_masque_char; // déclaration de la taille et de choix_masque en int
    int i, taille_int, choix_masque_int, rejouer = 1;

    CASE case_joueur;
    int **masque;
    int **grille;
    while (rejouer == 1) {
        do {
            printf("Quelle taille de grille voulez-vous utiliser ?\n");
            printf("1 : 4x4\n2 : 8x8\n3 : 16x16\n");
            fflush(stdin);
            scanf(" %c", &taille_char); // un espace pour éviter que la boucle s'exécute deux fois
        } while (taille_char != '1' && taille_char != '2' && taille_char != '3');
        do {
            printf("Que souhaitez-vous faire ? : \n");
            printf("1 : Voulez-vous saisir un masque\n2 : Utiliser un masque genere automatiquement\n");
            fflush(stdin);
            scanf(" %c", &choix_masque_char); // un espace pour éviter que la boucle s'exécute deux fois
        } while (choix_masque_char != '1' && choix_masque_char != '2');

        if (taille_char == '1')
            taille_int = 4;
        else if (taille_char == '2')
            taille_int = 8;
        else if (taille_char == '3')
            taille_int = 16;

        if (choix_masque_char == '1')
            choix_masque_int = 1;
        else if (choix_masque_char == '2')
            choix_masque_int = 2;

        grille = creer_matrice(taille_int);
        switch (taille_int) {
            case 4:
                remplir_matrice4(grille);
                break;
            case 8:
                remplir_matrice8(grille);
                break;
            default:
                remplir_matrice4(grille);
        }

        if (choix_masque_int == 1) {
            masque = saisir_masque(taille_int);
            afficher_tab(masque, taille_int);
        } else {
            masque = creer_masque(taille_int);
        }
        rejouer = jouer(grille, masque, case_joueur, taille_int);
    }
    return 0;
}
