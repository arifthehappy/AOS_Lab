#include <stdio.h>
#include <string.h>

void displayManPage(const char *command) {
    printf("Manual page for %s:\n", command);

    if (strcmp(command, "ls") == 0) {
        printf("NAME\n");
        printf("    ls - list files in a directory\n\n");
        printf("SYNOPSIS\n");
        printf("    ls [OPTION]... [FILE]...\n\n");
        printf("DESCRIPTION\n");
        printf("    List information about the FILEs (the current directory by default).\n");
        // Add more details for ls command as needed
    } else if (strcmp(command, "ps") == 0) {
        printf("NAME\n");
        printf("    ps - display process status\n\n");
        printf("SYNOPSIS\n");
        printf("    ps [OPTION]...\n\n");
        printf("DESCRIPTION\n");
        printf("    Report a snapshot of the current processes.\n");
        // Add more details for ps command as needed
    
    } else {
        printf("No manual entry available for %s\n", command);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s command\n", argv[0]);
        return 1;
    }

    displayManPage(argv[1]);

    return 0;
}
