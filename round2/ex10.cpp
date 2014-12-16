#include <cstdio>
#include <cstring>
#include <basics.h>
#include <fstream>
#include <openssl/aes.h>

int main(void){
  
  unsigned char subm[] = "YELLOW SUBMARINE";
  size_t blockSize = 0;
  while (subm[++blockSize]!='\0');

  AES_KEY key;
  
  AES_set_decrypt_key(subm,128,&key);
  
  char vektor[blockSize+1]; vektor[blockSize] = '\0';
  
  std::ifstream input("10.txt");
  std::string tmpStr;
  std::string totStr("");
  
  while (!input.eof()){
    input >> tmpStr;
    totStr+=tmpStr;
  }
  
  char encoded[totStr.size()+1];
  encoded[totStr.size()]='\0';
  memcpy(encoded,totStr.c_str(),totStr.size()); 
  size_t byteSize = 3*totStr.size()/4+((totStr.size()%4)?1:0);
  
  unsigned char bytes[byteSize+byteSize%blockSize+1];
  Base64ToBytes(encoded,totStr.size(),byteSize,bytes);

  char pad = byteSize%blockSize;
  for (size_t idx = 0; idx != byteSize%blockSize; ++idx){
    bytes[byteSize+idx]=pad;
  }
  bytes[byteSize+byteSize%blockSize] = '\0';  
  unsigned char result[byteSize+1];
  
  for (size_t idx = 0; idx != blockSize; ++idx){
    vektor[idx] = 0;
  }
  
  size_t iterations = byteSize/16+((byteSize%16!=0)? 1 : 0);
  for (size_t idx=0; idx!=iterations; ++idx){
    AES_decrypt(bytes+16*idx,result+16*idx,&key);
    for (size_t jdx=0; jdx!=blockSize; ++jdx){
      result[16*idx+jdx] = result[16*idx+jdx]^vektor[jdx];
      vektor[jdx] = bytes[16*idx+jdx];
    }
  }
  result[byteSize]='\0';
  printf("%s\n\n %s \n\n",result,bytes);
  
  AES_set_encrypt_key(subm,128,&key);

  for (size_t idx = 0; idx!=blockSize; ++idx){
    vektor[idx]=0;
  }
  for (size_t idx=0; idx!=iterations; ++idx){
    for (size_t jdx=0; jdx!=blockSize; ++jdx){
      result[16*idx+jdx] = result[16*idx+jdx]^vektor[jdx];
    }
    AES_encrypt(result+16*idx, bytes+16*idx, &key);
    for (size_t jdx=0; jdx!=blockSize; ++jdx){
      vektor[jdx] = bytes[16*idx+jdx];
    }
  }
  
  printf("%s\n\n",bytes);
  AES_set_decrypt_key(subm,128,&key);
 
  for (size_t idx = 0; idx!=blockSize; ++idx){
    vektor[idx]=0;
  }
  for (size_t idx=0; idx!=iterations; ++idx){
    AES_decrypt(bytes+16*idx,result+16*idx,&key);
    for (size_t jdx=0; jdx!=blockSize; ++jdx){
      result[16*idx+jdx] = result[16*idx+jdx]^vektor[jdx];
      vektor[jdx] = bytes[16*idx+jdx];
    }
  }
  
  result[byteSize]='\0';
  printf("%s\n",result);
}