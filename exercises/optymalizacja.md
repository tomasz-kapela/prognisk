Optymalizacja 
===============================
{:.no_toc}

* TOC
{:toc}

Pomoce
------

Na [stronie wykładu](https://ww2.ii.uj.edu.pl/~kapela/pn/listLectureSlides.php) można znaleźć listę optymalizacji, które można wypróbować.

**Rozwiązania zadań w wersji 32 bitowej należy przesłać na BaCę.**

Aby otrzymać punkty za zadanie należy użyć technik, które są opisane w treści zadania i dodatkowo osiągnąć czasy wymagane w testach na BaCy.

### BONUS:

Dla każdego zadania osoba z najszybszym rozwiązaniem dostaje dodatkowe 3p, druga w kolejności 2p, trzecia 1p.


Zadanie 1.
----------

Napisz w asemblerze funkcje 
```cpp
void  minmax(int n, int * tab, int & max, int & min);
```
która dla tablicy tab o rozmiarze n znajduje maksimum i minimum. 

Należy  napisać przynajmniej 3 wersje tej funkcji w tym:
* jedną w języku C++ i poddać optymalizacji -O0, -O1, -O2, -O3
* dwie wersje w asemblerze:
  * wersję wykorzystującą instrukcje CMOVXX, która ma tylko jeden skok warunkowy,
  * wersję, która jest możliwie najszybsza dla konkretnego procesora.  

Porównaj  prędkość różnych wersji funkcji używając programu
```cpp
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
   printf("\n time = %f ( %d cykli)", (stop - start)*1.0/CLOCKS_PER_SEC, (stop - start));
   return 0;
}
/* 
  min = -20000000    max = 10191479
*/
```

Zadanie 2. 
----------
Zaimplementuj w asemblerze odpowiednik funkcji C++ 
```cpp
void solve(int n, float * A, float * B, float * X){

}
```
Funkcja rozwiązuje n równań liniowych postaci
```
   a*x=b
```
gdzie a=A[i], b=B[i], x=X[i].

Jeżeli a==0 i b==0 to istnieje nieskończenie wiele rozwiązań, wynikiem powinno być x = +Inf 

Jeżeli a==0 i b!=0 to nie ma rozwiązań, wynikiem jest x = NaN.

Użyj instrukcji SSE do maskowania wyników tak aby poza instrukcją pętli nie było innych skoków warunkowych.

Dla uproszczenia zakładamy, że n jest podzielne przez 4.

Wskaźniki A, b, x  wskazują na tablice liczb typu float o rozmiarze n.

Na BaCy wszystkie wersje są dopuszczone (nie muszą korzystać z SSE), liczy się prędkość.

Zadanie 3.
----------
Zaimplementuj w asemblerze funkcję 
```cpp
extern "C" void multiply(float A[256][256], float B[256][256], 
                         float C[256][256]);
```
która mnoży dwie macierze A, B o wymiarze 256x256 i wynik zapisuje w macierzy C.

Zooptymalizuj ją tak aby działała jak najszybciej na BaCy w trybie 32-bitowym. 
```cpp
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
```

Zadania dodatkowe
-----------------

### Zadanie D1 

Zaimplementuj w asemblerze funkcję 
```cpp
void solve(int n, float * A, float * B, float * X);
```
Funkcja rozwiązuje n równań liniowych postaci
```
   a*x=b
```
gdzie a=A[i], b=B[i], x=X[i].

Jeżeli a==0 i b==0 to istnieje nieskończenie wiele rozwiązań, wynikiem powinno być x = +Inf 

Jeżeli a==0 i b!=0 to nie ma rozwiązań, wynikiem jest x = NaN.

Użyj instrukcji SSE do maskowania wyników tak aby poza instrukcją pętli nie było innych skoków warunkowych.

Dla uproszczenia zakładamy, że n jest podzielne przez 4.

Wskaźniki A, b, x  wskazują na tablice liczb typu float o rozmiarze n.

Na BaCy wszystkie wersje są dopuszczone (nie muszą korzystać z SSE), liczy się prędkość.
