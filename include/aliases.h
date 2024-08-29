#ifndef ALIASES_H
#define ALIASES_H

#define MAX_ALIASES 100

typedef struct {
    char *alias;
    char *command;
} Alias;

extern Alias aliases[MAX_ALIASES];
extern short num_aliases;

void alias(char **args);

void unalias(char **args);

char *expand_alias(const char *input);

#endif //ALIASES_H
