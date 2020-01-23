#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int n = 10;

int main() {
  int i;
  int *x;
  //dynamically allocate  memory with the specified size(10 int size)
  x = malloc(sizeof(int) * n);

	//print size of x pointer
  printf("%ld\n", sizeof(x));
  //print size of x value
  printf("%ld\n", sizeof(*x));

//for loop 10 times
  for(i=0;i<n;i++){
  	//use pointer as array
    x[i] = 2 * i;
  }

  for(i=0;i<n;i++){
  	//iterate x and print each element value
    printf("%d,%d\n", i, x[i]);    
  }
	//deallocates the memory previously allocated by a call to malloc.
  free(x);
  return EXIT_SUCCESS;
}
