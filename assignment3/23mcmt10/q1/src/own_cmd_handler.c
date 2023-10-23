#include "main.h"

//function to execute own commands

int ownCmdHandler(char** parsed){
    int NoOfOwnCmds = 5;
    int i = 0;
    int switchOwnArg  = -1;
  
    char* ListOfOwnCmds[NoOfOwnCmds];
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "compress";
    ListOfOwnCmds[4] = "extract";

    for(i = 0; i < NoOfOwnCmds; i++){
        if(strcmp(parsed[0], ListOfOwnCmds[i]) == 0){
            switchOwnArg = i;
            break;
        }
    }

    switch (switchOwnArg)
    {
    case 0:
        printf("\n\n....GoodBye...\nExiting shell....\n");
        exit(0);
        break;
    case 1:
        chdir(parsed[1]);
        return 1;
        break;
    case 2:
        openHelp();
        return 1;
    case 3:
        //compress(parsed[1]);
        return 1;
    case 4:
        //extract(parsed[1]);
        return 1;
    default:
        break;
    }

    return 0;
}