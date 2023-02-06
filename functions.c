#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "helpers.h"

#define FILE_DIR "../../test_vpn/server_config"

void list_codes() {
    DIR *dir = opendir(FILE_DIR);

    if (!dir) {
        printf("Something went wrong while scanning for servers\n");
        exit(1);
    }

    struct dirent *file;
    char *prev = strdup("dummy");
    while ((file = readdir(dir)) != NULL) {
        if (file->d_type == DT_REG) {
            char **tokens = tokenize(file->d_name, ".");

            if (!string_matches(tokens[0], prev)) {
                printf("%s\n", tokens[0]);
            }

            free(prev);
            prev = strdup(tokens[0]);

            free_tokens(tokens);
        }
    }

    free(prev);
    closedir(dir);
}

void connect_tcp(char *country) {
    
}
