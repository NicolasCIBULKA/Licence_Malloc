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
#include <stdlib.h>
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
int initMemory(int size){
    key_t key = ftok("/etc/passwd", 5);
    if(key == -1){
        return 0;
    }
    memory.mutex = mutalloc(key);
    memory.paginationPage = malloc(sizeof(PaginationUnit)*size);
    if(memory.paginationPage == NULL){
        return 0;
    }
    for(int i = 0; i < size; i++){
        memory.paginationPage[i] = initPaginationUnit();
    }
    memory.dataArray = initDataRibbon(size);
    if(memory.dataArray.ribbon == NULL){
        return 0;
    }
    return size;
    
}   

/**
 * @brief This function will free the great Memory structure
 * 
 * @return An Integer that wille be the size that the function has got back, or -1 if an error occured
 */
int freeMemory(){
    freeDataRibbon(&(memory.dataArray));
    free(memory.paginationPage);
    mutfree(memory.mutex);
}

/**
 * @brief This function will do the allocation of a block, according to the size given in parameter
 * 
 * @param size The size of the data block we want
 * @return A void* which is the adress of the data block
 */
void* myAlloc(int size){
    
    P(memory.mutex);
    
    if(memory.dataArray.usedSize + size > memory.dataArray.size){
        V(memory.mutex);
        return NULL;
    }
    
    PaginationUnit *unit = getFirstPaginationUnit();
    if(unit == NULL){
        V(memory.mutex);
        return NULL;
    }

    void* firstAdress = memory.dataArray.ribbon;
    void* startBlock =  getBestFit(size);
    
    if(startBlock == NULL){
        V(memory.mutex);
        return NULL;
    }

    int pos = startBlock - firstAdress;
    actualizeAllocatedMap(pos, size);

    unit->isFree = 0;
    unit->size = size;
    unit->zoneStart = startBlock;
    unit->zoneEnd = startBlock+size;

    memory.dataArray.usedSize += size;
    V(memory.mutex);
    return unit->zoneStart;
}

/**
 * @brief The Function that free the memory block given in parameter 
 * 
 * @param p The pointer to the data block
 * @return an Integer the size of the memory removed
 */
int myFree(void *p)
{
    P(memory.mutex);
    for(int i = 0; i < memory.dataArray.size; i++){
        if(memory.paginationPage[i].zoneStart == p){
            int size = memory.paginationPage[i].size;
            void* startMem = &memory.dataArray.ribbon[0];
            int startZone = startMem - memory.paginationPage[i].zoneStart;
            resetAllocatedMap(startZone, size);
            resetPaginationUnit(&memory.paginationPage[i]);
            memory.dataArray.usedSize-=size;
            V(memory.mutex);
            return size;
        }
    }    
}


/**
 * @brief Get the First Pagination Unit object
 * 
 * @return PaginationUnit* 
 */
PaginationUnit* getFirstPaginationUnit(){
    for(int i = 0; i < memory.dataArray.size; i++){
        if(memory.paginationPage[i].isFree == 0){
            return &(memory.paginationPage[i]);
        }
        i++;
    }
    return NULL;
}

/**
 * @brief Get the adress of the first element of the dataArray that would have enough place after
 * This according to the best Fit Algorithm
 * @param size The needed size for the block 
 * @return void* : The adress of the first element of the block
 */
void* getBestFit(int size){
    // tableau d'indice de tout les espaces mémoires
    // on retire tout les espaces mémoires utilisés
    // on trouve le plus petit qui convient
    int deltaSize = memory.dataArray.size + 1;
    void* adress = NULL;
    int cursor = 0;
    if(memory.dataArray.usedSize == 0){
        adress = memory.dataArray.ribbon[0];
    }

    while(cursor < memory.dataArray.size){
        if(memory.dataArray.allocatedMap[cursor] == 0){
            int tempCursor = cursor;
            int tempSize = 0;
            do{
                tempSize++;
                tempCursor++;  
            }while(memory.dataArray.allocatedMap[tempCursor] != 1 && tempCursor < memory.dataArray.size);

            if(tempSize > size && deltaSize > (tempSize - size)){
                adress = &memory.dataArray.ribbon[cursor];
                deltaSize = tempSize - size;
            }
            cursor = tempCursor;
        }
        cursor++;
    }
    
    return adress;
}

/**
 * @brief This function will update the map of allocatedAdress, to help bestFit Algorithm later.
 * This will turn all the elements in the aimed area in 1 to say that those elements are allocoated
 * 
 * @param startPos : the starting position of the allocated area
 * @param size : the size of the allocated area
 */
void actualizeAllocatedMap(int startPos, int size){
    for(int i = startPos; i < startPos+size; i++){
        memory.dataArray.allocatedMap[i] = 1;
    }
}

/**
 * @brief This function will update the map of allocatedAdress, to help bestFit Algorithm later.
 * This will turn all the elements in the aimed area in 0 to say that those elements are now released
 * 
 * @param startPos 
 * @param size 
 */
void resetAllocatedMap(int startPos, int size){
    for(int i = startPos; i < startPos+size; i++){
        memory.dataArray.allocatedMap[i] = 0;
    }
}