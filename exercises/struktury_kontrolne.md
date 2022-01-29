Struktury kontrolne
===============================
{:.no_toc}

* TOC
{:toc}

# Instrukcje skoku bezwarunkowego
Instrukcja JMP spowoduje wykonanie skoku bezwarunkowego (goto z języka C) do określonej etykiety
```nasm
JMP my_label
```

Wywołanie podprogramu odbywa się instrukcją `CALL`. Dokonuje ona skoku bezwarunkowego pod podany adres (etykietę będącą nazwą podprogramu) jednocześnie odkładając na stos adres powrotu (adres instrukcji występującej bezpośrednio po CALL). Umożliwia to instrukcji RET na powrót z podprogramu do miejsca wywołania.
```nasm
kwadrat:
  imul eax, eax
  ret
...
mov eax, 5
call kwadrat
```

# Instrukcje warunkowe
Instrukcje warunkowe pozwalają zaimplementować akcję w zależności od wyniku testu czy ostatnich operacji arytmetycznych. 
Podstawowy test  w asemblerze wykonuje się instrukcją CMP, porównującą dwa operandy i ustawiającą odpowiednie flagi rejestru flagowego. 
```nasm
CMP A, B
```
Działanie instrukcji CMP jest identyczne z SUB A, B z tą różnicą, że wynik nie jest zapamiętywany.

Innym testem jest instrukcja TEST
```nasm
TEST A, B
```
Wykonuje on operację bitowego AND A, B ustawiając odpowiednio flagi SF, ZF, PF i zerując OF i CF. 
Wykorzystuje się ją przede wszystkim by sprawdzić czy dana liczba jest równa 0 np. TEST EAX, EAX lub czy dany bit jest ustawiony np. TEST EAX, maska

Instrukcje skoków warunkowych, przedstawione w Tabeli 1 są wykonywane zazwyczaj bezpośrednio po instrukcji CMP lub TEST (inne instrukcje też mogą ustawiać rejestr flag procesora).
Tabela 1 Instrukcje skoków warunkowych

Korzystając z instrukcji przedstawionych powyżej można w prosty sposób stworzyć bloki kontrolne, odpowiadające konstrukcjom składniowym z języka C, np.:
```c
if ( EAX >= 5 )
    EBX = 1;
else
    EBX = 2;
```
można przetłumaczyć na:
```nasm
    cmp     eax, 5
    jge     thenblock
    mov     ebx, 2
    jmp     next
thenblock:
    mov     ebx, 1
next:
```

## Pętle
Instrukcje porównania i skoków można użyć do stworzenia pętli np. pętla for z języka C
```cpp
for (j=0,i=10; i>0; i--) { 	j=j+i; }
```
może być zaimplementowana w sposób następujący:
```nasm
   mov     eax, 0
   mov	    ecx, 10    ; ECX to zmienna I. i=10 
petla_for:     
  cmp	    ecx, 0		     
  jbe	    koniec_petli	; wychodzimy, gdy i <= 0   
  add	    eax, ecx	        ; EAX to zmienna J. j=j+i    
  dec    ecx		        ; i=i-1    
  jmp	    petla_for koniec_petli:
```    
Inny sposób implementacji pętli for to wykorzystanie instrukcji `LOOP`. 
Powyższy kod może być przepisany do postaci:
```nasm
   mov	    ecx, 10		; ECX to zmienna I. i=10
   mov     eax, 0
petla_for:     
   add	    eax, ecx	   ; EAX to zmienna J. j=j+i 
   loop	petla_for	     ; zmniejsz ECX o 1 i jeśli różny od 				
                       ; zera, skocz do: petla_for
```

## Wejście/wyjście z biblioteką asm64_io
Wczytywanie i wypisywanie liczb z assemblera nie jest łatwe. W tym celu można użyć biblioteki asm64_io, która ułatwia wywołanie odpowiednich funkcji języka C z assemblera. Biblioteka ta pozwala też wypisać zawartość rejestrów ułatwiając debugowanie.
Wiecej informacji....

Kompilacja własnego pliku w Geany (zakładając, że asm64_io jest skompilowane już w bieżącym katalogu)
(nasm "%f" -felf64 -o "%e".o) && (gcc "%e".o driver64.o asm64_io.o -o"%e")

# Zadanie 1

Napisz program w asemblerze sprawdzający, czy dana liczba jest liczbą pierwszą.
Dla liczby n należy sprawdzić czy któraś z liczb naturalnych pomiędzy 2 a pierwiastek z n dzieli n.  We wstępnej wersji można sprawdzać do n-1. 
W wersji podstawowej liczba może być na sztywno wpisana w program.
W wersji rozszerzonej wczytujemy liczbę z klawiatury.

# Zadanie 2

Napisz funkcję w asemblerze, która wypisze na ekran liczbę całkowitą ze znakiem umieszczona w rejestrze EAX wykorzystując przerwania systemowe. 
Przed wypisaniem należy zamienić liczbę na łańcuch tekstowy (np. dzielimy w pętli przez 10 z resztą a kolejne cyfry umieszczamy w buforze). 

# Zadanie 3

Proszę napisać program wypisujący rozkład zadanej liczby na czynniki pierwsze. 
Można wypisywać posługując się asm_io lub printf.
Np. dla liczby 60 wyjście powinno zawierać:
2 2 3 5

# Zadanie 4

Napisz program, który dla danej liczby n i przedziału [a, b] wyszuka i wypisze na ekran wszystkie liczby z przedziału [a,b] względnie pierwsze do n.
Program może po prostu dla każdej liczby x z przedziału [a,b] obliczać NWD(n,x) i wypisywać liczbę x jeżeli wynik jest równy 1.   

# Archiwum

## Zadanie 5

Napisz program szukający najmniejszej wspólnej wielokrotności dwóch liczb wczytanych z klawiatury.

## Zadanie 6 

Napisz program szukający liczb pierwszych w zadanym przedziale.
Algorytm może po prostu sprawdzać po kolei liczby z zadanego przedziału. 
