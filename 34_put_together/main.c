#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"


counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  char ** lines= NULL;
  char * line = NULL;
  size_t s_z;
  size_t g = 0;
  size_t counter = 0;
  FILE * fc = fopen(filename,"r");
  if(fc == NULL){
    fprintf(stderr,"Can't open the filename file\n");
  }
  while(getline(&line,&s_z,fc) >= 0){
    lines = realloc(lines, (g+1) * sizeof(*lines));
    char * newName = strtok(line, "\n");
    lines[g] = newName;
    line = NULL;
    g++;
  }
  free(line);
  counts_t * nc = malloc(sizeof(*nc));
  nc->n_arrString = g;
  nc->arrString = malloc(nc->n_arrString * sizeof(*nc->arrString));
  for(int k = 0; k < nc->n_arrString; k++){
    nc->arrString[k] = malloc(sizeof(*nc->arrString[k]));
    nc->arrString[k]->oneString = lines[k];
    nc->arrString[k]->n_oneString = 0;
  }
  for(int u = 0; u < nc->n_arrString; u++){
    for(int l = 0; l < kvPairs->n_array; l++){
      if(strcmp(nc->arrString[u]->oneString, kvPairs->kvArray[l]->key) == 0){
	nc->arrString[u]->oneString = kvPairs->kvArray[l]->value;
	nc->arrString[u]->n_oneString += 1;
	break;
      }      
      else{
	counter++;
	if(counter >= kvPairs->n_array){
	  nc->arrString[u]->oneString = NULL;
 	  nc->arrString[u]->n_oneString += 1;
	  break;
	}
      }
    }
    counter = 0;	       
  }
  for(int m = 0; m < nc->n_arrString; m++){
    if(nc->arrString[m]->oneString == NULL && nc->arrString[m]->n_oneString != 0){
      for(int y = 0; y < nc->n_arrString; y++){
	if(nc->arrString[y]->oneString == NULL && nc->arrString[y]->n_oneString != 0){
	  if(m != y){
	    nc->arrString[m]->n_oneString += 1;
	    nc->arrString[y]->n_oneString = 0;
	  }
	}
      }
    }
    else if(nc->arrString[m]->oneString != NULL && nc->arrString[m]->n_oneString != 0){
      for(int j = 0; j < nc->n_arrString; j++){
	if(nc->arrString[j]->oneString != NULL){
	  if(strcmp(nc->arrString[m]->oneString, nc->arrString[j]->oneString) == 0){
	    if(m != j){
	      nc->arrString[m]->n_oneString += 1;
	      nc->arrString[j]->n_oneString = 0;
	    }
	  }
	}  
      }
    }
  }
  for(int h = 0; h < nc->n_arrString; h++){
    free(lines[h]);
  }
  free(lines);
  if(fclose(fc) != 0){
    fprintf(stderr,"Can't close the filename file\n");
  }
  return nc;
}

void freeCounts_c(counts_t *oc){
  for(int w = 0; w < oc->n_arrString; w++){
    free(oc->arrString[w]);
  }
  free(oc->arrString);
  free(oc);
}

void freeKV(kvarray_t *kvs){
   for(int s = 0; s < kvs->n_array; s++){
     free(kvs->kvArray[s]->key);
     free(kvs->kvArray[s]);
  }
  free(kvs->kvArray);
  free(kvs);
}
  

int main(int argc, char ** argv) {
  if(argc < 3){
    perror("Invalid argc\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t *kv = malloc(sizeof(*kv));
  FILE *f_kv = fopen(argv[1], "r");
  kv->kvArray = NULL;
  char * curr = NULL;
  size_t sz;
  size_t n = 0;
  if(f_kv == NULL){
    fprintf(stderr, "Can't open the input file\n");
  }
  while(getline(&curr, &sz, f_kv) >= 0){
    kv->kvArray = realloc(kv->kvArray, (n+1) * sizeof(*kv->kvArray));
    kv->kvArray[n] = malloc(sizeof(*kv->kvArray[n]));
    kv->kvArray[n]->key = curr;
    char * value = strchr(curr,'=');
    *value = '\0';
    value++;
    value[strlen(value)-1] = '\0';
    kv->kvArray[n]->value = value;
    curr = NULL;
    n++;
  }
  free(curr);
  kv->n_array = n;
  if(fclose(f_kv) != 0){
    fprintf(stderr,"Failed to close the input file\n");
  }
  for(size_t i = 2; i < argc; i++){
    const char * fileName = argv[i];
    counts_t * c = countFile(fileName, kv);
    char * outName = malloc((strlen(fileName) + 8) * sizeof(*outName));
    strcpy(outName, fileName);
    strcat(outName, ".counts");
    FILE *f_o = fopen(outName, "w");
    if(f_o == NULL){
      fprintf(stderr,"Can't open the output file\n");
    }
    for(int j = 0; j < c->n_arrString; j++){
      if(c->arrString[j]->oneString != NULL && c->arrString[j]->n_oneString != 0){
	fprintf(f_o, "%s: %zu\n",c->arrString[j]->oneString, c->arrString[j]->n_oneString);
      }
    }
    for(int x = 0; x < c->n_arrString ; x++){
      if(c->arrString[x]->oneString == NULL && c->arrString[x]->n_oneString != 0){
	c->arrString[x]->oneString = "<unknown>";
	fprintf(f_o, "%s: %zu\n",c->arrString[x]->oneString, c->arrString[x]->n_oneString);
      }
    }
    freeCounts_c(c);
    if(fclose(f_o) != 0){
      fprintf(stderr,"Failed to close the outName file!");
    }
    free(outName);
  }
  freeKV(kv);
  return EXIT_SUCCESS;
}
