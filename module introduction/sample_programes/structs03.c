#include <stdio.h>
#include <malloc.h>

// using typedef will no longer have to write the struct keyword allover the place again and it is an advance c programing concept
typedef struct {
  unsigned int h;// unsigned int could hold either zero or positive integers only
  unsigned int m;
  unsigned int s;
} t;// t is the structure definition 

int main() {

  t *a; // declaring a pointer to the structure t 

  // malloc is a function which used to allocate memory to a structure dynamically 
  // on success malloc function will returns the base address of the of the memory block 
  //sizeof() function will cal
  a = (t *) malloc(sizeof(t));

  //arrow operator is used to direct a pointer to a structure variable 
  a->h = 5;
  a->m = 9;
  a->s = 45;

  //arrow operator used to direct pointer to structure 
  printf("Time a is %u:%02u:%02u\n", a->h, a->m, a->s);
  // free() function will deallocates the memory which was allocated by the malloc function 
  free(a);
  return 0;
}
