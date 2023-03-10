#include <stdbool.h>

#ifndef HELPERS
#define HELPERS

bool string_matches(char *, char *);

char **tokenize(char*, char*);
void free_tokens(char**);
int get_file_lines(char*);
void edit_server_files(char*, char*);
void print_help_msg();

#endif
