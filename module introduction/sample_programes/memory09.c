#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
  int a;
  int b;
} pair;

void inc(pair *w) {
  w->a = w->a + 1; 
  w->b = w->b + 1; 
}

int main() {
	//define type pair pointer
  pair *x;
  //dynamically allocate  memory with the specified size(one pair size)
  x = malloc(sizeof(pair));
  //assign value to pointer x-> a
  x->a = 12;
  //assign value to pointer x-> b
  x->b = 34;
  //call inc function and pass x pointer
  inc(x);
  //print incremented values
  printf("%d,%d\n", x->a, x->b);
  //deallocates the memory previously allocated by a call to malloc.
  free(x);
  return EXIT_SUCCESS;
}
