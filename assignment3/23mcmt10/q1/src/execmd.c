#include "main.h"

// function for executing commands
void exeCmd(char **argv){
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

// function for executing piped commands
void exeCmdPiped(char ** parsed, char ** parsedpipe){

    // 0 is read end 1 is write end
    int pipefd[2];
    pid_t p1, p2;

    if(pipe(pipefd) < 0){
        perror("\npipe could not be created");
        return;
    }
    p1 = fork();
    if(p1 < 0){
        perror("\nfork failed");
        return;
    }
    if(p1 == 0){
        // child 1 process
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if(execvp(parsed[0], parsed) < 0){
            perror("\nError: could not execute command 1..");
            exit(0);
        }
    }else{
        // parent process
        p2 = fork();

        if(p2 < 0){
            printf("fork failed");
            return;
        }

        //child 2 process
        if(p2 ==0){
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if(execvp(parsedpipe[0], parsedpipe) < 0){
                perror("\nError: could not execute command 2..");
                exit(0);
            }
        }else{
            // parent process execution
            wait(NULL);
            wait(NULL);
        }
    }
}
    



