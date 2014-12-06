#include <iostream>
#include <cstdio>
#include <cstring>
#include <funcs1.h>

int main(void){
  int idx = 0;
  while ( number[++idx + 1] != '\0' );
  char result[idx];

  int over = 0;
  double ratio = 1; // next base64 vs. curr hexa
  int newIdx = 0;

  while (idx != -1 || over != 0){
    ratio *= 64;
    while (ratio > 1 && idx != -1){
      over += hexaConv(number[idx])*(64/ratio);
      idx--;
      ratio /= 16;
    }

    result[newIdx] = base64[over%64];
    over /= 64;
    newIdx++;
  }
  result[newIdx] = '\0';
  reverseArray(result,newIdx);

  printf("%s %d\n", result,strcmp(result,answer));

  return 0;
}
