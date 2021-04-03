#include <stdio.h>
#include <stdlib.h>
#include "utils/memory.h"


int main(int argc, char const *argv[])
{
   // initialisation de la mémoire
   int n = initMemory(1000);
   if(n == -1){
      perror("Erreur dans l'allocation de la grande structure\n");
      exit(1);
   }

   // allocation avec myAlloc
   char* tab = myAlloc(sizeof(int) * 44);
   int* tab2 = myAlloc(sizeof(int)*30);
   
   myFree(tab2);
   
   if(tab == NULL){
      perror("erreur d'allocation memoire\n");
      exit(2);
   }

   for (int i = 0; i < 9; i++)
   {
      tab[i] = 'a';
      printf(" %c ", tab[i]);
   }

   // Liberation tableau
   myFree(tab);
   // Liberation st ructure
   freeMemory();
   
   return 0;
}
