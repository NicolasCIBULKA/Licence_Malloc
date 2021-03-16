/**
 * @file structures.c
 * @author Nicolas CIBULKA - Kevin BERNARD - Aelien MOUBECHE 
 * @brief this file is the .h used to manipulate the header block 
 * @version 0.1
 * @date 2021-03-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */


/**
 * @brief The structure for a header block
 * 
 */
typedef struct cell{
    int size;           //!< The size of the data block
    int isFree;         //!< a boolean to say of the block is free or not
    struct cell *next;  //!< the adress of the next block of data
}*Header;

Header initHeader(int);

