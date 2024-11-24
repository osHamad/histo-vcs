#include <sys/stat.h>

#define MAX_BLOBS   1000
#define MAX_NAME    150
#define MAX_IGNORE  100

typedef struct Blob {
    char name [MAX_NAME];
    ino_t inode;
    char type;
} Blob;

typedef struct Blobs {
    Blob store [MAX_BLOBS];
    int size;
} Blobs;

typedef struct FileTreeNode {
    int id;
    int blob;
    int children [MAX_BLOBS];
} FileTreeNode;

typedef struct FileTree {
    FileTreeNode head;
} FileTree;

typedef struct Commit {
    Blobs blobs;
    int number;
} Commit;

typedef struct Manager {
    int commits_made;
    char ignore_paths [MAX_NAME][MAX_BLOBS];
    int ignore_size;
} Manager;

Manager manager_create();