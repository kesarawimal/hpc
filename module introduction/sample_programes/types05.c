#include <stdlib.h>
#include <stdio.h>

//There are no booleans in C, but integers are used by conditional operators instead. 
//Work through the code and its output and see if you can work out what integer values are used to represent true and false.?

//integer values are 2 and 3
int main() {
  int a = 2;
  int b = 3;
  int c = 2;
  int d = 4;

  printf("There are no booleans in c\n");
  printf("%d\n", a==b);
  printf("%d\n", a==c);
  printf("%d\n", a!=b);
  printf("%d\n", a!=c);
  printf("%d\n", a==b);
  printf("%d\n", !(a==b));

  int e = (a == b) || (a == c);
  int f = (a == b) && (a == c);

  printf("e=%d\n", e);
  printf("f=%d\n", f);

  if(e) {
    printf("e=true\n");
  } else {
    printf("e=false\n");
  }

  if(f) {
    printf("f=true\n");
  } else {
    printf("f=false\n");
  }

  return EXIT_SUCCESS;
}
