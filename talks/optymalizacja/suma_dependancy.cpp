#include <iostream>
#include <chrono>
#include <ctime>
#include "immintrin.h"

int main() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  asm("# TK: my asm start \n");
  double sum=0;
//  const int N = 100, ITER = 150000000;
  const int N = 100000, ITER =   15000;
  //   const int N = 100000, ITER =   1;
  double tab[N] __attribute__ ((aligned (16))) = {1,2,3,4};
  for(int k=0; k<ITER; k++){
//#define SIMPLE
//#define PREFETCH
//#define VECTOR
#if defined(SIMPLE)

    sum = 0.0;
        for (int i = 0; i < N; i++)
           sum += tab[i];

#elif defined(PREFETCH)

    double  sum1 = 0., sum2 = 0., sum3 = 0., sum4 = 0.;

        for (int i = 0; i < N; i += 4){
			sum1 += tab[i];
			sum2 += tab[i+1];
			sum3 += tab[i+2];
			sum4 += tab[i+3];
			 //asm("prefetch (%0); prefetch 16(%0);" :: "r"(tab+i+4)); // to może spowolnić ELF: +30%
		   //~ 	 asm("prefetch (%0);" :: "r"(tab+i+4));
			__builtin_prefetch(tab+i+16, 0, 3);  // (adres, rw (w=1), locality strength(1-3))
		}
        sum = (sum1 + sum2) + (sum3 + sum4);
        // Szybsze niż
        // sum1 = sum1 + sum2 + sum3 + sum4;

#elif defined(PREFETCH8)

    double  sum1 = 0., sum2 = 0., sum3 = 0., sum4 = 0.;

        for (int i = 0; i < N; i += 8){
			sum1 += tab[i];
			sum2 += tab[i+1];
			sum3 += tab[i+2];
			sum4 += tab[i+3];

			sum1 += tab[i+4];
			sum2 += tab[i+5];
			sum3 += tab[i+6];
			sum4 += tab[i+7];

      		__builtin_prefetch(tab+i+16, 0, 3);  // (adres, rw (w=1), locality strength(1-3))
			__builtin_prefetch(tab+i+20, 0, 3);
        }
        sum = (sum1 + sum2) + (sum3 + sum4);

#elif defined(VECTOR)

    __m256d result = {0.0,0.0,0.0,0.0};

   for(int i=0; i<N; i+= 4){
	 __m256d x = _mm256_loadu_pd(tab+i);
	 result = _mm256_add_pd(result, x);
   }

   double z[4] = {0.};
   _mm256_storeu_pd(z, result);

   sum = z[0]+z[1]+z[2]+z[3];
#endif

  }
  std::cout <<  sum << std::endl;
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
