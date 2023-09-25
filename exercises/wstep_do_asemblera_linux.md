---
layout: default
title: Wstęp do assemblera
parent: Ćwiczenia
nav_order: 1
---

Wstęp do assemblera (w Linuxie)
===============================
{:.no_toc}

* TOC
{:toc}

## Pierwsze programy

### Program 64 bitowy

Listing 1. Asemblerowe "Hello world!" na 64 bitach
```nasm
; wersja NASM na system 64-bitowy (x86-64)
; kompilacja: nasm -felf64 hello.asm -o hello.o
; linkowanie: ld hello.o -o hello
; linkowanie: ld -m elf_x86_64  hello.o -o hello

section .text            ; początek sekcji kodu.

global _start            ; linker ld domyślnie rozpoczyna
                         ; wykonywanie programu od etykiety _start
                         ; musi ona być widoczna na zewnątrz (global)
_start:                   ; punkt startu programu
  mov     rax, 1          ; numer funkcji systemowej:
                          ; 1=sys_write - zapisz do pliku
  mov     rdi, 1          ; numer pliku, do którego piszemy.
                          ; 1 = standardowe wyjście = ekran
  mov     rsi, tekst      ; RSI = adres tekstu
  mov     rdx, dlugosc    ; RDX = długość tekstu
  syscall                 ; wywołujemy funkcję systemową

  mov     rax, 60         ; numer funkcji systemowej
                          ; (60=sys_exit - wyjdź z programu)
  mov     rdi, 0          ; RDI - kod wyjścia
  syscall                 ; wywołujemy funkcję systemową

section .data                   ; początek sekcji danych.
  tekst db "Czesc", 0ah   ; nasz napis, który wyświetlimy
  dlugosc equ $ - tekst   ; długość napisu
```
### Program 32 bitowy

Listing 2.  Asemblerowe "Hello world!"
```nasm
; NASM 32 bit: program zapisany w pliku hello.asm
; kompilacja: nasm -felf hello.asm -o hello.o
; linkowanie: ld hello.o -o hello
; linkowanie w systemach 64-bit:  ld -m elf_i386 hello.o -o hello
 

section .text      ; początek sekcji z kodem

global _start      ; linker ld domyślnie rozpoczyna wykonywanie 
                   ; programu od etykiety _start
_start:            ; musi ona być widoczna na zewnątrz (global)

  mov eax, 4       ; numer funkcji systemowej:  
                   ;  4= sys_write - zapisz do pliku
  mov ebx, 1       ; numer pliku, do którego piszemy.
                   ; 1 = standardowe wyjście = ekran
  mov ecx, tekst   ; ECX = adres (offset) tekstu
  mov edx, dlugosc ; EDX = długość tekstu
  int 80h          ; wywołujemy funkcję systemową

  mov eax, 1       ; numer funkcji systemowej
                   ; (1=sys_exit - wyjdź z programu)
  int 80h          ; wywołujemy funkcję szzystemową

section .data      ; początek sekcji danych.

  tekst	db "Czesc", 0ah	 ; nasz napis, który wyświetlimy + enter 
  dlugosc equ $ - tekst  ; makro obliczające długość napisu
                         ; (to nie jest zmienna)
```

## Podstawowe operacje

### `MOV` przenoszenie danych

```nasm 
mov eax, 3         ; zapis 3 do EAX (3 jest natychmiastowym operandem)
mov bx, ax         ; zapis wartości z AX do BX 
```

### `ADD` - dodawanie liczb całkowitych

```nasm 
add eax, 4         ; eax = eax + 4
add al, ah         ; al = al + ah
``` 

### `SUB` - odejmowanie liczb całkowitych

```nasm 
sub bx, 10         ; bx = bx - 10
sub ebx, edi       ; ebx = ebx - edi
```

### `INC` i `DEC` - zwiększania i zmniejszanie o 1

```nasm 
inc ecx             ; ecx++
dec dl              ; dl--
```
### `MUL` i `IMUL` - mnożenie liczb całkowitych bez znaku (MUL) i ze znakiem (IMUL)

Instrukcja MUL jest używana do mnożenia liczb całkowitych bez znaku, a instrukcja IMUL do mnożenia liczb całkowitych ze znakiem. 

W wersji jednoargumentowej instrukcji `MUL` i `IMUL` podajemy
tylko jeden mnożnik a drugi mnożnik i miejsce zapisania wyniku są niejawne i zależne od rozmiaru jawnego argumentu.
W tej wersji przepełnienie jest zapamiętywane dlatego wynik przeważnie znajduje się w parze rejestrów np. 'EDX:EAX' w przypadku 4 bajtowego argumentu.
W tabeli zebrano akcje wykonywane dla instrukcji  
`MUL/IMUL argument`

