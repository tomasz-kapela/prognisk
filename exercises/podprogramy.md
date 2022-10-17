---
layout: default
parent: Ćwiczenia
nav_order: 3
---

Podprogramy, tablice i stos
===============================
{:.no_toc}

* TOC
{:toc}

## Definiowanie tablic

Aby zdefiniować tablicę w segmencie danych inicjalizowanych .data 
używamy dyrektyw db, dw itd. 
Możemy wykorzystać dyrektywę TIMES by nie pisać wielokrotnie tego samego.

Aby zdefiniować tablicę w segmencie danych nieinicjalizowanych .bss 
używamy dyrektyw resb, resw itd., 
pamiętając o operandzie określającym ilość rezerwowanych jednostek pamięci.

```nasm
segment .data
a1 dd 1, 2, 3, 4, 5, 6, 7, 8, 9, 10   ; tablica 10 podwójnych słów zainicjalizowana na 1,2,..,10
a2 dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ; tablica 10 słów zainicjalizowana na 0
a3 times 10 dw 0                      ; j.w. z wykorzystaniem TIMES
a4 times 200 db 0                     ; tablica bajtów zawierająca 200 zer
times 100 db 1                        ; i potem 100 jedynek

segment .bss
a5 resd 10                      ; tablica 10 podwójnych słów
a6 resw 100                     ; tablica 100 słów
```

Warto pamiętać, że kompilator nie będzie w żaden sposób sprawdzał poprawności typów i ich właściwego użycia.

Poniższe zapisy definiują dokładnie takie same tablice (100 bajtów wypełnionych zerami).

```nasm 
tab1 times 100 db 0
tab2 times 50  dw 0
tab3 times 25  dd 0
```
Podany rozmiar jest głównie informacją dla assemblera jak ma traktować podaną stałą. 
Dlatego poniższe tablice nie są równoważne

```nasm
tab1 times 100 db 1       ; kolejne bajty to 1,1,1,1,1,1,1,1,...
tab2 times  50 dw 1       ;                  1,0,1,0,1,0,1,0,...
```

Dostęp do elementów tablicy
W asemblerze nie ma operatora [ ] z C, pozwalającego na dostęp do elementów tablicy. Aby uzyskać dostęp do elementu tablicy, należy obliczyć jego adres. Rozważmy definicje dwóch tablic:

```nasm
array1 db 5, 4, 3, 2, 1                 ; tablica bajtów
array2 dw 5, 4, 3, 2, 1                 ; tablica słów
```

Przykłady operacji na tablicach:

```nasm
mov al, [array1]                        ; al = array1[0]
mov al, [array1 + 1]                    ; al = array1[1]
mov [array1 + 3], al                    ; array1[3] = al
mov ax, [array2]                        ; ax = array2[0]
mov ax, [array2 + 2]                    ; ax = array2[1] (nie array2[2]!)
mov [array2 + 6], ax                    ; array2[3] = ax
mov [array2 + 3 * 2],  ax               ; można też tak
mov ax, [array2 + 1]                    ; w ax wartość 0x0400 (młodszy bajt z 5 i starszy z 4)
```

### Adresowanie pośrednie

W przypadku adresowania pośredniego (indirect addressing) rejestry pełnią rolę zmiennych wskaźnikowych. 
Aby wydobyć wartość spod adresu, który znajduje się w rejestrze, 
symbol rejestru w instrukcji umieszcza się w nawiasach kwadratowych:
```nasm
; jawne adresowanie zmiennej Data
mov ax, [Data]         ; ax = Data
; pośrednie adresowanie zmiennej Data
mov rbx, Data          ; rbx = &Data
mov ax, [rbx]          ; ax = *rbx
```

Na Listingu 1 przedstawiono przykład wykorzystania tablicy w procedurze sumującej liczby, 
wpisane w elementach tablicy:

*Listing 1*

