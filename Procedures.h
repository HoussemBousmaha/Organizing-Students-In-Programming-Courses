#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Utilisée pour la génération des nombres aléatoires
#include <windows.h>

#define LSIZ 1000 // Le nombre maximum de caractères
#define RSIZ 200  // Le nombre maximum de lignes

typedef struct participant
{
    char *NomP;
    char *PrenomP;
    float NoteP;
} participant;

// Déclaration de la structure de données "maillon"
typedef struct maillon maillon;

struct maillon
{
    participant part;
    maillon *adr;
};

// Définition du nouveau type Tptr (pointeur vers un maillon)
typedef maillon *Tptr;

/*****************************************************/
/**  Implémentation de la machine abstraite LLC TP  **/
/****            Par: ZAKARIA BELHADJ             ****/
/**            YOUCEF HOUSSEMEDDINE BOUSMAHA        **/
/*****************************************************/

// On alloue dynamiquement la structure de contrôle avec un malloc.
// La taille à allouer est calculée automatiquement avec sizeof(maillon).
// L'ordinateur saura qu'il doit allouer l'espace nécessaire au stockage de la structure maillon.

/********************************************************************************/

void Allouer(Tptr *p)
{
    *p = (Tptr)malloc(sizeof(maillon));
}

/********************************************************************************/

// Procédure qui détruit le maillon pointé par p.
void Liberer(Tptr p)
{
    free(p);
}

/********************************************************************************/

// Procédure qui affecte v dans le champ (part.NoteP)du maillon pointé par p.
void Aff_Note(Tptr p, float v)
{
    p->part.NoteP = v; // (p->part.NoteP) est l'équivalent de (*p.part.NoteP)
}

/********************************************************************************/

// Procédure qui affecte q dans le champ (adr) du maillon pointé par p.
void Aff_adr(Tptr p, Tptr q)
{
    p->adr = q; // (p->adr) est l'équivalent de (*p.adr)
}

/********************************************************************************/

// Procédure qui affecte q dans le champ (part.PrenomP) du maillon pointé par p.
void Aff_Prenom(Tptr p, char *Prenom)
{
    p->part.PrenomP = Prenom; // (part.p->PrenomP) est l'équivalent de (*p.part.PrenomP)
}

/********************************************************************************/

// Procédure qui affecte q dans le champ (part.NomP) du maillon pointé par p.
void Aff_Nom(Tptr p, char *Nom)
{
    p->part.NomP = Nom; // (part.p->NomP) est l'équivalent de (*p.part.PrenomP)
}

/********************************************************************************/

// Fonction qui retourne le contenu du champ (Note) du maillon pointé par p.
float Note(Tptr p)
{
    return p->part.NoteP; // (part.p->NoteP) est l'équivalent de (*p.part.NoteP)
}

/********************************************************************************/

// Fonction qui retourne le contenu du champ (Prenom) du maillon pointé par p.
char *Prenom(Tptr p)
{
    return p->part.PrenomP;
}

/********************************************************************************/

// Fonction qui retourne le contenu du champ (Nom) du maillon pointé par p.
char *Nom(Tptr p)
{
    return p->part.NomP;
}

/********************************************************************************/

// Fonction qui retourne le contenu du champ (adr) du maillon pointé par p.
Tptr Suivant(Tptr p)
{
    return p->adr;
}

/********************************************************************************/

/*******************************************************/
/***** Création d'une bibliothèque qui va nous   *******/
/** servir dans l'application de gestion de formation **/
/*******************************************************/

