#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "memory.h"
#include "ipcTools.h"

Memory memory;

int initMemory(int n){
    if(isMemoryFree()){
        // initialise the memory
        memory.usedSize = 0;
        memory.totalSize = n;
        memory.begin = NULL;
        memory.end = NULL;
        // mutex to guarantee a unique access to memory
        key_t key = ftok("/etc/passwd", 10);
        memory.mutex = mutalloc(key);
        return n;
    }
    return 0;
}

int freeMemory(){
    // free the mutex
    mutfree(memory.mutex);
}

int isMemoryFree(){
    if(memory.begin == NULL && memory.end == NULL){
        return 1;
    }
    return 0;
}

void* myAlloc(int size){
    // initiate variables
    void* block;
    Header header;
    
    // test that size is positive
    if(size < 0 || memory.usedSize+size > memory.totalSize){
        return NULL;
    }

    // starting a critical section
    P(memory.mutex);

    // allocating memory for datas
    int totalSize = sizeof(header) + size;
    block = sbrk(totalSize);

    // if error in allocation, exit
    if(block == (void*) -1){
        V(memory.mutex);
        return NULL;
    }

    // set memory block & fill header
    header = block;
    header->next = NULL;
    header->size = size;
    header->isFree = 0;

    // put memory block in the Memory
    if(memory.begin == NULL){
        memory.begin = header;
    }
    if(memory.end != NULL){
        memory.end->next = header;
    }
    memory.end = header;

    // end of critical section
    V(memory.mutex);
    return (void*) header+(sizeof(header));
}

int myFree(void* p){
    
}

