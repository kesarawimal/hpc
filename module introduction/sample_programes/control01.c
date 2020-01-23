#include <stdlib.h>
#include <stdio.h>

//For loop will print the values from o to 4, while loop will pick the updated 4 and print the values till 9,
// do while will pick the updated value 9 and print till 14. 
//since the latest i value is 14 if condition will print it as custard

int main() {
  int i;
  for(i=0;i<5;i++){
    printf("%d,", i);
  } 
  printf("\n");

  while(i<10){
    printf("%d,", i);
    i++;
  } 

  do {
    printf("%d,", i);
    i++;
  } while(i<15);
  printf("\n");

  if(i>13){
    printf("custard\n");
  } else {
    printf("gravy\n");
  }

  return EXIT_SUCCESS;
}
