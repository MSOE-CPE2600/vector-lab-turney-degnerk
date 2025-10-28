/**************************************************
* Filename: parser.h
* Name: Kadie Degner
* Date: 10/07/2025
* Description: Declares argument parser functions.
***************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "vector.h"
#include <stdbool.h>

// Load vectors from a csv file
bool load_vectors(const char *filename, LinkedList *list);

// Save vectors to a csv file
bool save_vectors(const char *filename, LinkedList *list);

// Evaluate an assignment (Includes '=')
bool eval_assignment(LinkedList *linked_list, const char *input);

// Evaluate an expression (Does not include '=')
bool eval_expression(LinkedList *list, const char *input);

// Display help text
void print_help();

#endif