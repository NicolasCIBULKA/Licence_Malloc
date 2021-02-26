#include <stdio.h>
#include "structures.h"


// structures

typedef struct{
    int totalSize;
    int usedSize;
    Header *begin;
    Header *end;
}Memory;

// functions

int initMemory(int);

int freeMemory();

int isMemoryFree();
