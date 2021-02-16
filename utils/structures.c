#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

/**
 * Initialize the structure that will contain all the datas stored by myalloc
 */

Ribbon initRibbon(int size){
    Ribbon ribbon;
    ribbon.tab = malloc(sizeof(void)*size);
    ribbon.size = size;
    return ribbon;
}


/**
 * release the global structure that contains all the data
 */
void freeRibbon(Ribbon ribbon){
    free(ribbon.tab);
}

/**
 * Initialize the list of adress that will point on datas stored on the ribbon
 */
List initList(){
    return NULL;
}

/**
 * release the global structure that contains all the adresses of datas stored in the ribbon
 */
void freeList(List *list){
    while (list != NULL)
    {
        List *cell = *list;
        list = (*list)->next;
        free(cell);
    }
}

/**
 * Release a cell ot the list
 */
List freeCell(List list, List cell){
        List tempList = list;
        while(tempList != NULL){
            if(tempList->next == cell){
                List tempCell = tempList;
                tempList->next = tempCell->next;
                free(tempCell);
            }
            tempList = tempList->next;
        }
        return list;
}




