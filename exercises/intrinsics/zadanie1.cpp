#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;
int main(){
  const int prog = 100000;
  const int rozmiar = 100;
  unsigned int tab[rozmiar];

  //srand(time(0));
  srand(2021);  // dla powtarzalności testów

  for(int i=0; i<rozmiar; ++i){
      tab[i] = rand() % prog;
  }
  unsigned int max = 0;
  for(int i=0; i<rozmiar; ++i){
      if(max < tab[i])
          max = tab[i];
  }
  printf("%d\n", max);
  return 0;
}
