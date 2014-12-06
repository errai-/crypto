#include <cstdio>
#include <cstring>
#include <basics.h>
#include <fstream>
#include <string>

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
  std::ifstream input("4.txt");
  std::string tmpStr;
  size_t Max = 0;
  while (!input.eof()){
    input >> tmpStr;
    char encoded[tmpStr.size()+1];
    encoded[tmpStr.size()]='\0';
    memcpy(encoded,tmpStr.c_str(),tmpStr.size()); 
    
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
      if ( amnt > 23 ) printf("%s %zu\n",messageBytes,amnt);
    } // idx, i
    if (max>Max) Max = max;
    if (max>26) printf("%zu\n",max);
  }
  printf("%zu\n",Max);

  return 0;
}
