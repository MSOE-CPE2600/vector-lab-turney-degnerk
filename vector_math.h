/**********************************************
* Filename: vector_math.h
* Name: Kadie Degner
* Date: 10/07/2025
* Description: Declares vector math functions.
***********************************************/

#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include "vector.h"

Vector add_vectors(Vector a, Vector b);

Vector subtract_vectors(Vector a, Vector b);

double dot_product(Vector a, Vector b);

Vector cross_product(Vector a, Vector b);

Vector scalar_multiply(Vector a, double k);

#endif
