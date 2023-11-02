#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    // Open the current directory
    DIR *dir = opendir(".");

    // Check if the directory opened successfully
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read the directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}
