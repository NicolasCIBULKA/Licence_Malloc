#include <stdio.h>
#include "memory.h"

// functions
Memory initMemory(int nBytes){
    // fork à faire ?
    // communication par tube pour les alloc/free/desalloc ?
    Memory memory;
    memory.dataRibbon = initRibbon(nBytes);
    memory.memoryList = initList();
    return memory;
}