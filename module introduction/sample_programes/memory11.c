#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int n = 10;

int main() {
  int i;
  //define two int pointers called x and y
  int *x, *y;
  //dynamically allocate  memory with the specified size
  x = malloc(sizeof(int) * n);
  //assign x into y
  y = x;

  for(i=0;i<n;i++){
  	//assign value to y elements
    *y = 2 * i;
    //increment y element index by one
    y++;
  }
//assign x into y
  y = x;

  for(i=0;i<n;i++){
  	//iterate y and print each element value (x and y both refer same address)
    printf("%d,%d\n", i, *y);    
    y++;
  }
//deallocates the memory previously allocated by a call to malloc.
  free(x);
  return EXIT_SUCCESS;
}
