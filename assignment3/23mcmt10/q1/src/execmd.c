#include "main.h"

// function for executing commands
void exeCmd(char **argv){
    char *command = NULL;
    char * actual_command = NULL;
    pid_t pid;

    if (argv){
        /* get the command */
        command = argv[0];

        // if command is exit, exit the shell
        if (strcmp(command, "exit") == 0){
                printf("GoodBye...\nExiting shell....\n");
            exit(0);
        }

        actual_command = get_location(command);

        pid = fork();

        if (pid == -1){
            perror("Error:");
        }
        else if (pid == 0){
            /* child process */

            //check for output redirection
            int i = 0;
        int output_redirection = 0;
        while (argv[i] != NULL) {
            if (strcmp(argv[i], ">") == 0) {
                output_redirection = 1;
                break;
            }
            i++;
        }

        if (output_redirection) {
            // Output redirection detected
            int file_descriptor = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (file_descriptor < 0) {
                perror("\nError opening file for redirection");
                exit(0);
            }

            // Redirect standard output to the file
            dup2(file_descriptor, STDOUT_FILENO);

            // Close the file descriptor
            close(file_descriptor);

            // Replace '>' and the filename with NULL to avoid them being passed as arguments
            argv[i] = NULL;
            argv[i + 1] = NULL;
        }

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

        char *actual_command = get_location(parsed[0]);
        if (actual_command == NULL) {
            perror("\nError: could not find command 1..");
            exit(0);
        }

        if(execve(actual_command, parsed, NULL) < 0){
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

            char *actual_command = get_location(parsedpipe[0]);
            if (actual_command == NULL) {
                perror("\nError: could not find command 2..");
                exit(0);
            }

            if(execve(actual_command, parsedpipe, NULL) < 0){
                perror("\nError: could not execute command 2..");
                exit(0);
            }
        }else{
            // parent process execution
            close(pipefd[0]);
            close(pipefd[1]);
            
            // wait for both child to finish            
            wait(NULL);
            wait(NULL);
        }
    }
}
    



