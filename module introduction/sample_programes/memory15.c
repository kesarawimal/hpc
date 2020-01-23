#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int w = 4;
int h = 3;
 //initialise two dimensional array
void initialise(int *p) {
  int r, c, i, j;
  j=10;
  for(r=0;r<h;r++){
    for(c=0;c<w;c++){
      i = (r*w) + c;
      p[i] = j++;
    }
  }
}
//increment each element by one
void inc(int *q) {
  int i;
  for(i=0;i<w*h;i++){
    *q = *q + 1; 
    q++;
  }
}
//print each element
void output(int *p) {
  int r, c, i = 0;
  for(r=0;r<h;r++){
    for(c=0;c<w;c++){
      printf("%d\t", p[i++]);          
    }
    printf("\n");
  }
}

int main() {
  int *p;
  //allocate  memory for two dimensional array
  p = malloc(sizeof(int) * w * h);

  initialise(p);
  inc(p);
  output(p);
//deallocates the memory previously allocated by a call to malloc.
  free(p);
  return EXIT_SUCCESS;
}
