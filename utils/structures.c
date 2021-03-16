/**
 * @file structures.c
 * @author Nicolas CIBULKA - Kevin BERNARD - Aelien MOUBECHE 
 * @brief this file is the .c used to manipulate the header block 
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "ipcTools.h"

/**
 * @brief This function will intialise a header for a data block with a given size for the data
 * 
 * @param size the size of the allocated data block
 * @return the header of the data block
 */
Header initHeader(int size){
    Header header;
    header->isFree = 1;
    header->size = size;
    return header;
}

