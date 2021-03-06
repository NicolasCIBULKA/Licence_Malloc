#include <stdio.h>
#include "memory.h"

Memory memory;

int initMemory(int n){
    if(isMemoryFree()){
        memory.usedSize = 0;
        memory.totalSize = n;
        memory.begin = NULL;
        memory.end = NULL;
        return n;
    }
    return 0;
}

int freeMemory(){
    
}

int isMemoryFree(){
    if(memory.begin == NULL && memory.end == NULL){
        return 1;
    }
    return 0;
}

void* myAlloc(int n){

}

int myFree(void* p){
    
}

