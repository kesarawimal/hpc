#include <stdio.h>

void printMemory(void *ptr, unsigned int n) {
  unsigned int i;
  unsigned char *p = ptr;
  for(i=0;i<n;i++){
    printf("%3d ", *p);
    p++;
  }
  printf("\n");
}

int add(int x) {
  return x+29;
}

void doEvilThings(int (*f)(int) ) {
  char *ptr = (char *) f;
  ptr = ptr + 12;
  *ptr = 66;
}

int main() {
  printf("%d\n", add(1));
  printMemory(&add, 20);
  doEvilThings(&add);
  printf("%d\n", add(1));

  return 0;
}
