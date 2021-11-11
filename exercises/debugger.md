Debugowanie
===============================
{:.no_toc}

* TOC
{:toc}

## Wprowadzenie

Debuger GDB umożliwie wykonanie programu instukcja po instrukcji i śledzenie wartości rejestrów i zmiennych. 
Pozwala to często zauważyć błędy w programie.

[Skrócony opis możliwości GDB](../talks/debugger.md)

## Zadania 

*Wskazówka:* W poniższych zadaniach do pobrania są pliki binarne. Aby zacząć je debugować należy najpierw nadać im atrybut wykonywalnośći np. poleceniem
```bash
chmod u+x nazwa_programu
```

### Zadanie 1

Program [hello64](https://ww2.ii.uj.edu.pl/~kapela/pn/bin/hello64) powinien wyświetlać napis “Hello World!”. Niestety nie wyświetla.

* Zdebugować program używając gdb i znaleźć przyczynę.  
* Naprawić błąd bezpośrednio w gdb tak aby program wykonał się poprawnie wyświetlając napis. 
* Napisać skrypt dla gdb, który automatyzuje ten proces.

 *Jako rozwiązanie prześlij sam skrypt gdb*

Wskazówki: 
 * Breakpointa można ustawić na etykietę `stop` (lub `_start`).
 * zdeasemblować funkcję `_start`
 * Wykonać program krok po kroku obserwując zawartość rejestrów. 


### Zadanie 2
Dostępny jest plik **[funkcja.c](funkcja.c)** z funkcją `main`, zawierający przykłady użycia i plik binarny **[oblicz32](https://ww2.ii.uj.edu.pl/~kapela/pn/bin/oblicz32)**  programu w wersji 32-bit. 
Chciano przekompilować ten program do wersji 64-bitowej. Niestety zaginął plik C  z definicją funkcji  
```c
long oblicz(short, int, long);
```
Odtwórz plik *oblicz.c* (z implementacją funkcji oblicz) używając gdb i analizując wersję binarną funkcji oblicz. 

Jako rozwiązanie prześlij tylko plik oblicz.c.

### Zadanie 3
Używając debugera do obejścia zabezpieczeń odczytaj sekretna informację.

Jako rozwiązanie prześlij hasło dostępu lub skrypt GDB obchodzący zabezpieczenia.

Programy binarne do wyboru:  
* [pass32.exe](https://ww2.ii.uj.edu.pl/~kapela/pn/bin/pass32.exe) - 32-bit, no-pie
* [pass64.exe](https://ww2.ii.uj.edu.pl/~kapela/pn/bin/pass64.exe) - 32-bit, no-pie
* [pass64_pie.exe](https://ww2.ii.uj.edu.pl/~kapela/pn/bin/pass64_pie.exe) - 32-bit, pie
