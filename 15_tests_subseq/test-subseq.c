#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void){
  int a1[]={1,2,4,6,7,8,9};
  int a2[]={-5,-4,-3,-2,-1};
  int a3[]={1};
  int a4[]={9,7,5,4,3,1};
  int a5[]={0,0,0,0,0};
  int a6[]={2,4,6,1,2,3,4,5};
  int a7[]={2,4,6,8,1,2,3};
  int a8[]={1,2,3,1,2,3};
  int a9[]={};
  int a10[]={-500,0,500};
  
  if(maxSeq(a1,7)!= 7){
    printf("Failed on 1\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a2,5)!= 5){
    printf("Failed on 2\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a3,1)!= 1) {
    printf("Failed on 3\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a4,6)!= 1) {
    printf("Failed on 4\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a5,5)!= 1) {
    printf("Failed on 5\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a6,8)!= 5) {
    printf("Failed on 6\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a7,7)!= 4) {
    printf("Failed on 7\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a8,6)!= 3) {
    printf("Failed on 8\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a9,0)!= 0) {
    printf("Failed on 9\n");
    exit(EXIT_FAILURE);
  }
  if(maxSeq(a10,3)!= 3) {
    printf("Failed on 10\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

