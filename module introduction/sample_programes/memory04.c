#include <stdio.h>
#include <stdlib.h>

//get int pointer as parameter and increment it value by one
void inc(int *w) {
  *w = *w + 1; 
}

int main() {
  int x = 123;
  //define int pointer
  int *y;
  //assign x address to y pointer
  y = &x;
  //call inc function and pass y pointer which contains x address
  inc(y);
  
  //print x value and y value (values are same because y is a referense of x)
  printf("%d,%d\n", x, *y);
  return EXIT_SUCCESS;
}
