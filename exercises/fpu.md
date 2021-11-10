# Operacje zmiennoprzecinkowe
 
## Wprowadzenie
**Koprocesor** jest wyposażony w 8 rejestrów do przechowywania liczb zmiennoprzecinkowych (każdy rejestr przechowuje 80 bitów danych). Rejestry noszą nazwy ST0, `ST1`, `ST2`, . . . ST7. Rejestry są zorganizowane w postaci stosu (LIFO) z rejestrem ST0 na wierzchu stosu. Lista rozkazów koprocesora jest długa - rozkazy te operują bezpośrednio na rejestrach koprocesora. Dobre wprowadzenie do zagadnień operacji zmiennoprzecinkowych i przykłady programów asemblerowych wykorzystujących koprocesor znajdują się tutaj. Bardzo dobre rozwinięcie tematyki operacji zmiennoprzecinkowych znajduje się w rozdziale 6 książki Paula Cartera "PC Assembly Language". Na Listingu 1 przedstawiono kod C, wywołujący asemblerową procedurę liczącą pierwiastki równania kwadratowego i pokazaną na Listingu 2 (przykład zaczerpnięty z książki Cartera).

*Listing 1*
```c
// kod C w main.c, kod asemblerowy w quad.asm
// KOMPILACJA:
// gcc -m32 -o main.o -c main.c
// nasm -felf32 -o quad.o quad.asm
// gcc -m32 -o quad quad.o main.o

#include <stdio.h>

extern int quadratic(double, double, double, double *, double *);

int main()
{
    double a, b, c, root1, root2;

    printf("Enter a , b, c : ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (quadratic(a,b,c,&root1,&root2))
        printf ("roots: %.10g %.10g\n", root1, root2 );
    else
        printf ("No real roots\n");
    return 0;
}
```
*Listing 2*
```nasm 
; funkcja quadratic
; znajduje pierwiastki równania kwadratowego:
; a*x^2 + b*x + c = 0
; prototyp C:
; int quadratic( double a, double b, double c,
;                double * root1, double *root2 )
; Parametry:
; a, b, c - współczynniki równania
; root1 - wskaźnik do zmiennej typu double, przechowującej rozwiązanie
; root2 - j.w.
; Wartość zwracana:
; 1 jeśli istnieją pierwiastki rzeczywiste, w przeciwnym wypadku 0

 %define a qword [ebp+8]
 %define b qword [ebp+16]
 %define c qword [ebp+24]
 %define root1 dword [ebp+32]
 %define root2 dword [ebp+36]
 %define disc qword [ebp-8]
 %define one_over_2a qword [ebp-16]

 segment .data
 MinusFour dw -4

 segment .text
 global quadratic
 quadratic:

 push ebp
 mov ebp, esp
 sub esp, 16              ; alokacja pamięci na dane lokalne procedury (disc i one_over_2a)
 push ebx                 ; KONWENCJA C - musimy zachować oryginalne dane z rejestru EBX

 fild word [MinusFour]    ; stack -4
 fld a                    ; stack: a, -4
 fld c                    ; stack: c, a, -4
 fmulp st1                ; stack: a*c, -4
 fmulp st1                ; stack: -4*a*c
 fld b
 fld b                    ; stack: b, b, -4*a*c
 fmulp st1                ; stack: b*b, -4*a*c
 faddp st1                ; stack: b*b - 4*a*c
 ftst                     ; porównaj ST0 z 0
 fstsw ax                 ; przenosimy flagi C koprocesora do rejestru AX
 sahf                     ; przenosimy dane z AX do rejestrów flagowych procesora
                          ; powyższe dwie instrukcje są konieczne do stworzenia instrukcji warunkowej!!!

 jb no_real_solutions     ; if disc < 0, nie ma rozwiązań rzeczywistych
 fsqrt                    ; stack: sqrt(b*b - 4*a*c)
 fstp disc                ; store and pop stack
 fld1                     ; stack: 1.0
 fld a                    ; stack: a, 1.0
 fscale                   ; stack: a * 2^(1.0) = 2*a, 1
 fdivp st1                ; stack: 1/(2*a)
 fst one_over_2a          ; stack: 1/(2*a)
 fld b                    ; stack: b, 1/(2*a)
 fld disc                 ; stack: disc, b, 1/(2*a)
 fsubrp st1               ; stack: disc - b, 1/(2*a)
 fmulp st1                ; stack: (-b + disc)/(2*a)

 mov ebx, root1           ; ładuję adres root1 do rejestru
 fstp qword [ebx]         ; ściągam ze stosu do *root1
 fld b                    ; stack: b
 fld disc                 ; stack: disc, b
 fchs                     ; stack: -disc, b
 fsubrp st1               ; stack: -disc - b
 fmul one_over_2a         ; stack: (-b - disc)/(2*a)

 mov ebx, root2
 fstp qword [ebx]
 mov eax, 1               ; return 1
 jmp short quit

 no_real_solutions:
 mov eax, 0               ; return 0

 quit:
 pop ebx
 mov esp, ebp
 pop ebp
 ret
```

## Przesyłanie rozwiązań

Wszystkie zadania powinny być rozwiązane w assemblerze 32 bitowym i przesłane na BaCę 

[http://pn.baca.ii.uj.edu.pl]

Wysłać należy tylko plik assemblerowy. 

## Zadania 

### Zadanie 1
Proszę napisać w assemblerze funkcję o nagłówku
```c++
extern "C" double wartosc(double a, double b, double  c, double d, double x);
```
wyliczającą wartość wyrażenia y=ax^3+bx^2+cx+d. 

Funkcja ma pobierać dane wejściowe od procedury wołającej napisanej w C, która wyświetla wyniki obliczeń.

### Zadanie 2
Proszę napisać funkcję asemblerową o nagłówku
```c++
extern "C" void prostopadloscian( float a, float b, float c, float * objetosc, float * pole);
```
wyliczającą objętość i pole powierzchni prostopadłościanu a. 

Funkcja ma pobierać dane wejściowe od procedury wołającej napisanej w C, która wyświetla wyniki obliczeń.

### Zadanie 3
Proszę napisać funkcję asemblerową o nagłówku
```c++
extern "C" long double iloczyn_skalarny(int n, long double * x, long double * y);
```
mnożącą skalarnie dwa n-wymiarowe wektory liczb rzeczywistych o współrzędnych w tablicach x i y. 

Funkcja ma pobierać dane wejściowe od procedury wołającej napisanej w C, która wyświetla wyniki obliczeń.

### Zadanie 4
Proszę napisać funkcję asemblerową o nagłówku
```c++
extern "C" void tablicuj(double a, double b, double P, double Q, double xmin, double xmax, int k,  double * wartosci);
```
Funkcja ma tablicować wartości funkcji:
```
    y=a*(sin(P*2*pi*x))2 + b*(sin(Q*2*pi*x))2
```
dla k>=2 równoodległych punktów w przedziale od xmin do xmax.(tj.  x1 = xmin ... xk = xmax )

Wynik ma być zapisany w tablicy wartosci (zakladamy, że jest odpowiednio duza);

Funkcja ma pobierać dane wejściowe od procedury wołającej napisanej w C, która wyświetla wyniki obliczeń.
