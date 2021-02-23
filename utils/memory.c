#include <stdio.h>
#include "memory.h"

// functions
Memory initMemory(int nBytes){

    Memory memory;
    memory.dataRibbon = initRibbon(nBytes);
    memory.memoryList = initList();
    
    return memory;
}