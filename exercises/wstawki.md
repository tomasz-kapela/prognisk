
# Wstawki asemblerowe w C++

## Składnia AT&T

| Składnia AT&T                                             | Przykład |
| --------------                                            | ----     |
| Zmieniona kolejność operandów : najpierw źródło potem cel | OpCode źrodlo cel |
| Nazwy rejestrów poprzedzamy %                             |  %eax, %ebx   |
| Stałe poprzedzamy znakiem $, stałe szesnastkowe przez $0x | $1, $322, $0xffff |
| Rozmiar operandów określamy dodając do OpCode przyrostek b (8 bit), w (16 bit), l (32 bit) | movl zmienna, %ebc | 
| Adresowanie pamięci wykorzystuje () zamiast []            | movl (%ebx), %eax |
| Adresowaniu skalowanemu w stylu Intela `[base + index*scale + disp]` w AT&T odpowiada `disp(base, index, scale)` | movl  %eax,  -0xf4(%ebx, %ecx, 4) |


# Wstawki asemblerowe 

Do umieszczania prostych wstawek używamy instrukcji 
```nasm
asm( "Instrukcje asemblerowe");
```
Na przykład
```nasm
asm("movl %%ecx, %%eax \n\t addl %%ebx, %%eax");
```
Powoduje to proste  wklejenie danego tekstu (kodu asemblerowego) do pliku generowanego przez gcc,
bez żadnego sprawdzenia poprawności.  Dlatego też konieczne jest np. wstawienie znaków nowej linii po każdej instrukcji. 

Ogólna postać wstawki asemblerowej ma postać
```nasm
 asm ( "szablon instrukcji asemblerowych" 
      : wyjściowe operandy               /* opcjonalne */
      : wejściowe operandy               /* opcjonalne */
      : lista niszczonych rejestrów      /* opcjonalne */
     );
```     

Operandy podaje się jako listę elementów postaci  
```
"xxx" (wartosc), 
```
gdzie xxx określa miejsce umieszczenia wartości np. 
```
"a" = rax 
"b" = rbx
"c" = rcx
"d" = rdx
"S" = rsi 
"D" = edi  
"r" = jakiś ogólny rejestr 
"m" = pamięć 
"i" = stała całkowita 
"f" = rejestr zmiennoprzecinowy 
"t" = ST0
```

Operandy te są dostępne pod literałami `%0, %1, %2, ...` (numerujemy najpierw wyjście potem wejście) 

Przed operandami wejściowymi dodatkowo dajemy znak = np. `"=r" (wyjscie)`

Przykład
```cpp
int x=2, y=3, result;
asm( "addl %%ebx, %%eax"   // % jest symbolem specjalnym dlatego nazwy rejestrów to np. %%eax
    : "=a"(result)         // wynik z rejestru eax nalezy umieścić w zmiennej result
    : "a"(x), "b"(y)       // na wejściu x będzie w rejestrze eax, a zmienna y w ebx 
    );
```
Ze względów optymalizacyjnych dobrze jest wybór rejestru do przekazywania parametrów pozostawić kompilatorowi,
można też przekazywać zmienne w pamięci.
```cpp
int x=2, y=3, result;
asm( "movl %1, %%eax;"  
     "addl %2, %%eax;"
     "movl %%eax, %0"
    : "=r"(result)      // wynik będzie zwrócony w rejestrze %0 i zapisany do zmiennej result 
    : "r"(x),           // x będzie w którymś z rejestrów dostępnym pod nazwą %1,
      "m"(y)            // y będzie w pamięci pod adresem %2
    : "eax"             // informujemy kompilator, że nasz kod zmienia eax i kompilator nie może 
);                      // juz ufać wartości tego rejestru
```
Więcej informacji można znaleźć na stronie: [http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html](http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html)

## Zadanie 1

Wykorzystując operacje łańcuchowe i  przedrostek REP zaimplementuj w C++ wykorzystując wstawkę asemblerową funkcję 
```cpp
// kopiuje n liczb typu int z zrodla do celu 
void kopiuj(int * cel, int * zrodlo, unsigned int n);
```

## Zadanie 2
 
Napisz w C++ funkcję 
```cpp
char * dodaj(char * tab1, char * tab2, int n)
```
dodającą do siebie odpowiednie elementy dwóch tablic o rozmiarze n i zwracającą wynik w nowej tablicy utworzonej na stercie.

Dodawanie powinno być z wysyceniem i powinno wykorzystywać instrukcje SSE:  `PADDSB` (Packed add with saturation bytes). 

W tym celu użyj odpowiednią wstawkę asemblerową.

## Zadanie 3

Napisz klasę Przedział o końcach typu double.

Posługując się wstawkami asemblerowymi zaimplementuj operatory + i - : dodający i odejmujący poprawnie dwa przedziały. 

W ścisłych obliczeniach arytmetycznych zamiast liczb zmiennoprzecinkowych wykorzystuje się przedziały, określając dla nich zwykłe operacje arytmetyczne w ten sposób, że wynikiem działania jest możliwie najmniejszy przedział, 
który zawiera wszystkie możliwe wyniki pomiędzy elementami pierwszego i drugiego przedziału.

Np. dla dodawania [a,b] + [c,d] = [a+c, b+d].

Niestety liczby a+c i b+d mogą nie być reprezentowalne na komputerze, dlatego aby otrzymać własność  zawierania musimy obliczyć a+c zaokrąglając w dół, a b+d zaokrąglając w górę. Można tego dokonać ustawiając przed dodawaniem odpowiednie flagi FPU tzw control word lub SSE (w zależności jakiego trybu używamy i na jakiej jednostce zamierzamy liczyć). 

Niestety z poziomu C++ nie mamy dostępu do tych flag i musimy to zrobić z poziomu asemblera.

Do zmiany control word służą instrukcje 
```
fstcw mem   - zapisuje w pamięci control word
fldcw mem   - wczytuje z pamięci control word
```
Za zaokrąglanie są odpowiedzialne bity 11 i 12  
```
00 - zaokrąglanie do najbliższej 
01 - zaokrąglanie w dół (wartość 0x0400)
10 - zaokrąglanie w górę (wartość 0x800)
```


```cpp
#include <iostream> 
using namespace std;  
class Interval{ 	
  double left, right;   
public: 	
  Interval(double left, double right) 
  : left(left), right(right){ 	} 	
  double inf() { return left; } 	
  double sup() { return right; }	   	
  friend Interval operator+ (const Interval & a, const Interval &b); 	
  friend Interval operator- (const Interval & a, const Interval &b); 
}  
int main(){ 	
  Interval a(1.,1.); 	
  Interval b(1e-20,1e-20);  	
  Interval c = a + b; 	
  if( (c.inf() == c.sup()) or (c.sup() <= 1.0)  or (c.inf() != 1.0)) 	  
    cout << "Blad operatora +!\n";    
  c = a - b; 	
  if( (c.inf() == c.sup()) or (c.sup() != 1.0) or (c.inf() >= 1.0)) 	  
    cout << "Blad operatora -!\n";  	
  return 0; 
}

