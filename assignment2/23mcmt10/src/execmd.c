#include "main.h"

void execmd(char **argv){
    char *command = NULL;
    char * actual_command = NULL;
    pid_t pid;

    if (argv){
        /* get the command */
        command = argv[0];

        actual_command = get_location(command);

        pid = fork();

        if (pid == -1){
            perror("Error:");
        }
        else if (pid == 0){
            /* child process */
            /* execute the command with execve */
            if (execve(actual_command, argv, NULL) == -1){
                perror("Error:");
                exit(1);
            };
        }
        else{
            /* parent process */
            int status;
            waitpid(pid, &status, 0); 
        }

        
    }

}
