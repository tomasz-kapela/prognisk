---
layout: default
title: XXX
nav_exclude: true
---

Interfejsowanie do C w 32 bitach - standard cdecl
=================================================



## Kompilacja na Linuxie 64-bitowym

Aby kompilować programy 32 bitowe w systemie Linux 64 bitowym przeważnie trzeba doinstalować odpowiednie 32 bitowe pakiety `gcc-multilib` i `lib32stdc++-XX-dev` (gdzie XX to wersja kompilatora g++). Przykładowo w Ubuntu
```bash
sudo apt install gcc-multilib lib32stdc++10-dev
```
Kompilując i linkując musimy dodawać odpowiednie opcje `-felf32` i `-m32` informujące, że chcemy otrzymać kod binarny 32 bitowy. Przykładowo dla plików zródłowych main.cpp i funkcja.asm mamy
```bash
g++ -m32 -c main.cpp -o main.o
nasm -felf32 funkcja.asm -o funkcja.o
g++ -m32 main.o funkcja.o -o main
```

