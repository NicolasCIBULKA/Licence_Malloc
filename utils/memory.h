#include <stdio.h>
#include "structures.h"


/**
 * @brief The structure of the Memory
 * 
 */
typedef struct{
    PaginationUnit* paginationPage;
    DataRibbon dataArray;
    int mutex;

}Memory;

// ----- Usable functions -----

int initMemory(int size);

int freeMemory();

void* myAlloc(int);

int myFree(void*);

// ----- Helpful functions -----

PaginationUnit* getFirstPaginationUnit();

void* getBestFit(int size);

void actualizeAllocatedMap(int startPos, int size);

void resetAllocatedMap(int startPos, int size);