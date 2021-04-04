#include <stdio.h>
#include <stdlib.h>
#include "utils/memory.h"


int main(int argc, char const *argv[])
{
   // initialisation de la mémoire
   int n = initMemory(900);
   if(n == -1){
      perror("Erreur dans l'allocation de la grande structure\n");
      exit(1);
   }

   // allocation avec myAlloc
   char* tab = myAlloc(sizeof(char) * 44);
   if(tab == NULL){
      perror("erreur d'allocation memoire sur tab\n");
      exit(2);
   }
   printf("sizeof tab : %ld\n", sizeof(char)*44);


   int* tab2 = myAlloc(sizeof(int)*30);
   if(tab2 == NULL){
      perror("erreur d'allocation memoire sur tab2\n");
      exit(2);
   }
   printf("sizeof tab2 : %ld\n", sizeof(int)*30);


   int* tab3 = myAlloc(sizeof(int)*50);
   if(tab3 == NULL){
      perror("erreur d'allocation memoire sur tab3\n");
      exit(2);
   }
   printf("sizeof tab3 : %ld\n", sizeof(float)*50);

   printf("filling tab : ");
   for (int i = 0; i < 9; i++)
   {
      tab[i] = 'a';
      printf(" %c ", tab[i]);
   }
   printf("\n");

   // Liberation tableau
   myFree(tab);
   myFree(tab2);

   tab2 = myAlloc(sizeof(int)*30);
   if(tab2 == NULL){
      perror("erreur d'allocation memoire sur tab2\n");
      exit(2);
   }
   printf("sizeof tab2 : %ld\n", sizeof(int)*30);


   tab = myAlloc(sizeof(char) * 44);
   if(tab == NULL){
      perror("erreur d'allocation memoire sur tab\n");
      exit(2);
   }
   printf("sizeof tab : %ld\n", sizeof(char)*44);


   myFree(tab3);
   // Liberation st ructure
   freeMemory();
   
   return 0;
}
