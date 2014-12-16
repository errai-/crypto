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

char commonChar[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
  'O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g',
  'h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
  ' ','-','&'+1,':','.',',','!','?','0','1','2','3','4','5','6','7','8','9'};
  
void ReverseArray( char* array ){
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

void ReverseArray( unsigned char* array, size_t size ){
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

unsigned char HexaConv( char no ){ 
  for (size_t idx = 0; idx != 16; ++idx){ 
    if ( hexas[idx] == no ) return (unsigned char) idx; 
  } 
  return 255;
}

unsigned char Base64Conv( char no ){
  for (size_t idx = 0; idx != 64; ++idx){
    if ( base64[idx] == no ) return (unsigned char) idx;
  }
  return 255;
}

void HexToBytes(char *hexNo, size_t size, unsigned char *byteNo){
  unsigned char tmpChar = 0;
  // Loop over number hexNo
  for (size_t idx = 0; idx != size; ++idx){
    unsigned char offTmp = HexaConv( hexNo[size-1-idx] );
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

void Base64ToBytes(char *base64No, size_t b64Size, size_t byteSize, unsigned char *byteNo){
  size_t bits = 0;
  size_t byteCount = 0;
  
  unsigned char tmpChar = 0;
  // Loop over number base64No
  for (size_t idx = 0; idx != b64Size; ++idx){
    unsigned char offTmp = Base64Conv( base64No[b64Size-1-idx] );
    bits +=6;
    if (bits>=8){
      bits -= 8;
      tmpChar |= (offTmp << (bits+2));
      byteNo[byteSize-1-byteCount++] = tmpChar;
      tmpChar = offTmp >> (6-bits);
    } else { // zero bits in store
      tmpChar = offTmp;
    }
  }
  if (bits != 0){
    byteNo[0]=tmpChar;
  }
  byteNo[byteSize]='\0';
}

void BytesToHex(unsigned char *byteNo, size_t size, char *hexNo){
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
  hexNo[size]='\0';
}

void BytesToBase64(unsigned char *byteNo, size_t byteSize, size_t b64Size, char *base64No){
  size_t idx = 0;
  size_t bits = 0;
  unsigned char tmpChar;
  size_t over = 0; // A Hex no idx

  for (size_t byteIdx = 0; byteIdx != byteSize; ++byteIdx){
    // Take only the necessary amount of bits from the next byte, add base64
    tmpChar = byteNo[byteSize-1-byteIdx] << bits;
    tmpChar <<= 2; tmpChar >>= 2;
    over += (size_t) tmpChar;
    base64No[b64Size-1-idx++] = base64[over];
    // 6-bits bits unused, put to the next storage
    tmpChar = byteNo[byteSize-1-byteIdx] >> (6-bits);
    bits = 2+bits;
    // If enough bits, use also these for a new hex
    if (bits > 5){
      tmpChar <<= 8-bits; tmpChar >>= 8-bits; // Unnecessary data away
      over = (size_t) tmpChar;
      base64No[b64Size-1-idx++] = base64[over];
      bits -= 6;
      tmpChar = byteNo[byteSize-1-byteIdx] >> (8-bits);
    }
    over = (size_t) tmpChar;
  }
  if (over != 0) base64No[0] = base64[over];

  base64No[b64Size] = '\0'; 
}

size_t CharDiff(char first, char second){
  size_t diff = 0;
  char tester = 1;
  char probe = first^second;
  for (size_t idx = 0; idx != 8; idx++){
    if ((probe&(tester<<(7-idx)))!=0) diff++;
  }
  return diff;
}

size_t Difference(char *first,char *second){
  size_t idx = 0;
  size_t totDiff = 0;
  while ((first[idx] != '\0') && (second[idx]!='\0')){
    totDiff += CharDiff(first[idx],second[idx]);
    idx++;
  }
  return totDiff;
}

size_t Difference(char *first,char *second, size_t size){
  size_t totDiff = 0;
  for (size_t idx = 0; idx != size; ++idx){
    totDiff += CharDiff(first[idx],second[idx]);
  }
  return totDiff;
}


bool IsChar(char tested){
  for (size_t i = 0; i != 58; ++i){
    if (commonChar[i]==tested) return true;
  } // i
  return false;
}

size_t RealChars(unsigned char* bytes, size_t size){
  size_t counter = 0;
  for (size_t i = 0; i != size; ++i){
    if (IsChar(bytes[i])) counter++;
  }
  return counter;
}

#endif // BASICS_H
