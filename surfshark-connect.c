#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "definitions.h"
#include "helpers.h"

int main(int argc, char **argv) {
    
    if (argc == 1 || argc > 3) {
        print_help_msg();
        exit(1);
    }

    char *option = argv[1];
    char *args = argc == 3 ? argv[2] : option;

    // Switch statement does not work on string comparisons 
    if (string_matches(option, LIST_CODE)) {
        list_codes();
    } else if (string_matches(option, USE_UDP)) {
        connect(args, false);
    } else if (string_matches(option, USE_TCP)) {
        connect(args, true);
    } else if (string_matches(option, SET_UNAME)) {
        set_username(args);
    } else if (string_matches(option, SET_PASSWD)) {
        set_passwd(args);
    } else {
        connect(args, true);
    }

    return 0;
}
