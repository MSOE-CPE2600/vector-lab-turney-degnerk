/**********************************************
* Filename: vector.h
* Name: Kadie Degner
* Date: 09/30/2025
* Description: Defines a vector struct.
***********************************************/

#ifndef VECTOR_H
#define VECTOR_H

#define MAX_NAME 16

typedef struct
{
    char varname[MAX_NAME];
    float x;
    float y;
    float z;
} Vector;

#endif