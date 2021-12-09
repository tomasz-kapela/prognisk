#include <cstdio>
#include <time.h>
#include <cstdlib>
using namespace std;

extern "C" void minmax(int n, int * tab, int * max, int * min);

int main(){

   const int rozmiar = 100000;
   const int liczba_powtorzen = 10000;

   int tab[rozmiar];
   srand(2021);

   for(int i=0; i<rozmiar; ++i){
     tab[i] = rand() % 20192020 - 10000000;
   }
   tab[rozmiar-1] = -20000000;
   int min, max;
   
   clock_t start, stop;
   start = clock();

   for(int i=0; i<liczba_powtorzen; i++){
      minmax(rozmiar, tab, &max, &min);
   }
   printf("min = %d    max = %d\n", min, max);
   
   stop = clock();
   printf("\n time = %f ( %ld cykli)", (stop - start)*1.0/CLOCKS_PER_SEC, (stop - start));
   return 0;
}
/*
  min = -20000000    max = 10191479
*/

