#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

char * findValue(char * line){
  char * value = strchr(line, '=');
  *value = '\0';
  value++;
  value[strlen(value)-1] = '\0';
  return value;
}

/*kvpair_t * readKVpair(char * curr){
  const char * separator = strchr(curr, '=');
  const char * endPtr = strchr(curr, '\n');
  kvpair_t * myPair = malloc(sizeof(*myPair));
  myPair->key = malloc((separator - curr) * sizeof(char*));
  strncpy(myPair->key, curr, separator - curr);
  myPair->value = malloc((endPtr - separator) * sizeof(char*));
  strncpy(myPair->value, separator + 1, endPtr - separator -1);
  return myPair;
  }*/

kvarray_t * readKVs(const char * fname) {
  kvarray_t *myArray = malloc(sizeof(*myArray));
  //myArray->kvArray = malloc(myArray->n_array * sizeof(*myArray->kvArray));
  myArray->kvArray = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  FILE *f = fopen(fname, "r");
  if(f == NULL){
    fprintf(stderr, "Can't open the input file\n");
  }
  while(getline(&curr, &sz, f) >= 0){
    myArray->kvArray = realloc(myArray->kvArray, (i+1) * sizeof(*myArray->kvArray));
    myArray->kvArray[i] = malloc(sizeof(*myArray->kvArray[i]));
    myArray->kvArray[i]->key = curr;
    myArray->kvArray[i]->value = findValue(curr);
    curr = NULL;
    i++;
  }
  free(curr);
  myArray->n_array = i;  
  if(fclose(f) != 0){
    fprintf(stderr, "Can't close the input file\n");
  }
  return myArray;
}

void freeKVs(kvarray_t * pairs) {
  for(int m = 0; m < pairs->n_array; m++){
    //kvpair_t *myPair = pairs->kvArray[m];
    //free(myPair->key);
    //free(myPair->value);
    //free(myPair);
    free(pairs->kvArray[m]->key);
    //free(pairs->kvArray[m]->value);
    free(pairs->kvArray[m]);
    //free(pairs->kvArray);
  }
  free(pairs->kvArray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for(size_t i = 0; i < pairs->n_array; i++){
    char * k1 = pairs->kvArray[i]->key;
    char * v1 = pairs->kvArray[i]->value;
    printf("key = '%s' value = '%s'\n", k1, v1);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for(size_t j = 0; j < pairs->n_array; j++){
    char * k1 = pairs->kvArray[j]->key;
    char * v1 = pairs->kvArray[j]->value;
    if(strcmp(k1, key) == 0){
      return v1;
    }
  }
  return NULL;
}
