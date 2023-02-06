#include <stdbool.h>

#ifndef HELPERS
#define HELPERS

bool string_matches(char *, char *);

char **tokenize(char*, char*);
void free_tokens(char**);

#endif
