#include <sys/types.h>

int semalloc(key_t key, int valInit);

void P(int semid);

void V(int semid);

int semfree(int semid);

int mutalloc(key_t key);

int mutfree(int semid);