/****************************************************************************
  This version adds 1000 coins to the account without using threads.
  
  Compile with:

    cc -o penny13 penny13.c time_diff.c time_diff.c -lrt

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "time_diff.h"

//add a penny to the bank balance
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

//loop 1000 times to add 1000 pennies to account
  for(i=0;i<1000;i++){
    add_penny(&account);
  }
  
  //  this fuction use to get the real time at the end
  clock_gettime(CLOCK_MONOTONIC, &finish);
  
//  this function use to calculate different between start and end time
  time_difference(&start, &finish, &difference);

  printf("accumulated %dp\n", account);
  
//  print different between start and end time
  printf("run lasted %lldns or %9.5lfs\n", difference, difference/1000000000.0);
  return 0;
} 
