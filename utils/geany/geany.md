---
layout: default
title: Edytor Geany
parent: Narzędzia
nav_order: 1
---

# Edytor Geany

Pliki assemblerowe można edytować dowolnym edytorem tekstu, 
jednak na zajęciach w pracowniach polecam edytor Geany.
Na tej stronie zamieszczam instrukcję jak można go dostosować w celu wygodniejszej pracy.

## Polecenia kompilacji

W Geany można zdefiniować swoje własne polecenia kompilacji/budowania/uruchomienia 
dla każdego z języków osobno  (menu `Zbuduj` -> `Zdefiniuj polecenia budowania`):

* Kompilacja i linkowanie pojedynczego pliku  *.asm   
  
  `(nasm "%f" -felf64 -o "%e".o) && (ld -m elf_x86_64 "%e".o -o"%e")`

* Kompilacja pliku *.asm i linkowanie z biblioteką asm64_io 
  (zakładamy, że jest już skompilowana w tym samym katalogu)

  `(nasm "%f" -felf64 -o "%e".o) && (gcc "%e".o asm64_io.o -o"%e")`

* Kompilacja pary plików XXX.asm i XXX.cpp i następnie linkowanie ich

  `(nasm "%f" -felf64 -o "%e".o) && (g++ -c "%e".cpp -o "%e".co) && (g++ "%e".co "%e".o  -o"%e")`

## Kolorowanie kodu i polecenia kompilacji

*Geany* dość słabo koloruje kod asemblerowy NASM. 
Przygotowałem plik z poprawionym kolorowaniem [filetypes.asm](filetypes.asm).

[Pobierz plik filetypes.asm](filetypes.asm)

Plik ten należy umieścić w swoim katalogu domowym w katalogu:
.config/geany/filedefs

Następnie należy ponownie otworzyć Geany 
lub wczytać konfigurację (Narzędzia / Wczytaj ponownie konfigurację)

>  Uwaga. W pliku tym są także zdefiniowane polecenia kompilacji 
>  i nadpiszą one dotychczasowe.
