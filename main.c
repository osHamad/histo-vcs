#include <stdio.h>
#include <string.h>
#include "./commands/cmds.h"

int main(int argc, char **argv) {

    if (argc == 1) {
        histo_help();
        return 0;
    }

    if (strcmp(argv[1], "init") == 0) {
        histo_init();
    }

    else if (strcmp(argv[1], "commit") == 0) {
        histo_commit();
    }

    else if (strcmp(argv[1], "help") == 0) {
        histo_help();
    }

    else {
        printf("'%s' not a valid command. Try 'help' to see all commands\n", argv[1]);
    }

    return 0;
}