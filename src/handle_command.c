#include "handle_command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

void handle_command(char **args, char *cwd) {
    if (strcmp(args[0], "cd") == 0) {
        return cd(args);
    }

    if (strcmp(args[0], "pwd") == 0) {
        return pwd(args, cwd);
    }

    if (strcmp(args[0], "ls") == 0) {
        return ls(args, cwd);
    }

    if (strcmp(args[0], "exit") == 0) {
        return exit(args);
    }

    run(args);
}

void cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }
    if (chdir(args[1]) < 0) {
        perror("chdir failed");
    }
}

void pwd(char **args, char *cwd) {
    if (args[1] != NULL) {
        fprintf(stderr, "exit: unexpected arguments\n");
        return;
    }
    printf("%s\n", cwd);
}

void ls(char **args, const char *cwd) {
    if (args[1] != NULL) {
        fprintf(stderr, "ls: unexpected arguments\n");
    }
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(cwd)) == NULL) {
        perror("opendir failed");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("%s ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
}

void exit(char **args) {
    if (args[1] != NULL) {
        fprintf(stderr, "exit: unexpected arguments\n");
        return;
    }
    exit(EXIT_SUCCESS);
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
