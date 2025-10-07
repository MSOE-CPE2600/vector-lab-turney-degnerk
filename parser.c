/**********************************************
* Filename: parser.c
* Name: Kadie Degner
* Date: 10/07/2025
* Description: Defines argument parser functions.
***********************************************/

#include "parser.h"
#include "vector_array.h"
#include "vector_math.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Evaluate expression with assignment
bool eval_assignment(const char *input) {
    char left_operand[16], operand1[16], operator[4], operand2[16];
    double x, y, z;

    // Direct numeric assignment
    if (sscanf(input, "%15s = %lf %lf %lf", left_operand, &x, &y, &z) == 4) {
        Vector v = {"", x, y, z};
        strcpy(v.varname, left_operand);
        add_vect(v);
        return true;
    }

    // Two operands with operator
    if (sscanf(input, "%15s = %15s %3s %15s", left_operand, operand1, operator, operand2) == 4) {
        Vector A, B, result;
        double k;
        bool a_exists = false;
        bool b_exists = false;

        // Check if the vectors exist
        Vector temp = find_vector(operand1);
        if (temp.varname[0] != '\0') 
        { 
            A = temp; 
            a_exists = true; 
        }
        temp = find_vector(operand2);
        if (temp.varname[0] != '\0') 
        { 
            B = temp; 
            b_exists = true; 
        }

        // Vector operations
        if (strcmp(operator, "+") == 0) // Addition
        {
            if (!a_exists || !b_exists) 
            { 
                printf("Error: missing vector.\n"); 
                return false; 
            }
            result = add_vectors(A, B);
            strncpy(result.varname, left_operand, 15);
            result.varname[15] = '\0';
            add_vect(result);
            printf("%s = %.3f %.3f %.3f\n", result.varname, result.x, result.y, result.z);
        }
        else if (strcmp(operator, "-") == 0) // Subtraction
        {
            if (!a_exists || !b_exists) {
                printf("Error: missing vector.\n");
                return false;
            }
            result = subtract_vectors(A, B);
            strncpy(result.varname, left_operand, 15);
            result.varname[15] = '\0';
            add_vect(result);
            printf("%s = %.3f %.3f %.3f\n", result.varname, result.x, result.y, result.z);
        }
        else if (strcmp(operator, "*") == 0) // Scalar Multiplication
        {
            if (a_exists && !b_exists) 
            {
                k = atof(operand2);
                result = scalar_multiply(A, k);
                strncpy(result.varname, left_operand, 15);
                result.varname[15] = '\0';
                add_vect(result);
                printf("%s = %.3f %.3f %.3f\n", result.varname, result.x, result.y, result.z);
            } 
            else if (!a_exists && b_exists) 
            {
                k = atof(operand1);
                result = scalar_multiply(B, k);
                strncpy(result.varname, left_operand, 15);
                result.varname[15] = '\0';
                add_vect(result);
                printf("%s = %.3f %.3f %.3f\n", result.varname, result.x, result.y, result.z);
            } 
            else
            {
                printf("Error: invalid scalar multiply.\n");
                return false;
            }
        }
        else if (strcmp(operator, ".") == 0) // Dot product
        {
            if (!a_exists || !b_exists)
            { 
                printf("Error: missing vector.\n"); 
                return false; 
            }
            double scalar_result = dot_product(A, B);
            printf("%s = %.3f\n", left_operand, scalar_result);
            return true;
        }
        else if (strcmp(operator, "x") == 0 || strcmp(operator, "X") == 0) // Cross Product
        {
            if (!a_exists || !b_exists)
            {
                printf("Error: missing vector.\n");
                return false;
            }
            result = cross_product(A, B);
            strncpy(result.varname, left_operand, 15);
            result.varname[15] = '\0';
            add_vect(result);
            printf("%s = %.3f %.3f %.3f\n", result.varname, result.x, result.y, result.z);
            return true;
        }
        else // Invalid operator
        {
            printf("Error: invalid operator.\n");
            return false;
        }
        return true;
    }

    printf("Error: Invalid assignment format.\n");
    return false;
}


