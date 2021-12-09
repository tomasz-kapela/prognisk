#include <stdio.h> 

extern "C" void obliczSSE(float * wynik, float *a, float *b, float x, int n){
   for(int i=0; i<n; i++){
	   if(a[i] != 0){
		   wynik[i] = b[i]/a[i] * x;
	   } else if(a[i] > b[i]){
		   wynik[i] = (a[i]-b[i]) * x;
	   } else {
		   wynik[i] = a[i]*x + b[i]*x*x;
	   }
   }
}
int main(void) {     
  const int N=20;
  float a[N] = {0, 0, 1, 2, 3, -1, -2, -3, -4, 100000};
  float b[N] = {0, 1, 2, 3, -1, -2, -3, -4, 100000};
  float wynik[N];
  float x = 4;
  obliczSSE(wynik, a, b, x, N);
  for(int i=0; i<N; i++)         
     printf("%f ", wynik[i]);
  }
