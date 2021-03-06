
/**
 * file that defines the global structures of the allocation functions
 */

typedef struct cell{
    int size;
    int isFree;
    struct cell *next;
}*Header;

Header initHeader(int);

