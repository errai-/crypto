#include <cstdio>
#include <basics.h>
#include <cstring>

char object1[] = "1c0111001f010100061a024b53535009181c";
char object2[] = "686974207468652062756c6c277320657965";
char answer[] = "746865206b696420646f6e277420706c6179";

int main(void){
  size_t size=0;
  while (object1[++size]!='\0');
  size_t byteAmount = (size+1)/2;
  unsigned char byteObj1[byteAmount];
  unsigned char byteObj2[byteAmount];
  unsigned char byteObj3[byteAmount];

  hexToBytes(object1,size,byteObj1);
  hexToBytes(object2,size,byteObj2);
  for (size_t idx = 0; idx != byteAmount; ++idx){
    byteObj3[idx] = byteObj1[idx]^byteObj2[idx];
  }

  char object3[size];
  bytesToHex(byteObj3,size,object3);
  printf("%s %d\n", object3,strcmp(object3,answer));
}
