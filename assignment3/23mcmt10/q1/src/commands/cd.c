#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void changeDirectory(char *arg) {
    if (arg == NULL) {
        // If no argument is provided, print an error message
        fprintf(stderr, "cd: missing argument\n");
    } else {
        // Attempt to change the directory
        if (chdir(arg) != 0) {
            perror("cd");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return 1;
    }

    changeDirectory(argv[1]);

    return 0;
}
