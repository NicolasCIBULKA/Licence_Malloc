/**
 * file that defines the global structures of the allocation functions
 */

typedef struct cell{
    void* adress;
    int size;
    struct cell *next;
}*List;

typedef struct{
    void* tab;
    int size;
}Ribbon;

/**
 * Prototypes of the functions of the Ribbon 
 */

Ribbon initRibbon(int);

void freeRibbon(Ribbon);




/**
 * Prototypes of the functions of the List
 */

List initList();

void freeList(List*);

List freeCell(List, List);
