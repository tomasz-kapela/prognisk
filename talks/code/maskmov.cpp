#include <iostream>
using namespace std;

extern "C" void compute(int n, float * tab);

int main(){

  float tab[] = { 1.0,  2.0, 3.0, -3,
	              -2.0, 4.5, -4.2, 1.9};
	              
  compute(8, tab);
  for(auto x : tab){
	  cout << x <<"  ";
  } 
  return 0;
}