```nasm 
 array2 dw 5, 4, 3, 2, 1     ; tablica słów
; ...
  mov rbx, array1         ; rbx = adres tablicy bajtów array1
  mov rdx, 0              ; edx będzie zawierać sumę 
  mov rax, 0              ; zerujemy rax, bo w sumowaniu uczestniczy rejestr eax
  mov rcx, 5              ; wielkość tablicy array2
lp:
  mov ax, [rbx]           ; ax = *rbx
  add edx, eax            ; edx += eax (nie al!)
  add rbx, 2              ; rbx++    (przesuwamy wskaźnik na następny element)
  loop lp
```

### Adresowanie skalowane ModR/M

Przy iteracyjnym dostępie do tablic korzysta się z adresowania skalowanego (ModR/M). Najbardziej ogólna forma takiego adresowania wygląda następująco:
```nasm
[ base_reg + factor * index_reg + offset ]
```
gdzie

*  `base_reg` - rejestr ogólnego przeznaczenia np. `RAX`, `RBX`, `RDI`, `R9` itd
*  `factor`  - stała 1, 2, 4 lub 8 (odpowiada on rozmiarowi danych w indeksowanej tablicy t.j. bajt, słowo, podwójne słowo, poczwórne słowo),
*  `index_reg` - rejestr ogólnego przeznaczenia np. `RAX`, `RBX`, `RDI`, `R9` itd
*  `offset` jest stałą (może np. służyć do wskazywania na dane pole wewnątrz większej struktury).

Na Listingu 2 wykorzystujemy adresowanie skalowane by obliczyć tą samą sumę co na Listingu 1.

*Listing 2*
```nasm
array2 dw 5, 4, 3, 2, 1     ; tablica słów
; ...
mov rbx, array2             ; rbx = adres tablicy array2
mov rcx, 5                  ; liczba elementów tablicy
xor rdx, rdx                ; zerujemy dx
sumowanie:
add dx, [rbx + 2*rcx - 2]   ; dodajemy elementy od ostatniego
loop sumowanie
```

## Wyznaczanie adresu elementu

Jeżeli chcemy obliczyć adres elementu tablicy (np. w celu przekazania go do fukcji) 
możemy użyć instrukcji `lea`

```nasm
lea rdx, [rbx + 2*rcx - 2]    ;  jeżeli rcx=2 to rdx będzie zawierał
                              ;  adres drugiego elementu tablicy (a nie jego wartość)
lea rbx, [rel array2 + 2]     ;  jest to szczególnie przydatne przy pisaniu 
                              ;  kodu position-independent 
```

## Niestandardowy przykład przekazywania adresu powrotu

Na Listingu 3 przedstawiono fragment kodu wykorzystującego rejestry oraz 
pośrednie adresowanie w celu przekazania danych pomiędzy programem głównym i procedurą.

Podprogram przekazuje też adres powrotu w rejestrze ecx, 
co jest niestandardowym sposobem i przykładem złych praktyk. 
Ma na celu pokazać jak uciążliwa i podatna na błędy jest taka konwencja.

*Listing 3*
```nasm
; UWAGA: Przykład złych praktyk przy wywoływaniu podprogramu

BITS 32

segment .bss

    input1 resd 1

    input2 resd 1

segment .text

...
  mov ebx, input1             ; ładujemy adres input1 do ebx
  mov ecx, ret1               ; łądujemy adres etykiety ret1 do ecx - do tej etykiety nastąpi powrót z procedury
  jmp short get_int           ; wywołanie procedury get_int
ret1:
  mov ebx, input2
  mov ecx, $ + 7             ; ecx = adres bieżący + 7
                             ; jest to adres pierwszego bajtu instrukcji do której wracamy z procedury get_int
  ;  musimy znać ilość bajtów ile zajmie na danej maszynie kod maszynowy instrukcji jmp 
  ;  co czyni ten kod nieprzenaszalnym
jmp short get_int
...
; subprogram get_int
; Parametry:
; ebx - adres podwójnego słowa,w którym przechowywana będzie wczytana liczba
; ecx - adres instrukcji powrotu
get_int:
  call read_int
  mov [ebx], eax                  ; zapisujemy dane wejściowe do pamięci
  jmp ecx                         ; powrót do procedury wołającej
```

