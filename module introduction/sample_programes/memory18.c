#include <stdio.h>
//print int values of ptr
void printMemory(void *ptr, unsigned int n) {
  unsigned int i;
  unsigned char *p = ptr;
  for(i=0;i<n;i++){
    printf("%3d ", *p);
    p++;
  }
  printf("\n");
}
//print char values of ptr
void printMemory2(void *ptr, unsigned int n) {
  unsigned int i;
  unsigned char *p = ptr;
  for(i=0;i<n;i++){
    printf("%c ", *p);
    p++;
  }
  printf("\n");
}

int main(){
  unsigned char a[] = {65, 66, 67, 90};
  printMemory(a, 4);
  printMemory2(a, 4);
  int b = 197127;
  printMemory(&b, 4);
  char c[] = "XYZ123";
  printMemory(c, 6);

  double d = 65536;
  printf("%lu\n", sizeof(d));
  printMemory(&d, 8);

  printf("%p %p %p %p\n", a, &b , c, &d);
}
