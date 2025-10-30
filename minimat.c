/***********************************************************************************
* Filename: minimat.c
* Name: Kadie Degner
* Date: 09/30/2025
* Description: Runs the vector calculator and parsing.
* Note: compile with gcc -o minimat minimat.c vector_array.c vector_math.c parser.c
*       run with ./minimat
***********************************************************************************/

#include "vector_linked_list.h"
#include "vector_math.h"
#include "parser.h"
#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Initialize linked list
    LinkedList *linked_list = initialize_list();

    // Display help if -h flag is provided
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        print_help();
        printf("\n");
    }

    char line[128];
    char filename[64];
    int count;

    printf("Mini MATLAB - 3D Vector Calculator\n");
    printf("Type 'help' for commands or 'quit' to exit.\n");

    while (1) {
        printf("minimat> ");
        fflush(stdout);

        // Read line of user input
        if (!fgets(line, sizeof(line), stdin))
        {
            break;
        }

        // Trim newline
        line[strcspn(line, "\n")] = '\0';

        // Ignore empty lines
        if (strlen(line) == 0)
        {
            continue;
        }

        // Check for load and save
        if (sscanf(line, "load %s", filename) == 1)
        {
            load_vectors(filename, linked_list);
            continue;
        } else if (sscanf(line, "save %s", filename) == 1){
            save_vectors(filename, linked_list);
            continue;
        } else if (sscanf(line, "fill %d", &count) == 1){
            fill_random_vectors(linked_list, count);
            continue;
        }

        // Check for quit, clear, list, or help commands
        if (strcmp(line, "quit") == 0)
        {
            clear(linked_list);
            free(linked_list);
            linked_list = NULL;
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(line, "clear") == 0)
        {
            clear(linked_list);
            printf("Vector memory cleared.\n");
            continue;
        }
        else if (strcmp(line, "list") == 0)
        {
            list(linked_list);
            continue;
        }
        else if (strcmp(line, "help") == 0)
        {
            print_help();
            continue;
        } 

        // Determine whether input has '=' (assignment)
        if (strstr(line, " = ") != NULL) {
            if (!eval_assignment(linked_list, line)) {
                printf("Remember spaces between arguments and type 'help' for more information.\n");
            }
        } else {
            if (!eval_expression(linked_list, line)) {
                printf("Remember spaces between arguments and type 'help' for more information.\n");
            }
        }
    }

    return 0;
}