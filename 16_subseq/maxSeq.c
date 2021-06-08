#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  if (n == 0){
    return 0;
  }

  int maxSeqValue = 1;
  int tempAnswer = 1;

  for (int i = 1; i < n; i++){
    if (array[i] > array[i-1]){
      tempAnswer++;

      if (tempAnswer > maxSeqValue){
	maxSeqValue = tempAnswer;
      }
    }
    else {
      tempAnswer = 1;
    }
  }
  return maxSeqValue;
}

//int main(void){
//int a1[]={1,2,4,6,7,8,9};
//printf("a1 is 7 and I got %zu\n",maxSeq(a1,7));
//} 
