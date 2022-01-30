#include "Procedures.h"

int main()
{
    FILE *file;
    system("mode con  LINES=60 COLS=130");
    char fname[20] = "Participants.txt";
    file = fopen(fname, "r");
    system("color 0b");
    system("cls");
    int n, choix, test;
    Tptr *Formations = (Tptr *)malloc(7 * sizeof(Tptr)), save = NULL; // declarations du tableau des listes.
    interace();
    printf("\n\t\t\t\t\tTaper sur Entrer :D pour continuer \n");
    getchar();
    system("cls");
    do
    {
        printf("\n");
        waitfor(200);
        printf(" ______  _____  __ \t\t\t\t\t\t\t\t\t  _______ _____    __ \n");
        waitfor(200);
        printf("|  ____|/ ____||__| %ccole nationale\t\t\t\t\t\t\t |__   __|  __ \\  /_ |  \n", 144);
        waitfor(200);
        printf("| |__  | (___   __ \t\t\t\t\t\t\t\t\t    | |  | |__) |  | |\n");
        waitfor(200);
        printf("|  __|  \\___ \\ |  | Sup%crieure\t\t\t\t\t\t\t\t    | |  |  ___/   | |\n", 130);
        waitfor(200);
        printf("| |____ ____) ||  |\t\t\t\t\t\t\t\t\t    | |  | |       | |\n");
        waitfor(200);
        printf("|______|_____/ |__| d'Informatique\t\t\t\t\t\t\t    |_|  |_|       |_|\n");
        printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t1: Initialisation des structures\n\n");
        waitfor(200);
        printf("\t\t\t\t\t2: Parcours des listes\n\n");
        waitfor(200);
        printf("\t\t\t\t\t3: Changement de formation\n\n");
        waitfor(200);
        printf("\t\t\t\t\t4: Afficher la liste des participants \n\t\t\t\t\t   dans une formation ordonn%ce par notes\n\n", 130);
        waitfor(200);
        printf("\n\n\t\t\t\t\tEntrer votre choix: ");
        scanf("%d", &choix);
        if (choix == 1)
        {
            generer_tableau(file, Formations);
            save = *Formations;
        }
        else if (choix == 2)
        {
            if (save == NULL)
            {
                printf("\n\n\t\tErreur, Structures non initialis%ce! \n", 130);
                printf("%c", 7);
            }
            else
                parcour(Formations);
        }
        else if (choix == 3)
            if (save == NULL)
            {
                printf("\n\n\t\tErreur, Structures non initialis%ce! \n", 130);
                printf("%c", 7);
            }
            else
            {
                changement_formation(Formations);
                resultat(Formations);
            }
        else if (choix == 4)
            if (save == NULL)
            {
                printf("\n\n\t\tErreur, Structures non initialis%ce! \n", 130);
                printf("%c", 7);
            }
            else
                aff_ordre(Formations);
        else
            printf("\n\n\t\t\t\t\tErreur de choix !\n");
        printf("\n\n\t\t\t\t\tVoulez_vous Quitter le programme ?\n\n\t\t\t\t\tNon :!0\n\t\t\t\t\tOui : Entrez 0\n\n\t\t\t\t\tVotre Choix : ");
        fflush(stdin);
        scanf("%d", &test);
        system("cls");
    } while (test != 0);
    resultat(Formations);
    system("Resultats.txt");
    fclose(file);
    return 0;
}