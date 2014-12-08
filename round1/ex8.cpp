#include <cstdio>
#include <cstring>
#include <basics.h>
#include <fstream>
#include <string>
#include <openssl/aes.h>

int main(void){
  
  std::ifstream input("8.txt");
  std::string tmpStr;
  
  size_t stringNo = 0;
  double min = 10000;
  size_t minInd = 0;
  unsigned char storage[161];
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
    
    double total = 0;
    size_t normalize = 0;
    size_t iterations = byteSize/16;
    for (size_t i=0; i!=iterations-1; ++i){
      for (size_t j=0; j!=iterations; ++j){
	total += ((double)Difference((char*)bytes+i*16,(char*)bytes+j*16,16));
	normalize++;
      }
    }
    total /= normalize;
    printf("String %zu: %f, len: %zu\n",++stringNo,total,byteSize);
    if (total < min){
      min = total;
      minInd = stringNo;
    }
    if (stringNo == 133){
      memcpy(storage,bytes,160);
      printf("Hui: %s\n",encoded);
    }
    
  }
  
  printf("Minimal string %zu: %f\n",minInd,min);

  unsigned char keyString[] = "YELLOW SUBMARINE";
  
  AES_KEY key;
  
  AES_set_decrypt_key(keyString,128,&key);
  
  unsigned char result[161];
  size_t iterations = 10;
  for (size_t idx=0; idx!=iterations; ++idx){
    AES_decrypt(storage+16*idx,result+16*idx,&key);
  }
  result[160]='\0';
  printf("Nothing sensible: %s\n",result);
  return 0;

}