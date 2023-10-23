// program to kill process which utilizes more tha 50% CPU
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define LOG_FILE "killLog.csv"

// get current date and time
char *getCurrentDateTime() {
    time_t now = time(0);
    struct tm tStruct;
    static char buf[80];
    tStruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tStruct);
    return buf;
}

int main(){
    FILE* log_file = fopen(LOG_FILE, "a");
    
    if(log_file == NULL){
        perror("Error opening log file");
        return 1;
    }

    while (1){
        // get process information
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        FILE* proc_info = popen("ps -eo pid,%cpu,comm --sort=-%cpu --no-headers", "r");
        if(proc_info == NULL){
            perror("Error opening process info");
            fclose(log_file);
            return 1;
    
        }

        // read process info
        while(fgets(buffer, sizeof(buffer), proc_info) != NULL){
            int pid;
            float cpu_usage;
            char process_name[256];

            if(sscanf(buffer, "%d %f %s", &pid, &cpu_usage, process_name) == 3){
                if(cpu_usage > 50.0){
                    //log
                    char* datetime = getCurrentDateTime();
                    fprintf(log_file, "%d,%s,%f\n", pid, datetime, cpu_usage);
                    fflush(log_file);

                    // kill process
                    char kill_command[256];
                    sprintf(kill_command, "kill -9 %d", pid);
                    system(kill_command);

                    printf("Process %d killed\n", pid);
                }
            }
        }

        pclose(proc_info);

        sleep(5);
    }

    fclose(log_file);
    return 0;
}