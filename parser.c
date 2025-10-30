/**********************************************
* Filename: parser.c
* Name: Kadie Degner
* Date: 10/07/2025
* Description: Defines argument parser functions.
***********************************************/

#include "parser.h"
#include "vector.h"
#include "vector_linked_list.h"
#include "vector_math.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


bool load_vectors(const char *filename, LinkedList *linked_list) 
{
    char line[128];

    // Clear existing vectors
    clear(linked_list);

    // Open csv file
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: could not open file %s for reading.\n", filename);
        return false;
    }

    // Fix for BOM so first vector is read correctly
    unsigned char bom[3];
    if (fread(bom, 1, 3, file) == 3) {
        if (!(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)) {
            // Not a BOM
            fseek(file, 0, SEEK_SET);
        }
    }

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\0') 
        {
            continue; // skip empty lines
        }

        line[strcspn(line, "\r\n")] = '\0';

        // Split by commas (expect 4 tokens)
        char *p = line;
        char *t1 = strsep(&p, ",");
        char *t2 = strsep(&p, ",");
        char *t3 = strsep(&p, ",");
        char *t4 = strsep(&p, ",");

        if (!t1 || !t2 || !t3 || !t4) {
            printf("Skipping Invalid Line: \"%s\"\n", line);
            continue;
        }

        // Copy name
        char name[MAX_NAME];
        strncpy(name, t1, MAX_NAME - 1);
        name[MAX_NAME - 1] = '\0';
        name[strcspn(name, "\r\n")] = '\0'; 

        // Parse floats
        char *end2 = NULL, *end3 = NULL, *end4 = NULL;
        float x = strtof(t2, &end2);
        float y = strtof(t3, &end3);
        float z = strtof(t4, &end4);
        if ((end2 == t2) || (end3 == t3) || (end4 == t4)) {
            printf("Skipping Invalid Line: \"%s\"\n", line);
            continue;
        }

        add_vector(linked_list, name, x, y, z);
        printf("Loaded: '%s' (%.2f, %.2f, %.2f)\n", name, x, y, z);
    }


    fclose(file);
    return true;
}


bool save_vectors(const char *filename, LinkedList *list) {
    // Open csv file
    FILE *file = fopen(filename, "w");
    Vector *current = list->first;

    if (file == NULL) {
        printf("Error: could not open file %s for writing.\n", filename);
        return false;
    }

    // Write each vector to file
    while (current != NULL) {
        fprintf(file, "%s,%.2f,%.2f,%.2f\n", current->varname, current->x, current->y, current->z);
        current = current->next;
    }

    fclose(file);
    return true;
}


// Evaluate expression with assignment
bool eval_assignment(LinkedList *linked_list, const char *input) {
    char left_operand[16], operand1[16], operator[4], operand2[16];
    double x, y, z;

    // Direct numeric assignment
    if (sscanf(input, "%15s = %lf %lf %lf", left_operand, &x, &y, &z) == 4) {
        add_vector(linked_list, left_operand, x, y, z);
        return true;
    }

    // Two operands with operator
    if (sscanf(input, "%15s = %15s %3s %15s", left_operand, operand1, operator, operand2) == 4) {
        Vector A, B, result;
        double k;
        bool a_exists = false;
        bool b_exists = false;

        // Check if the vectors exist
        Vector temp = find_vector(linked_list, operand1);
        if (temp.varname[0] != '\0') 
        { 
            A = temp; 
            a_exists = true; 
        }
        temp = find_vector(linked_list, operand2);
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
            add_vector(linked_list, result.varname, result.x, result.y, result.z);
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
            add_vector(linked_list, result.varname, result.x, result.y, result.z);
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
                add_vector(linked_list, result.varname, result.x, result.y, result.z);
                printf("%s = %.3f %.3f %.3f\n", result.varname, result.x, result.y, result.z);
            } 
            else if (!a_exists && b_exists) 
            {
                k = atof(operand1);
                result = scalar_multiply(B, k);
                strncpy(result.varname, left_operand, 15);
                result.varname[15] = '\0';
                add_vector(linked_list, result.varname, result.x, result.y, result.z);
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
            add_vector(linked_list, result.varname, result.x, result.y, result.z);
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
bool eval_expression(LinkedList *linked_list, const char *input) {
    char operand1[16], operator[4], operand2[16];

    // Two operands with operator
    if (sscanf(input, "%15s %3s %15s", operand1, operator, operand2) == 3) {
        Vector A, B, result;
        double k;
        bool a_exists = false;
        bool b_exists = false;

        // Check if the vectors exist
        Vector temp = find_vector(linked_list, operand1);
        if (temp.varname[0] != '\0') 
        { 
            A = temp; 
            a_exists = true; 
        }
        Vector temp2 = find_vector(linked_list, operand1);
        if (temp2.varname[0] != '\0') 
        { 
            B = temp2; 
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
        Vector v = find_vector(linked_list, operand1);
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
    puts("Mini MATLAB Commands:");
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
    puts("  load <filename>  load vectors from file");
    puts("  save <filename>  save vectors to file");
    puts("  fill <count>     generate random vectors");
    puts("  quit             exit program");
}

