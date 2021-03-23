#include <stdio.h>
#include "utils/memory.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>

// Constantes
#define SIZETAB 100

// prototype fonctions
void interactivemode(int argc, char* argv[]);
void commandeLineMode(int argc, char* argv[]);
void batchMode(int argc, char* argv[]);
void languageParser(char* line);



// variables globales
char* tabNomVar[SIZETAB];  // tab des pointeurs vers les zones mémoires allouées
void* tabVar[SIZETAB];     // tab des noms de variables. La variable a la place i sera la zone mémoire à la position i dans le tableau de zones mémoires   
char* tabline[100];
char line[250];
int currentPos = 0; 


// MAIN
int main(int argc, char *argv[])
{
    if(argc >= 2){
        // mode interactif
        if(!strcmp(argv[1], "-i")){
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
    printf("\n----- You picked the batch mode -----\n\n");
    // testing if the file name has been given
    if(argc < 3){
        perror("No file name has been given\n");
        exit(1);
    }
    //char test[] = "init en 32 3";
    //printf(test);
    

    // opening the file
    FILE* file = fopen(argv[2], "r");
    if(!file){
        perror("File does not exist\n");
        exit(2);
    }
    
    // reading lines of the file
    while(fgets(line, 100, file) != NULL){
        languageParser(line);
    }
    printf("\n----- End of batch mode ----- \n ");
}

void languageParser(char* line){
    char* delim = " ";
    
    *tabline = strtok(line, delim);
    
    int n = 1;
    while(tabline[n-1] != NULL){
        tabline[n++] = strtok(0, " ");
    }    
    
    if(!strcmp(tabline[0],"init")){
        int sizeAllocate = initMemory( atoi(tabline[2]));
        if(sizeAllocate == 0){
            perror("An error has occured while executing InitMemory !\n");
            exit(4);
        }
        printf("InitMemory done - success \n");
    }
    else if(!strcmp(tabline[1],"alloc")){
        // enregistrement de la variable
        char* nomVar = tabline[0];
        tabNomVar[currentPos] = nomVar;

        // allocation
        tabVar[currentPos] = myAlloc( atoi(tabline[3]));
        if(tabVar[currentPos] == NULL){
            perror("An error has occured while executing MyAlloc !\n");
            exit(5);
        }
        // on incremente la position du curseur d'allocation 
        currentPos++;

        printf("MyAlloc done - success\n");

    }
    else if(!strcmp(tabline[0],"free")){
        int researchCursor = 0;
        int freeDone = 0;
        int resultFree = 0;
        while(researchCursor < currentPos && freeDone == 0){
            if(!strcmp(tabNomVar[researchCursor], tabline[2])){
                printf("\n%s\n",tabNomVar[researchCursor]);
                resultFree = myFree(tabVar);
                freeDone = 1;
            }
            researchCursor++;
        }
        if(freeDone == 1){
            perror("Variable hasn't been free, maybe this variable doesn't exist \n");
            exit(6);
        }
        else if(resultFree == -1){
            perror("An error has occured while executing MyFree ! \n");
            exit(7);
        }
        printf("myFree done - success\n");
        
    }
    else if(!strcmp(tabline[0],"close")){
        freeMemory();
        printf("freeMemory done - success\n");
    }
    else{
        printf("Error - Instruction not understood\n");
    }
    
}
