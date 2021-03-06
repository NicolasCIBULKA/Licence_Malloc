#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "ipcTools.h"


Header initHeader(int size){
    Header header;
    header->isFree = 1;
    header->size = size;
    return header;
}

