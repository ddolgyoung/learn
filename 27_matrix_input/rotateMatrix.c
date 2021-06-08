#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]){
  char tempMatrix[10][10];
  for(int i=0; i < 10; i++){
    for(int j=0; j < 10; j++){
      tempMatrix[i][j] = matrix[i][j];
    }
  }
  for(int i=0; i < 10; i++){
    for(int j=0; j < 10; j++){
      matrix[i][j] = tempMatrix[9-j][i];
    }
  }
}

int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr,"Invalid argc\n");
    return EXIT_FAILURE;
  }
  FILE *f = fopen(argv[1],"r");
  if(f == NULL){
    fprintf(stderr,"Could not open file\n");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char str[12];
  int m = 0;
  if(fgets(str,12,f) == NULL){
    fprintf(stderr,"blank file\n");
    return EXIT_FAILURE;
  }
  while(fgets(str,12,f) != NULL){
    if(strchr(str, '\n') == NULL){
    fprintf(stderr,"Line is too long\n");
    return EXIT_FAILURE;
    }
    for(int i = 0; i < 10; i++){
      if(str[i] == '\n'){
	fprintf(stderr,"Line is too short\n");
	return EXIT_FAILURE;
      }
    }
    for(int j = 0; j < 10; j++){
      matrix[m][j] = str[j];
    }
    m++;
    if(m == 10){
      if(str[0] != EOF){
	fprintf(stderr,"too long file\n");
	return EXIT_FAILURE;
      }
    }
  }
  if(m < 9){
    fprintf(stderr,"less row\n");
    return EXIT_FAILURE;
  }
  rotate(matrix);
  for(int k = 0; k < 10; k++){
    for(int n = 0; n < 10; n++){
      printf("%c",matrix[k][n]);
    }
    printf("\n");
  }
  if(fclose(f) != 0){
    fprintf(stderr,"Failed to close the input file\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
