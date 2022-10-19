---
layout: default
parent: Ćwiczenia
nav_order: 4
---

Asembler i C - standard cdecl w 32 bit
===============================
{:.no_toc}

* TOC
{:toc}

## Wprowadzenie

Pisanie większych programów wyłącznie w asemblerze jest bardzo nieefektywne.
Dlatego najczęściej asembler jest używany do tworzenia wybranych funkcji, 
wołanych z programów pisanych w językach wysokiego poziomu.
Aby takie wywołania (np. pomiędzy asemblerem a C) poprawnie działały, należy przestrzegać konwencji 
wywołania funkcji przyjętych w odpowiednich standardach 
(definiujących sposób przekazywania argumentów, odbioru wyniku, zachowywania rejestrów itd).
Standardy te różnią się w zależności od architektury procesora, systemu operacyjnego, języka programowania 
(czy nawet jego wersji).

## Standard cdecl 

Konwencja **cdecl** (stosowana przez język C w trybie 32-bitowym) w wielkim skrócie:

*  Argumenty są przekazywane do funkcji za pośrednictwem stosu 
   i umieszczane w kolejności od prawej do lewej (*RLO*).
*  Wartość w zależności od typu i rozmiaru zwracana jest w rejestrze 
   *  `EAX` : wskaźniki oraz liczby całkowite np. `int`, `char`, `short`  
   *  `EDX:EAX` : małe struktury
   *  `ST0` : liczby zmiennoprzecinkowe: `float`, `double`, `long double`
*  Rejestry `EBX`, `ESI`, `EDI`, `EBP`, `CS`, `DS`, `SS`, `ES` 
   po wyjściu z funkcji powinny mieć niezmienione wartości.

Więcej szczegółów można znaleźć w materiałach z wykładu.


## Kompilacja na Linuxie 64-bitowym

Aby kompilować programy 32 bitowe w systemie Linux 64 bitowym przeważnie trzeba doinstalować odpowiednie 32 bitowe pakiety `gcc-multilib` i `lib32stdc++-XX-dev` (gdzie XX to wersja kompilatora g++). Przykładowo w Ubuntu
```bash
sudo apt install gcc-multilib lib32stdc++10-dev
```
Kompilując i linkując musimy dodawać odpowiednie opcje `-felf32` i `-m32` informujące, że chcemy otrzymać kod binarny 32 bitowy. Przykładowo dla plików zródłowych main.cpp i funkcja.asm mamy
```bash
g++ -m32 -c main.cpp -o main.o
nasm -felf32 funkcja.asm -o funkcja.o
g++ -m32 main.o funkcja.o -o main
```

## Wywołanie funkcji języka C z asemblera

Na Listingu 1 pokazano kod programu asemblerowego wywołującego funkcję `printf`.

W Windows nazwy funkcji poprzedzane są znakiem _. 
Aby skompilować przykłady należy dodać podkreślenia do etykiet `main` i `printf`.

*Listing 1* : [c_asm.asm](code/c_asm.asm)

```nasm 
; KOMPILACJA:  plik źródłowy c_asm.asm
; nasm -o c_asm.obj -felf c_asm.asm
; gcc -m32 -nopie c_asm.obj -o c_asm
section .text

extern printf          ; definicja funkcji printf znajduje się w bibliotece standardowej C
global main  
main:                  ; punkt wejścia - funkcja main
enter 0, 0
                       ; printf("Liczba jeden to: %d\n", 1);
push   dword 1         ; drugi argument
push   dword napis     ; pierwszy argument 
                       ; UWAGA: kolejność argumentów RLO (od prawej do lewej)
call   printf          ; uruchomienie funkcji
add    esp, 2*4        ; posprzątanie stosu - rejestr ESP wskazuje to samo, 
                       ; co przed wywołaniem funkcji printf
xor    eax, eax        ; return 0;
leave
ret                    ; wyjście z programu
section .data
napis: db "Liczba jeden to: %d", 10, 0
```

## Wywołanie z C funkcji zaimplementowanej w asemblerze

Na Listingu 2 pokazano kod programu napisanego w C, 
wołającego funkcję asemblerową przedstawioną na Listingu 3.

*Listing 2* [main.c](cdecl/main.c)

```c
// KOMPILACJA - kod źródłowy C w main.c, kod źródłowy ASM w suma.asm
// LINUX :
// nasm -felf32 suma.asm -o suma.o
// gcc -m32 -no-pie -o main.o -c main.c
// gcc -m32 -no-pie main.o suma.o -o suma
#include <stdio.h>

int suma (int a, int b);         /* prototyp funkcji */

int main(){
  int c=1, d=2;
  scanf("%d %d",&c,&d);
  printf("%d\n", suma(c,d));
  return 0;
}
```

