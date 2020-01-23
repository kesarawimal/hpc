#include <stdio.h>
#include <stdlib.h>
//define struct called pair which contains tow int types.
struct pair {
  int a;
  int b;
};

int main() {
	/* Declare x of type pair */
  struct pair x;
  //assign value to type x.a
  x.a = 12;
  //assign value to type x.a
  x.b = 34;
  //print x.a value, x.b value and size of type pair
  printf("%d,%d,%ld\n", x.a, x.b, sizeof(struct pair));
  return EXIT_SUCCESS;
}
