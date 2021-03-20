/**
 * @file memory.c
 * @author Nicolas CIBULKA - Kevin BERNARD - Aelien MOUBECHE
 * @brief This file is the .c that allow to do all the operations of allocation/free on the memory
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "memory.h"
#include "ipcTools.h"

/**
 * @brief The memory variable that will store all the allocated elements
 * 
 */
Memory memory;

/**
 * @brief Function to initiate the memory list
 * 
 * @param n Represent the size of the great structure that will contains all the allocated elements
 * @return An Integer that will be 0 if an error occured, or the size given in parameter if the operation succeed 
 */
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

/**
 * @brief This function will free the great Memory structure
 * 
 * @return An Integer that wille be the size that the function has got back, or -1 if an error occured
 */
int freeMemory(){
    // free the mutex
    mutfree(memory.mutex);
}

/**
 * @brief This function will check if the great Memory structure is empty
 * 
 * @return An Integer that is 1 if the structure is empty, 0 if not
 */
int isMemoryFree(){
    if(memory.begin == NULL && memory.end == NULL){
        return 1;
    }
    return 0;
}

/**
 * @brief This function will do the allocation of a block, according to the size given in parameter
 * 
 * @param size The size of the data block we want
 * @return A void* which is the adress of the data block
 */
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
    memory.usedSize += size;

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

/**
 * @brief The Function that free the memory block given in parameter 
 * 
 * @param p The pointerto the data block
 * @return an Integer the size of the memory removed
 */

int myFree(void *p)
{
    Header header;
    Header tmp;
    void *progBreak;

    // test that p is a block
    if (!p){
        return 1;
    }
    // starting a critical section
    P(memory.mutex);
    
    header = (Header*)p - 1;
    progBreak = sbrk(0);

    if ((char*)p + header->size == progBreak) {
        if (memory.begin == memory.end) {
            memory.begin = memory.end = NULL;
        } else {
            tmp = memory.begin;
            while (tmp) {
                if(tmp->next == memory.end) {
                    tmp->next = NULL;
                    memory.end = tmp;
                }
                tmp = tmp->next;
            }
        }
        memory.usedSize -= header->size;
        sbrk(0 - sizeof(header) - header->size);
        V(memory.mutex);
        return 0;
    }
    header->isFree = 1;
    V(memory.mutex);
}

