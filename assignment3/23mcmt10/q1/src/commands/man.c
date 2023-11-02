#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayManPage(const char *command) {
    char filename[50];
    FILE *file;

    snprintf(filename, sizeof(filename), "man/%s.1", command);
    file = fopen(filename, "r");

    if (file != NULL) {
        char line[256];

        while (fgets(line, sizeof(line), file) != NULL) {
            if (line[0] == '.') {
                // This line starts with a troff macro
                if (strncmp(line, ".SH", 3) == 0) {
                    printf("\n%s", line);
                } else if (strncmp(line, ".B", 2) == 0) {
                    printf("\033[1m%s\033[0m", line + 2); // Print bold text
                } else {
                    printf("%s", line);
                }
            } else {
                // Regular text
                printf("%s", line);
            }
        }

        fclose(file);
    } else {
        perror("Failed to open");
        printf("No manual entry available for %s\n", command);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s command\n", argv[0]);
        return 1;
    }

    printf(".TH %s 1 \"October 2023\" \"User Commands\"\n", argv[1]);
    displayManPage(argv[1]);

    return 0;
}