/*-1-*/ void generer_tableau(FILE *file, Tptr TFormations[]);
/*-2-*/ void parcour(Tptr formation[]);
/*-3-*/ void changement_formation(Tptr A[]);
/*-4-*/ void aff_ordre(Tptr A[]);
/*-5-*/ void resultat(Tptr Formations[]);
/*-6-*/ Tptr sequential_search(Tptr head, char fnom[]);
/*-7-*/ void aff_llc(Tptr head);
/*-8-*/ void delete_by_value(Tptr *head_ref, Tptr student);
/*-9-*/ char *concat(const char *s1, const char *s2);
/*-10-*/ void insert(Tptr head, Tptr student);
/*-11-*/ void remove_spaces(char *s);
/*-12-*/ void Swap(Tptr a, Tptr b);
/*-13-*/ void tri_bulles_note(Tptr head);
/*-14-*/ int longeur_LLC(Tptr head);
/*-15-*/ void waitfor(unsigned int secs);
/*-16-*/ void tri_bulles_noms(Tptr head);
/*-17-*/ int getline(char s[], int lim, FILE *file);
/*-18-*/ int have_spaces(char *s);
/*-19-*/ void interace();

void generer_tableau(FILE *file, Tptr *TFormations)

{
    /*****************************************************/
    /**                    Le Role                      **/
    /**   Cette fonction nous permet d'initialiser le   **/
    /**     tableau qui lit ses donnés du fichier       **/
    /*                  Particiant.txt                  **/
    /*****************************************************/

    char line[RSIZ][LSIZ];
    char *save, *nom;
    char *f = (char *)malloc(30 * sizeof(char));
    strcpy(f, "Formation:");
    char nom_formations[7][256] = {"C", "C++", "C#", "Java", "JavaScript", "Python", "PHP"};
    int i = 0, nb_line = 0, j = 0;

    Tptr p = NULL, q = NULL; // des pointeurs vers des maillons pour chainer les maillosn de 7 listes.

    srand(time(NULL)); // initialisation des nombres aléatoires!

    // Stocker le contenu du fichier ligne par ligne dans un tableau
    if (file == NULL)
    {
        exit(1);
        printf("Erreur , fichier non trouve! \n");
    }
    while (fgets(line[i], sizeof(line[i]), file))
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    nb_line = i; // 'nb_line' est le nombre de ligne du fichier, on va l'utuliser!

    // boucle principale pour creer les listes et affecter les tetes dans les 7 cases du tableau TFormations.
    for (int i = 0; i < nb_line; i++)
    {

        if (line[i][0] == 'F' && line[i][9] == ':')

        // cette Condition <=> line[i] == "F????????:" <=> On a trouver une formation
        {
            Allouer(&q);
            Aff_Nom(q, f);
            Aff_Prenom(q, nom_formations[j]);
            Aff_Note(q, -1);
            TFormations[j++] = q; // Affecter la tête trouve dans la j'iemme case du tableau et incrementer le j.
            i++;
        }
        save = line[i];
        Allouer(&p);
        Aff_adr(p, NULL);

        nom = strtok(save, " "); // diviser le nom_complet en (nom et prenom)
        Aff_Nom(p, nom);
        nom = strtok(NULL, " ");
        Aff_Prenom(p, nom);

        Aff_Note(p, (float)rand() / RAND_MAX * 13 + 7);
        Aff_adr(q, p);
        q = p;
    }
    if (q == NULL || p == NULL)
        printf("\n\t\t\t\tErreur,Tableau D%cja initialis%c!\n", 130, 130);
    else
        printf("\n\n\n\t\t\t\t\tTableau de formations initialis%c avec Succ%cs !\n", 130, 130);
}

