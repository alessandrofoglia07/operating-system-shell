#include "pipes.h"
#include "utils.h"
#include "common.h"
#include "commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_pipes(char *input, char *cwd) {
    char *commands[MAX_ARGS];
    int num_commands = 0;

    char *command = strtok(input, "|");
    while (command != NULL) {
        commands[num_commands++] = command;
        command = strtok(NULL, "|");
    }
    commands[num_commands] = NULL;

    int pipefds[2 * (num_commands - 1)];
    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipefds + i * 2) < 0) {
            perror("pipe failed");
            return;
        }
    }

    for (int i = 0; i < num_commands; i++) {
        const pid_t pid = fork();
        if (pid == 0) {
            // child process

            // redirect input from previous command
            if (i > 0) {
                if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) < 0) {
                    perror("dup2 failed");
                    exit(EXIT_FAILURE);
                }
            }

            // redirect output to next command
            if (i < num_commands - 1) {
                if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) < 0) {
                    perror("dup2 failed");
                    exit(EXIT_FAILURE);
                }
            }

            // close all pipe file descriptors
            for (int j = 0; j < 2 * (num_commands - 1); j++) {
                close(pipefds[j]);
            }

            // parse and execute commands
            char *args[MAX_ARGS];
            int num_args = 0;
            int redirect_input = 0, redirect_output = 0;
            char *input_file = NULL, *output_file = NULL;

            tokenize(commands[i], args, &num_args, &redirect_input, &redirect_output, &input_file, &output_file);
            handle_command(args, cwd, &redirect_input, &redirect_output, &input_file, &output_file);

            exit(EXIT_SUCCESS);
        }
        if (pid < 0) {
            perror("fork failed");
            return;
        }
    }

    for (int i = 0; i < 2 * (num_commands - 1); i++) {
        close(pipefds[i]);
    }

    for (int i = 0; i < num_commands; i++) {
        wait(NULL);
    }
}
