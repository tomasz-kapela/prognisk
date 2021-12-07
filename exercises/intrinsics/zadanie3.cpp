#include <iostream>
#include <cmath>
using namespace std;
// width powinien dzielic sie przez 4
const int width = 300, height = 168;

void filtr(int imageWidth, int imageHeight,
           float image[height][width],
           float weight[3][3],
           float result[height][width]){

  // TODO !!!

}

int main(void)
{
    const int headerLength = 122; // 64; //sizeof(BMPHEAD);
    char header[headerLength];
    float data[3][height][width];    // tablica dla każdej składowej koloru
    float result[3][height][width];

    float weight[3][3]= {{0, -2, 0} ,{ -2, 11, -2}, {0, -2, 0}};
    
    int i,j,k;
    FILE *file;
    file=fopen("pigeon.bmp","rb");
    if(!file) { std::cerr << " Error opening file !"; exit(1); }
    fread(header, headerLength, 1, file);
    for(i=0;i<height;i++)
        for(j=0;j<width;j++)
           for(k=0; k<3; ++k)
            data[k][i][j]=fgetc(file);
    fclose(file);
    
    for(i=0;i<3;i++)   // filtrujemy dla każdej składowej osobno
        filtr(width, height, data[i], weight, result[i]);

    file=fopen("result.bmp","wb");
    fwrite(header, headerLength, 1, file);
    for(i=0;i<height;i++)
      for(j=0;j<width;j++)
        for(k=0; k<3; ++k)
          fputc((unsigned char)result[k][i][j],file);
    fclose(file);
}
