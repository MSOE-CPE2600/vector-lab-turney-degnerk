/**************************************************
* Filename: parser.h
* Name: Kadie Degner
* Date: 10/07/2025
* Description: Declares argument parser functions.
***************************************************/

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

// Evaluate an assignment (Includes '=')
bool eval_assignment(const char *input);

// Evaluate an expression (Does not include '=')
bool eval_expression(const char *input);

// Display help text
void print_help();

#endif