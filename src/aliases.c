#include "aliases.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alias(char **args) {
    if (args[1] == NULL) {
        // Print all aliases
        for (int i = 0; i < num_aliases; i++) {
            printf("%s='%s'\n", aliases[i].alias, aliases[i].command);
        }
        return;
    }
    const char *name = strtok(args[1], "=");
    const char *command = strtok(NULL, "=");
    if (name == NULL || command == NULL) {
        fprintf(stderr, "Usage: alias name=command\n");
        return;
    }
    if (num_aliases >= MAX_ALIASES) {
        fprintf(stderr, "Too many aliases\n");
        return;
    }
    aliases[num_aliases].alias = strdup(name);
    aliases[num_aliases].command = strdup(command);
    num_aliases++;
}

void unalias(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "Usage: unalias name\n");
        return;
    }
    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(args[1], aliases[i].alias) == 0) {
            free(aliases[i].alias);
            free(aliases[i].command);
            for (int j = i; j < num_aliases - 1; j++) {
                aliases[j] = aliases[j + 1];
            }
            num_aliases--;
            return;
        }
    }
    fprintf(stderr, "Alias not found\n");
}

char *expand_alias(const char *input) {
    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(input, aliases[i].alias) == 0) {
            return strdup(aliases[i].command);
        }
    }
    return strdup(input);
}
