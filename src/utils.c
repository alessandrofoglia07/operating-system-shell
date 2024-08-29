#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void tokenize(char *input, char **args, int *pNum_args, int *pRedirect_input, int *pRedirect_output, char **pInput_file,
              char **pOutput_file) {
    char *arg = strtok(input, " ");
    while (arg != NULL) {
        if (strcmp(arg, ">") == 0) {
            *pRedirect_output = 1;
            arg = strtok(NULL, " ");
            if (arg == NULL) {
                fprintf(stderr, "syntax error\n");
                return;
            }
            *pOutput_file = arg;
        } else if (strcmp(arg, "<") == 0) {
            *pRedirect_input = 1;
            arg = strtok(NULL, " ");
            if (arg == NULL) {
                fprintf(stderr, "sintax error\n");
                return;
            }
            *pInput_file = arg;
        } else {
            args[(*pNum_args)++] = arg;
        }
        arg = strtok(NULL, " ");
    }
    args[(*pNum_args)] = NULL;
}
