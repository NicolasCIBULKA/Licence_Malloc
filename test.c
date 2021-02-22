#include <stdio.h>
#include "utils/memory.h"

int main(int argc, char const *argv[])
{
   
   Memory mem = initMemory(10);
   printf("%d",mem.dataRibbon.size);
   return 0;
}
