/*************************************************************************
* Filename: minimat.c
* Name: Kadie Degner
* Date: 09/30/2025
* Description: Runs the vector calculator and parsing.
* Note: compile with gcc -o minimat minimat.c vector_array.c vector_math.c
*       run with ./minimat
**************************************************************************/

#include "vector_array.h"
#include "vector_math.h"
#include "parser.h"
#include "vector.h"
#include <stdio.h>
#include <string.h>

#define MAX_NUM_VECTORS 10


int main(int argc, char *argv[])
{
    // Display help if -h flag is provided
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        print_help();
        printf("\n");
    }

    clear(); // Clear vector storage
    char line[128];

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

        // Check for quit, clear, list, or help commands
        if (strcmp(line, "quit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(line, "clear") == 0)
        {
            clear();
            printf("Vector memory cleared.\n");
            continue;
        }
        else if (strcmp(line, "list") == 0)
        {
            list();
            continue;
        }
        else if (strcmp(line, "help") == 0)
        {
            print_help();
            continue;
        }

        // Determine whether input has '=' (assignment)
        if (strstr(line, " = ") != NULL) {
            if (!eval_assignment(line)) {
                printf("Remember spaces between arguments and type 'help' for more information.\n");
            }
        } else {
            if (!eval_expression(line)) {
                printf("Remember spaces between arguments and type 'help' for more information.\n");
            }
        }
    }

    return 0;
}