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
    int redirect_output = 0, redirect_input = 0;
    char *input_file = NULL, *output_file = NULL;

    while (1) {
        char cwd[MAX_CWD_SIZE];
        printf("%s%s%s$ ", ANSI_COLOR_BLUE, getcwd(cwd, MAX_CWD_SIZE), ANSI_COLOR_RESET);
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("fgets failed");
            exit(EXIT_FAILURE);
        }
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

        strcpy(input, expand_alias(input));

        char *args[64];
        int num_args = 0;

        tokenize(input, args, &num_args, &redirect_input, &redirect_output, &input_file, &output_file);

        handle_command(args, cwd);
    }
}
