SSE - Operacje wektorowe SIMD
=============================
Architektura SIMD i udostępniane przez nią techniki programowania niskopoziomowego używane są w celu efektywniejszego wykonywania 
obliczeń poprzez równoległe przetwarzanie wielu bajtów danych. Technologia ta bazuje na spakowanych typach danych i specjalnych instrukcjach procesora. 

## SSE
SSE to skrót od Streaming SIMD Extensions, z koleji SIMD to skrót od Single Instruction Multiple Data. 

Operacje wykonywane są w dwóch trybach 
* **scalar** na pojedynczych danych, oznaczenie `s` w mnemoniku instrukcji 
* **packed** na wektorach danych (danych spakowancyh), oznaczenie `p` w mnemoniku instrukcji
W nazwie instrukcji kodujemy też typ pojedynczego elementu
* `s` - single precision: typ `float`
* `d` - double precision: typ `double`

```nasm
movss xmm0, [x]  ; załaduj spod adresu x jednego float
addpd xmm0, xmm1 ; dodaj do siebie dwa wekory liczb double
```

### Rejestry SSE

*  `XMM0`-`XMM15` - 128-bitowe, mogą przechować: 4 x float, 2 x double, 4 x int, 16 x char
*  `YMM0`-`YMM15` - 256-bitowe - rozszerzają rejestry `XMM*`, wymagają rozszerzenia `AVX`
*  `ZMM0`-`ZMM15` - 512-bitowe - wymagają rozszerzenia `AVX512`

# Przesyłanie danych
```nasm
movss       ; kopiuj jednego floata 
movsd       ; kopiuj jednego double
movaps      ; kopiuj paczkę 4xfloat spod adresu podzielnego przez 16
movups      ; kopiuj paczkę 4xfloat spod dowolnego adresu
movdqa      ; kopiuj wektor liczb całkowitych (16 bajtów) spod adresu podzielnego przez 16
movdqu      ; kopiuj wektor liczb całkowitych (16 bajtów) spod dowolnego adresu  
movlps      ; kopiuj dolną połowę rejestru (2xfloat)
movhps      ; kopiuj górną połowę rejestru (2xfloat)
movhlps     ; kopiuj górną połowę rejestru do dolnej połowy (2xfloat)
movlhps     ; kopiuj dolną połowę rejestru do górnej połowy (2xfloat)
```
### Operacje arytmetyczne
Operacje arytmetyczne mogą być wykonywane :
* **wektorowo** na odpowienich parach elementów (**@=ps** lub **@=pd**)
* **skalarnie** na elemencie o indeksie 0 (**@=ss** lub **@=sd**). 

