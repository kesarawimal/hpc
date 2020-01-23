#include <stdlib.h>
#include <stdio.h>

int main() {
  printf("Strings are just arrays of chars\n");
// character pointer will stores string values
  char *message1 = "hello";
  char *message2 = "kevan";
// printing using the stored string values 
  printf("%s %s\n", message1, message2);
  
  printf("Look in /usr/include/string.h for functions\n");
  printf("that can be applied. Each has a man page.\n");
  return EXIT_SUCCESS;
}
