#include <basics.h>
#include <cstdio>
#include <cstring>

char string[] = "Burning 'em, if you ain't quick and nimble\n"
  "I go crazy when I hear a cymbal";
char result[] = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a262263242"
  "72765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
int main(void){
  char cipher[] = "ICE";

  size_t loc = 0;
  
  while (string[++loc]!='\0');
  
  unsigned char shifted[loc];
  
  char hex[2*loc+1];
 
  for (size_t idx=0; idx != loc; ++idx){
    shifted[idx]=string[idx]^cipher[idx%3];
  }
  
  BytesToHex(shifted,2*loc,hex);
  
  printf("%s %d \n",hex,strcmp(result,hex));
  
}
