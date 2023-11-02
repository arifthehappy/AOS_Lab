#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

void listFiles(const char *path, int showHidden);

int main(int argc, char *argv[]) {
    int showHidden = 0;
    int opt;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                showHidden = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // If no directory is specified, list the current directory
    if (optind == argc) {
        listFiles(".", showHidden);
    } else {
        // List the specified directories
        for (int i = optind; i < argc; i++) {
            listFiles(argv[i], showHidden);
        }
    }

    return 0;
}

void listFiles(const char *path, int showHidden) {
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Check if hidden files should be displayed
        if (showHidden || entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}
