#include <stdio.h>
#include <stdlib.h>

//get int pointer as parameter and increment it value by one
void inc(int *w) {
  *w = *w + 1; 
}

int main() {
  int x = 123;
  int y = x;
  //call inc function and pass y memory address
  inc(&y);
  printf("%d,%d\n", x, y);
  return EXIT_SUCCESS;
}
