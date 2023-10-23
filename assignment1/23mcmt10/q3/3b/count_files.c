#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s path_directory\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *path_directory = argv[1];

    if (access(path_directory, F_OK) == -1) {
        perror("Directory not found");
        exit(EXIT_FAILURE);
    }

    int pipe_fd[2];
    pid_t child_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        close(pipe_fd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        close(pipe_fd[1]);

        execlp("ls", "ls", path_directory, NULL);

        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[1]);

        // Use 'grep' to count files
        dup2(pipe_fd[0], STDIN_FILENO);

        close(pipe_fd[0]);

        int wc_pipe_fd[2];

        if (pipe(wc_pipe_fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t wc_child_pid;

        if ((wc_child_pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (wc_child_pid == 0) {
            // Child process for 'grep'
            close(wc_pipe_fd[0]);

            // Redirect stdout to the write end of the pipe
            dup2(wc_pipe_fd[1], STDOUT_FILENO);

            close(wc_pipe_fd[1]);

            execlp("grep", "grep", "^A.*\\.txt$", NULL);

            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            close(wc_pipe_fd[1]);

            // Use 'wc' to count lines (files)
            dup2(wc_pipe_fd[0], STDIN_FILENO);

            close(wc_pipe_fd[0]);

            execlp("wc", "wc", "-l", NULL);

            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
