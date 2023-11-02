#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void countStats(FILE *file, const char *filename, int countLines, int countWords, int countChars);

int main(int argc, char *argv[]) {
    // Parse options
    int countLines = 0, countWords = 0, countChars = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            countLines = 1;
        } else if (strcmp(argv[i], "-w") == 0) {
            countWords = 1;
        } else if (strcmp(argv[i], "-c") == 0) {
            countChars = 1;
        }
    }

    if (!countLines && !countWords && !countChars) {
        // If no options provided, default to -lwc
        countLines = 1;
        countWords = 1;
        countChars = 1;
    }

    // Process input from the pipeline
    if (isatty(fileno(stdin))) {
        // No input from pipeline, use command line arguments as files
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                perror("Error opening file");
                return 1;
            }

            countStats(file, argv[i], countLines, countWords, countChars);

            fclose(file);
        }
    } else {
        // Input from pipeline, use stdin
        countStats(stdin, NULL, countLines, countWords, countChars);
    }

    return 0;
}


void countStats(FILE *file, const char *filename, int countLines, int countWords, int countChars) {
    int lines = 0, words = 0, characters = 0;
    int inWord = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        characters++;

        if (c == '\n') {
            lines++;
        }

        if (c == ' ' || c == '\t' || c == '\n') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    if (countLines) {
        printf("%7d", lines);
    }

    if (countWords) {
        printf("%7d", words);
    }

    if (countChars) {
        printf("%7d", characters);
    }

    if (filename != NULL) {
        printf(" %s", filename);
    }

    printf("\n");
}
