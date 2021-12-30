#include <iostream>
#include <cmath>
using namespace std;

extern "C" void compute(int n, float * tab);

int main(){

  float tab[] = { 1.0,  2.0, 3.0, -3,
	              -2.0, 4.5, -4.2, 1.9};
	              
  compute(8, tab);
  int i =0;
  for(auto x : tab){
	  cout << x <<"  ";
	  cout << ( (tab[i] > 0) ? (tab[i]+4)*sqrt(tab[i]) : (tab[i]*tab[i])*sqrt(-tab[i])) << "\n"; 
      i++;
  } 
  return 0;
}
