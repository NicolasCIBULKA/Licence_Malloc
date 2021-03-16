#include <stdio.h>
#include "structures.h"


/**
 * @brief The structure of the Memory
 * 
 */
typedef struct{
    int totalSize;  //!< The total size of the memory
    int usedSize;   //!< The used size of the memory
    int mutex;      //!< The mutex of the memory, to guarantee the unicity of the access to the memory
    Header begin;   //!< The first element of the list of blocks
    Header end;     //!< The last element of the list of blocks
}Memory;

// functions

int initMemory(int);

int freeMemory();

int isMemoryFree();

void* myAlloc(int);

int myFree(void*);

