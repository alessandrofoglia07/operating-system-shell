#include "commands.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "ANSI_escapes.h"

void handle_command(char **args, char *cwd, int *pRedirect_input, int *pRedirect_output, char **pInput_file,
                    char **pOutput_file) {
    if (strcmp(args[0], "cd") == 0) {
        return cd(args);
    }

    if (strcmp(args[0], "pwd") == 0) {
        return pwd(args, cwd);
    }

    if (strcmp(args[0], "ls") == 0) {
        return ls(args, cwd);
    }

    if (strcmp(args[0], "clear") == 0) {
        return clear();
    }

    if (strcmp(args[0], "echo") == 0) {
        return echo(args);
    }

    if (strcmp(args[0], "set") == 0) {
        return set(args);
    }

    if (strcmp(args[0], "unset") == 0) {
        return unset(args);
    }

    if (strcmp(args[0], "cat") == 0) {
        return cat(args);
    }

    if (strcmp(args[0], "mkdir") == 0) {
        return mkdir_shell(args);
    }

    if (strcmp(args[0], "touch") == 0) {
        return touch(args);
    }

    if (strcmp(args[0], "exit") == 0) {
        return exit_shell();
    }

    run(args, pRedirect_input, pRedirect_output, pInput_file, pOutput_file);
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
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        printf("%s ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
}

void clear() {
    printf(ANSI_CONSOLE_CLEAR);
}

void echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void set(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "set: missing argument\n");
        return;
    }
    const char *name = strtok(args[1], "=");
    const char *value = strtok(NULL, "=");
    if (name == NULL || value == NULL) {
        fprintf(stderr, "Usage: set name=value\n");
    }
    if (setenv(name, value, 1) < 0) {
        perror("setenv failed");
    }
}

void unset(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "unset: missing argument\n");
        return;
    }
    if (unsetenv(args[1]) < 0) {
        perror("unsetenv failed");
    }
}

void cat(char **args) {
    const char *filename = args[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "cat: cannot open file\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void mkdir_shell(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mkdir: missing argument\n");
        return;
    }
    if (mkdir(args[1], 0777) < 0) {
        perror("mkdir failed");
    }
}

void touch(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "touch: missing argument\n");
        return;
    }
    if (creat(args[1], 0644) < 0) {
        perror("creat failed");
    }
}

void exit_shell() {
    printf("Do you really want to exit? (y/n) ");
    const char c = getchar();
    if (toupper(c) == 'y') {
        exit(EXIT_SUCCESS);
    }
}

void run(char **args, int *pRedirect_input, int *pRedirect_output, char **pInput_file,
         char **pOutput_file) {
    // create child process
    const pid_t pid = fork();
    if (pid == 0) {
        // child process

        // handle output redirection
        if (*pRedirect_output) {
            const int fd = open(*pOutput_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // open file for writing
            if (fd < 0) {
                perror("open failed");
                exit(EXIT_FAILURE);
            }
            // redirect stdout to file
            if (dup2(fd, STDOUT_FILENO) < 0) {
                perror("dup2 failed");
                exit(EXIT_FAILURE);
            }
            close(fd);
        }

        if (*pRedirect_input) {
            const int fd = open(*pInput_file, O_RDONLY); // open file for reading
            if (fd < 0) {
                perror("open failed");
                exit(EXIT_FAILURE);
            }
            // redirect stdin to file
            if (dup2(fd, STDIN_FILENO) < 0) {
                perror("dup2 failed");
                exit(EXIT_FAILURE);
            }
            close(fd);
        }

        // execute command
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

    *pRedirect_output = 0;
    *pRedirect_input = 0;
    *pInput_file = NULL;
    *pOutput_file = NULL;
}
