#ifndef HANDLE_COMMAND_H
#define HANDLE_COMMAND_H

void handle_command(char **args, char *cwd, int *pRedirect_input, int *pRedirect_output, char **pInput_file,
                    char **pOutput_file);

void cd(char **args);

void pwd(char **args, char *cwd);

void ls(char **args, const char *cwd);

void clear();

void echo(char **args);

void set(char **args);

void unset(char **args);

void exit_shell(char **args);

void run(char **args, int *pRedirect_input, int *pRedirect_output, char **pInput_file,
         char **pOutput_file);

#endif //HANDLE_COMMAND_H
