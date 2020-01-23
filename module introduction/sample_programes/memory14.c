#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int n = 10;
//get int pointer as parameter and assign values for 10 elements
void initialise(int *w) {
  int i;
  for(i=0;i<n;i++){
    *w = 2 * i;
    w++;
  }
}
//get int pointer as parameter and increment it each element value by one
void inc(int *w) {
  int i;
  for(i=0;i<n;i++){
    *w = *w + 1; 
    w++;
  }
}
//get int pointer as parameter and print it each element index and value
void output(int *w) {
  int i;
  for(i=0;i<n;i++){
    printf("%d,%d\n", i, w[i]);    
  }
}

int main() {
  int *x;
   //dynamically allocate  memory with the specified size(10 int size)
  x = malloc(sizeof(int) * n);

  initialise(x);
  inc(x);
  output(x);


  free(x);
  return EXIT_SUCCESS;
}