/*-2-*/ void parcour(Tptr *formation) // procedure 2
{
    /*****************************************************/
    /**                    Le Rôle                      **/
    /**   Cette fonction nous permet de parcourir le    **/
    /**  tableau afin de réaliser quelques tâches       **/
    /*****************************************************/
    int choice, i, n;
    Tptr student;
    char nom[20], prenom[20], *full_name;
    full_name = (char *)malloc(50 * sizeof(char));
    do
    {
        printf("\n\t\t\t\t1 :Affichage la note d un participant donne\n\n");
        printf("\t\t\t\t2 :Afficher la moyenne des participant a une formation donnee\n\n");
        printf("\t\t\t\t3 :Afficher les participants nayant pas reussi durant la session en cours\n\t\t\t\t  ordonn%cs par formation\n\n", 130);
        printf("\t\t\t\tEntrer Le Choix: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            int i = 0;
            printf("\n\t\t\t\tEntrer le Nom d'%ctudiant: ", 130);
            fflush(stdin);                 // Réinstialiser pour lire des données
            getline(full_name, 50, stdin); // Lire une nouvelle ligne et la stocker dans full_name
            if (have_spaces(full_name) == 1)
                remove_spaces(full_name);
            full_name[strlen(full_name) - 1] = '\0';
            while (i < 7)
            {
                student = sequential_search(formation[i], full_name);
                if (student != NULL)
                {
                    printf("\n\t\t\t\tEtudiant Trouve ! \n\n\t\t\t\tLa Note de L'etudiant est: %0.2f\n", Note(student));
                    break;
                }
                else
                {
                    i++;
                }
            }
            if (student == NULL)
            {
                printf("\n\n\t\t\t\tEtudiant Non Trouve!\n");
                printf("%c", 7);
            }
        }
        else if (choice == 2)
        {
            char f[10], *c;
            float s = 0.0;
            int choix = 0;
            Tptr head;
            c = (char *)malloc(30 * sizeof(char));
            system("cls"); // Le code qui est au dessus pour afficher nos formations
            waitfor(500);
            printf("\n\n");
            printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
            printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
            printf("\t\t\t   %c             C          %c", 179, 179);
            printf("\t   %c          Java          %c\n", 179, 179);
            printf("\t\t\t   %c                        %c", 179, 179);
            printf("\t   %c                        %c\n", 179, 179);
            printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
            printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
            printf("\t\t\t\t\t(1)\t\t\t\t(4)");
            printf("\n\n");
            printf("\n\n");
            printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
            printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
            printf("\t\t\t   %c           C++          %c", 179, 179);
            printf("\t   %c       JavaScript       %c\n", 179, 179);
            printf("\t\t\t   %c                        %c", 179, 179);
            printf("\t   %c                        %c\n", 179, 179);
            printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
            printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
            printf("\t\t\t\t       (2)\t\t\t       (5)");
            printf("\n\n");
            printf("\n\n");
            printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
            printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
            printf("\t\t\t   %c            C#          %c", 179, 179);
            printf("\t   %c          Python        %c\n", 179, 179);
            printf("\t\t\t   %c                        %c", 179, 179);
            printf("\t   %c                        %c\n", 179, 179);
            printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
            printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
            printf("\t\t\t\t       (3)\t\t\t       (6)");
            printf("\n\n");
            printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
            printf("\t\t\t\t\t%c           PHP          %c\n", 179, 179);
            printf("\t\t\t\t\t%c                        %c\n", 179, 179);
            printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
            printf("\t\t\t\t\t\t     (7)");
            printf("\n\n\n\t\t\t\t\t  Entrer votre choix: ");
            waitfor(200);
            scanf("%d", &choix);
            if (choix > 7 || choix < 1)

            {
                printf("\n \t\t\t\tErreur de choix !");
                printf("%c", 7);
            }
            else
            {
                head = formation[choix - 1];
                while (formation[choix - 1] != NULL)
                {
                    if (formation[choix - 1]->part.NoteP != -1.0)
                    {
                        s += Note(formation[choix - 1]);
                    }
                    formation[choix - 1] = Suivant(formation[choix - 1]);
                }
                waitfor(200);
                printf("\n\t\t\t\t  La moyenne de la formation est: %0.2f\n", s / (longeur_LLC(head) - 1));
                waitfor(200);
                printf("\n\t\t\t\tSi Vous Voulez affichez les participants de cette\n\t\t\t\t formations ordonn%ce par note Entrer 'Oui'  : ", 130);
                fflush(stdin);
                getline(c, 30, stdin);
                c[strlen(c) - 1] = '\0';
                if (strcmpi(c, "Oui") == 0) // Comparer entre deux chaînes de caractères sans faire aucune différence entre le majiscule et miniscule
                {
                    waitfor(200);
                    tri_bulles_note(head); //Trier la liste selon la note
                    aff_llc(head);         // Pour afficher la liste
                }
            }
        }
        else if (choice == 3)
        {
            int i = 0;
            Tptr save;
            while (i < 7)
            {
                save = formation[i];
                while (save != NULL)
                {
                    if (Note(save) < 10)
                    {
                        if (Note(save) < 7)
                            printf("\n\n\t\t%15s %s\n\n", Nom(save), Prenom(save));
                        else
                            printf("\n\t\t%20s | %20s | %5.2f", Nom(save), Prenom(save), Note(save));
                        waitfor(200);
                    }
                    save = Suivant(save);
                }
                i++;
            }
        }
        else
            printf("\n\t\t\t\tErreur! \n");
        printf("\n\n\t\t\t\t\t\tVoulez-vous continuer ?\n\n\t\t\t\t\t\tNon : Entrez 0\n\t\t\t\t\t\tOui : Entrez !0\n\n\t\t\t\t\t\t\tVotre Choix : ");
        scanf("%d", &i);
        system("cls");
    } while (i != 0);
}

