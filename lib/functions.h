#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "./models.h"
#include "../src/functions.c"



char* file_to_string(char* filename);
char *get_line(char **content);
char *read_line_keyboard(FILE *f);
int number_of_lines(char *content);
float float_rand( float min, float max );



student *init_student(char *name);
void ll_insert(student **head, student *new_student);
void ll_print(student *head);
student *ll_search(student *head, char *name);


void init_structure(student *table[], char *content);
void traversal(student **table);


int get_mark_student(student **table);
float get_mean_module(student **table);
void get_failed_student(student **table);
