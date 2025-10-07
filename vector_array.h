/**********************************************
* Filename: vector_array.h
* Name: Kadie Degner
* Date: 09/30/2025
* Description: Declares vector array functions.
***********************************************/

#ifndef VECTOR_ARRAY_H
#define VECTOR_ARRAY_H

#include "vector.h"

// Add vector to list
int add_vect(Vector vector);

// Fina a vector by name
Vector find_vector(char *name);

// Clear list of vectors
void clear(void);

// List all vectors
void list(void);

#endif