#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
  for(size_t j = 0; j < count; j++){
    printf("%s", data[j]);
    free(data[j]);
  }
}

int main(int argc, char ** argv) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  if(argc == 1){
    while(getline(&curr, &sz, stdin) >= 0){
      lines = realloc(lines, (i+1) * sizeof(*lines));
      lines[i] = curr;
      curr = NULL;
      i++;
    }
    free(curr);
    sortData(lines,i);
    free(lines);
    return EXIT_SUCCESS;
  }
  if(argc >= 2){
    for(size_t k = 1; k < argc; k++){
      FILE *f = fopen(argv[k], "r");
      if(f == NULL){
	fprintf(stderr,"Can't open the input file\n");
        return EXIT_FAILURE;
      }
      lines = NULL;
      curr = NULL;
      i = 0;
      while(getline(&curr, &sz, f) >= 0){
	lines = realloc(lines, (i+1) * sizeof(*lines));
	lines[i] = curr;
	curr = NULL;
	i++;
      }
      free(curr);
      sortData(lines,i);
      free(lines);
      if(fclose(f) != 0){
        fprintf(stderr,"Can's close the input file\n");
        return EXIT_FAILURE;
      }
    }
    return EXIT_SUCCESS;
  }
}
