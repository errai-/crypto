#include <cstdio>
#include <cstring>
#include <basics.h>

int main(void){
  
  char subm[] = "YELLOW SUBMARINE";
  size_t blockSize = 0;
  while (subm[++blockSize]!='\0');
  char vektor[blockSize+1]; vektor[blockSize] = '\0';
  for (size_t idx = 0; idx != blockSize; ++idx){
    vektor[idx] = 0;
  }
  
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
  
  size_t size = 0;
  while( subm[++size] != '\0' );

  char newStr[fullSize+1];
  Padder(subm,size,fullSize,newStr);
  
  printf("%s\n%s%d\n",subm,newStr,newStr[18]);
}