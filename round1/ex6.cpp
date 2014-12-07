#include <cstdio>
#include <cstring>
#include <basics.h>
#include <fstream>
#include <string>

size_t FindKeySize(size_t byteSize, unsigned char *bytes){
  size_t maxKey = 100;
  size_t indicator = byteSize/maxKey;
  double max = 1000;
  size_t maxInd = 0;
  for (size_t KEYSIZE = 2; KEYSIZE != maxKey+1; ++KEYSIZE){
    double total = 0;
    size_t normalize = 0;
    char study1[KEYSIZE+1]; study1[KEYSIZE]='\0';
    char study2[KEYSIZE+1]; study2[KEYSIZE]='\0';
    for (size_t i = 0; i != indicator-1; ++i){
      for (size_t j = i+1; j != indicator; ++j){
	memcpy(study1,bytes+i*KEYSIZE,KEYSIZE);
	memcpy(study2,bytes+j*KEYSIZE,KEYSIZE);
	total += ((double)Difference(study1,study2,KEYSIZE))/KEYSIZE;
	normalize++;
      } // j
    } // i
    total /= normalize;
    if (total < max){
      max = total;
      maxInd = KEYSIZE;
    }
  }
  printf("%f %zu\n",max,maxInd);
  //unsigned char messageBytes[(size+1)/2+1];
  return maxInd;
}

char SetPartKey(size_t size, unsigned char *range){
  unsigned char messageBytes[size];
 
  size_t amnt = 0;
  size_t max = 0; size_t mIdx = 0;
  for (size_t idx=0; idx!=58; ++idx){
    for (size_t j=0; j!=size; ++j){
      messageBytes[j] = range[j]^commonChar[idx];
    } // j
    amnt = RealChars(messageBytes,size); 
    if ( amnt >= max ){ 
      max = amnt;
      mIdx = idx;
    }
  } // idx, i
  return commonChar[mIdx];
}

void SetKey(size_t len, size_t size, char *key, unsigned char *bytes){
  
  for (size_t idx = 0; idx != len; ++idx){
    size_t testVars = size/len + ((size%len<idx)? 0 : 1);
    unsigned char testRange[testVars];
    for (size_t i = 0; i != testVars; ++i){
      testRange[i] = bytes[idx+i*len];
    } // i
    key[idx] = SetPartKey(testVars,testRange);
  } // idx
}

int main(void){

  std::ifstream input("6.txt");
  std::string tmpStr;
  std::string totStr("");
  
  printf("%f\n",(double)Difference("this is a test","wokka wokka!!!",14)/14);
  while (!input.eof()){
    input >> tmpStr;
    totStr+=tmpStr;
  }
  char encoded[totStr.size()+1];
  encoded[totStr.size()]='\0';
  memcpy(encoded,totStr.c_str(),totStr.size()); 
    
  size_t size = 0;
  while (encoded[++size]!='\0');
  size_t byteSize = 3*size/4+((size%4)?1:0);
  
  unsigned char bytes[byteSize+1];
  Base64ToBytes(encoded,size,byteSize,bytes);

  size_t keylen = FindKeySize(byteSize,bytes);
  char key[keylen+1]; key[keylen] = '\0';
  SetKey(keylen,byteSize,key,bytes);
  
  printf("%s\n",key);
  
  char final[byteSize+1]; final[byteSize] = '\0';
  for (size_t idx = 0; idx != byteSize; ++idx){
    final[idx] = bytes[idx]^key[idx%keylen];
  }
  printf("%s\n",final);
  return 0;
}