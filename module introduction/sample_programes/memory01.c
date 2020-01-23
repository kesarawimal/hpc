#include <stdio.h>
#include <stdlib.h>

int main() {
  int x = 123;
  long int y = 321;
  /*sizeof() returns the size of a variable, it simply returns the amount of memory allocated to that data type*/
  
  //print x and size of x
  printf("%d %ld\n",  x, sizeof(x));
  //print y and size of x
  printf("%ld %ld\n", y, sizeof(y));
  return EXIT_SUCCESS;
}
