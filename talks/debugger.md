---
layout: default
parent: Wykłady
nav_order: 8
---

Debuger GDB
=============
{:.no_toc}

* TOC
{:toc}

## Wstęp 
Debuger jest narzędziem, które umożliwia m.in. śledzenie wykonania programu instrukcja po instrukcji, sprawdzenie zawartości rejestrów czy pamięci, 
ustawianie breakpointów (pułapek), modyfikowanie programu i wiele innych. 

## Debuger GDB
Tutaj przedstawimy podstawy debugera gdb, ponieważ jest on najczęściej dostępny w Linuxie.

Aby zacząć załadować program o nazwie `program` do debugera gdb wpisujemy w linii poleceń
```shell
gdb ./program
```
Załaduje to program i przeanalizuje go pod kątem zawartych w nim etykiet czy dodatkowych informacji umieszczonych przez kompilator 
(dodając odpowiednie opcje podczas kompilacji (np. -g) możemy zwiększych ilość tych informacji).

Następnie ustawiamy **breakpoint**, czyli miejsce, w którym chcemy zatrzymać wykonanie programu i rozpocząć debugowanie. 
Przykładowo jeżeli chcemy zatrzymać się na początku funkcji `myFunction` wpisujemy
```
break myFunction
```
Jeżeli chcemy rozpocząć debugowanie od początku programu to możmy ustawic breakpoint na etykietę `_start` lub `main`.

Gdy ustawimy już breakpointy (możemy ustawić więcej niż jeden), możemy uruchomić program poleceniem
```
run
run lista argumentów
```
Rozpocznie to wykonanie programu aż do napotkania pierwszego breakpointa i przekaże ponownie sterowanie do debuggera. 
Mamy wtedy możliwość np. sprawdzenia zawartości rejestrów, stosu czy pamięci, prześledzenia kolejnych kroków instrukcja po instrukcji.  

[GDB QUICK REFERENCE](https://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)

## Sterowanie wykonaniem programu
```gdb
r  run       # wykonuje program aż do napotkania breakpointa 
si stepi     # przejście o jedną instrukcję dalej, wchodzi do wnętrza wywoływanych funkcji
ni nexti     # przejdź jedną instrukcję, bez wchodzenia do funkcji
s  step      # jedna linia kodu dalej (np. w C++), wchodzi do wywoływanych funkcji
n  next      # jedna linia kodu dalej, niew wchodzi do funkcji
c  continue  # kontynuuje debugowanie do następnego breakpointʼa lub końca/błędu wykonania
where        # wypisuje cały proces wywoływań którym program doszedł do danego miejsca
```

## Breakpoints
Do ustawiania breakpointów służy `break` (można używać skrótu `b`)

```gdb
break fun         # breakpoint na etykiecie/funkcji fun  
break 10          # breakpoint na linii nr 10 w kodzie źródłowym   
break *0xFF12345  # breakpoint na adresie 0xFF12345
tbreak etykieta   # breakpoint tymczasowy, zatrzymuje się tylko raz 
```

### Zarządzanie *breakpointami*
```gdb
info break        # wyświetla wszystkie breakpointy
delete n          # usuwa breakpoint numer n
disable n         # deaktywuje breakpoint numer n
enable n          # aktywuje breakpoint numer n
ignore n k        # ignoruje breakpoint numer n k razy
```
### Breakpointy warunkowe
```gdb
break etykieta if i==5  # zatrzymaj na etykiecie jeżeli zmienna i ma wartość 5 
condition 2 i==4        # dodanie warunku do istniejącego breakpointa nr 2 
condition 3 $eax==4     # przerwij wykonywanie jeżeli wartość w eax będzie równa 4
```

## Wyświetlanie zawartości

```
info reg         # zawartość rejestrów całkowitoliczbowych
info float       # zawartość rejestrów zmiennoprzecinkowych
info all-reg     # wszystkie rejestry
info stack       # stos wywołań funckji 
info functions.  # lista funkcji
info frame       # informacja o ramce stosu
```

```
print [/f] [expr]  # wypisze wartość wyrażenia expr w podanych formacie f
p /x $eax          # wypisz wartość w EAX szesnastkowo
p /d $ex           # wypisz dziesiętnie ze znakiem wartość w $eax
  x hexadecimal
  d signed decimal
  u unsigned decimal
  o octal
  t binary
  a address, absolute and relative
  c character
  f floating point
```

```
x [/Nuf] adres.   # wypisze zawartość pamięci pod danym adresem
   N   ile elementów wypisać
   u   rozmiar jednego elementu: b=1, h=2, w=4, g=8
   f   format jak w print + dodatkowo:
       s  łańcuch tekstowy zakończony 0
       i  instrukcja asemblerowa           
```

## Deasemblowanie funkcji
Ponadto możemy wyświetlić listę zdefiniowanych funkcji wpisując:

```
info functions
```
i zdeasemblować wybraną funkcję poleceniem:
```
disassemble nazwa_funkcji
```
Aby zdefiniować jaką składnię chcemy uzyskać przy deasembacji, piszemy:
```
set disassembly-flavor xxx    ;gdzie w miejsce xxx wstawiamy intel lub att
```

## Zmiana wartości
```
set $reg=???                    - ustawia wartość rejestru reg na wartość ???,

set variable zmienna=???        - ustawia wartość zmiennej na ???,

set variable *0x########=???    - ustawia wartość ??? w pamięci pod adresem 0x########.
```

## Tryb TUI

Ciekawą opcją jest przejście w tryb TUI. Włączamy go kombinacją klawiszy CTRL+x, a lub poleceniem gdb --tui.

Terminal zostaje podzielony na kilka okienek tekstowych na których możemy jednocześnie obserwować kod programu, rejestry itd.

Kolejne widoki przełączamy kombinacją klawiszy CTRL+x,2

Szczegóły można znaleźć np. na tej [stronie](http://www.cs.fsu.edu/~baker/ada/gnat/html/gdb_23.html). 

## Domyślne ustawienia GDB

Aby dostosować GDB bez konieczności wpisywania za każdym razem tych samych poleceń można umieścić je w pliku `.gdbinit` w katalogu domowym. 

Poniższy przykładowy plik `.gdbinit` ustawia domyślnie składnię intela i włącza gdb w trybie TUI z wyświetlonymi rejestrami.
```
set disassembly-flavor intel
set print pretty on
layout reg
```


## Skrypty GDB

Przykładowy skrypt skrypt.gdb

```
set verbose off

break _start
commands 1
  info r
  continue
end
run
quit
```

Uruchamiamy gdb poleceniem
```bash
gdb ./program -x skrypt.gdb -q
```
