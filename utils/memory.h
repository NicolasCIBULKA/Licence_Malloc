#include <stdio.h>
#include "structures.h"


// structures

typedef struct{
    int totalSize;
    int usedSize;
    Header *begin;
    Header *end;
}HeaderList;

