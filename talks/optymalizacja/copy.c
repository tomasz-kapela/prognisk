#include <stdio.h>
#include <time.h>

#ifndef COPY
#define COPY copy
#endif

void COPY(int *dest, int *src, int n);

//~ #define rozmiar 1000000
//~ #define N 10000
#define rozmiar 10000
#define N 1000000


int main(){
	  clock_t start = clock();
    
    int i;
    int src[rozmiar] = {1, 2, 3};
    src[rozmiar-1] = -1;
    int dest[rozmiar];
    
    for(i=0; i<N; ++i){
        COPY(dest, src, rozmiar);
    }
    for(i=0; i<10; ++i){
        printf("%d ", dest[i]);
    } 

    clock_t end = clock();
	  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\n time = %f\n", seconds);

    return 0;
}
