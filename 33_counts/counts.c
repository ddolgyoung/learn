#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  c->n_arrString = 12;
  c->arrString = malloc(c->n_arrString * sizeof(*c->arrString));
  for(int n = 0; n < c->n_arrString; n++){
    c->arrString[n] = malloc(sizeof(*c->arrString[n]));
    c->arrString[n]->n_oneString = 0;
  }
  return c;
}

void addCount(counts_t * c, const char * name) {
  if(name == NULL){
    c->arrString[c->n_arrString-1]->oneString = "<unknown>";
    c->arrString[c->n_arrString-1]->n_oneString += 1;
    return;
  }
  else{
    char * newName = (char *)name;
    for(int i = 0; i < c->n_arrString; i++){
      if(c->arrString[i]->n_oneString == 0){
        c->arrString[i]->oneString = newName;
        c->arrString[i]->n_oneString += 1;
        return;  
      }	
      else{
        if(strcmp(newName, c->arrString[i]->oneString) == 0){
	  c->arrString[i]->n_oneString += 1;
	  return;
        }
      }
    }
  }
}
					  
    
void printCounts(counts_t * c, FILE * outFile) {
  for(int m = 0; m < c->n_arrString; m++){
    if(c->arrString[m]->n_oneString != 0){
      printf("%s: ""%zu\n", c->arrString[m]->oneString, c->arrString[m]->n_oneString);
    }
  }
  if(fclose(outFile) != 0){
    fprintf(stderr, "Can't close the output file\n");
  }
}

void freeCounts(counts_t * c) {
  for(int k = 0; k < c->n_arrString; k++){
    free(c->arrString[k]);
  }
  free(c->arrString);
  free(c);
}
