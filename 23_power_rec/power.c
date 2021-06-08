#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y){
  unsigned ans;

if(x==0 && y==0){
  ans = 1;
 }
 else if(x==0 && y !=0){
   ans = 0;
 }
 else if(x !=0 && y==0){
   ans = 1;
 }
else{
       ans = x * power(x, y-1);
  }
 return ans;
}


//int main(void){
//unsigned power1 = power(5,5);
//printf("%d\n", power1);
//}

   

     
