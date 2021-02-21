#include <stdio.h>
#include "structures.h"

// structures

typedef struct{
    Ribbon dataRibbon;
    List *memoryList;
}Memory;

// functions

Memory initMemory(int);