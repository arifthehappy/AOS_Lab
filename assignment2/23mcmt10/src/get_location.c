#include "main.h"

char *get_location(char *command) {
    char *location;
    char *location_copy;
    char * path_token;
    char *file_path;
    size_t command_length;
    size_t directory_length;
    struct  stat statbuf;    

    location = getenv("PATH");
    
    if(location){
        location_copy = strdup(location);
            
        command_length = strlen(command);

        path_token = strtok(location_copy, ":");

        while(path_token != NULL){
            directory_length = strlen(path_token);

            file_path = malloc(command_length + directory_length + 2);
            
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, command);
            strcat(file_path, "\0");

            if(stat(file_path, &statbuf) == 0){
                free(location_copy);

                return (file_path);
            }
            else{
                free(file_path);
                path_token = strtok(NULL, ":");
            }

            
        }
        free(location_copy);

        if(stat(command, &statbuf) == 0){
            return (command);
        }

        return (NULL);


        
    }

    return NULL;
}
