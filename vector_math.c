/**********************************************
* Filename: vector_math.c
* Name: Kadie Degner
* Date: 10/07/2025
* Description: Defines vector math functions.
***********************************************/

#include "vector.h"

Vector add_vectors(Vector a, Vector b)
{
    Vector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}


Vector subtract_vectors(Vector a, Vector b)
{
    Vector result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}


double dot_product(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


Vector cross_product(Vector a, Vector b) 
{
    Vector result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}


Vector scalar_multiply(Vector a, double k)
{
    Vector result;
    result.x = a.x * k;
    result.y = a.y * k;
    result.z = a.z * k;
    return result;
}

