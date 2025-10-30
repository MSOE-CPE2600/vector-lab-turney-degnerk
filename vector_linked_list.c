/***************************************************
* Filename: vector_linked_list.c
* Name: Kadie Degner
* Date: 10/14/2025
* Description: Defines vector linked list functions.
****************************************************/

#include "vector.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


LinkedList *initialize_list(void)
{
    // Create and initialize linked list
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        fprintf(stderr, "Memory allocation failed for LinkedList\n");
        exit(1);
    }

    list->first = NULL;
    list->last = NULL;
    return list;
}


int get_list_size(LinkedList *list)
{
    int count = 0;
    Vector *current = list->first;
    // Loop through linked list and count elements
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}


void add_vector(LinkedList *list, char *name, float x, float y, float z)
{   
    // Allocate memory for new vector
    Vector *new_vector = malloc(sizeof(Vector));

    if (new_vector == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Copy values from input vector to new vector
    strncpy(new_vector->varname, name, MAX_NAME - 1);
    new_vector->varname[MAX_NAME - 1] = '\0';
    
    new_vector->x = x;
    new_vector->y = y;
    new_vector->z = z;
    new_vector->next = NULL;
    new_vector->prev = NULL;

    // Add to linked list
    if (list->first == NULL)
    {
        list->first = new_vector;
        list->last = new_vector;
    }
    else
    {
        list->last->next = new_vector;
        new_vector->prev = list->last;
        list->last = new_vector;
    }
}


// Make a certain number of random vectors
void fill_random_vectors(LinkedList *list, int count) {
    if (count <= 0) {
        printf("Error: count must be greater than 0.\n");
        return;
    }

    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    char name[16];
    char num[16];

    for (int i = 1; i <= count; i++) {
        strcpy(name, "vector");
        sprintf(num, "%d", i);
        strcat(name, num);

        float x = ((float)rand() / RAND_MAX) * 20.0f - 10.0f;
        float y = ((float)rand() / RAND_MAX) * 20.0f - 10.0f;
        float z = ((float)rand() / RAND_MAX) * 20.0f - 10.0f;

        add_vector(list, name, x, y, z);
    }
    printf("%d random vectors created.\n", count);
}


Vector find_vector(LinkedList *list, char *name)
{
    // Get first element
    Vector *current = list->first;
    // Loop through vector array and compare names
    while (current != NULL)
    {
        if (strcmp(current->varname, name) == 0)
        {
            return *current; // Found, return vector
        }
        current = current->next;
    }
    Vector empty_vector = {"\0", 0.0, 0.0, 0.0};
    return empty_vector; // Not found, return empty vector
}


void clear(LinkedList *list)
{
    // Get first element
    Vector *current = list->first;

    // Loop through linked list and free memory
    while (current != NULL)
    {
        Vector *next = current->next;
        free(current);
        current = next;
    }
    list->first = NULL;
    list->last = NULL;
}


void list(LinkedList *list)
{
    // Get first element
    Vector *current = list->first;

    if (current == NULL)
    {
        printf("Empty\n");
    }
    else
    {
        while (current != NULL)
        {
            printf("%s: (%.2f, %.2f, %.2f)\n", current->varname, current->x, current->y, current->z);
            current = current->next;
        }
    }
}
