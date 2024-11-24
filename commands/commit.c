#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "../defscmd.h"
#include "../structures.h"

int store_blob_files(const char* dir_name, Commit* files);
int save_blob_file(char* source_path, Commit* commit, Blob* curr_blob);

int histo_commit() {

    // Store information to open .histo
    const char* folder = "./.histo";
    struct stat sb;

    // Check if .histo exists
    if (stat(folder, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        printf("Fatal: no repository exists. Try 'histo init' to create one\n");
        return ERR_NO_COMMIT;
    }

    // Load histo manager
    Manager manager;
    FILE *info_file = fopen("./.histo/info", "r+b");
    fread(&manager, sizeof(Manager), 1, info_file);
    
    // Create new commit object
    Commit new_commit;
    new_commit.number = manager.commits_made;

    // Create new directory to store commit files
    char com_dir_name[24] = "./.histo/objects/";
    char num_string[6] = "";
    sprintf(num_string, "%d", new_commit.number);
    strcat(com_dir_name, num_string);
    mkdir(com_dir_name, S_IRWXU);

    // Create a file for each commited file
    // Store file information in commit blobs
    store_blob_files(".", &new_commit);

    // Save manager to info file and close
    manager.commits_made++;
    fseek(info_file, 0, SEEK_SET);
    fwrite(&manager, sizeof(Manager), 1, info_file);
    fclose(info_file);

    return ERR_OK;
}

int store_blob_files(const char* dir_name, Commit* files) {

    // Store directory name and create dirent struct to manage files
    DIR* parent_dir = opendir(dir_name);
    struct dirent* parent_struct;

    // Keep looping until no more files in the directory
    while ((parent_struct = readdir(parent_dir)) != NULL) {
        
        // If the directory is the ".." or "." directory, then ignore
        // Subject to change later
        if (strcmp(parent_struct->d_name, ".") == 0 || strcmp(parent_struct->d_name, "..") == 0 || strcmp(parent_struct->d_name, ".histo") == 0 || strcmp(parent_struct->d_name, ".git") == 0) {
            continue;
        }

        // Store name of the current file or directory
        char child_dir[512];
        size_t dir_len = strlen(dir_name);
        size_t name_len = strlen(parent_struct->d_name);
        snprintf(child_dir, sizeof(child_dir), "%s/%s", dir_name, parent_struct->d_name);
        
        // Store blob information into the commit structure
        Blob* curr_blob = &files->blobs.store[files->blobs.size];
        strcpy(curr_blob->name, parent_struct->d_name);
        curr_blob->inode = parent_struct->d_ino;

        // Check if the current thing is a file or directory
        // Give a type of d or f accordingly, and increase blobs number
        struct stat sb;
        if (stat(child_dir, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            curr_blob->type = 'd';
            files->blobs.size++;
            
            // Recursively get all the remaining files in the sub directories
            store_blob_files(child_dir, files);
        } else {
            curr_blob->type = 'f';
            files->blobs.size++;
            save_blob_file(child_dir, files, curr_blob);
        }
    }

    // Close directory and return
    closedir(parent_dir);
    return 0;
}

int save_blob_file(char* source_path, Commit* commit, Blob* blob) {
    FILE *source_file, *dest_file;
    char buffer[1024];  // Buffer to hold the data temporarily

    // Creating the string for destination file path
    char dest_path[50] = "";
    sprintf(dest_path, "./.histo/objects/%d/%ld", commit->number, blob->inode);

    // Open the source file in read mode
    source_file = fopen(source_path, "rb");

    // Open the destination file in write mode
    dest_file = fopen(dest_path, "wb");

    // Read the source file and write to the destination file
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest_file);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(dest_file);
            return 1;
        }
    }

    // Close the files
    fclose(source_file);
    fclose(dest_file);

    return 0;
}