/*-3-*/ void changement_formation(Tptr A[])
{

    Tptr Etudiant, *save, *save1;
    int ind = -1, choix, i;
    float Note;
    char fnom[20], formation[20];

    do
    {
        fflush(stdin);
        printf("\n\t\t\t\t\t1: Changement de formation\n");
        printf("\n\t\t\t\t\t2: mettre a jour la note de l'examen\n");
        printf("\n\n\t\t\t\t\tEntrer Votre Choix: ");
        scanf("%d", &choix);
        if (choix == 1)
        {
            printf("\n\t\t\t\tVeillez Entrer le nom du participant: ");
            fflush(stdin);
            fgets(fnom, 20, stdin);
            remove_spaces(fnom);
            fnom[strlen(fnom) - 1] = '\0';
            for (int i = 0; i < 7; i++)
            {
                Etudiant = sequential_search(A[i], fnom);
                if (Etudiant != NULL)
                {
                    ind = i;
                    break;
                }
            }
            if (Etudiant == NULL || ind == -1)
                printf("\n\t\t\t\tEtudiant non trouve! ");
            else
            {
                int choice;
                printf("\n\t\t\t\tEtudiant Trouve! \n");
                system("cls");
                waitfor(500);
                printf("\n\n\t\t\t\tChoisissez la formation destinataire \n");
                waitfor(500);
                printf("\n\n");
                printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
                printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
                printf("\t\t\t   %c             C          %c", 179, 179);
                printf("\t   %c          Java          %c\n", 179, 179);
                printf("\t\t\t   %c                        %c", 179, 179);
                printf("\t   %c                        %c\n", 179, 179);
                printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
                printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
                printf("\t\t\t\t\t(1)\t\t\t\t(4)");
                printf("\n\n");
                printf("\n\n");
                printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
                printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
                printf("\t\t\t   %c           C++          %c", 179, 179);
                printf("\t   %c       JavaScript       %c\n", 179, 179);
                printf("\t\t\t   %c                        %c", 179, 179);
                printf("\t   %c                        %c\n", 179, 179);
                printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
                printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
                printf("\t\t\t\t       (2)\t\t\t       (5)");
                printf("\n\n");
                printf("\n\n");
                printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
                printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
                printf("\t\t\t   %c            C#          %c", 179, 179);
                printf("\t   %c          Python        %c\n", 179, 179);
                printf("\t\t\t   %c                        %c", 179, 179);
                printf("\t   %c                        %c\n", 179, 179);
                printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
                printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
                printf("\t\t\t\t       (3)\t\t\t       (6)");
                printf("\n\n");
                printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
                printf("\t\t\t\t\t%c           PHP          %c\n", 179, 179);
                printf("\t\t\t\t\t%c                        %c\n", 179, 179);
                printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
                printf("\t\t\t\t\t\t     (7)");
                printf("\n\t\t\t\t\tEntrer votre choix: ");
                scanf("%d", &choice);
                if (choice > 7 || choice < 1)
                    printf("\n\t\t\t\t\tErreur de choix");
                else
                {
                    insert(A[choice - 1], Etudiant);
                    delete_by_value(&A[ind], Etudiant);
                    tri_bulles_noms(A[choice - 1]);
                    printf("\n\n\t\t\t\t\tChangement effectu%c avec succ%cs!\n", 130, 130);
                }
            }
        }
        else if (choix == 2)
        {
            printf("\n\t\t\t\tVeuillez entrer le nom du participant: ");
            fflush(stdin);
            fgets(fnom, 20, stdin); // Pour lire le nom complet
            fnom[strlen(fnom) - 1] = '\0';
            remove_spaces(fnom);
            for (int i = 0; i < 7; i++)
            {
                Etudiant = sequential_search(A[i], fnom);
                if (Etudiant != NULL)
                    break;
            }
            if (Etudiant == NULL)
                printf("\n\t\t\t\t%ctudiant non Trouv%c! \n", 144, 130);
            else
            {
                printf("\n\t\t\t\t%ctudiant Trouv%c , Veuillez introduire la nouvelle note : ", 144, 130);
                scanf("%f", &Note);
                if (Note > 20 || Note < 0)
                    printf("\n\n\t\t\t\tErreur, La marque doit etre comprise entre 0 et 20 inclusivement!\n");
                else
                {
                    Aff_Note(Etudiant, Note);
                    printf("\n\t\t\t\tDone! \n");
                }
            }
        }
        printf("\n\n\t\t\t\t\tVoulez-vous continuer ?\n\n\t\t\t\t\tNon : Entrez 0\n\t\t\t\t\tOui : Entrez !0\n\n\t\t\t\tVotre Choix : ");
        scanf("%d", &i);
        if (i != 0)
            system("cls");
    } while (i != 0);
}

