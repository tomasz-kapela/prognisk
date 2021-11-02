# Wywołania systemowe Linuxa 64-bit

Poniżej znajdują się wybrane wywołania systemowe Linuxa potrzebne do rozwiązania zadań. 
Pełne listy wywołań systemowych danego Linuxa można szukać w plikach 
```
/usr/include/asm/unistd_32.h
/usr/include/asm/unistd_64.h
```

Argumenty wywołania możemy sprawdzić przez plecenie man np.
```
man 2 open
man 2 write
```

Numer wywołania systemowego umieszczamy w rejestrze `RAX`.

Argumenty umieszczamy kolejno w rejestrach `EDI, ESI, EDX, R10, R8, R9`.

Wywołanie systemowe może dodatkowo zmodyfikować wartość rejestrów `RCX, R11`.

## Wyjście z programu (sys_exit)
* Numer: RAX = 60
* Parametry: 
  * RDI = kod zakończenia programu


## Zapis do pliku / na ekran (sys_write)
* Numer: RAX = 1
* Parametry: 
  * RDI = deskryptor pliku (ekran = 1)
  * RSI = adres ciągu bajtów do zapiania
  * RDX = liczba bajtów w ciągu
* Zwraca w EAX liczbę zapisanych bajtów lub kod błędu (liczba ujemna)

## Odczyt z pliku / klawiatury (sys_read)
* Numer: RAX = 0
* Parametry: 
  * RDI = deskryptor pliku (klawiatura = 0)
  * RSI = adres bufora docelowego
  * RDX = liczba bajtów do przeczytania
* Zwraca w EAX liczbę przeczytanych bajtów lub kod błędu


## Otwarcie pliku (sys_open)
* Numer: RAX = 2
* Parametry: 
  * RDI = adres pod którym znajduje sie nazwa pliku (zakonczona zerem)
  * RSI = tryb pracy 
  * RDX = prawa dostępu (jeżeli tworzymy nowy plik)
* Zwraca w RAX deskryptor pliku lub kod błędu

**Tryby pracy (z /usr/include/asm/fcntl.h)**
| nazwa	| ósemkowo	| komentarz |
|--- | --- | ---| 
|O_ACCMODE | 3 | Pełne prawa dostępu | 
|O_RDONLY |0 |Otwieranie tylko do odczytu. Dostępne dla sys_mq_open. |

O_WRONLY 
1 
Otwieranie tylko do zapisu. Dostępne dla sys_mq_open. 
O_RDWR 
2 
Otwieranie do odczytu i zapisu. Dostępne dla sys_mq_open. 
O_CREAT 
100 
Utworzenie pliku. Dostępne dla sys_mq_open. 
O_EXCL 
200 
Nie twórz pliku, jeśli już istnieje. Dostępne dla sys_mq_open. 
O_NOCTTY 
400 
Jeśli podana nazwa pliku to terminal, to NIE zostanie on terminalem kontrolnym procesu. 
O_TRUNC 
1000 
Obcięcie pliku 
O_APPEND 
2000 
Dopisywanie do pliku 
O_NONBLOCK 
4000 
Nie otwieraj, jeśli spowoduje to blokadę. Dostępne dla sys_mq_open. 
O_NDELAY 
O_NONBLOCK 
jak wyżej 
O_SYNC 
10000 
specyficzne dla ext2 i urządzeń blokowych 
FASYNC 
20000 
fcntl, dla zgodności z BSD 
O_DIRECT 
40000 
podpowiedź bezpośredniego dostępu do dysku, obecnie ignorowana 
O_LARGEFILE 
100000 
Pozwól na otwieranie plików >4GB 
O_DIRECTORY 
200000 
musi być katalogiem 
O_NOFOLLOW 
400000 
nie podążaj za linkami 


**Prawa dostępu (/usr/include/linux/stat.h)**

nazwa	ósemkowo	komentarz
S_ISUID 
4000 
ustaw ID użytkownika przy wykonywaniu (suid) 
S_ISGID 
2000 
ustaw ID grupy przy wykonywaniu (sgid) 
S_ISVTX 
1000 
"sticky bit" - usuwać z takiego katalogu może tylko właściciel 
S_IRUSR 
400 
czytanie przez właściciela (S_IREAD) 
S_IWUSR 
200 
zapis przez właściciela (S_IWRITE) 
S_IXUSR 
100 
wykonywanie/przeszukiwanie katalogu przez właściciela (S_IEXEC) 
S_IRGRP 
40 
czytanie przez grupę 
S_IWGRP 
20 
zapis przez grupę 
S_IXGRP 
10 
wykonywanie/przeszukiwanie katalogu przez grupę 
S_IROTH 
4 
czytanie przez innych (R_OK) 
S_IWOTH 
2 
zapis przez innych (W_OK) 
S_IWOTH 
1 
wykonywanie/przeszukiwanie katalogu przez innych (X_OK) 
S_IRWXUGO
(S_IRWXU | S_IRWXG | S_IRWXO) 
czytanie, pisanie i wykonywanie przez wszystkich 
S_IALLUGO 
(S_ISUID | S_ISGID | S_ISVTX | S_IRWXUGO) 
czytanie, pisanie i wykonywanie przez wszystkich + suid + sgid + sticky bit 
S_IRUGO 
(S_IRUSR | S_IRGRP | S_IROTH) 
czytanie dla wszystkich 
S_IWUGO 
(S_IWUSR | S_IWGRP | S_IWOTH) 
zapis dla wszystkich 
S_IXUGO 
(S_IXUSR | S_IXGRP | S_IXOTH) 
wykonywanie/przeszukiwanie katalogu dla wszystkich 

Zamknięcie pliku (sys_close)
Numer: EAX = 6 / RAX = 3
Parametry: 
EBX / RDI = deskryptor pliku
Zwraca w EAX kod błędu
Pobranie czasu systemowego (sys_time)
Numer: EAX = 13 / RAX = 201
Parametry: 
EBX / RDI = NULL lub adres bufora, który otrzyma kopie wyniku
Zwraca w EAX liczbę sekund która upłynęła od 1 stycznia 1970 roku (minus 1)