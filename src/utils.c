#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void tokenize(char *input, char **args, int *pNum_args) {
    char *arg = strtok(input, " ");
    while (arg != NULL) {
        args[(*pNum_args)++] = arg;
        arg = strtok(NULL, " ");
    }
    args[(*pNum_args)] = NULL;
}
