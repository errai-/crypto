#include <cstdio>
#include <cstring>
#include <basics.h>

char encoded[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
unsigned char joke[] = "ETAOIN SHRDLU";

bool isChar(char tested){
  for (size_t i = 0; i != 52; ++i){
    if (base64[i]==tested) return true;
  } // i
  return false;
}

size_t realChars(unsigned char* bytes, size_t size){
  size_t counter = 0;
  for (size_t i = 0; i != size; ++i){
    if (isChar(bytes[i])) counter++;
  }
  return counter;
}

int main(void){

  size_t size = 0;
  while (encoded[++size]!='\0');

  unsigned char bytes[(size+1)/2+1];
  unsigned char messageBytes[(size+1)/2+1];
  hexToBytes(encoded,size,bytes);
 
  size_t amnt = 0;
  size_t max = 0;
  for (size_t idx=0; idx!=64; ++idx){
    for (size_t j=0; j!=(size+1)/2; ++j){
      messageBytes[j] = bytes[j]^base64[idx];
    } // j
    //reverseArray(messageBytes,(size+1)/2);
    amnt = realChars(messageBytes,(size+1)/2); 
    //printf("%zu %zu \n", amnt, size/2 );
    if ( amnt > max ) max = amnt;
    if ( amnt == 27 ) printf("%s %zu %c\n",messageBytes,idx,base64[idx]);
  } // idx, i
  printf("%zu\n",max);
  unsigned char Joke[14];
  for (size_t idx = 0; joke[idx]!='\0'; ++idx){
    Joke[idx] = joke[idx]^'x';
  }
  Joke[13] = '\0';
  printf("%s\n",Joke);
  return 0;
}
