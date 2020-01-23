#include <stdio.h>
#include <stdlib.h>
//adds a type alias pair in the global name space and thus allows you to just write
typedef struct  {
  int a;
  int b;
} pair;

int main() {
	//Declare x of type pair, struct keyword no longer needed
  pair x;
  //assign value to type x.a
  x.a = 12;
  //assign value to type x.a
  x.b = 34;
  //print x.a value, x.b value and size of type pair
  printf("%d,%d,%ld\n", x.a, x.b, sizeof(pair));
  return EXIT_SUCCESS;
}