*Listing 3* : [suma.asm](cdecl/suma.asm)   

```nasm
BITS 32
section .text
global suma        ; funkcja suma ma być widziana w innych modułach aplikacji
suma:
   enter 0, 0     ;  tworzymy ramkę stosu na początku funkcji
      ; ENTER 0,0 = PUSH EBP / MOV EPB, ESP
      ; po wykonaniu enter 0,0
      ; w [ebp]    znajduje się stary EBP
      ; w [ebp+4]  znajduje się adres powrotny z procedury
      ; w [ebp+8]  znajduje się pierwszy parametr,
      ; w [ebp+12] znajduje się drugi parametr
      ; itd.
; pomocnicze makrodefinicje
   %idefine    a    [ebp+8]
   %idefine    b    [ebp+12]
; tu zaczyna się właściwy kod funkcji
   mov    eax, a
   add    eax, b
; tu kończy się właściwy kod funkcji
   leave     ; usuwamy ramkę stosu LEAVE = MOV ESP, EBP / POP EBP
ret    ; wynik zwracany jest w rejestrze eax
```

## Zadanie 1

Napisać w assemblerze funkcję main, która wczytuje dwie liczby całkowite ze znakiem przy użyciu funkcji scanf z biblioteki standardowej języka C i wypisujący na ekran ich iloraz przy użyciu funkcji printf.
Należy przysłać tylko plik ASM.

| Input | Output |
|---    |---     |
| 2 1	  | 2 |
| -4 -2	| 2 |            
| -6 2  |  -3   |

## Zadanie 2
Napisać aplikację 32 bitową wyliczającą iloczyn elementów tablicy liczb int.

Aplikacja ma być złożona z dwóch modułów:

*  w C (inicjalizacja tablicy, operacje wejścia/wyjścia),
*  w ASM (funkcja licząca iloczyn) parametrami funkcji są ilość elementów tablicy i wskaźnik na pierwszy element tablicy.
   
   ```c
   int iloczyn(int n, int * tab);
   ```

Zadbaj o to aby funkcja `iloczyn` była zgodna ze standardem **cdecl**.

## Zadanie 3

Napisać funkcję o nagłówku

```c 
void sortuj( int * a, int *b, int * c);
```

sortującą malejąco wartości trzech podanych zmiennych.
Po wywołaniu funkcji wartości zmiennych powinny zostać odpowiednio pozamieniane.

Na przykład

```c
int x=5, y=3, z=4;

sortuj( &x, &y, &z);

printf(" %d %d %d \n", x, y, z);
```
powinno wypisać
```
5 4 3
```

[Program z testami](cdecl/sortuj.c)

##  Zadanie 4

Napisać moduł asemblerowy implementujący 32 bitowyą funkcję minmax  

```c 
MinMax minmax( int N, ...);
```

wyliczającą minimalny i maksymalny spośród argumentów funkcji. 
Pierwszym argumentem funkcji jest liczba całkowita N>0, 
po której następuje N argumentów całkowitych.

Wyniki mają być zwracane jako struktura MinMax.
```c 
typedef struct{
    int min;
    int max;
} MinMax;
```

Sposób zwracania zależy od systemu operacyjnego i wersji kompilatora:

*  Linux: Jako pierwszy argument funkcji minmax zostanie przekazany wskaźnik 
   na obiekt typu MinMax, który należy uzupełnić.
*  Windows, starsze gcc pod Linuxem: Struktura MinMax mieści się w sumie rejestrów EDX:EAX 
   i tam powinna być zwrócona.

Aplikacja ma być złożona z dwóch modułów: 

* w C (operacje I/O, wywołanie funkcji), 
* w ASM implementacja funkcji minmax (tylko ten plik przesyłamy jako rozwiązanie).

   
```c 
#include <stdio.h>

typedef struct{
    int min;
    int max;
} MinMax;


int main(){

   MinMax wynik = minmax(7, 1, -2, 4 , 90, 4, -11, 101); // -11 101
   printf("min = %d, max = %d \n", wynik.min, wynik.max); 

   wynik = minmax(5, 1, -2, 4 , 90, 4, -11, 101);        // -2 90
   printf("min = %d, max = %d \n", wynik.min, wynik.max); 

   wynik = minmax(1, 0);                                 // 0 0
   printf("min = %d, max = %d \n", wynik.min, wynik.max);

   return 0;
}
```

