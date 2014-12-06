#include <iostream>
#include <cstdio>
#include <cstring>

char hexas[] = {'0','1','2','3','4','5','6','7','8','9',
  'a','b','c','d','e','f'};
char base64[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
  'P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h',
  'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0',
  '1','2','3','4','5','6','7','8','9','+','/'};

char number[] = "49276d206b696c6c696e6720796f757220627261696e206c696b6520612"
  "0706f69736f6e6f7573206d757368726f6f6d";

char answer[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2h"
  "yb29t";

int hexaConv( char no ){
  for (int idx = 0; idx != 16; ++idx){
    if ( hexas[idx] == no ) return idx;
  }
  return -1;
}

void reverseArray( char* array, int size ){
  char tmpChar;
  size_t swaps = size/2;
  size_t upperStart = swaps;
  if (size%2!=0) upperStart++;
  for (int i=0; i!=swaps; ++i){
    tmpChar = array[swaps-1-i];
    array[swaps-1-i] = array[upperStart+i];
    array[upperStart+i] = tmpChar;
  }
  return;
}

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
