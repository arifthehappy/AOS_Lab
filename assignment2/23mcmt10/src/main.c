#include "main.h"


int main(int ac, char **argv){
    struct passwd *pw;
    char *username;
    char hostname[256];
    char cwd[PATH_MAX];
    char prompt[PATH_MAX + 512];
    
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;

    /* declaring void variables */
    (void)ac;

    /* get the username */
    pw = getpwuid(getuid());
    if(pw){
        username = pw->pw_name;
    }else{
        username = "unknown";
    }

    /* get the hostname */
    if(gethostname(hostname, sizeof(hostname)) == -1){
        perror("gethostname");
        return (-1);
    }

    /*welcome message for ShellKhan*/
    printf("Welcome to the ShellKhan!\n");


    /* Create a loop for the shell's prompt */
    while (1) {
        /* get the current working directory */
        if (getcwd(cwd, sizeof(cwd)) == NULL){
            perror("getcwd");
            return (-1);
        }

        /*construct the prompt*/
        snprintf(prompt, sizeof(prompt), "%s@%s:%s$ ", username, hostname, cwd);

        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */ 
        if (nchars_read == -1){
            printf("\nGoodBye...\nExiting shell....\n");
            return (-1);
        }

        /* allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy== NULL){
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL){
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++){
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* execute the command */
        execmd(argv);

    } 


    /* free up allocated memory */ 
    free(lineptr_copy);
    free(lineptr);

    return (0);
}
