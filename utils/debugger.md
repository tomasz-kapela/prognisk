---
layout: default
title: Debugger
parent: Narzędzia
nav_order: 2
---

Debugger
=======

* Debugger pomaga prześledzić działanie programu, stany rejestrów, pamięci itd.
* Mamy w nim możliwość ustawienia breakpointów na konkretnych instrukcjach lub etykietach.
* Możemy śledzić wykonywanie programu instrukcja po instrukcji, cały czas monitorując stan rejestrów, flag procesora czy zmiennych w pamięci.

## Debugger GDB

Standardowym debuggerem pod Linuxem jest gdb. 
Jest to potężne narzędzie, niestety działa w trybie tekstowym 
i jego obsługa jest dość skomplikowana. 

[Krótki opis moźliwości GDB](../talks/debugger.md)

## Debuggery z GUI

Dużo łatwiejsze w użyciu są debuggery z GUI. Poniżej lista kilku darmowych debuggerów.

*  [DDD](https://www.gnu.org/software/ddd/) - nakładka na gdb
*  [SASM](https://dman95.github.io/SASM/english.html) - edytor SASM ma wbudowany debugger
*  [EDB](http://codef00.com/projects#debugger) - prosty debugger dla Linuxa
*  [OllyDbg](http://www.ollydbg.de/) - debugger dla Windowsa 