## Stos

Inny sposób wymiany danych pomiędzy procedurami korzysta ze stosu - obszaru pamięci 
zorganizowanego w postaci listy LIFO. 
Przy obsłudze stosu korzystamy z instrukcji PUSH, odkładającej dane na stos, 
i z instrukcji POP, ściągającej dane ze stosu.

Rejestr RSP zawiera adres szczytu stosu. 
Jest on automatycznie modyfikowany przez instrukcje push i pop. 
Stos rośnie w "dół" tzn. odłożenie danych na stos zmniejsza RSP.

Instrukcja

```nasm 
push rcx
```

jest formalnie równoważna

```nasm 
sub rsp, 8
mov  [rsp], rcx
```

Instrukcja

```nasm 
pop rax
```

może być zastąpiona przez

```nasm 
mov rax, [rsp]
add rsp, 8
```

Wyłącznie w programach 32 bitowych mamy dostępne instrukcje PUSHA i POPA, które odkładają i przywracają wszystkie rejestry ogólnego przeznaczenia.

Stos jest kwantowany  co oznacza, że dane są odkładane w "paczkach" 8 bajtowych w systemach 64 bitowych oraz po 4 bajty w systemach 32 bitowych. Dlatego też odkładamy tylko całe rejestry.

Ponieważ możemy ręcznie modyfikować RSP, należy dbać o to aby wartość rejestru RSP była zawsze podzielna odpowiednio przez 8 lub 4. Czasami funkcje wymagają nawet więcej np. aby szczyt stosu (RSP) był wyrównany do granicy 16 bajtów (podzielny przez 16).

Poniżej zakładam, że system jest  64 bitowy.

Poniższe instrukcje przedstawiają sposób użycia stosu, przy założeniu, 
że początkowo RSP wskazuje na adres 1000h.

```nasm 
mov rax, 1
push rax           ; 1 zapisana pod adresem 0FF8h, RSP = 0FF8h
push 2             ; 2 zapisana pod adresem 0FF0h, RSP = 0FF0h
push 3             ; 3 zapisana pod adresem 0FE8h, RSP = 0FE8h
pop rax                  ; RAX = 3, RSP = 0FF0h
pop rbx                  ; RBX = 2, RSP = 0FF8h
pop rcx                  ; RCX = 1, RSP = 1000h
```

## Instrukcje `CALL` i `RET`

Stos zdecydowanie ułatwia korzystanie z podprogramów i jest niejawnie wykorzystywany 
przez instrukcje `CALL` (wywołanie procedury) i `RET` (powrót z procedury). 

Instrukcja `CALL` przed skokiem pod podany adres wcześniej odkłada na stos adres następnej instrukcji (RIP). 
Natomiast instrukcja `RET` wykonuje skok pod adres pobrany ze szczytu stosu.

Fragment kodu wykonujący wczytanie 2 liczb wykorzystując asm64_io 
i umieszczenie ich w pamięci pod wskazanym adresem:

*Listing 4*
```nasm 
%include "asm64_io.inc"
BITS 64
segment .bss
    input1 resd 1
    input2 resd 1

segment .text
global asm_main
asm_main:
;...
mov  ebx, input1             ; ładujemy adres input1 do ebx
call get_int                 ; wywołanie procedury get_int
mov ebx, input2
call get_int
ret

; subprogram get_int
; Parametry:
; ebx - adres podwójnego słowa,gdzie zapisana zostanie wczytana liczba
get_int:
push rax                ; odkładamy rax na stos bo read_int go modyfikuje
call read_int
mov [ebx], eax          ; zapisujemy dane wejściowe do pamięci
pop  rax                ; odtwarzamy rax
ret                     ; powrót do procedury wołającej
```

Ponieważ `CALL` i `RET` korzystają ze stosu, należy bardzo ostrożnie obsługiwać stos w podprogramach
- błąd w obsłudze stosu (np. pozostawienie jakiś danych na stosie) może spowodować,
że powrót z procedury nie uda się (nastąpi skok pod zły adres).

