#include <stdio.h>
#include "../defscmd.h"
#include "../structures.h"
#include <sys/stat.h>

int histo_init() {

    const char* histo_folder = "./.histo";
    struct stat histo_sb;

    if (stat(histo_folder, &histo_sb) == 0 && S_ISDIR(histo_sb.st_mode)) {
        printf("Fatal: project already initialized\n");
        return ERR_OK;
    } 
    
    else if (mkdir(".histo", 0777) == 0) {
        FILE *info_file = fopen("./.histo/info", "wb");
        Manager manager = manager_create();
        fwrite(&manager, sizeof(Manager), 1, info_file);
        fclose(info_file);

        mkdir(".histo/objects", 0777);

        printf("Initialized successfully\n");
        return ERR_OK;
    } 
    
    else {
        printf("Error creating directory\n");
        return ERR_NO_INIT;
    }
}