| argument | rozmiar (B) | akcja            | 
| ---------| :---------: | ---------------- |
| reg/mem8 | 1           | 	 AX = AL*argument |
|	reg/mem16 | 2 | 	 	 DX:AX = AX*argument |
| reg/mem32 | 4 |	 	 EDX:EAX = EAX*argument |
| reg/mem64 | 8 |	 	 RDX:RAX = RAX*argument |


```nasm 
mul cl          ; AX = AL*CL
mul bx          ; DX:AX = AX*BX
mul esi         ; EDX:EAX = EAX*ESI
mul rdi         ; RDX:RAX = RAX*RDI
```

**Tylko instrukcja `IMUL`** ma wersje dwu- lub trzyargumentowe, które operują na jawnych argumentach i ewentualne przepełnienie jest ignorowane.

```nasm 
imul eax, ebx         ; eax = eax * ebx
imul bx, 5            ; bx = bx * 5
imul [x], ebx         ; zmienna x jest przemnożona przez wartość ebx
imul rax, rbx, 2      ; rax = rbx * 2
```

### `DIV` i `IDIV` - dzielenie liczb całkowitych bez znaku (DIV) i ze znakiem (IDIV)

Instrukcje DIV i IDIV wykonują dzielenia na liczbach całkowitych bez znaku (DIV) i ze znakiem (IDIV), wyliczając jednocześnie resztę z dzielenia. 
Składnia obu operacji jest identyczna:
```nasm 
div dzielnik
idiv dzielnik
```
Przykładowo jeżeli dzielnik jest 32-bitowy, to dzielna jest pobierana z  EDX:EAX, wynik trafia do EAX a reszta do EDX. Niejawne argumenty dla innych rozmiarów zebrano w tabeli

| dzielnik  | rozmiar (B) | dzielna          | iloraz | reszta | 
| --------- | :---------: | :---: | :---: | :---: |
| reg/mem8  | 1           |  AX   | AL | AH |
|	reg/mem16 | 2 | 	 	      DX:AX | AX | DX |
| reg/mem32 | 4 |	 	 EDX:EAX  | EAX | EDX |
| reg/mem64 | 8 |	 	 RDX:RAX  | RAX | RDX |

**Uwaga:** Wynik nie mieszczący się w rejestrze docelowym powoduje błąd wykonania. Dlatego ważne jest aby przed wykonaniem dzielenia odpowiednio przygotować dzielną, przeważnie:
* dla `DIV` zerujemy rejestr ah/dx/edx/rdx np. instrukcją `xor edx, edx`
* dla `IDIV` rozszerzamy liczbę bitem znaku używając instrukcji `CBW`/`CWD`/`CDQ`/`CQO` w zależności od rozmiaru dzielnika. Przykładowo `CDQ` wypełnia `EDX` zerami lub jedynkami w zależności czy w `EAX` jest liczba dodatnia czy ujemna.  

```nasm 
div cl        ; AL = (AX div CL), AH = (AX mod CL)
div bx        ; AX = (DX:AX div BX),
              ; DX = (DX:AX mod BX)
idiv edi      ; EAX = (EDX:EAX div EDI),
              ; EDX = (EDX:EAX mod EDI)
div rsi       ; RAX = (RDX:RAX div RSI),
              ; RDX = (RDX:RAX mod RSI)
```

## Deklarowanie zmiennych

Informacje o deklarowaniu danych i tematach pokrewnych są dostępne po kliknięciu na poniższe linki:
deklarowanie danych zainicjowanych
deklarowanie danych niezainicjowanych
deklarowanie stałych
prefix TIMES: powtarzanie instrukcji

Pamięć w programie asemblerowym może być zarezerwowana na dwa sposoby. W pierwszym przypadku rezerwujemy miejsce na dane, a w drugim: rezerwujemy miejsce i inicjalizujemy dane. Pierwsza metoda wykorzystuje dyrektywę RESX, gdzie X zastępujemy literą określającą rozmiar obiektu (byte B, word W, double word D, quad word Q, ten bytes T). Druga metoda wykorzystuje dyrektywę DX, gdzie X ma to samo znaczenie, jak w przypadku RESX. Zarezerwowane miejsca w pamięci oznacza się etykietami, które pozwalają w prosty sposób uzyskać dostęp do adresu komórki pamięci jak i do danych tam wpisanych.

```nasm 
L1 db 0                ; byte labeled L1 with initial value 0
L2 dw 1000             ; word labeled L2 with initial value 1000
L3 db 110101b          ; byte initialized to binary 110101 (53 dec)
L4 db 12h              ; byte initialized to hex 12 (18 in decimal)
L5 db 17o              ; byte initialized to octal 17 (15 in decimal)
L6 dd 1A92h            ; double word initialized to hex 1A92
L7 resb 1              ; 1 uninitialized byte
L8 db "A"              ; byte initialized to ASCII code for A (65)
L9 db 0, 1, 2, 3                 ; defines 4 bytes
L10 db "w", "o", "r", ’d’, 0     ; defines a C string = "word"
L11 db ’word’, 0                 ; same as L10
L12 times 100 db 0               ; equivalent to 100 (db 0)’s
L13 resw 100                     ; reserves room for 100 words
```