Instrukcja `RET` może mieć postać

```nasm
ret n
```

gdzie n jest stałą. Instrukcja po powrocie z prodprogramu dodatkowo dodaje n do rejestr RSP. 
Może zostać to wykorzystywane przez podprogram do usunięcia ze stosu argumentów 
odłożonych na stosie przed wywołaniem podprogramu.

## Zadanie 1

Zaimplementować program wczytujący liczby całkowite ze znakiem i odkładający je na stos aż do wczytania 0.

Następnie wczytujemy dodatkową liczbę całkowitą A.

Na ekran należy wypisać ilość wczytanych liczb podzielnych przez A.

```asm
INPUT:
4 -9 7 6 336 78 91 88 -111 0 3
OUTPUT:
5
```

## Zadanie 2

Zaimplementować funkcję szukającą elementu maksymalnego w tablicy liczb typu int (32 bitowe).

*  Przed wywołaniem funkcji na stosie znajdują się liczba elementów tablicy 
i wskaźnik na pierwszy element tablicy.
*  Funkcja powinna samodzielnie posprzątać te dane ze stosu (proszę uważać na adres powrotu).
*  Po powrocie z funkcji element maksymalny powinien znajdować się w rejestrze RAX.

Przykładowe użycie (z wykorzystaniem asm64_io)
```nasm
section .data
  tab1 dd 4, -5, 91, 44, 104, 4
  tab2 dd -1, -2, -3, -5
;...
section .text
global MAIN 
MAIN:
  push tab1
  push 5
  call find_max    ; wynik = 104
  call println_int
  push tab2
  push 4
  call find_max    ; wynik = -1
  call println_int 
  ret
```


## Zadanie 3

Napisać funkcję przekształcającą dany łańcuch tekstowy (zakończony zerem) 
na liczbę całkowitą oraz drugą funkcję przekształcającą liczbę całkowitą (ze znakiem) 
na łańcuch tekstowy zakończony zerem ( np. dla liczby 123 wynikiem powinno być "123",0).

Program powinien prezentować możliwości tych funkcji.

Jak przekazać argumenty i jak zwrócić wynik?

Czy można wynik zwrócić na stosie?

## Zadanie 4

Zaimplementować program szyfrujący znanym harcerskim szyfrem typu GA-DE-RY-PO-LU-KI.

Dany jest szyfr składający się z par liter zakończonych podwójnym zerem. 

```nasm 
szyfr db "ga","de","ry","po","lu","ki", " -", 0, 0
```

Napisz podprogram, który dla każdej litery ciągu wejściowego (zakończonego zerem)
sprawdzi czy dana litera występuje w szyfrze.

*  Jeżeli występuje to zamienia ją na odpowiadającą literę z pary.
*  Natomiast nie znalezione znaki wypisuje bez zmian.

Argumentami dla podprogramu powinny być adresy początku szyfru i łańcucha wejściowego. 
Podprogram modyfikuje odpowiednio łańcuch wejściowy. 

*Przykład*:

```bash
INPUT : ala ma kota
OUTPUT: gug-mg-iptg

INPUT : 123 gug-mg-iptg.
OUTPUT: 123-ala ma kota.
```

## Archiwum
### Zadanie 5

Dane są dwa ciągi znaków s1 i s2 o równej długości (poniższe są przykładowe):

```
s1="abcdefghijklmnopqrstuvwxyz"
s2="zyxwvutsrqponmlkjihgfedcba"
```

Napisz program, który dla każdej litery ciągu wejściowego znalezionej na pozycji `n` w ciągu `s1` 
wypisze odpowiadającą jej literę z ciągu `s2` na pozycji `n`, 
natomiast nie znalezione znaki wypisuje bez zmian.

*Przykład*:

```bash
Podaj ciąg znaków...
ala ma kota
zoz nz plgz

Podaj ciąg znaków...
123 zoz nz plgz.
123 ala ma kota.
```