/**********************************************
* Filename: vector.h
* Name: Kadie Degner
* Date: 09/30/2025
* Description: Defines a vector struct.
***********************************************/

#ifndef VECTOR_H
#define VECTOR_H

#define MAX_NAME 16

typedef struct Vector Vector;

typedef struct Vector
{
    char varname[MAX_NAME];
    float x;
    float y;
    float z;
    Vector *next;
    Vector *prev;
} Vector;

typedef struct
{
    Vector *first;
    Vector *last;
} LinkedList;

#endif