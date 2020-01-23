#include <stdio.h>
#include <stdlib.h>
//define a type alias pair in the global name space and thus allows you to just write
typedef struct {
  int a;
  int b;
} pair;
//get struct pair type pointer as parameter and increment it both values by one
void inc(pair *w) {
  w->a = w->a + 1; 
  w->b = w->b + 1; 
}

int main() {
	//Declare x of type pair, struct keyword no longer needed
  pair x;
  //assign value to type x.a
  x.a = 12;
  //assign value to type x.a
  x.b = 34;
   //call inc function and pass x address
  inc(&x);
  //print x.a value and x.b value (both values are incremented by one)
  printf("%d,%d\n", x.a, x.b);
  return EXIT_SUCCESS;
}
