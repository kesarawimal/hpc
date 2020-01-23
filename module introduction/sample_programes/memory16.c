#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct  {
  int a;
  int b;
} pair;

int w = 4;
int h = 3;
//initialise two dimensional pair type array
void initialise(pair *p) {
  int r, c, i, j;
  j=10;
  for(r=0;r<h;r++){
    for(c=0;c<w;c++){
      i = (r*w) + c;
      p[i].a = j++;
      p[i].b = j++;
    }
  }
}
//increment each element both values by one
void inc(pair *q) {
  int i;
  for(i=0;i<w*h;i++){
    q->a = q->a + 1; 
    q->b = q->b + 1; 
    q++;
  }
}
//print each element both values
void output(pair *p) {
  int r, c, i = 0;
  for(r=0;r<h;r++){
    for(c=0;c<w;c++){
      printf("%d,%d\t", p[i].a, p[i].b);
      i++;          
    }
    printf("\n");
  }
}

int main() {
  pair *p;
  //allocate  memory for pair type two dimensional array
  p = malloc(sizeof(pair) * w * h);

  initialise(p);
  inc(p);
  output(p);
//deallocates the memory previously allocated by a call to malloc.
  free(p);
  return EXIT_SUCCESS;
}
