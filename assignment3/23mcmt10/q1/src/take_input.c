#include "main.h"

// function to take input
int takeInput(char* str){
    char* buf;

    buf = readline("\n>");
    if(strlen(buf) != 0){
        add_history(buf);
        strcpy(str, buf);
        return 0;
    }else{
        return 1;
    }
}