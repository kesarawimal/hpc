#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//get int pointer as parameter and increment it value by one
void inc(int *w) {
  *w = *w + 1; 
}

int main() {
	//malloc method is used to dynamically allocate a single large block of memory with the specified size
  int *x = malloc(sizeof(int));
  //assign value to x
  *x = 123;
  int *y;
  assign x pointer to y pointer
  y = x;
 //call inc function and pass y pointer which contains x address
  inc(y);
  //print x value and y value (values are same because y is a referense of x)
  printf("%d,%d\n", *x, *y);
  //deallocates the memory previously allocated by a call to malloc.
  free(x);
  return EXIT_SUCCESS;
}
