#include <cstdio>
#include <cstring>
#include <basics.h>
#include <fstream>
#include <string>
#include <openssl/aes.h>

int main(void){

  unsigned char keyString[] = "YELLOW SUBMARINE";
  
  AES_KEY key;
  
  AES_set_decrypt_key(keyString,128,&key);

  std::ifstream input("8.txt");
  std::string tmpStr;
  
  while (!input.eof()){
    input >> tmpStr;
    char encoded[tmpStr.size()+1];
    encoded[tmpStr.size()]='\0';
    
    memcpy(encoded,tmpStr.c_str(),tmpStr.size()); 
    
    size_t size = 0;
    while (encoded[++size]!='\0');
    
    size_t byteSize = size/2+((size%2)?1:0);
    unsigned char bytes[byteSize+1];
    
    HexToBytes(encoded,size,bytes);
  }
    
  
  
  unsigned char result[byteSize+1];
  size_t iterations = byteSize/16+((byteSize%16!=0)? 1 : 0);
  for (size_t idx=0; idx!=iterations; ++idx){
    AES_decrypt(bytes+16*idx,result+16*idx,&key);
  }
  result[byteSize]='\0';
  printf("%s\n",result);
  
  return 0;
}