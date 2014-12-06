#include <iostream>
#include <cstdio>
#include <cstring>
#include <funcs1v1.h>

int main(void){
  int idx = 0;
  while ( number[++idx] != '\0' );
  unsigned char result[(idx+1)/2];
  char base64res[idx];
  hexToBytes(number,idx,result);
  bytesToBase64(result,(idx+1)/2,base64res);
  reverseArray( base64res );
  printf("%s %d \n", base64res, strcmp(base64res,answer));
  return 0;
}
