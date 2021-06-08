#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int arrayMax(int * array, int n) {
  if(n == 0){
    return -1;
  }
  int largestIndex = 0;
  for (int i=1; i < 26; i++){
    if (array[i] > array[largestIndex]){
      largestIndex = i;
    }
  }
  return largestIndex;
}


void occurrence(FILE * f, int *array){
  int c;
  while((c = fgetc(f)) != EOF){
    if(isalpha(c)){
      c = tolower(c);
      c -= 'a';
      array[c]++;
    }
  }
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Invalid argc\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr,"Could not open file\n");
    return EXIT_FAILURE;
  }
  int array[26]={0};
  occurrence(f, array);
  int m = arrayMax(array, 26);
  if(m == 0 && array[0] == 0){
    fprintf(stderr,"no alphabet\n");
    return EXIT_FAILURE;
  }
  int key = (m+22)%26;
  printf("%d\n",key);
  if (fclose(f) != 0) {
    fprintf(stderr,"Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
