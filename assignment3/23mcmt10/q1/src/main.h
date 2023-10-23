#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <limits.h> 
#include <readline/readline.h>
#include <readline/history.h>

// clear the screen 
#define clear() printf("\033[H\033[J")

#define MAXCOM 1000
#define MAXLIST 100
// #define PATH_MAX 1000

void exeCmd(char **argv);
void init_shell();
int takeInput(char* str);
int processString(char* str, char **parsed, char **parsedpipe);
void exeCmdPiped(char ** parsed, char ** parsedpipe);
void openHelp();
int parsePipe(char * str, char ** strpiped);
char *get_location(char *command);
int ownCmdHandler(char** parsed);