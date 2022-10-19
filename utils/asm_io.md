# Biblioteka asm64_io

Wejście i wyjście z programu asemblerowego są, łagodnie rzecz ujmując, uciążliwe.
Aby uprościć obsługę operacji wejścia/wyjścia, w programach asemblerowych można wywoływać funkcje C.
Asemblerowy interfejs do funkcji printf i scanf został zaimplementowany w bibliotece
*  asm64_io (64bit),
*  [asm63_io_pie](asm64_io_pie.zip) (64bit, gcc wersja powyżej 5).


## Funkcje biblioteki asm64_io

| Funkcja | opis |
|----     | ---- |
|`print_int` |	 Drukuje na ekran wartość całkowitą z rejestru EAX |
|`print_char` |	 Drukuje na ekran znak, którego kod ASCII jest w rejestrze AL|
|`print_string` |	 Drukuje napis, którego adres znajduje się w EAX. Napis musi się kończyć zerem (typ C).|
|`print_nl` |	 Nowa linia|
|`read_int` |	 Czyta z klawiatury liczbę całkowitą i wrzuca do rejestru EAX|
|`read_char` |	 Czyta znak z klawiatury i wrzuca jego kod ASCII do EAX |         
|`println_int` <br/> `println_char` <br/>`println_string` |	 (tylko asm64_io) drukuje na ekran dodatkowo przechodząc do nowej linii. |
|`dump_regs X` |	 Wypisanie zawartości rejestrów i flag. Liczba całkowita X jest etykietą.   |

Tabela 2. Funkcje biblioteki asm64_io

Po załadowaniu do rejestrów odpowiednich danych, procedury z Tabeli 2 woła się instrukcją call np.:
````asm
mov rax, 10
call print_int     ; wypisze na ekran liczbę 10
````

## Stosowanie biblioteki

Zastosowanie biblioteki asm64_io wymaga pobrania jednej wersji poniżej. Z zawartych w niej plików modyfikujemy tylko plik starter.asm.

starter.asm

```nasm 
%include "asm64_io.inc"    ;odpowiednik dyrektywy #include z C

segment .data
;
; dane zainicjalizowane
;

segment .bss
;
; dane niezainicjalizowane
;

segment .text
global MAIN
MAIN:
enter 0,0         ; setup 

; ----
; Właściwy kod wstawiamy tu. 
; Nie należy modyfikować kodu przed i po tym komentarzu
; ---

mov eax, 0 ; kod zwracany z funkcji
leave
ret
```

Najpierw należy zbudować bibliotekę asm64_io.asm (wystarczy zrobić to tylko raz)
```bash
nasm -f elf64 asm64_io.asm -o asm64_io.o
```

Następnie kompilujemy własny program starter.asm i linkujemy go z biblioteką
```bash
nasm -felf64 -o starter.o starter.asm
gcc -o starter starter.o asm64_io.o 
```

Można też skorzystać z załączonego pliku Makefile i wywołać polecenie make

## Przykład
````asm
%include "asm64_io.inc"
segment .data
pytanie db "Podaj dwie liczby : ", 0  ; tekst musi kończyć się zerem
wynik   db "Suma = ", 0

segment .bss
segment .text
global MAIN
MAIN:
enter 0,0
; ----

dump_regs 1     ; pierwsze wypisanie zawartości rejestrów

mov rax, pytanie
call print_string

call read_int   ; wczytanie liczby int
mov ebx, eax

call read_int   ; wczytanie drugiej liczby
cmp eax, ebx

dump_regs 2     ; drugie wypisanie zawartości rejestrów
call print_nl

add eax, ebx
call println_int  ; wypisanie liczby int z rax

call print_nl
; ---

mov rax, 0 ; powrót do C
leave
ret
````

## Wersje biblioteki
Najnowszą biblioteką jest [asm64_io_pie](../utils/asm64_io_pie.zip) pozwala ona na tworzenie oprogramowania i w wersji PIE i NO-PIE. Starsza biblioteka ams64_io jest głownie dla starszych wersji Linuxa i nie wspiera ona PIE. Biblioteka asm_io jest dla systemów 32 bitowych.



