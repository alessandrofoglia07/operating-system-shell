#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ANSI_escapes.h"
#include "commands.h"
#include "utils.h"
#include "aliases.h"

#define MAX_INPUT_SIZE 1024
#define MAX_CWD_SIZE 1024
#define MAX_ARGS 64

Alias aliases[MAX_ALIASES];
short num_aliases;

int main() {
    char input[MAX_INPUT_SIZE];
    while (1) {
        char cwd[MAX_CWD_SIZE];
        printf("%s%s%s$ ", ANSI_COLOR_BLUE, getcwd(cwd, MAX_CWD_SIZE), ANSI_COLOR_RESET);
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("fgets failed");
            exit(EXIT_FAILURE);
        }
        input[strcspn(input, "\n")] = '\0';

        strcpy(input, expand_alias(input));

        char *args[64];
        int num_args = 0;

        tokenize(input, args, &num_args);

        handle_command(args, cwd);
    }
}
