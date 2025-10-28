/****************************************************
* Filename: vector_linked_list.h
* Name: Kadie Degner
* Date: 10/14/2025
* Description: Declares vector linked list functions.
*****************************************************/

#ifndef VECTOR_ARRAY_H
#define VECTOR_ARRAY_H

#include "vector.h"

// Initialize linked list
LinkedList *initialize_list(void);

// Get size of linked list
int get_list_size(LinkedList *list);

// Add vector to list
void add_vector(LinkedList *list, char *name, float x, float y, float z);

// Make a certain number of random vectors
void fill_random_vectors(LinkedList *list, int count);

// Fina a vector by name
Vector find_vector(LinkedList *list, char *name);

// Clear list of vectors
void clear(LinkedList *list);

// List all vectors
void list(LinkedList *list);

#endif