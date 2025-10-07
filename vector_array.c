/**********************************************
* Filename: vector_array.c
* Name: Kadie Degner
* Date: 09/30/2025
* Description: Defines vector array functions.
***********************************************/

#include "vector_array.h"
#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX_NUM_VECTORS 10

static Vector vector_array[MAX_NUM_VECTORS];
static int num_elements = 0;


int add_vect(Vector vector)
{   
    // First, check for matching name to replace
    for (int i = 0; i < num_elements; i++)
    {
        if (strcmp(vector_array[i].varname, vector.varname) == 0)
        {
            vector_array[i] = vector;
            return 0;
        }
    }

    // Next, check if array is full. If not, add vector. Else, print error.
    if (num_elements < MAX_NUM_VECTORS)
    {
        vector_array[num_elements] = vector;
        num_elements++;
    }
    else
    {
        printf("Error: Vector array is full.\n");
    }
    return 0;
}


Vector find_vector(char *name)
{
    // Loop through vector array and compare names
    for (int i = 0; i < num_elements; i++)
    {
        if (strcmp(vector_array[i].varname, name) == 0)
        {
            return vector_array[i]; // Match, return copy
        }
    }
    Vector empty_vector = {"\0", 0.0, 0.0, 0.0};
    return empty_vector; // Not found, return empty vector
}


void clear(void)
{
    num_elements = 0;
    for (int i = 0; i < MAX_NUM_VECTORS; i++)
    {
        // Reset names and values
        vector_array[i].varname[0] = '\0';
        vector_array[i].x = 0.0;
        vector_array[i].y = 0.0;
        vector_array[i].z = 0.0;
    }
}


void list(void)
{
    if (num_elements == 0)
    {
        printf("Empty");
    }
    else
    {
        for (int i = 0; i < num_elements; i++)
        {
            Vector vector = vector_array[i];
            printf("%s = %.3f + %.3f + %.3f\n", 
            vector.varname, vector.x, vector.y,
            vector.z);
        }
    }
}
