#include <stdlib.h>
#include <stdio.h>


//printf function will show the division of the long values
int main() {
  long int x = 10L;
  long int y = 3L;

  printf("%ld / %ld = %ld\n", x, y, x/y);
  return EXIT_SUCCESS;
}
