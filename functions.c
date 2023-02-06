#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"
#include "helpers.h"

#define TCP "com_tcp"
#define UDP "com_udp"

char *FILE_DIR = "../../test_vpn/server_config/";
char TEMPLATE_COMMAND[] = "sudo openvpn ";
char *CRED_PATH = "../../test_vpn/login.conf";

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

void connect(char *country, bool is_tcp) {
    DIR *dir = opendir(FILE_DIR);
    
    if (!dir) {
        printf("Something went wrong\n");
        exit(1);
    }

    struct dirent *file;

    bool country_found = false;
    while((file = readdir(dir)) != NULL) {
        if (file->d_type == DT_REG) {
            char **tokens = tokenize(file->d_name, ".");

            if (!string_matches(country, tokens[0])) {
                free_tokens(tokens);
                continue;
            }
            
            country_found = true;

            bool execute_success = true;

            bool matches_tcp = string_matches(TCP, tokens[3]) && is_tcp;
            bool matches_udp = string_matches(UDP, tokens[3]) && !is_tcp;
            if (matches_tcp || matches_udp) {
                strcat(TEMPLATE_COMMAND, FILE_DIR);
                strcat(TEMPLATE_COMMAND, file->d_name);
                execute_success = system(TEMPLATE_COMMAND);
            }

            free_tokens(tokens);

            if (!execute_success) {
                printf("\nError: Something went wrong while executing openvpn command\n");
            }
        }
    }

    if (!country_found) 
        printf("\nError: Cannot find code: %s\n", country);
    else
        printf("\n Error: Something went wrong\n");
}

void set_username(char *uname) {
    if (get_file_lines(CRED_PATH) < 2) {
        FILE *file = fopen(CRED_PATH, "w");
        fprintf(file, "%s\n", uname);
        fclose(file);
        return;  
    }

    FILE *rfile = fopen(CRED_PATH, "r");
    if (rfile == NULL) {
        printf("\n Error: Unable to read login.conf\n");
        exit(1);
    }

    char password[100];
    fscanf(rfile, "%s", &password); //skips the first line
    fscanf(rfile, "%s", &password); //and get the password
    fclose(rfile);

    FILE *wfile = fopen(CRED_PATH, "w");
    fprintf(wfile, "%s\n", uname);
    fprintf(wfile, "%s\n", password);
    fclose(wfile);
}

void set_passwd(char *passwd) {
    int file_lines = get_file_lines(CRED_PATH);

    if (file_lines < 2) {
        FILE *file = fopen(CRED_PATH, "a");
        
        if (file_lines != 1) {
            fputs("dummy\n", file);
        }

        fprintf(file, "%s\n", passwd);
        fclose(file);
        return;
    }

    FILE *rfile = fopen(CRED_PATH, "r");
    if (rfile == NULL) {
        printf("\n Error: Unable to read login.conf\n");
        exit(1);
    }

    char uname[100];
    fscanf(rfile, "%s", &uname);
    fclose(rfile);
    printf("%s\n", uname);

    FILE *wfile = fopen(CRED_PATH, "w");
    fprintf(wfile, "%s\n", uname);
    fprintf(wfile, "%s\n", passwd);
    fclose(wfile);
}
