#include <stdio.h>

// Define a structure to represent a command
typedef struct {
    const char *name;
    const char *description;
} Command;

// Function to display help information for all commands
void displayHelp(const Command commands[], size_t numCommands) {
    printf("Welcome to ShellKhan!\n");
    printf("List of Commands:\n");

    for (size_t i = 0; i < numCommands; i++) {
        printf("%lu. %s - %s\n", i + 1, commands[i].name, commands[i].description);
    }

    printf("\nUsage: command [options]\n");
}

int main() {
    // Define an array of commands with their descriptions
    Command commands[] = {
        {"ls", "List files in the current directory"},
        {"ps", "Display process status"},
        {"man", "Display manual page for a command"},
        {"help", "Display help information"},
        {"exit", "Exit the shell"},
        {"cd", "Change the current directory"},
        {"wc", "Count lines, words, and characters in a file"},
        {"mkdir", "Create a new directory"},
        {"touch", "Create a new file"},
        {"cat", "Concatenate files and print their contents"},
        {"echo", "Print a string to standard output"},

        // Add more commands as needed
    };

    // Calculate the number of commands in the array
    size_t numCommands = sizeof(commands) / sizeof(commands[0]);

    // Display help information for all commands
    displayHelp(commands, numCommands);

    return 0;
}
