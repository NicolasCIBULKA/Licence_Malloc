#include <stdio.h>
#include "utils/memory.h"


int main(int argc, char const *argv[])
{
   int n = initMemory(1000);
   printf("%d\n", n);
   printf("test");
   
   int* testtab = myAlloc(sizeof(int)*4);
   
   printf("%s", testtab);
   
   testtab[0] = 1;
   
   testtab[1] = 3;
   testtab[2] = 2;
   testtab[3] = 5;
   for(int i = 0; i < 4; i++){
      printf("%d - ", testtab[i]);
   }
   
   return 0;
}
