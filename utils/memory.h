#include <stdio.h>
#include "structures.h"
// structures

typedef struct{
    int totalSize;
    int usedSize;
    int mutex;
    Header begin;
    Header end;
}Memory;

// functions

int initMemory(int);

int freeMemory();

int isMemoryFree();

void* myAlloc(int);

int myFree(void*);

