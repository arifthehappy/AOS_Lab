#include <stdio.h>

int main(int argc, char *argv[]) {
    // Loop through command-line arguments and print them
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);

        // Add a space between arguments, except for the last one
        if (i < argc - 1) {
            printf(" ");
        }
    }

    // Print a newline character at the end
    printf("\n");

    return 0;
}
