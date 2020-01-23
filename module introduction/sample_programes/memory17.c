#include <stdio.h>

int main() {
	/*unsigned is a qualifier which is used to increase the values to be written in the memory blocks. For example - char can store values between -128 to +127, while an unsigned char can store value from 0 to 255 only.*/
  unsigned char a = 10;
  //assign a address to b
  unsigned char *b = &a;
  //print a value and b value
  printf("%d %d\n", a, *b);
//Define and Declare unsigned char array
  unsigned char c[] = {21, 15, 92};
  unsigned char *d = c;
  //print d address
  printf("%p\n", d);
  //print d value 21
  printf("%d ", *d);
  //increment index by one
  d++;
  //print value 15
  printf("%d ", *d);
  d++;
  printf("%d\n", *d);
  printf("%p\n", d);

  int g[] = {21, 15, 92};
  int *h = g;
  printf("%p\n", h);
  printf("%d ", *h);
  h++;
  printf("%d ", *h);
  h++;
  printf("%d\n", *h);
  printf("%p\n", h);

  unsigned int e = 197127; // (3*65536) + (2*256) + 7
  unsigned char *f = (char *) &e;
  printf("%ld\n", sizeof(e));
  printf("%d ", *f);
  f++;
  printf("%d ", *f);
  f++;
  printf("%d ", *f);
  f++;
  printf("%d\n", *f);
}
