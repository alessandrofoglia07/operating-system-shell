#ifndef HANDLE_COMMAND_H
#define HANDLE_COMMAND_H

void handle_command(char **args, char *cwd);

void cd(char **args);

void pwd(char **args, char *cwd);

void ls(char **args, const char *cwd);

void exit(char **args);

void run(char **args);

#endif //HANDLE_COMMAND_H
