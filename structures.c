#include "structures.h"
#include "defscmd.h"
#include <string.h>

Manager manager_create() {
    Manager manager;
    manager.commits_made = 0;
    manager.ignore_size = 3;
    strcpy(manager.ignore_paths[0], "./.histo");
    strcpy(manager.ignore_paths[1], ".");
    strcpy(manager.ignore_paths[2], "..");
    return manager;
}

