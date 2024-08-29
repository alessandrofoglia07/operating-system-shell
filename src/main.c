#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT_SIZE];
    while (1) {
        printf("$ ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("fgets failed");
            exit(EXIT_FAILURE);
        }
        input[strcspn(input, "\n")] = '\0';
        printf("%s\n", input);

        char *args[64];
        int num_args = 0;

        tokenize(input, args, &num_args);

        run(args);

        if (strcmp(input, "exit") == 0) {
            break;
        }
    }

    return 0;
}
