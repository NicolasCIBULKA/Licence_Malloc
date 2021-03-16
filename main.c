#include <stdio.h>
#include "utils/memory.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>

// prototype fonctions
void interactivemode(int argc, char* argv[]);
void commandeLineMode(int argc, char* argv[]);
void batchMode(int argc, char* argv[]);

// MAIN
int main(int argc, char *argv[])
{
    if(argc >= 2){
        // mode interactif
        if(!strcmp(argv[1], "-i")){
            printf("aa");
            interactivemode(argc, argv);
        }
        // mode ligne de commande
        else if(!strcmp(argv[1], "-f")){
            batchMode(argc, argv);
        }
        // mode batch
        else{
            commandeLineMode(argc, argv);
        }
    }
    return 0;
}

// CODE FONCTIONS

// mode interactif
void interactivemode(int argc, char* argv[]){
    printf("\n----- You picked the interactive mode -----\n");
}

// mode ligne de commande
void commandeLineMode(int argc, char* argv[]){
    printf("\n----- You picked the command line mode -----\n");

}

// mode batch
void batchMode(int argc, char* argv[]){
    printf("\n----- You picked the batch mode -----\n");
    // testing if the file name has been given
    if(argc < 3){
        perror("No file name has been given\n");
        exit(1);
    }

    // opening the file
    int fd = open(argv[2], O_RDONLY);
    if(fd == -1){
        perror("File does not exist");
        exit(2);
    }
    
    // reading lines of the file

}


