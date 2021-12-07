#include <stdio.h>

extern "C" void scaleSSE(float *,float *,int);

int main(void)
{
    const int N=400,HL=1078;
    float data[N][N],
          wynik[N][N];
    unsigned char header[HL];
    unsigned char ch;
        int i,j;

    FILE *strm;
    strm=fopen("circle3.bmp","rb");
    fread(header, 1, HL, strm);  // wczytuje header
    for(i=0;i<N;i++)             // wczytuje dane bitmapy
        for(j=0;j<N;j++)         // konwertując piksele na float
            data[i][j]=(float)fgetc(strm);
    fclose(strm);

    // właściwe skalowanie bitmapy wiersz po wierszu
    for(i=0;i<N/2;i++) 
        scaleSSE(wynik[i],data[2*i],N);
    
    // Modyfikujemy rozmiar bitmapy w nagłówku
    header[4]=0; header[3]=160; header[2]=118; // rozmiar pliku

    header[18]=200;   header[19]=0;  // szerokość bitmapy
    header[22]=200;   header[23]=0;  // wysokość bitmapy

    // Zapisuje wynik do pliku
    strm=fopen("wynik3.bmp","wb");
    fwrite(header, 1, HL, strm);      
    for(i=0;i<N/2;i++)
        for(j=0;j<N/2;j++)    // konwertuje wyniki na skalę szarości
            fputc((unsigned char)wynik[i][j],strm);
    fclose(strm);
}