/*-4-*/ void aff_ordre(Tptr A[])
{
    char formation[20];
    Tptr save;
    int choix, k;
    system("cls");
    do
    {
        waitfor(500);
        printf("\n\n");
        printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
        printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
        printf("\t\t\t   %c             C          %c", 179, 179);
        printf("\t   %c          Java          %c\n", 179, 179);
        printf("\t\t\t   %c                        %c", 179, 179);
        printf("\t   %c                        %c\n", 179, 179);
        printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
        printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
        printf("\t\t\t\t\t(1)\t\t\t\t(4)");
        printf("\n\n");
        printf("\n\n");
        printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
        printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
        printf("\t\t\t   %c           C++          %c", 179, 179);
        printf("\t   %c       JavaScript       %c\n", 179, 179);
        printf("\t\t\t   %c                        %c", 179, 179);
        printf("\t   %c                        %c\n", 179, 179);
        printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
        printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
        printf("\t\t\t\t       (2)\t\t\t       (5)");
        printf("\n\n");
        printf("\n\n");
        printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
        printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
        printf("\t\t\t   %c            C#          %c", 179, 179);
        printf("\t   %c          Python        %c\n", 179, 179);
        printf("\t\t\t   %c                        %c", 179, 179);
        printf("\t   %c                        %c\n", 179, 179);
        printf("\t\t\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
        printf("\t   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
        printf("\t\t\t\t       (3)\t\t\t       (6)");
        printf("\n\n");
        printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191, 191);
        printf("\t\t\t\t\t%c           PHP          %c\n", 179, 179);
        printf("\t\t\t\t\t%c                        %c\n", 179, 179);
        printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 191);
        printf("\t\t\t\t\t\t     (7)");
        printf("\n\t\t\t\t\tEntrer votre choix: ");
        scanf("%d", &choix);
        waitfor(200);
        printf("\n\n");
        switch (choix)
        {
        case 1:
            save = A[0];
            tri_bulles_note(save);
            aff_llc(save);
            break;
        case 2:
            save = A[1];
            tri_bulles_note(A[1]);
            aff_llc(save);
            break;
        case 3:
            save = A[2];
            tri_bulles_note(save);
            aff_llc(save);
            break;
        case 4:
            save = A[3];
            tri_bulles_note(save);
            aff_llc(save);
            break;
        case 5:
            save = A[4];
            tri_bulles_note(save);
            aff_llc(save);
            break;
        case 6:
            save = A[5];
            tri_bulles_note(save);
            aff_llc(save);
            break;
        case 7:
            save = A[6];
            tri_bulles_note(save);
            aff_llc(save);
            break;
        default:
            printf("\n\t\t\t\t\tErreur de choix ! \n");
            break;
        }
        fflush(stdin);
        scanf("%d", &k);
    } while (k != 0);
}

