#include "main.h"

// function for finding pipe 
int parsePipe(char * str, char ** strpiped){
    int i;

    for(i = 0; i < 2; i++){
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
        {
            break;
        }
    }

    if(strpiped[1] == NULL){
        return 0; // no pipe
    }
    else{
        return 1; // has pipe
    }

}

