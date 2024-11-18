#include <stdio.h>
#include "defs.h"

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(folder) _mkdir(folder)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define MKDIR(folder) mkdir(folder, 0777)
#endif

int vcs_init() {

    if (MKDIR(".histo") == 0) {
        printf("Initialized successfully\n");
        return ERR_OK;
    } else {
        printf("Error creating directory\n");
        return ERR_NO_INIT;
    }
}

int vcs_add(int add) {
    printf("hello from add\n");
    return ERR_OK;
}

int vcs_commit(int commit) {
    printf("hello from commit\n");
    return ERR_OK;
}

int vcs_checkout(int checkout) {
    printf("hello from checkout\n");
    return ERR_OK;
}

int vcs_log(int log) {
    printf("hello from log\n");
    return ERR_OK;
}

int vcs_help() {
    printf("here are the common functions used:\n");
    printf("add, commit, checkout, log\n");
    return ERR_OK;
}