#include <stdio.h>
#include <stdlib.h>
#include <utime.h>
#include <sys/stat.h>
#include <time.h>  // Include this header for the time function

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file_name\n", argv[0]);
        return 1;
    }

    // Open the file or create it if it doesn't exist
    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Close the file
    fclose(file);

    // Update the access and modification times to the current time
    struct utimbuf utime_buf;
    utime_buf.actime = utime_buf.modtime = time(NULL);

    if (utime(argv[1], &utime_buf) != 0) {
        perror("utime");
        return 1;
    }

    printf("File '%s' created or updated successfully.\n", argv[1]);

    return 0;
}
