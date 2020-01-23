/****************************************************************************
  This version adds 100 coins to the account without using threads.
  
  Compile with:

    cc -o penny12 penny12.c time_diff.c -lrt

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

//loop 100 times to add 100 pennies to the account
  for(i=0;i<100;i++){
    add_penny(&account);
  }
  
  //  this fuction use to get the real time at the end
  clock_gettime(CLOCK_MONOTONIC, &finish);
  
//  this function use to calculate different between start and end time
  time_difference(&start, &finish, &difference);

  printf("accumulated %dp\n", account);     
  printf("run lasted %lldns or %9.5lfs\n", difference, difference/1000000000.0);
  return 0;
} 
