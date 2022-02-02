
#include "../lib/functions.h"






int main() {

    char file_name[] = "../in/Participants.txt";

    char *content = file_to_string(file_name);

    
    


    student *table[7];
    
    init_structure(table, content);


    int choice;
    printf("\n\nWelcome To Our Program\n");



    do {
        printf("\n\tYour have several choices: \n\n\t\t0: exit");
        printf("\n\t\t1: traversal");
        printf("\n\t\t2: modification");
        printf("\n\t\t3: sorting courses\n");
        printf("\n\tPlease select a choice: ");
        scanf("%d", &choice);

        system("cls");


        switch (choice)
        {
        case 1:
            traversal(table);
            break;

        case 2:
            modification(table);
            break;

        case 3:
            sort_student_list(table);
            break;
        }
    } while(choice != 0);


    printf("\nThank you for using our program! good luck\n\n");


    return 0;
}