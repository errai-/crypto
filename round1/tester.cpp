#include <cstdio>
#include <cstring>
#include <basics.h>
#include <fstream>
#include <string>

int main(void){

  unsigned char testString[] = "TEstailua hexiin ja takaisin; fufufu";
  unsigned char bach[37];
  char hex[49];
  BytesToBase64(testString,36,48,hex);
  Base64ToBytes(hex,48,36,bach);
  printf("%s\n%s\n%s\n",testString,bach,hex);
  printf("%c%c\n",Base64Conv(hex[45])<<4|Base64Conv(hex[46])>>2,(Base64Conv(hex[46])<<6) | Base64Conv(hex[47]));
  return 0;
}
