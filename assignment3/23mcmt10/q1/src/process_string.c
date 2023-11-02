#include "main.h"

// function for parsing command words
void parseSpace(char * str, char ** parsed){
    int i;

    for(i = 0; i < MAXLIST; i++){
        parsed[i] = strsep(&str, " ");
        
        if(parsed[i] == NULL){
            break;
        }

        if(strlen(parsed[i]) == 0)
            i--;
        
    }
}

int processString(char* str, char **parsed, char **parsedpipe){
    char* strpiped[2];
    int piped = 0;
    piped = parsePipe(str,strpiped);

    if(piped){
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);
    }
    else{
        parseSpace(str, parsed);
    }

    // if(ownCmdHandler(parsed)){
    //     return 0; // own command
    // }
    // else{
        return 1 + piped; // system command
    // }
}