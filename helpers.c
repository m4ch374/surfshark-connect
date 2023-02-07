#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_TOKENS 5

bool string_matches(char *str1, char *str2) {
    return strcmp(str1, str2) == 0 ? true : false;
}

char **tokenize(char *string, char *delimiter) {
    // We are sure that there are 5 tokens
    // Last one for null pointer
    char **tokens = malloc((NUM_TOKENS + 1) * sizeof(*tokens));

    char *strcpy = strdup(string);
    char *token = strtok(strcpy, delimiter);
    for (int i = 0; token != NULL; i++) {
        tokens[i] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    tokens[NUM_TOKENS] = NULL;

    free(strcpy);
    return tokens;
}

void free_tokens(char **tokens) {
    for (int i = 0; i < NUM_TOKENS; i++) {
        free(tokens[i]);
    }

    free(tokens);
}

int get_file_lines(char *file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL)
        return -1;

    char c;
    int count = 0;
    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n')
            count++;
    }

    return count;
}

void edit_server_files(char *server, char* cred_path) {
    char *tmp_file_path = "./tmp_server";

    FILE *file = fopen(server, "r");
    FILE *tfile = fopen(tmp_file_path, "w");

    char line[1024];
    while (fgets(line, 1024, file)) {
        if (strstr(line, "auth-user-pass") != NULL) {
            fprintf(tfile, "%s", "auth-user-pass ");
            fprintf(tfile, "%s\n", cred_path);
        } else {
            fputs(line, tfile);
        }
    }

    fclose(tfile);
    fclose(file);

    char command[1024] = "sudo mv ";
    strcat(command, tmp_file_path);
    strcat(command, " ");
    strcat(command, server);

    system(command);
}

void print_help_msg() {
    printf("\nsurfshark-connect [--options] <value>\n");
    printf("\nAvalible commands:\n");
    printf("\t--list\n");
    printf("\t--udp <country_code>\n");
    printf("\t--tcp <country_code>\n");
    printf("\t--username <username>\n");
    printf("\t--passwd <password>\n\n");
}
