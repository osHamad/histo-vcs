#include <stdio.h>
#include <string.h>
#include "defs.h"

int main(int argc, char **argv) {

    if (argc == 1) {
        vcs_help();
        return ERR_OK;
    }


    if (strcmp(argv[1], "init") == 0) {
        vcs_init(4);
    }

    else if (strcmp(argv[1], "add") == 0) {
        vcs_add(4);
    }

    else if (strcmp(argv[1], "commit") == 0) {
        vcs_commit(4);
    }

    else if (strcmp(argv[1], "checkout") == 0) {
        vcs_checkout(4);
    }

    else if (strcmp(argv[1], "log") == 0) {
        vcs_log(4);
    }

    else if (strcmp(argv[1], "help") == 0) {
        vcs_help();
    }

    else {
        printf("'%s' not a valid command. Try 'help' to see all commands\n", argv[1]);
    }

    return ERR_OK;
}