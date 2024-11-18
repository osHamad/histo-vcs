// Exit codes
#define ERR_OK              0
#define ERR_FILE_NOT_EXIST  1
#define ERR_NO_INIT         2

// Forward declarations
int vcs_init();
int vcs_add(int add);
int vcs_commit(int commit);
int vcs_checkout(int checkout);
int vcs_log(int log);
int vcs_help();