/*-5-*/ void resultat(Tptr Formations[]) // procedure 5
{
    int i = 0;
    char frname[20] = "Resultats.txt";
    Tptr x;
    FILE *file1 = fopen(frname, "w");
    while (i < 7)
    {
        x = Formations[i];
        fprintf(file1, "%10s %s\n", Nom(x), Prenom(x));
        x = Suivant(x);
        while (x != NULL)
        {
            fprintf(file1, "%15s | %15s | %4.2f\n", Nom(x), Prenom(x), Note(x));
            x = Suivant(x);
        }
        i++;
    }
    fclose(file1);
}
/*-6-*/ void tri_bulles_noms(Tptr head)
{
    int swapped, temp;
    Tptr current, next;

    for (int i = longeur_LLC(head) - 3; i >= 0; i--)
    {
        current = Suivant(head);
        next = Suivant(current);

        for (int j = 0; j <= i; j++)
        {
            if (strcmpi(Nom(current), Nom(next)) > 0)
                Swap(current, next);
            current = next;
            next = Suivant(next);
        }
    }
}

void tri_bulles_note(Tptr head)
{
    int swapped;
    Tptr current, next;

    int temp;

    for (int i = longeur_LLC(head) - 3; i >= 0; i--)
    {
        current = Suivant(head);
        next = Suivant(current);

        for (int j = 0; j <= i; j++)
        {
            if (Note(current) < Note(next))
                Swap(current, next);
            current = next;
            next = Suivant(next);
        }
    }
}

void Swap(Tptr a, Tptr b)
{
    char *temp_Nom = Nom(a);
    Aff_Nom(a, Nom(b));
    Aff_Nom(b, temp_Nom);

    float temp = Note(a);
    Aff_Note(a, Note(b));
    Aff_Note(b, temp);

    char *temp_PreNom = Prenom(a);
    Aff_Prenom(a, Prenom(b));
    Aff_Prenom(b, temp_PreNom);
}

int longeur_LLC(Tptr head)
{
    int i = 0;
    while (head != NULL)
    {
        i++;
        head = Suivant(head);
    }
    return i;
}

void remove_spaces(char *s)
{
    const char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while (*s++ = *d++);
}
int have_spaces(char *s)
{
    while (*s != '\0')
    {
        if (*s == ' ')
            return 1;
        s += 1;
    }
    return 0;
}
void aff_llc(Tptr head)
{
    while (head != NULL)
    {
        if (strcmp(Nom(head), "Formation:") == 0)
            printf("\n\n\t\t\t\t%10s %s\n\n", Nom(head), Prenom(head));
        else
            printf("\t\t\t\t%20s | %20s | %4.2f\n", Nom(head), Prenom(head), Note(head));
        head = Suivant(head);
        waitfor(200);
    }
}