```nasm
add@ x, y     ;  x = x + y 
sub@ x, y     ;  x = x - y
mul@ x, y     ;  x = x * y
div@ x, y     ;  x = x / y
rcp@ x, y     ;  x = 1 / y
sqrt@ x, y    ;  x = sqrt(y)
rsqrt@ x, y   ;  x = 1 / sqrt(y)
max@ x, y     ;  x = max(x, y)
min@ x, y     ;  x = min(x, y)
```
### Operacje bitowe
```nasm
andps x, y    ;  x = x and y
orps  x, y    ;  x = x or y
xorps x, y    ;  x = x xor y
andnps x, y   ;  x = x and !y
```
### Materiały
* [Notatki z wykłądu](https://ww2.ii.uj.edu.pl/~kapela/pn/splitLecture.php?slideNumber=4&lectureNumber=10)
* [Proste zestawienie przydatnych instrukcji](http://www.songho.ca/misc/sse/sse.html)
* [Intel® Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html) - pełne zestawienie instrukcji z wygodną wyszukiwarką.

### Przykład
[Iloczyn dwóch tablic](https://ww2.ii.uj.edu.pl/~kapela/pn/splitLecture.php?slideNumber=10&lectureNumber=10) 

## Zadanie 1
Zaimplementować w asemblerze funkcję 
```
void diff(char *out,char *tab, int n);
```
która wykorzystując operacje SSE wyliczy różnice sąsiednich elementów tablicy *tab* o rozmiarze *n+1* 
```
out[i] = tab[i+i] - tab[i]
```
Aby uniknąć przepełnień należy zastosować odejmowanie z nasyceniem (instrukcja `PSUBSB`).

*Dane wejściowe mogą być np. wierszem pikseli obrazu a otrzymany wynik można interpretować jako pochodną numeryczną.*


Przykład użycia funkcji `diff` 
```cpp
#include <stdio.h>
const int N = 100;

// na wyjściu out[i] = wiersz[i+1] - wiersz[i]
extern "C" void diff(char *out,char *wiersz, int n);

int main(void)
{
    char tablica[N+1], DIFF[N];
    int i;

    tablica[0]=1;

    for(i=1;i<=N;i++)
        tablica[i]=tablica[i-1]+i;

    diff(DIFF, tablica, N);

    for(i=0;i<N;i++)
        printf("%d ",DIFF[i]);

    printf("\n");
}

// OUT: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -128 17 18 19 20 
```

## Zadanie 2
Korzystając z instrukcji SSE proszę napisać procedurę wyliczającą amplitudę gradientu obrazu - 8-bitowej bitmapy.
Na Listingu 4 przedstawiono również prototyp funkcji liczącej gradient. 
Gradient GRAD(i,j) w pikselu (i,j) liczony jest według wzoru:

GRAD(i,j)= scale * sqrt((DATA(i+1,j)-DATA(i-1,j))2+(DATA(i,j+1)-DATA(i,j-1))2)

Na Listingu przedstawiony jest kod z instrukcjami pozwalającymi czytać i pisać do bitmapy 256-kolorowej. 
Dla polepszenia dokładności obliczeń gradientu, zarówno dane wejściowe jak i wyjściowe są typu float. 


Listing 4 Opakowanie asemblerowej funkcji liczącej gradient obrazu
```cpp
#include <stdio.h> 

//Na wyjściu: grad[i] = scale * sqrt( (data[i+1] - data[i-1])^2 + (data[i+N] - data[i-N])^2)  
// dla i=0,1,...,N-2  
extern "C" void gradientSSE(float *grad, float * data, int N, float scale);  
int main(void) {     
  const int N=400, HL=1078;
  char header[HL];
  float data[N][N];    
  float grad[N][N];     
            
  FILE *strm = fopen("circle3.bmp","rb");
  fread(header, 1, HL, strm); // wczytuje header
  for(int i=0; i<N; i++)         
    for(int j=0; j<N; j++)             
      data[i][j]=(float)fgetc(strm);  // czyta piksele i konwertuje na float     
  fclose(strm);      
  
  for(int i=1; i<N-1; i++) // Dla wszystkich pikseli "wewnętrznych"         
    gradientSSE(grad[i]+1, data[i]+1, N, 7);    // wyznaczamy gradient      
  
  for(int i=0; i<N; i++){ // Tworzymy białą ramkę obrazka       
     grad[0][i]=255; grad[N-1][i]=255; grad[i][0]=255; grad[i][N-1]=255;     
  }                   
  
  strm=fopen("wynik.bmp","wb");         
  fwrite(header, 1, HL, strm);
  for(i=0;i<N;i++)         
    for(j=0;j<N;j++)             
      fputc((unsigned char)grad[i][j],strm);     
  fclose(strm);              
}
```
Progam działa tylko dla obrazków 400x400 w skali szarości. Przykładowe obrazy wejściowy i wyjściowy przedstawiono poniżej.

| Obraz wejściowy  | Obraz wyjściowy |
| ---------------- | --------------- |
|  ![wejście](circle3.bmp)    | ![wyjście](dum.bmp)   |
|  [Pobierz](circle3.bmp)    | [Pobierz](dum.bmp)   |



Uwaga: Obrazek należy otworzyć w nowym oknie a następnie zapisać! Bezpośrednie zapisanie może powodować błędny format pliku.

UWAGA: Zaproponowana w zadaniu procedura liczenia gradientu z obrazu nie ma szczególnie dobrych własności i raczej nie jest wykorzystywana w praktyce. 
Filtry gradientowe można jednak zaimplementować, korzystając z analogicznych metod, jak rozważane w zadaniu.

## Zadanie 3
Korzystając z instrukcji SSE proszę napisać procedurę zmniejszającą dwukrotnie rozmiar bitmapy z poprzedniego zadania. 

Każdy stopień szarości piksela OUT(i,j) wynikowej bitmapy ma być średnią z czterech odpowiednich stopni szarości pikseli bitmapy wejściowej IN według wzoru: 

```
OUT(i,j) = (IN(2*i,2*j) + IN(2*i +1,2*j) + IN(2*i,2*j + 1) + IN(2*i + 1,2*j + 1))/4
```

Na Listingu przedstawiony jest kod opakowania dla procedury skalującej bitmapę wraz z prototypem i sposobem użycia tej funkcji.

```cpp
#include <stdio.h>

extern "C" void scaleSSE(float *,float *,int);

int main(void)
{
    float data[400][400],dum[200][200];
    unsigned char header[1078];
    unsigned char ch;
    int N=400,HL=1078;
    int i,j;

    FILE *strm;
    strm=fopen("circle.bmp","rb");
    for(i=0;i<HL;i++) header[i]=fgetc(strm);
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            data[i][j]=(float)fgetc(strm);
    fclose(strm);

    for(i=0;i<N/2;i++) scaleSSE(dum[i],data[2*i],N);
    
// Modyfikujemy rozmiar bitmapy w nagłówku
    header[4]=0;
    header[3]=160;
    header[2]=118;

    header[18]=200;
    header[19]=0;
    header[22]=200;
    header[23]=0;

    strm=fopen("dum.bmp","wb");
    for(i=0;i<HL;i++) fputc(header[i],strm);      
    for(i=0;i<N/2;i++)
        for(j=0;j<N/2;j++)
            fputc((unsigned char)dum[i][j],strm);
    fclose(strm);
}
```

*Uwaga:*
Informacje o wielkości bitmapy są zapisane w modyfikowanych bajtach nagłówka. 
W bajtach od 2 poczynając zakodowany jest rozmiar bitmapy w bajtach 
(równy wysokość * szerokość zaokrąglona do najbliższej liczby podzielnej przez 4 + ilość bajtów nagłówka). 
W bajtach od 18 poczynając zakodowane są wysokość i szerokość bitmapy.
