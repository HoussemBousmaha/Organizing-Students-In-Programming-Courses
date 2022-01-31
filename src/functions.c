
char* file_to_string(char* filename)
{
    FILE* file = fopen(filename,"r");
    if(file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);

    char* content = (char*)calloc(size + 1, 1);

    fread(content,1,size,file);

    return content;
}

char *get_line(char **content) {

    if (**content == '\0')
        return "";

    int size = 0;

    for (int i = 0; *(*content + i) != '\n'; i++) {
        size++;
    }

    char *line = calloc(sizeof(char), size + 1);

    for (int i = 0; i < size; i++) {
        line[i] = *(*content + i);
    }

    line[size + 1] = '\0';

    (*content) += size + 1;

    return line;
}


char *read_line_keyboard(FILE *f) {
    int size = 0;
    
    char c;


    char *s = calloc(sizeof(char), 30);
    
    while ((c = fgetc(stdin)) != '\n') {
        s[size++] = c;
    }

    s[size] = '\0';


    return s;
}



int number_of_lines(char *content) {
    int size = 0, i = 0;

    while (content[i] != '\0') {
        if (content[i] == '\n')
            size++;

        i++;
    }


    return size;
}

float float_rand(float left, float right) {
    float randomNumber = sin(rand() * rand());
    return left + (right - left) * fabs(randomNumber);
}

student *init_student(char *name) {
    student *new_student = malloc(sizeof(student));

    float a = float_rand(7.0, 20.0);

    new_student->name = name;
    new_student->mark = a;
    new_student->next = NULL;

    return new_student;
}


void ll_insert(student **head, student *new_student) {

    if (*head == NULL) {
        *head = new_student;
    } else {
        student *curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        curr->next = new_student;
    }
}

void ll_print(student *head) {
    while(head) {
        if (head->mark != 0.0)
            printf("\t\t-> (name: %-27s mark: %-4.2f)\n", head->name, head->mark);
        else 
            printf("\n\t\t\t  (%s)\n\n", head->name);
        head = head->next;
    }
}

student *ll_search(student *head, char *name) {
    
    while(head) {
        if (strcmp(head->name, name) == 0) 
            return head;
        else 
            head = head->next;
    }

    return NULL;
}

void init_structure(student *table[], char *content) {
    srand(time(NULL));

    int num_lines = number_of_lines(content);
    int row = 0;

    // student **table = calloc(sizeof(student*), 7);
    char *line;
    student *st;

    for (int i = 0 ; i < num_lines; i++) {
        line = get_line(&content);

        // printf("%s", line);

        st = init_student(line);

        if (line[0] == 'F' && line[9] == ':') {
            st->mark = 0.0;
            table[row] = st;
            row++;
        } else {
            ll_insert(&table[row - 1], st);
        }
    }

    // for (int i = 0; i < 7; i++) {
    //     ll_print(table[i]->next);

    //     printf("--------------------------------------\n");
    // }

    // return table;
}

int get_mark_student(student **table) {

    printf("\n\t\tName of student: ");
    fflush(stdin);
    char *student_name = read_line_keyboard(stdin);

    for (int i = 0; i < 7; i++) {

        student *st = ll_search(table[i]->next, student_name);

        if (st != NULL) {
            printf("\n\t\tSuccess!\n\n\t\t>> %s\n\t\t>> mark: %-5.2f\n\n", st->name, st->mark);
            return st->mark;
        }
    }

    printf("\n\t\t>> Failed\n\t\t>> \"%s\" was not found\n\n", student_name);

    return -1;

}


float get_mean_module(student **table) {
    for (int i = 0; i < 7; i++) {
        printf("\t\t\t|%d --> %-21s|\n", i+1, table[i]->name);
    }

    int choice;
    printf("\n\t\tYour choice: ");
    scanf("%d", &choice);

    if (choice > 7 || choice < 1) {
        printf("\n\t\tChoice out of range!\n");
    } else {
        student *current = table[choice - 1]->next;

        float sum = 0.0;
        int size = 0;

        while(current) {
            size++;
            sum += current->mark;
            current = current->next; 
        }

        char *course_name = table[choice - 1]->name;
        course_name += 11;

        printf("\n\t\tCourse: %s\n\t\tAverage : %-5.2f\n", course_name, sum / size);
        return sum / size;
    }

}

void get_failed_student(student **table) {

    student **sorted_table = calloc(sizeof(student*), 7);


    for (int i = 0; i < 7; i++) {
        student *current_head = table[i];

        while(current_head != NULL) {
            student *st = init_student(current_head->name);
            st->mark = current_head->mark;

            if (st->mark < 10)
                ll_insert(&sorted_table[i], st);

            current_head = current_head->next;
        }
    }

    for (int i = 0; i < 7; i++) {
        student *first = sorted_table[i];
        student *second = first;
        student *head = first;
        

        while (head != NULL) {
            second = first;
            while (second->next != NULL) {
                if (second->mark > second->next->mark) {
                    char *tmp_name = second->name;
                    second->name = second->next->name;
                    second->next->name = tmp_name;


                    float tmp_mark = second->mark;
                    second->mark = second->next->mark;
                    second->next->mark = tmp_mark; 
                }
                second = second->next;
            }
            head = head->next;
        }
    }

    for (int i = 0; i < 7; i++) {
        ll_print(sorted_table[i]);
    }
}



void traversal(student **table) {
    int choice;
        printf("\n\n\tWelcome to traversal section !\n");
      
    do {
        printf("\n\t\tyou have several choices: \n\n");
        printf("\t\t0: go back\n");
        printf("\t\t1: get the mark of a given student\n");
        printf("\t\t2: get the average point of a given class\n");
        printf("\t\t3: get the failed students ordered by mark-class\n\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        system("cls");

        printf("\n\n");

        switch (choice)
        {
        case 1:
            get_mark_student(table);
            break;
        
        case 2:
            get_mean_module(table);
            break;

        case 3:
            get_failed_student(table);
            break;
        }
    } while(choice != 0);

}