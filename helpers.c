#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_TOKENS 5

bool string_matches(char *str1, char *str2) {
    return strcmp(str1, str2) == 0 ? true : false;
}

char **tokenize(char *string, char *delimiter) {
    // We are sure that there are 5 tokens
    // Last one for null pointer
    char **tokens = malloc((NUM_TOKENS + 1) * sizeof(*tokens));

    char *token = strtok(string, delimiter);
    for (int i = 0; token != NULL; i++) {
        tokens[i] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    tokens[NUM_TOKENS] = NULL;

    return tokens;
}

void free_tokens(char **tokens) {
    for (int i = 0; i < NUM_TOKENS; i++) {
        free(tokens[i]);
    }

    free(tokens);
}