void delete_by_value(Tptr *head_ref, Tptr student)
{
    // Store head node
    Tptr temp = *head_ref, prev;

    // If head node itself holds the value to be deleted
    if (temp != NULL && temp == student)
    {
        *head_ref = Suivant(temp); // Changed head
        Liberer(temp);             // free old head
        return;
    }

    // Search for the valeur to be deleted, keep track of the
    // previous node as we need to change 'prev->adr'
    while (temp != NULL && temp != student)
    {
        prev = temp;
        temp = Suivant(temp);
    }

    // If valeur was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the node from linked list
    //prev->adr = temp->adr;
    Aff_adr(prev, Suivant(temp));

    Liberer(temp); // Free memory
}

Tptr sequential_search(Tptr head, char fnom[])
{
    for (int i = 0; i < 30 && Suivant(head) != NULL; i++)
    {
        char *c = (char *)malloc(30 * sizeof(char));
        strcpy(c, Nom(head));
        strcat(c, Prenom(head));
        if (strcmpi(c, fnom) == 0)
        {
            return head;
        }
        head = Suivant(head);
    }
    return NULL;
}

char *concat(const char *s1, const char *s2)
{
    char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code we would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


/*************************************************************************************************************************************************************/


void insert(Tptr head, Tptr student)
{
    int v = rand() % (13) + 7;
    Tptr prev = NULL, cp_student = NULL;

    Allouer(&cp_student);

    Aff_Nom(cp_student, Nom(student));
    Aff_Prenom(cp_student, Prenom(student));
    Aff_Note(cp_student, v); 
    Aff_adr(cp_student, NULL);


    while (head != NULL)
    {
        prev = head;
        head = Suivant(head);
    }
    Aff_adr(prev, cp_student);
}


/*************************************************************************************************************************************************************/

void waitfor(unsigned int secs)
{
    int c, d;

    for (c = 1; c <= 32 * secs; c++)
        for (d = 1; d <= 32 * secs; d++)
        {
        }
    return;
}


/*************************************************************************************************************************************************************/
int getline(char s[], int lim, FILE *file)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = fgetc(file)) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}



