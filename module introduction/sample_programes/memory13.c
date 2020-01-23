#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int n = 10;
//get int pointer as parameter and increment it each element value by one
void inc(int *w) {
  int i;
  for(i=0;i<n;i++){
    *w = *w + 1; 
    w++;
  }
}

int main() {
  int i;
  int *x, *y;
  //dynamically allocate  memory with the specified size(10 int size)
  x = malloc(sizeof(int) * n);
  y = x;

  for(i=0;i<n;i++){
  	//asign values to each element
    *y = 2 * i;
    //increment pointer index by one
    y++;
  }

  inc(x);
  y = x;

  for(i=0;i<n;i++){
    printf("%d,%d\n", i, *y);    
    y++;
  }
//x and y refer same address

  //deallocates the memory previously allocated by a call to malloc.
  free(x);
  return EXIT_SUCCESS;
}
