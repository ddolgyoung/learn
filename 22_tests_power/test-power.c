#include <stdio.h>
#include <stdlib.h>

int main(void){
  
  unsigned power (unsigned x, unsigned y);

  if(power(2,3) != 8){
  printf("Failed on power1\n");
  exit(EXIT_FAILURE);
  }
  if(power(0,0) != 1){
  printf("Failed on power2\n");
  exit(EXIT_FAILURE);
  }
  if(power(0,1) != 0){
  printf("Failed on power3\n");
  exit(EXIT_FAILURE);
  }
  if(power(5,0) != 1){
  printf("Failed on power4\n");
  exit(EXIT_FAILURE);
  }
  if(power(100,2) != 10000){
  printf("Failed on power5\n");
  exit(EXIT_FAILURE);
  }
  if(power(7832145,1) != 7832145){
  printf("Failed on power6\n");
  exit(EXIT_FAILURE);
  }
  
  return EXIT_SUCCESS;
}
  
