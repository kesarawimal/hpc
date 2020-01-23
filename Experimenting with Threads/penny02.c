/****************************************************************************
  This version does the same as the previous version, but records how long
  it takes to run. This is so that the relative speeds of later versions can 
  be compared.
  
  Compile with:

    cc -o penny02 penny02.c time_diff.c -lrt

*****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include "time_diff.h"

//add a penny to the bank balance
void add_penny(int *balance) {
  int b = *balance;
//  waiting 1000000 number of microseconds 
  usleep(1000000);
  b = b + 1;
  *balance = b;
}

int main(){
  struct timespec start, finish;
  long long int difference;   
  int account = 0;
  clock_gettime(CLOCK_MONOTONIC, &start);

//calling add penny fuction
  add_penny(&account);

//  this fuction use to get real time at the end
  clock_gettime(CLOCK_MONOTONIC, &finish);
  
//  this function use to calculate different between start and end time
  time_difference(&start, &finish, &difference);
  printf("accumulated %dp\n", account);
  printf("run lasted %9.5lfs\n", difference/1000000000.0);
  return 0;
} 
