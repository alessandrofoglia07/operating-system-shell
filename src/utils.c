#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void tokenize(char *input, char **args, int *pNum_args) {
    char *arg = strtok(input, " ");
    while (arg != NULL) {
        args[(*pNum_args)++] = arg;
        arg = strtok(NULL, " ");
    }
    args[(*pNum_args)] = NULL;
}

void run(char **args) {
    // create child process
    const pid_t pid = fork();
    if (pid == 0) {
        // child process, execute command
        if (execvp(args[0], args) < 0) {
            perror("execvp failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
    } else {
        // parent process
        wait(NULL);
    }
}
