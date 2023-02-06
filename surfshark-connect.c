#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "definitions.h"
#include "helpers.h"

int main(int argc, char **argv) {
    
    if (argc == 1) {
        printf("%s\n", HELPMSG);
        exit(1);
    }

    char *option = argv[1];

    // Switch statement does not work on strings
    if (string_matches(option, LIST_CODE)) {
        list_codes();
    } else if (string_matches(option, USE_UDP)) {
        connect(argv[2], false);
    } else if (string_matches(option, USE_TCP)) {
        connect(argv[2], true);
    } else {
        connect(option, true);
    }

    return 0;
}
