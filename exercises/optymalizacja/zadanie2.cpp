#include <stdio.h> 
#include <cstdlib>
#include "Timer.h"
using namespace std;

extern "C" void obliczSSE(float * wynik, float *a, float *b, float x, int n);

int main(void) { 
  const int liczbaPowtorzen = 1000;    
  const int N=20;
  float a[N] = {0, 1, 3, 3, -2, -2, -3, -4, 100000, 1};
  float b[N] = {0, 1, 2, 2, -1, -1, -3, -4, 100000, 1};
  srand(2021);
  for(int i=10; i<N; i++){
	  a[i] = rand() % 2000 - 1000;
	  b[i] = rand() % 4000 - 1000;
  }
  float wynik[N];
  float x = 4;
  
  
  Timer time("Czas obliczen");
	for(int i=0; i<liczbaPowtorzen; ++i){
		obliczSSE(wynik, a, b, x, N);
	}
  time.stop();
  
  for(int i=0; i<N; i+=4)         
     printf("%15.5f %15.5f %15.5f %15.5f \n", wynik[i], wynik[i+1], wynik[i+2], wynik[i+3]);
}
/* Output:
        4.00000        20.00000        40.00000        40.00000 
      -24.00000       -24.00000       -44.00000       -60.00000 
  1600004.00000        20.00000     34655.30078      7246.57617 
    -5735.45068     -2712.30566     -4383.20020     -6770.80127 
   -13106.12988     -3977.03564     25110.60156      6893.25586 
*/
