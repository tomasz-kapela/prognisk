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

| nazwa	   | ósemkowo	| komentarz |
|---       |       ---:| ---       | 
|O_ACCMODE | 3o        | Pełne prawa dostępu | 
|O_RDONLY  |0o         |Otwieranie tylko do odczytu. Dostępne dla sys_mq_open. |
|O_WRONLY  |1o         |Otwieranie tylko do zapisu. Dostępne dla sys_mq_open. |
|O_RDWR    |2o         |Otwieranie do odczytu i zapisu. Dostępne dla sys_mq_open. |
|O_CREAT   |100o       |Utworzenie pliku. Dostępne dla sys_mq_open. |
|O_EXCL    |200o       |Nie twórz pliku, jeśli już istnieje. Dostępne dla sys_mq_open. |
|O_NOCTTY  |400o       |Jeśli podana nazwa pliku to terminal, to NIE zostanie on terminalem kontrolnym procesu. |
|O_TRUNC   |1000o      |Obcięcie pliku |
|O_APPEND  |2000o      |Dopisywanie do pliku |
|O_NONBLOCK  |4000o    |Nie otwieraj, jeśli spowoduje to blokadę. Dostępne dla sys_mq_open. |
|O_NDELAY    |4000o    |jak wyżej |
|O_SYNC      |10000o   |specyficzne dla ext2 i urządzeń blokowych |
|FASYNC      |20000o   |fcntl, dla zgodności z BSD |
|O_DIRECT    |40000o   |podpowiedź bezpośredniego dostępu do dysku, obecnie ignorowana |
|O_LARGEFILE |100000o  |Pozwól na otwieranie plików >4GB |
|O_DIRECTORY |200000o  |musi być katalogiem |
|O_NOFOLLOW  |400000o  |nie podążaj za linkami |


**Prawa dostępu (/usr/include/linux/stat.h)**

|nazwa	  | ósemkowo|komentarz|
|:---    |     ---:|:---      |
|S_ISUID |  4000o  |ustaw ID użytkownika przy wykonywaniu (suid) |
|S_ISGID |  2000o  |ustaw ID grupy przy wykonywaniu (sgid) |
|S_ISVTX |  1000o  |"sticky bit" - usuwać z takiego katalogu może tylko właściciel |
|S_IRUSR |    400o |czytanie przez właściciela (S_IREAD) |
|S_IWUSR |    200o |zapis przez właściciela (S_IWRITE) |
|S_IXUSR |    100o |wykonywanie/przeszukiwanie katalogu przez właściciela (S_IEXEC) |
|S_IRGRP |     40o |czytanie przez grupę |
|S_IWGRP |     20o |zapis przez grupę |
|S_IXGRP |     10o |wykonywanie/przeszukiwanie katalogu przez grupę |
|S_IROTH |      4o |czytanie przez innych (R_OK) |
|S_IWOTH |      2o |zapis przez innych (W_OK) |
|S_IWOTH |      1o |wykonywanie/przeszukiwanie katalogu przez innych (X_OK) |
|S_IRWXUGO|   777o |czytanie, pisanie i wykonywanie przez wszystkich |
|S_IALLUGO | 7777o |czytanie, pisanie i wykonywanie przez wszystkich + suid + sgid + sticky bit |
|S_IRUGO |    444o |czytanie dla wszystkich |
|S_IWUGO |    222o |zapis dla wszystkich |
|S_IXUGO |    111o |wykonywanie/przeszukiwanie katalogu dla wszystkich |

## Zamknięcie pliku (sys_close)
* Numer: RAX = 3
* Parametry: 
  * RDI = deskryptor pliku
* Zwraca w EAX kod błędu

## Pobranie czasu systemowego (sys_time)
* Numer: RAX = 201
* Parametry: 
  * RDI = NULL lub adres bufora, który otrzyma kopie wyniku
* Zwraca w EAX liczbę sekund która upłynęła od 1 stycznia 1970 roku (minus 1)
