#include <iostream>
#include <cstdio>
#include <cstring>

#ifndef BASICS_H
#define BASICS_H

char hexas[] = {'0','1','2','3','4','5','6','7','8','9',
  'a','b','c','d','e','f'};
char base64[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
  'P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h',
  'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0',
  '1','2','3','4','5','6','7','8','9','+','/'};

void reverseArray( char* array ){
  char tmpChar;
  size_t size = 0;
  while (array[++size] != '\0');
  size_t swaps = size/2;
  size_t upperStart = swaps;
  if (size%2!=0) upperStart++;
  for (size_t i=0; i!=swaps; ++i){
    tmpChar = array[swaps-1-i];
    array[swaps-1-i] = array[upperStart+i];
    array[upperStart+i] = tmpChar;
  }
  return;
}

void reverseArray( unsigned char* array, size_t size ){
  char tmpChar;
  size_t swaps = size/2;
  size_t upperStart = swaps;
  if (size%2!=0) upperStart++;
  for (size_t i=0; i!=swaps; ++i){
    tmpChar = array[swaps-1-i];
    array[swaps-1-i] = array[upperStart+i];
    array[upperStart+i] = tmpChar;
  }
  return;
}

unsigned char hexaConv( char no ){ 
  for (size_t idx = 0; idx != 16; ++idx){ 
    if ( hexas[idx] == no ) return (unsigned char) idx; 
  } 
  return 255;
} 

void hexToBytes(char *hexNo, size_t size, unsigned char *byteNo){
  unsigned char tmpChar = 0;
  // Loop over number hexNo
  for (size_t idx = 0; idx != size; ++idx){
    unsigned char offTmp = hexaConv( hexNo[size-1-idx] );
    if (idx%2) {
      tmpChar |= (offTmp << 4);
      byteNo[(size-1)/2-idx/2] = tmpChar;
      tmpChar = 0;
    } else {
      tmpChar = offTmp; 
    } 
  }
  if (size%2){
    byteNo[(size-1)/2] = tmpChar;
  }
  byteNo[(size-1)/2+1] = '\0';
  return;
}

void bytesToHex(unsigned char *byteNo, size_t size, char *hexNo){
  unsigned char tmpChar = 0;
  for (size_t idx = 0; idx != size; ++idx){
    tmpChar = byteNo[(size-1)/2-idx/2]; 
    if (idx%2==0){
      tmpChar <<= 4; tmpChar >>= 4;
    } else {
      tmpChar >>= 4;
    }  
    hexNo[size-1-idx] = hexas[tmpChar]; 
  }
}

void bytesToBase64(unsigned char *byteNo, size_t byteSize, char *base64No){
  size_t idx = 0;
  size_t byteIdx = 0;
  size_t bits = 0;
  unsigned char tmpChar;
  size_t over = 0;

  while(byteIdx != byteSize){
    tmpChar = byteNo[byteIdx] << bits;
    tmpChar <<= 2; tmpChar >>= 2;
    over += (size_t) tmpChar; 
    base64No[idx++] = base64[over];
  
    tmpChar = byteNo[byteIdx] >> (6-bits);
    bits = 2+bits;
    if (bits > 5){
      tmpChar <<= 8-bits; tmpChar >>= 8-bits;
      over = (size_t) tmpChar;
      base64No[idx++] = base64[over];
      bits -= 6;
      tmpChar = byteNo[byteIdx] >> (8-bits);
    }
    over = (size_t) tmpChar;
    byteIdx++;
  }
  if (over != 0) base64No[idx++] = base64[over];

  base64No[idx] = '\0'; 
}

#endif // BASICS_H
