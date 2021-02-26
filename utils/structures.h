#include <stdio.h>

/**
 * file that defines the global structures of the allocation functions
 */

typedef struct cell{
    int size;
    int isFree;
    int mutex;
    struct cell *next
}*Header;

Header initHeader(int);


