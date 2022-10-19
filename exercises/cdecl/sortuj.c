#include <stdio.h>

void sortuj( int * a, int *b, int * c);

int check(int x, int y, int z){
  return (x>=y) && (y>=z) && (y>=z);
}

void test(int x, int y, int z){
  sortuj(&x, &y, &z);
  printf(" %d %d %d %s\n", x, y, z, check(x,y,z)? "OK": "BLAD!!");
}

int main(int argc, char **argv){

  test(3,4,5);

  test(3,5,4);

  test(4,3,5);

  test(4,5,3);

  test(5,3,4);

  test(5,4,3);

  test(6,7,6);

  test(-1,2,0);

  test(-12,-4,-8);

  return 0;
}