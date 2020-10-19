#include<stdio.h>
void function(int a, int b, int c) {
   char buffer1[5];
   int *ret;
	
   ret = buffer1 + 21;
   (*ret) += 2;
}

void main() {
  int x;

  x = 50;
  function(1,2,3);
  x = 10;
  printf("%d\n",x);
}
