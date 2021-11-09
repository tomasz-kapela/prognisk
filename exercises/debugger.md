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

### Zadanie 1

Uruchomić gdb na przykładowym programie debug lub debug64 ustawić break na etykietę stop i wypisać zawartość rejestrów oraz listę funkcji, a następnie zdeasemblować wszystkie funkcje programu i znaleźć błąd odpowiedzialny za niewyświetlanie napisu “Hello World!”

Naprawić błąd bezpośrednio w gdb tak aby program wykonał się poprawnie wyświetlając napis. 

Napisać skrypt dla gdb, który automatycznie naprawia ten błąd. 

### Zadanie 2
Dostępny jest plik *main.c* z funkcją **main**, zawierający przykłady użycia i plik binarny **funkcja32**  programu w wersji 32-bit (fukcja32_O2 - wersja skompilowana z optymalizacją O2). 
Chciano przekompilować ten program do wersji 64-bitowej. Niestety zaginął plik C  z definicją funkcji  
```c
char f(char, char, char);
```
Odtwórz plik *funkcja.c* (z implementacją funkcji f) używając gdb i analizując wersję binarną funkcji f. 

Jako rozwiązanie prześlij tylko plik funkcja.c.

### Zadanie 3
Używając debugera do obejścia zabezpieczeń odczytaj sekretna informację.

Jako rozwiązanie prześlij hasło dostępu lub skrypt GDB obchodzący zabezpieczenia.
