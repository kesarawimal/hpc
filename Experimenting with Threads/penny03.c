/****************************************************************************
  This version adds five coins to the account. How long will it take to run?
  How much money will eventually be stored in the account?
  
  Compile with:

    cc -o penny03 penny03.c time_diff.c time_diff.c -lrt

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "time_diff.h"

void add_penny(int *balance) {
  int b = *balance;

// 1 second delay (simulating large calculation time)

  usleep(1000000);

  b = b + 1;
  *balance = b;
}

int main(){
  struct timespec start, finish;
  int i;
  long long int difference;   
  int account = 0;
  clock_gettime(CLOCK_MONOTONIC, &start);

//loop 5 times to add 5 pennies
  for(i=0;i<5;i++){
    add_penny(&account);
  }
  
//  this fuction use to get real time at the end
  clock_gettime(CLOCK_MONOTONIC, &finish);
  
//  this function use to calculate different between start and end time
  time_difference(&start, &finish, &difference);

  printf("accumulated %dp\n", account);     
  printf("run lasted %lldns or %9.5lfs\n", difference, difference/1000000000.0);
  return 0;
} 
