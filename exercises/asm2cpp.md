Interfejsowanie do C++
===============================
{:.no_toc}

* TOC
{:toc}

## Wstęp 

Do rozwiązania zadań przydatna jest znajomość wykładów
* [Struktury i C++](https://ww2.ii.uj.edu.pl/~kapela/pn/tableOfContent.php?lectureNumber=8)
* [Operacje łańcuchowe](https://ww2.ii.uj.edu.pl/~kapela/pn/tableOfContent.php?lectureNumber=11)

*Rozwiąż te zadania jako programy 64-bitowe!*

## Zadanie 1
Zaimplementuj w osobnym module assemblerowym funkcje, które rotują w lewo bity w liczbie x o n pozycji o następujących nagłówkach  
```cpp
unsigned int rotate(unsigned int x, int n = 1);

unsigned char rotate(unsigned char x, int n = 1);
```

Przykład użycia
```cpp
#include <cstdio>
using namespace std;
unsigned int rotate(unsigned int x, int n = 1);
unsigned char rotate(unsigned char x, int n = 1);

template <typename T>
void test(){
  T a = 1, b = 127;
  printf("%u  %u\n", (unsigned)rotate(a, 1), (unsigned)rotate(b,1));
  printf("%u  %u\n", (unsigned)rotate(a, 8), (unsigned)rotate(b,8));
  printf("%u  %u\n", (unsigned)rotate(a, 31), (unsigned)rotate(b,31));
  printf("--------\n");
}

int main(){
  test<unsigned char>();
  test<unsigned int>();
  return 0;
}

/** Spodziewane wyjście
2  254
1  127
128  191
--------
2  254
256  32512
2147483648  2147483711
--------
*/
```

*Wskazówki:* 
*  aby zobaczyć nazwy jakie funkcjom nadał kompilator użyj funkcję w funkcji main a następnie przetłumacz plik do asemblera 
   ```cpp
   g++ -S plik.cpp -o plik.s
   ```
*  Do rotacji użyj instrukcji `ROL` (przesunięcie powinno być podane w rejestrze CL)
   ```cpp
   ROL rejestr, przesunięcie
   rol eax, cl
   ```
   
## Zadanie 2

Wykorzystując [operacje łańcuchowe](https://ww2.ii.uj.edu.pl/~kapela/pn/tableOfContent.php?lectureNumber=11) i  przedrostek `REP` zaimplementuj w asemblerze funkcje
```cpp
// kopiuje n liczb typu int z zrodla do celu 
void kopiuj(unsigned int * cel, unsigned int * zrodlo, unsigned int n);

// zeruje tablice liczb typu int o rozmiarze n
void zeruj(unsigned int * tablica, unsigned int n);
```

## Zadanie 3 (2 punkty)
Poniższa klasa **BigInt** reprezentuje bardzo duże liczby całkowite bez znaku. Liczbę taka przechowujemy następująco:
zapisujemy ją binarnie, a następnie tniemy na kawałki po 32 bity i każdy taki kawałek jest przechowywany jako liczba unsigned int w tablicy dane. 

Dla klasy BigInt 
```cpp
#include <iostream>
// Funkcje z zadania 2
// kopiuje n liczb typu int z zrodla do celu 
void kopiuj(unsigned int * cel, unsigned int * zrodlo, unsigned int n);
// zeruje tablice liczb typu int o rozmiarze n
void zeruj(unsigned int * tablica, unsigned int n);

class BigInt{  
  unsigned int rozmiar;   
  unsigned int * dane;      
public:  
  explicit BigInt(unsigned int rozmiar) 
  : rozmiar(rozmiar), dane( new unsigned[rozmiar] ){
    zeruj(dane, rozmiar);  
  }  
  BigInt(const BigInt & x)   
  :  rozmiar(x.rozmiar),       dane(new unsigned[x.rozmiar]){     
    kopiuj(dane, x.dane, x.rozmiar);  
  }    
  BigInt & operator=(const BigInt & x) {    
    if(rozmiar != x.rozmiar){      
      unsigned * tmp = new unsigned[x.rozmiar];      
      delete[] dane;       
      rozmiar = x.rozmiar;      
      dane = tmp;    
    }    
    kopiuj(dane, x.dane, x.rozmiar);    
    return *this;  
  }  
  ~BigInt(){		    
    delete[] dane;  
  }
  // do zaimplementowania w zadaniu 3  
  int dodaj(unsigned int n);  
  int pomnoz(unsigned int n);  
  int podzielZReszta(unsigned int n);    
  BigInt & operator=(const char * liczba);  
  friend std::ostream & operator << (std::ostream & str, const BigInt & x);
  
  // do zaimplementowania w zadaniu 4  
  friend BigInt operator+ (const BigInt & a, const BigInt & b);  
  friend BigInt operator- (const BigInt & a, const BigInt & b);
}; 
```
zaimplementuj w asemblerze metody 
* ```cpp
  int BigInt::dodaj(unsigned int n);
  ```
  dodaje do obiektu BigInt (modyfikując go) liczbę całkowitą n,
  funkcja zwraca 1 jeżeli nastąpiło przepełnienie liczby BigInt, 0 w przeciwnym wypadku,
  (w praktyce dodajemy n do  dane[0] a potem tylko propagujemy przeniesienie)

* ```cpp
  int BigInt::pomnoz(unsigned int n);
  ```
  mnoży obiekt BigInt  przez n (modyfikując obiekt),
  funkcja zwraca 1 jeżeli nastąpiło przepełnienie liczby BigInt, 0 w przeciwnym wypadku,

* ```cpp
  unsigned int BigInt::podzielZReszta(unsigned int n);
  ```
  dzieli obiekt BigInt przez n (modyfikując go) i zwraca resztę z dzielenia.

* Z ich pomocą (można już w języku C++) zdefiniuj operatory:
  * wypisania liczby BigInt do strumienia 
    ```cpp
    BigInt a(1234);
    cout << a << endl;
    ```
  * przypisania łańcucha tekstowego, zawierającego liczbę np.   
    ```cpp
    a="1234214243543543543243543534";
    ```

## Zadanie 4
Dla klasy BigInt dopisz operatory dodawania i odejmowania 
```cpp
BigInt operator+ (const BigInt & a, const BigInt & b);
BigInt operator- (const BigInt & a, const BigInt & b);
```
Proszę te operatory całkowicie napisać w assemblerze, 
W prostszej wersji można założyć, że a i b są tej samej długości.

*Wskazówki:*
* Aby utworzyć obiekt wynikowy z asemblera wywołaj konstruktor klasy BigInt dla adresu pamięci przekazanego jako pierwszy argument.  
* W dodawaniu dobrze jest skorzystać z instrukcji `ADC` (add with carry), która dodaje dwie liczby dodając dodatkowo 1 jeżeli w poprzednim dodawaniu została ustawiona flaga `CF`.
* Dla odejmowania można analogicznie użyć instrukcji SBB (subtract with borrow).
