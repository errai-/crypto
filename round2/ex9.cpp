#include <cstdio>
#include <cstring>
#include <basics.h>

size_t Padder(char *original, size_t initSize, size_t finalSize, char *target){
  size_t missing = finalSize-initSize;
  unsigned char replace = (unsigned char) missing;
  memcpy(target,original,initSize);
  for (size_t idx = initSize; idx != finalSize; ++idx){
    target[idx] = (char) replace;
  }
  target[finalSize] = '\0';
}

int main(void){
  
  char subm[] = "YELLOW SUBMARINE";
  size_t fullSize = 20;
  
  size_t size = 0;
  while( subm[++size] != '\0' );

  char newStr[fullSize+1];
  Padder(subm,size,fullSize,newStr);
  
  printf("%s\n%s%d\n",subm,newStr,newStr[18]);
}