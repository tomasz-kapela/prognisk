# Polimorfizm w C++

Polimorfizm w C++ pozwala na zróżnicowanie zachowania ogólnego algorytmu 
w zależności od tego jakiego dokładnie typu jest obiekt wskazywany przez wskaźnik 
do klasy bazowej lub referencję. Pozwala to na bardziej elastyczną implementację.

Celem tego zestawu jest poznanie przykładowych sposobów jak polimorfizm 
jest wewnętrznie implementowany przez GCC. Więcej szczegółów można znaleźć w 
* [notatkach z wykładu](http://ww2.ii.uj.edu.pl/~kapela/pn/tableOfContent.php?lectureNumber=8) 
* dokumentacji kompilatora GCC
* Itanium C++ ABI
* polimorfizm w Visual Studio C++

## Zadanie 1.

Zaimplementuj  funkcję `zmien`, która dla danego obiektu zmieni działanie funkcji oblicz, 
tak aby zamiast kwadratu n*n obliczała 3*n. 

```cpp
// kompilacja 
//   g++ -fno-devirtualize -c main.cpp -o main.o
//   nasm -felf64 zmien.asm -o zmien.o
//   g++ -fno-devirtualize main.o zmien.o -o main
#include <iostream>
using namespace std;
class A{
  public:
  virtual int oblicz(int n){
    return n*n;
  }
};
extern "C" void zmien(A & a);
int main(){
  A a, b; 
  A *pa = &a, *pb = &b; 
  cout << pa->oblicz(1) << " " << pa->oblicz(2)<< " "<< pb->oblicz(2) << endl;
  zmien(a);
  cout << pa->oblicz(1) << " " << pa->oblicz(2)<< " "<< pb->oblicz(2) << endl;
   
  return 0;
}
// Spodziewane wyjście:
// 1 4 4
// 3 6 4
```

## Zadanie 2.

  Zaimplementuj (w asemblerze lub C++) funkcję zmien, która dla danego obiektu zmieni działanie  
pierwszej funkcji w tablicy funkcji wirtualnych (zwracającej inta), 
w ten sposób, że zwracany wynik będzie o jeden mniejszy od oryginalnego wyniku.  

Funkcja ta może mieć różne nazwy i argumenty, nie koniecznie takie jak w poniższym przykładzie.

Dla uproszczenia przyjmujemy, że wszystkie klasy mają dokładnie dwie funkcje wirtualne. 
Działanie drugiej funkcji powinno pozostać bez zmian.

```cpp
#include <iostream>
using namespace std;
class A{
  public:
  virtual int oblicz(int n){
    return n*n;
  }
  virtual void wypisz(){
     cout << "hej! ";
  }
};
class B : public A {
  public:
  int oblicz(int n){
    return 3*n  - 4;
  }
};
class F {
  public:
  virtual int wylicz(int a, int b){
 return a - b;
  }
  virtual int oblicz(int a){
         return 3*a;
  }
};
extern "C" void zmien(void * ptr);
int main(){
  A a, b; 
  A *pa = new A, *pb = new B, *pc = new B; 
  cout << pa->oblicz(1)<< " "<< pb->oblicz(2) << " " << pc->oblicz(3) << endl;
  zmien(pa); zmien(pb);
  cout << pa->oblicz(1)<< " "<< pb->oblicz(2) << " " << pc->oblicz(3)  << endl;
  cout << pa->wypisz() << pb->wypisz() << endl;
  F *pf = new F;
  cout << pf->wylicz(7, 2) << " "<< pf->oblicz(2)  << endl;
  zmien(pf);
  cout << pf->wylicz(7, 2) << " "<< pf->oblicz(2) << endl;
  return 0;
}
// Spodziewane wyjście:
// 1 2 5
// 0 1 5
// hej! hej!
// 5 6
// 4 6
```

# Zadanie 3

Zaimplementuj funkcję 
```cpp
extern "C" double sum(Node ** tab, int size, ...);
```
Funkcja powinna dla każdego obiektu w tablicy tab (o rozmiarze size) wywołać 
odpowiednią funkcję wirtualną w zależności od liczby podanych w "..." argumentów typu double  
(dla 0 - identity, dla 1 - inverse, dla 2 - compute, liczba argumentów zmiennoprzecinkowych znajduje się z rax). 
Do funkcji przekazujemy te argumenty zmiennoprzecinkowe. 

Następnie należy zsumować zwrócone wartości i zwrócić tą sumę.  

```cpp  
#include <iostream>
using namespace std;
// represents abstract operation #
class Node{
 public:
  // return element such that x # identity() = x
  virtual double identity() = 0;
  // returns solution to x # a = identity()
  virtual double inverse(double a) = 0;
  // compute a # b
  virtual double compute(double a, double b) = 0;
  virtual ~Node(){}
};
class AddNode : public Node {
 public:
  virtual double inverse(double a) { return -a; }
  virtual double compute(double a, double b) { return a + b; }
  virtual double identity(){ return 0.0; }
};
class MulNode : public Node {
 public:
  virtual double inverse(double a) { return 1.0 / a; }
  virtual double compute(double a, double b){ return a*b; }
  virtual double identity(){ return 1.0; }
};
class SubNode : public Node {
  public:
  virtual double inverse(double a){ return a; }
  virtual double compute(double a, double b) { return a - b; }
  virtual double identity() { return 0.0; }
};
// returns sum of results returned by virtual functions calls
// for each element of an array tab (of given size) we call
// virtual function depending on how many floating point arguments are given in ...
extern "C" double sum(Node ** tab, int size, ...);
int main(){
  Node * tab[] = {new AddNode(), new MulNode(), new SubNode() };
  cout << sum(tab, 3) << endl;                   // 1.0
  cout << sum(tab, 3, 4.0, 2.0) << endl;     // 16
  cout << sum(tab, 3, 0.5) << endl;            // 2
  cout << sum(tab, 2, 0.5) << endl;            // 1.5
  return 0;
}
```
