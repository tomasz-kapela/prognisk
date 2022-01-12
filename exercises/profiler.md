
Profiler
========

## Profiler `gprof`

* [Notatki z wykładu: profiler gprof](https://ww2.ii.uj.edu.pl/~kapela/pn/splitLecture.php?lectureNumber=20&slideNumber=5)

## Perf

* [Tutorial dla perf](https://www.brendangregg.com/perf.html)

Poniższe komendy pozwalają dla danego polecenia (command) zebrać i wyświetlić statystyki liczników procesora tj. źle przewidziane skoki, nietrafienia w bufor. 
Narzędzie perf wymaga uprawnień roota. 
```bash
# CPU counter statistics for the specified command: 
perf stat command

# Detailed CPU counter statistics (includes extras) for the specified command: 
perf stat -d command

# CPU counter statistics for the specified PID, until Ctrl-C: 
perf stat -p PID
```

## Zadanie 1 

Przy pomocy profilera gprof przeanalizuj aplikację napisaną w C++ (to może być stary projekt zaliczeniowy, projekt open source-owy). 
Aplikacja ta powinna być odpowiedniego rozmiaru (więcej niż jedno plikowa ale też nie za duża).

Znajdź wąskie gardła i zaproponuj optymalizacje.

Następnie porównaj statystyki przed i po optymalizacji. 

## Zadanie 2

Użyj narzędzia `perf` aby zbadać z czego wynikają różnice w działaniu wersji 1 i 2  poniższego programu `cache.cpp`.

```cpp
/**
 * @file cache2.cpp
 * Kompilacja: 
 * g++ cache.cpp -O2 -o cache -std=c++11  
*/
#include <iostream> 
#include <chrono> 
#include <ctime> 
using namespace std;  
int main() {     
  const int M = 256;    // Sprawdź też rozmiary 128, 512, 1024     
  int i, j, k;     
  int tab[M][M];     
  chrono::time_point<chrono::system_clock> start, end;     
  start = chrono::system_clock::now();          
  for(k=0; k<1000; k++){                  
    for(i=0; i<M; i++){             
      for(j=0; j<M; j++){                
        tab[j][i] =  j*i+k;       // Wersja 1.                
        //~ tab[i][j] = j*i+k;    // Wersja 2.             
      }         
    }     
  }          
  end = chrono::system_clock::now();     
  chrono::duration<double> elapsed_seconds = end-start;     
  cout << "elapsed time: " << elapsed_seconds.count() << "s\n";      
  int suma=0;      
  for(int i=0; i<M; i++){         
    for(int j=0; j<M; j++){             
      suma+= tab[i][j];         
    }     
  }        
  cout << suma <<endl; }
```

## Zadanie 3. 

Poniższy pogram liczy sumę elementów w tablicy tab, które są mniejsze niż dany próg THRESHOLD.

Użyj narzędzia perf aby zbadać z czego wynikają różnice w działaniu  poniższego programu dla tablicy posortowanej i losowej.

```cpp
/// @file cache2.cpp
/// Kompilacja: 
///   g++ cache2.cpp -O2 -o cache2 -std=c++11 
#include <iostream> 
#include <chrono> 
#include <ctime> 
#include <climits> 
#include <algorithm>  
using namespace std; 
int main() {          
  const int M = 256*256;    // array size     
  const int ITER = 10000;   // number of iterations     
  const int THRESHOLD = 128;     
  int i, k;     
  unsigned char tab[M];     
  std::srand(0);     
  std::generate(tab, tab+M, []{return std::rand()%256;});           
  
  //~ std::sort(tab, tab+M);    ///<<<<<<<<<<<<<<<<<<< SORT      
  
  std::chrono::time_point<std::chrono::system_clock> start, end;     
  start = std::chrono::system_clock::now();          
  int sum=0;     
  for(k=0; k<ITER; k++){            
    for(i=0; i<M; i++){ 		   
      if(tab[i] < THRESHOLD ){ 			   
        sum += tab[i]; 		   
      }
    }     
  }                
  end = std::chrono::system_clock::now();     
  std::chrono::duration<double> elapsed_seconds = end-start;     
  std::cout << "\nelapsed time: " << elapsed_seconds.count() << "s\n";             
  std::cout << sum<<std::endl; 
}
```
