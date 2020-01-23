#include <stdio.h>

//convert to Binary
void toBinary(unsigned char c, unsigned char *result) {
  unsigned char i;
  unsigned char mask = 128;

  for(i=0;i<8;i++){
    if(mask & c) {
      result[i]='1';
    } else {
      result[i]='0';
    }
    mask = mask >> 1;
  }
  result[8]=0;
}

int main() {
  char result1[9];
  char result2[9];
  char result3[9];
  char result4[9];
  char result5[9];
  char result6[9];
  char result7[9];
  char result8[9];

  unsigned char n;
  unsigned char mask = 110;
  unsigned char or;
  unsigned char and;
  unsigned char not;
  unsigned char leftOnce;
  unsigned char leftTwice;
  unsigned char rightOnce;
  unsigned char rightTwice;
  int i;

  for(i=0;i<256;i++){
    n = i;
    or = n | mask;
    and = n & mask;
    not = ~n;
    // Left Shift
    leftOnce = n << 1; 
    // Left Shift
    leftTwice = n << 2; 
    //Right Shift
    rightOnce = n >> 1; 
    //Right Shift
    rightTwice = n >> 2; 
    toBinary(n, result1);  
    toBinary(or, result2);  
    toBinary(and, result3);  
    toBinary(not, result4);  
    toBinary(leftOnce, result5);  
    toBinary(leftTwice, result6);  
    toBinary(rightOnce, result7);  
    toBinary(rightTwice, result8);  
    printf("%3hu %s %s %s %s %s %s %s %s\n",
      n, result1, result2, result3, result4, 
      result5, result6, result7, result8);
    n++;
  }
}
