#include <stdio.h>

struct t { // t is the structure definition 
  unsigned int h; // unsigned int could hold either zero or positive integers only
  unsigned int m;
  unsigned int s;
};

int main() {
  // variable declaration for the structure and variable a is considered as the internal pointer and hold the base address of the structure
  //6 bytes will be allocated for the structure considering the variables declared witin the struct t
  struct t a;
  //pointer declaration to the struct t 
  struct t *b;

  // accessing the structure using the "a" and assigning a value to the "h" variable using the dot operator 
  a.h = 5; 
  // accessing the structure using the "a" and assigning a value to the "m" variable using the dot operator 
  a.m = 9;
  // accessing the structure using the "a" and assigning a value to the "s" variable using the dot operator 
  a.s = 45;

  // printing the values using the dot operator.Format specifier %u will print the unsigned interger
  //%02u will print the value for two decimal places 
  printf("Time a is %u:%02u:%02u\n", a.h, a.m, a.s);

//pointer b will hold the base address of the structure "a"
  b = &a;
  //arrow operator is used to direct a pointer to a structure and same value will get printed as in the previous printf statement  
  printf("Time b is %u:%02u:%02u\n", b->h, b->m, b->s);

  return 0;
}
