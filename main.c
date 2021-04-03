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
    // mode interactif
    if(!strcmp(argv[1], "-i")){
        interactivemode(argc, argv);
    }
    // mode batch
    else if(!strcmp(argv[1], "-f")){
        batchMode(argc, argv);
    }
    // mode ligne de commande
    else{
        commandeLineMode(argc, argv);
    }
    return 0;
}

// CODE FONCTIONS

// mode interactif
void interactivemode(int argc, char* argv[]){
    printf("\n----- You picked the interactive mode -----\n");
    // initial command description
    interactivemodehelp();

    // buffer and boolean initialisation
    char buffer[40];
    int running = 1;

    // scanning for inputs while the user doesn't exit interactive mode
    while(running){
        // interactive mode interface
        printf(">");
        scanf('%s',buffer);

        // pre-parsing to handle the specific interactive mode commands
        if(!strcmp(buffer,"help")){
            interactivemodehelp();

        }else if (!strcmp(tabline[0],"exitmode")){
            // loop variant set to false = 0
            running = 0;

        }else {
            // empty command
            if(strlen(buffer)==0){
                perror('No command given, try help for a list of command');

            }else{
                // sending the cmd to the parser
                languageParser(buffer);
            }
        }

        // preparing for next command
        printf('\n');
    } 

    printf("\n----- End of interactive mode -----\n");
}

void interactivemodehelp(){
    // explaining the command's syntax
    printf("\n----- Command list for interactive mode -----\n");
    printf(" > init [size] : InitMemory with given [size]\n");
    printf(" > [nameVar] alloc [size] : allocating [size] to your [nameVar] variable\n");
    printf(" > free [nameVar] : free the allocated memory for [nameVar] variable\n");
    printf(" > close memory : freeMemory and end of function\n");
    printf("----- Interactive mode specific -----\n");
    printf(" > help  : get a reminder of these commands\n");
    printf(" > exitmode  : exit the interactive mode\n");
}



// mode ligne de commande
void commandeLineMode(int argc, char* argv[]){
    printf("\n----- You picked the command line mode -----\n");
    // testing if command has been given
    if(argc < 2){
        perror("No command has been given\n");
        exit(1);
    }
    char templine[1000] = " ";
    for(int i = 1; i < argc; i++){
        strcat(templine," " );
        strcat(templine, argv[i]);
    }

    // command line division
    char* delim = ",";
    int nbCmd = 0;
    argv++;

    char* tabcmdline[100];
    tabcmdline[0] = strtok(templine, delim);
    
    while(tabcmdline[nbCmd] != NULL) {
        tabcmdline[++nbCmd] = strtok(NULL, delim);
    }
    
    // reading columns of the table containing all commands
    for(int index=0; index < nbCmd; index++) {
        //printf("%s", tabcmdline[index]);
        languageParser(tabcmdline[index]);
    }
    
    printf("\n----- End of command line mode ----- \n ");
}
// mode batch
void batchMode(int argc, char* argv[]){
    printf("\n----- You picked the batch mode -----\n\n");
    // testing if the file name has been given
    if(argc < 3){
        perror("No file name has been given\n");
        exit(1);
    }
   

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
        int sizeAllocate = initMemory( atoi(tabline[1]));
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
        tabVar[currentPos] = myAlloc( atoi(tabline[2]));
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
            //printf("\n%s,%s", tabNomVar[researchCursor], tabline[1]);
            if(!strcmp(tabNomVar[researchCursor], tabline[1])){
                resultFree = myFree(tabVar);
                freeDone = 1;
            }
            researchCursor++;
        }
        if(freeDone == 1){
            perror("Variable hasn't been freed, maybe this variable doesn't exist \n");
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
