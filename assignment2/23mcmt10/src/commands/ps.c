#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#define MAX_BUF 1024
#define TICKS_PER_SECOND sysconf(_SC_CLK_TCK)

int main() {
    DIR *dir;
    struct dirent *entry;

    printf("%-8s %-10s %-15s %s\n", "PID", "TTY", "TIME", "CMD");

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Error opening /proc");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a directory and its name is a number (process ID)
        if (entry->d_type == DT_DIR) {
            int pid = atoi(entry->d_name);
            if (pid > 0) {
                char stat_path[MAX_BUF];
                snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);

                // Read the process status information
                FILE *file = fopen(stat_path, "r");
                if (file != NULL) {
                    int ppid, tty_nr;
                    char comm[MAX_BUF];
                    unsigned long utime, stime;

                    // Parse the process status
                    fscanf(file, "%*d %s %*c %d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %lu", comm, &ppid, &tty_nr, &utime, &stime);

                    // Get the terminal associated with the process
                    char tty[MAX_BUF] = "???";
                    if (tty_nr > 0) {
                        snprintf(tty, sizeof(tty), "/dev/tty%d", tty_nr);
                    }

                    // Calculate the total CPU time in seconds
                    unsigned long total_seconds = (utime + stime) / TICKS_PER_SECOND;

                    // Display the process information
                    printf("%-8d %-10s %02lu:%02lu:%02lu %s\n", pid, tty, total_seconds / 3600, (total_seconds % 3600) / 60, total_seconds % 60, comm);

                    fclose(file);
                }
            }
        }
    }

    closedir(dir);

    return 0;
}