/*************************************************************************************************************************************************************/
void interace()
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
    waitfor(200);
    printf("\n\n\n\n\n\n");
    waitfor(200);
    printf("                            _ _           _   _                   _                        _   _              \n");
    waitfor(200);
    waitfor(200);
    printf("          /\\               | (_)         | | (_)                 | |                      | | (_)             \n");
    waitfor(200);

    printf("         /  \\   _ __  _ __ | |_  ___ __ _| |_ _  ___  _ __     __| | ___    __ _  ___  ___| |_ _  ___  _ __   \n");
    waitfor(200);

    printf("        / /\\ \\ |  _ \\|  _ \\| | |/ __/ _  | __| |/ _ \\|  _ \\   / _  |/ _ \\  / _  |/ _ \\/ __| __| |/ _ \\|  _ \\\n");
    waitfor(200);

    printf("       / ____ \\| |_) | |_) | | | (_| (_| | |_| | (_) | | | | | (_| |  __/ | (_| |  __/\\__ \\ |_| | (_) | | | |\n");
    waitfor(200);

    printf("      /_/    \\_\\  __/|  __/|_|_|\\___\\____|\\__|_|\\___/|_| |_|  \\____|\\___|  \\___ |\\___||___/\\__|_|\\___/|_| |_| \n");
    waitfor(200);

    printf("               | |   | |                                                    __/ |                     \n");
    waitfor(200);

    printf("               |_|   |_|                                                   |___/                              \n");
    waitfor(200);
    printf("\t\t\t      _        ______                         _   _             \n");
    waitfor(200);
    printf("\t\t\t     | |      |  ____|                       | | (_)             \n");
    waitfor(200);
    printf("\t\t\t   __| | ___  | |__ ___  _ __ _ __ ___   __ _| |_ _  ___  _ __  \n");
    waitfor(200);
    printf("\t\t\t  / _  |/ _ \\ |  __/ _ \\|  __|  _   _ \\ / _  | __| |/ _ \\|  _ \\ \n");
    waitfor(200);
    printf("\t\t\t | (_| |  __/ | | | (_) | |  | | | | | | (_| | |_| | (_) | | | |\n");
    waitfor(200);
    printf("\t\t\t  \\____|\\___| |_|  \\___/|_|  |_| |_| |_|\\____|\\__|_|\\___/|_| |_|\n");
    waitfor(200);
    printf("\n\n\n\n\n\n\n");
    waitfor(200);
    printf("______________________________________________________________________________________________________________\n\n\n");
    waitfor(200);
    printf("\t\t\t\t\t\t REALIS%c PAR:\n\n\n", 144);
    waitfor(200);
    printf("\t\t\t\tZAKARIA BELHADJ |  YOUCEF HOUSSEM-EDDINE BOUSMAHA \n\n");
    waitfor(200);
    printf("\t\t\t\t\t\tSECTION B  |  GROUPE 05\n\n");
    waitfor(200);
    printf("\t\t\t\t\tENCADR%c PAR: Dr.BENMALLEK MOURAD\n\n", 144);
    waitfor(200);
    printf("\t\t\t\t\t\t\t\t\t   ANN%cE UNIVERSITAIRE : 2020/2021\n\n\n\n", 144);
    waitfor(200);
    printf("\n");
    printf("\n\t\t\t\t\tTaper sur Entrer :D pour continuer \n");
    getchar();
    system("cls");
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
    waitfor(200);
    printf("\n\n\n\n\n\t\t\t\t\t\tAide et notices");
    waitfor(500);
    printf("\n\n\n\n\n\n\n\n\t\tL'institut de formation sp%ccialis%c en informatique (Formation+) souhaite d%cvelopper une application\n", 130, 130, 130);
    waitfor(500);
    printf("\tde gestion des participants %c la s%crie de formations en programmation qu'il organise. Pour ce faire,\n", 133, 130);
    waitfor(500);
    printf("\tl'institut fait appel %c votre expertise en programmation pour le d%cveloppement de cette application.\n\n\n", 133, 130);
    waitfor(500);
    printf("\tDans cette application :\n\n");
    waitfor(500);
    printf("\t\t%c Les sept (07) formations propos%ces par l'institut (Formation+) sont : C, C++, C#, Java, JavaScript,\n", 16, 130);
    waitfor(500);
    printf("\t\t\tPython et PHP.\n\n");
    waitfor(500);
    printf("\t\t%c Durant la session en cours, chaque participant peut s'inscrire %c une seule formation.\n", 16, 133);
    waitfor(500);
    printf("\t\t Les listes des participants sont stock%ces dans un tableau de sept (07) cases (Formations [1..7]) :\n\n", 130);
    waitfor(500);
    printf("\t\t\t- Chaque groupe de participants est repr%csent%c par une liste lin%caire cha%cn%ce unidirectionnelle.\n", 130, 130, 130, 140, 130);
    waitfor(500);
    printf("\t\t\tLes listes de participants sont ordonn%ces, selon l'ordre alphab%ctique croissant.\n\n");
    waitfor(500);
    printf("\t\t\t- Chaque participant est repr%csent%c par un enregistrement (Participant) contenant les\n");
    waitfor(500);
    printf("\t\t\tinformations suivantes :\n\n");
    waitfor(500);
    printf("\t\t1. Nom (NomP) : une cha%cne de caract%cres.\n\n", 140, 138);
    waitfor(500);
    printf("\t\t2. Pr%cnom (PrenomP) : une cha%cne de caract%cres.\n\n", 130, 140, 138);
    waitfor(500);
    printf("\t\t3. Note (NoteP) : un r%cel indiquant la note obtenue dans l'examen post-formation.\n\n\n\n", 130);
    waitfor(500);
    printf("\t\tEt pour bien manipuler cette application , on vous demande de suivre les inctructions et Merci \n");
}
