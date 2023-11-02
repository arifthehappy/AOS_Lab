// #include "main.h"

// char *get_location(char *command) {
//     char *location;
//     char *location_copy;
//     char * path_token;
//     char *file_path;
//     size_t command_length;
//     size_t directory_length;
//     struct  stat statbuf;    

//     location = getenv("PATH");
    
//     if(location){
//         location_copy = strdup(location);
            
//         command_length = strlen(command);

//         path_token = strtok(location_copy, ":");

//         while(path_token != NULL){
//             directory_length = strlen(path_token);

//             file_path = malloc(command_length + directory_length + 2);
            
//             strcpy(file_path, path_token);
//             strcat(file_path, "/");
//             strcat(file_path, command);
//             strcat(file_path, "\0");

//             if(stat(file_path, &statbuf) == 0){
//                 free(location_copy);

//                 return (file_path);
//             }
//             else{
//                 free(file_path);
//                 path_token = strtok(NULL, ":");
//             }

            
//         }
//         free(location_copy);

//         if(stat(command, &statbuf) == 0){
//             return (command);
//         }

//         return (NULL);


        
//     }

//     return NULL;
// }


#include "main.h"

char *get_location(char *command) {
    char *file_path;
    struct stat statbuf;

    // Assuming your bin folder is located in the same directory as your src folder
    const char *bin_folder = "bin/commands";

    // Construct the full path for the command in the bin folder
    file_path = malloc(strlen(bin_folder) + 1 + strlen(command) + 1);
    strcpy(file_path, bin_folder);
    strcat(file_path, "/");
    strcat(file_path, command);
    strcat(file_path, "\0");

    // printf("file_path: %s\n", file_path);

    // Check if the command exists in the bin folder
    if (stat(file_path, &statbuf) == 0) {
        return file_path;
    }

    free(file_path);

    // If the command is not found in the bin folder, return NULL
    return NULL;
}
