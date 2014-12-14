#include <cstdio>
#include <cstring>
#include <basics.h>

int main(void){
  
  char subm[] = "YELLOW SUBMARINE";
  size_t fullSize = 20;
  
  size_t size = 0;
  while( subm[++size] != '\0' );

  char newStr[fullSize+1];
  Padder(subm,size,fullSize,newStr);
  
  printf("%s\n%s%d\n",subm,newStr,newStr[18]);
}