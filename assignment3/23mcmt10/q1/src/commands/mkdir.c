#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
        return 1;
    }

    // Create a directory with the specified name
    if (mkdir(argv[1], 0777) != 0) {
        perror("mkdir");
        return 1;
    }

    printf("Directory '%s' created successfully.\n", argv[1]);

    return 0;
}
