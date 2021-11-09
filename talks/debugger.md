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

## Sterowanie wykonaniem programu
```gdb
r  run       # wykonuje program aż do napotkania breakpointa 
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
### Breakpointy warunkowe
```

### Zarządzanie *breakpointami*
```gdb
info break        # wyświetla wszystkie breakpointy
delete n          # usuwa breakpoint numer n
disable n         # deaktywuje breakpoint numer n
enable n          # aktywuje breakpoint numer n
ignore n k        # ignoruje breakpoint numer n k razy
```
## Wyświetlanie zawartości

## Zmiana wartości

## Tryb TUI
