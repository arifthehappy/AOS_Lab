#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return 1;
    }

    char *input_file_name = argv[1];
    char *output_file_name = "output.txt";

    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Unable to open input file %s\n", input_file_name);
        return 1;
    }

    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Unable to open output file %s\n", output_file_name);
        fclose(input_file);
        return 1;
    }

    char line[128];
    while (fgets(line, sizeof(line), input_file) != NULL) {
        int input_number, base_input, base_conversion;
        if (sscanf(line, "%d %d %d", &input_number, &base_input, &base_conversion) == 3) {
            // Convert the input number from base_input to base_conversion
            char command[256];
            snprintf(command, sizeof(command), "echo 'obase=%d; ibase=%d; %d' | bc", base_conversion, base_input, input_number);
            FILE *bc_process = popen(command, "r");
            if (bc_process == NULL) {
                fprintf(stderr, "Error: Unable to execute bc\n");
                fclose(input_file);
                fclose(output_file);
                return 1;
            }

            char converted_number[128];
            if (fgets(converted_number, sizeof(converted_number), bc_process) != NULL) {
                // Write the converted number to the output file
                fprintf(output_file, "%s", converted_number);
                // Print the converted number
                printf("%s", converted_number);
            } else {
                fprintf(stderr, "Error: Conversion failed\n");
            }

            pclose(bc_process);
        } else {
            fprintf(stderr, "Invalid input line: %s", line);
        }
    }

    fclose(input_file);
    fclose(output_file);

    printf("Conversion completed. Results are stored in %s\n", output_file_name);

    return 0;
}
