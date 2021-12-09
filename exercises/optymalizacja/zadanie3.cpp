// Kompilacja: g++ -std=c++11 -o main.o -c main.cpp
#include <iostream>
#include <vector>
using namespace std;
const int dim=256;
extern "C" void multiply(float A[dim][dim], float B[dim][dim], float C[dim][dim]);
int main(int argc, char **argv){
   float A[dim][dim]; 
   float B[dim][dim]; 
   float C[dim][dim];
   for(int i=0; i<dim; i++){
      for(int j=0; j<dim; j++){
         A[i][j] = i;
         B[i][j] = (i-j)%19;
      }
   }


  multiply(A, B, C);

  int coeff[]={0, 1, 2, 3, 4, 100, 255}; 
  for(int i: coeff){
     for(int j : coeff){
        cout << C[i][j] << " ";
     }
     cout << "\n";
  }
  cout << endl;
  return 0;
}
/**
 * Oczekiwane wyjście
 * 
0 0 0 0 0 0 0 
2259 2250 2241 2232 2223 504 -2259 
4518 4500 4482 4464 4446 1008 -4518 
6777 6750 6723 6696 6669 1512 -6777 
9036 9000 8964 8928 8892 2016 -9036 
225900 225000 224100 223200 222300 50400 -225900 
576045 573750 571455 569160 566865 128520 -576045 
*/