// Evaluate expression without assignment
bool eval_expression(const char *input) {
    char operand1[16], operator[4], operand2[16];

    // Two operands with operator
    if (sscanf(input, "%15s %3s %15s", operand1, operator, operand2) == 3) {
        Vector A, B, result;
        double k;
        bool a_exists = false;
        bool b_exists = false;

        // Check if the vectors exist
        Vector temp = find_vector(operand1);
        if (temp.varname[0] != '\0') 
        { 
            A = temp; 
            a_exists = true; 
        }
        temp = find_vector(operand2);
        if (temp.varname[0] != '\0') 
        { 
            B = temp; 
            b_exists = true; 
        }

        // Vector operations
        if (strcmp(operator, "+") == 0) // Addition
        {
            if (!a_exists || !b_exists) 
            { 
                printf("Error: missing vector.\n"); 
                return false; 
            }
            result = add_vectors(A, B);
            printf("%.3f %.3f %.3f\n", result.x, result.y, result.z);
        }
        else if (strcmp(operator, "-") == 0) // Subtraction
        {
            if (!a_exists || !b_exists) {
                printf("Error: missing vector.\n");
                return false;
            }
            result = subtract_vectors(A, B);
            printf("%.3f %.3f %.3f\n", result.x, result.y, result.z);
        }
        else if (strcmp(operator, "*") == 0) // Scalar Multiplication
        {
            if (a_exists && !b_exists) 
            {
                k = atof(operand2);
                result = scalar_multiply(A, k);
                printf("%.3f %.3f %.3f\n", result.x, result.y, result.z);
                return true;
            } 
            else if (!a_exists && b_exists) 
            {
                k = atof(operand1);
                result = scalar_multiply(B, k);
                printf("%.3f %.3f %.3f\n", result.x, result.y, result.z);
                return true;
            } 
            else
            {
                printf("Error: invalid scalar multiply.\n");
                return false;
            }
        }
        else if (strcmp(operator, ".") == 0) // Dot product
        {
            if (!a_exists || !b_exists)
            { 
                printf("Error: missing vector.\n"); 
                return false; 
            }
            double scalar_result = dot_product(A, B);
            printf("%.3f\n", scalar_result);
            return true;
        }
        else if (strcmp(operator, "x") == 0 || strcmp(operator, "X") == 0) // Cross Product
        {
            if (!a_exists || !b_exists)
            {
                printf("Error: missing vector.\n");
                return false;
            }
            result = cross_product(A, B);
            printf("%.3f %.3f %.3f\n", result.x, result.y, result.z);
            return true;
        }
        else // Invalid operator
        {
            printf("Error: invalid operator.\n");
            return false;
        }
        return true;
    }

    // Single name
    if (sscanf(input, "%15s", operand1) == 1) {
        Vector v = find_vector(operand1);
        if (v.varname[0] == '\0') {
            printf("Vector not found: %s\n", operand1);
            return true;
        }
        printf("%s = %.3f %.3f %.3f\n", v.varname, v.x, v.y, v.z);
        return true;
    }

    // Invalid input
    printf("Error: invalid input. Remember spaces around symbols.\n");
    return false;
}


// Display help text
void print_help() {
    puts("Commands:");
    puts("  var = x y z      assign 3D vector");
    puts("  var = a + b      add vectors");
    puts("  var = a - b      subtract vectors");
    puts("  var = a * k      scalar multiply (or k * a)");
    puts("  a + b            display result of addition");
    puts("  a - b            display result of subtraction");
    puts("  a * k            display result of scalar multiplication");
    puts("  var              display stored vector");
    puts("  list             list all vectors");
    puts("  clear            clear vector storage");
    puts("  quit             exit program");
}