Etykiety używa się na dwa sposoby. Etykieta oznacza adres zmiennej, a więc pełni tą samą rolę co wskaźnik w C. Jeśli etykieta jest umieszczona w nawiasach kwadratowych, oznacza wartość wpisaną pod adresem skojarzonym z etykietą (wyłuskanie w C).

```nasm 
mov al, [L1]                     ; copy byte at L1 into AL
mov eax, L1                      ; EAX = address of byte at L1
mov [L1], ah                     ; copy AH into byte at L1
mov eax, [L6]                    ; copy double word at L6 into EAX
add eax, [L6]                    ; EAX = EAX + double word at L6
add [L6], eax                    ; double word at L6 += EAX
mov al, [L6]                     ; copy first byte of double word at L6 into AL
```

Asembler nie sprawdza, czy etykiety są używane poprawnie, co może być źródłem wielu błędów. Przy próbie wpisywania danych do pamięci należy pamiętać o konwersji typów np.:

```nasm 
mov [L6], 1               ; próba zapisu 1 do L6 - niepoprawna, zwróci błąd operation size not specified
mov dword [L6], 1         ; próba zapisu 1 do L6 - poprawna
```
### Wywołania systemowe
Wywołania systemowe są podprogramami dostarczanymi przez system operacyjny. Dzięki nim mamy dostęp m.in. do klawiatury, ekranu, systemu plików, zegara systemowego. Uruchamiamy je instrukcją `syscall`.

[Skrócona lista przydatnych wywołań systemowych](../talks/syscalls.md)

## Przydatne narzędzia

### Debugger
Pisanie programów w assemblerze i szukanie błędów znacznie ułatwia debugger, który pozawala śledzić wykonanie programu instrukcja po instrukcji. 
Więcej informacji można znaleźć w dziale o [debuggerach](../utils/debugger.md).

### Edytor 
Do pisania programów w asemblerze nie potrzebne jest rozbudowane IDE, wystarczy edytor tekstowy najlepiej z kolorowaniem składni. 
Ja polecam **Geany**, mały edytor pozwalający dodatkowo zdefinować dla każdego języka osobne polecenia kompilacji.  

Przykładowe ustawienia, które jednym klawiszem kompilują i linkują plik bieżący plik asemblerowy
(Zbuduj -> ustawienia kompilacji):

`(nasm "%f" -felf64 -o "%e".o) && (ld -m elf_x86_64 "%e".o -o"%e")`


## Zadania

### Zadanie 1

* Skompiluj przykładowy program,
* Zmodyfikuj go w ten sposób aby:
  * pytał o imię, 
  * wczytywał je z klawiatury,
  * wypisywał spersonalizowane przywitanie.

```
Jak masz na imię? Tomek
Witaj Tomek!
```

### Zadanie 2
Napisz program, który wczyta dwie liczby (jedno cyfrowe) wymnoży je do siebie i wyświetli wynik.

Wskazówka: Użyj dwukrotnie sys_read aby wczytać dwa teksty, pierwsze znaki skonwertuj na liczby odejmując kod ASCII '0', pomnóż je, rozdziel cyfry jedności i dziesiątek, potem skonwertuj na napis (można uzupełnić odpowiednio przygotowany tekst) i wypisz.  

### Zadanie 3

Napisz program który otwiera plik do dopisywania (jeżeli go nie ma to go tworzy) i wpisuje do niego tekst np. Twoje imię i nazwisko a następnie go zamyka.
Przy drugim uruchomieniu programu tekst w pliku powinien być wpisany dwukrotnie itd. 

*Wskazówka: Na [liście wywołań systemowych](../talks/syscalls.md) tryby i prawa dostępu są podane ósemkowo (przyrostek o), a odpowiedni tryb uzyskujemy robiąc OR bitowy np. 100o|2o tworzy plik do odczytu i zapisu.*


### Zadanie 4

Napisz program, który odczyta czas systemowy i wypisze aktualna godzinę. 

Wskazówki: 
  * Możesz wykorzystać wywołanie systemowe sys_time (13 lub 201).
    Jako wynik wywołania systemowego otrzymujemy liczbę sekund od 1 stycznia 1970.
  * Reszta z dzielenia przez 10 da nam cyfrę jedności liczby sekund, następnie dzielenie przez 6 da nam cyfrę dziesiątek liczby sekund itd.
    Przed każdym dzieleniem należy wyzerować EDX/RDX
  * Wygodnie jest przygotować sobie tekst jak poniżej i uzupełnić miejsca # odpowiednimi cyframi.
    ```
    db "Time: ##:##:##", 0ah
    ```
   

