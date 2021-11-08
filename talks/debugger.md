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
```
Rozpocznie to wykonanie programu aż do napotkania pierwszego breakpointa i przekaże ponownie sterowanie do debuggera. 
Mamy wtedy możliwość np. sprawdzenia zawartości rejestrów, stosu czy pamięci, prześledzenia kolejnych kroków instrukcja po instrukcji.  

## Sterowanie wykonaniem programu
```
run      - wykonuje program aż do napotkania breakpointa 
stepi    - przejście o jedną instrukcję dalej,
ni       - przejdź jedną instrukcję (to samo co stepi),
si       - przejdź dokładnie jedną instrukcję,
rni      - cofa się o jedną instrukcję (odwrotność ni),
rsi      - cofa o dokładnie jedną instrukcję (odwrotność si),
c        - kontynuuje debugowanie do następnego breakpointʼa lub końca/błędu wykonania,
rc       - kontynuuje debug programu wstecz (odwraca kolejność wykonywania instrukcji programowych),
where    - wypisuje cały proces wywoływań którym program doszedł do danego miejsca.
```
Komendy z cofaniem (reverse steps) nie zawsze działają w programach.

## Breakpoints

## Wyświetlanie zawartości

## Zmiana wartości

## Tryb TUI
