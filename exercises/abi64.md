ABI 64 - Interfejsowanie do C++ w trybie 64 bitowym
==================================================
{:.no_toc}

* TOC
{:toc}

## Wstęp

Interfejsowanie do C/C++ w trybie 64 bitowym znacznie różni się od trybu 32 bitowego. 
Dla Linuxa standard określa dokument System V Application Binary Interface [ELF x86-64-ABI psABI](https://refspecs.linuxbase.org/elf/x86_64-SysV-psABI.pdf).
Najbardziej aktualne [źródła w LaTeX-u](https://gitlab.com/x86-psABIs/x86-64-ABI).

W dużym skrócie:
* Argumenty są przekazywane w pierwszej kolejności przez odpowiednie rejestry w zależności od ich typu:
   * całkowitoliczbowe i wskaźniki : `RDI, RSI, RDX, RCX, R8, R9`
   * zmiennoprzecinkowe (poza long double) : `XMM0, XMM1, ..., XMM7`
  
  Dopiero gdy braknie miejsca w odpowiednich rejestrach argumenty są odkładane na stosie od prawej do lewej. 
  Rejestr `RAX` powinien zawierać liczbę argumentów przekazywanych przez rejestry zmiennoprzecinkowe.
* Przed wywołaniem funkcji stos powinien być wyrównany do granicy 16 bajtowej.
* Funkcja musi zachowywać wartość rejestrów:
  `RBX, RBP, RSP, R12, R13, R14, R15`
* Wynik zwracamy w zależności od typu: 
   * RAX, RDX - całkowitoliczbowy, wskaźnik
   * XMM0, XMM1 - float, double
   * ST0 - long double
   * więsze obiekty w pamięci pod adresem wskazywanym przez `RDI`  

Więcej informacji i przykłady można znaleźć w [notatkach z wykładu](https://ww2.ii.uj.edu.pl/~kapela/pn/tableOfContent.php?lectureNumber=7).

Poniższe zadania powinny być rozwiązane w trybie 64 bitowym.

## Zadanie 1
Napisz w assemblerze funkcję 
```cpp
extern "C" int suma (int n, int * tab);
```
która oblicza sumę n liczb całkowitych znajdujących się w tablicy tab np. 
```cpp
int tab[] ={1, 2, 3, 4};
suma(4, tab);
```
powinno zwrócić 10.   

## Zadanie 2
Napisz w assemblerze funkcję 
```cpp
extern "C" double wartosc (double a, double b, double x, int n);
```
która zwraca wartosc = (a*x+b)^n

Wywołanie `wartosc(4.0, 3.0, 2.0, 2);` powinno zwrócić 121.    

Obliczenia zmiennoprzecinkowe należy wykonać na jednostce "SSE". 

## Zadanie 3
Zaimplementuj w assemblerze funkcję 
```cpp
extern "C" int iloczyn (int n, ...);
```
która oblicza iloczyn n liczb całkowitych podanych jako kolejne argumenty np. 
```cpp
iloczyn(4, 1, 2, 3, 4);
iloczyn(10, 1, 2, 3, 4, 1, 1, 1, 1, 1, 10);
```
powinno zwrócić 24 oraz 240.   

*Wskazówka*: Po zdjęciu adresu powrotu można na stosie odłożyć w kolejności R9, R8, RCX, RDX, RSI i wtedy otrzymamy tablicę wszystkich argumentów (elementy znajdują się co 8 bajtów!).

## Zadanie 4

```cpp
#include <cstdio>
using namespace std;
class Faktura{
private:
  int id;
  float obrot;
  float podatekNaliczony;
  float stawkaPodatku; 
  static int nextID; 
public:
  Faktura(double obrot,  double stawkaPodatku = 0.23, double podatekNaliczony = 0.0):
  id(nextID++), obrot(obrot), 
  podatekNaliczony(podatekNaliczony), stawkaPodatku(stawkaPodatku){}
};
int Faktura::nextID = 0;
extern "C" float podatek(Faktura f);
extern "C" void wypisz(const Faktura & f); 
int main(){
  Faktura buraki(1000,  0.23, 100);
  printf("Podatek : %f\n", podatek( buraki));
  wypisz(buraki);
  return 0;
}
```

Dla powyższego kodu w C++ napisz moduł assemblerowy implementujący funkcje:
*  `float podatek(Faktura f)` - zwracającą należny podatek według wzoru:  
    podatek= (obrót - podatekNaliczony) * stawkaPodatku
*  `void wypisz(const Faktura & f)` - wypisującą na ekran napis przy pomocy standardowej funkcji `printf`   
   ```cpp 
    printf("Faktura %d : obrot %f podatek %f\n", f.id, f.obrot, podatek(f));
   ```
   
*Wskazówki*:
* Obiekt klasy Faktura przekazywany do funkcji podatek przez wartość zostanie pocięty na kawałki 8 bajtowe: pierwszy trafi do RDI, drugi do XMM0. 
* Funkcja printf wymaga aby  
  * standard ABI64 był przestrzegany, w szczególności: stos był wyrównany,  
    w rejestrze RAX umieszczona była liczba argumentów znajdujących się w rejestrach XMM
  * liczby typu float były przekazane jako double (konwersja np. cvtss2sd). 
