#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  if(str == '\0'){
    return;
  }

  size_t length = strlen(str);
  char * myReverse = str;
  char temp;

  for(size_t i=0; i < length/2; i++){
    int index = length-i-1;
      	temp = str[i];
	myReverse[i] = str[index];
	myReverse[index] = temp;
    }
    return;
}   

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
