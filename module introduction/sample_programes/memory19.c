#include <stdio.h>

void f1() {
  printf("cat\n");
}

void f2() {
  printf("mouse\n");
}
//pass function as parameter
void f3(void (*f)() ) {
  f();
}

int main() {
	//call f3 and pass f1 function address
  f3(&f1);
  //call f3 and pass f2 function address
  f3(&f2);
  return 0;
}
