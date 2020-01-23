/****************************************************************************
  This version adds five coins to the account using 5 threads. 
  How long will it take to run?
  How much money will eventually be stored in the account?
  
  Compile with:

    cc -o penny05 penny05.c time_diff.c -lrt -pthread 

*****************************************************************************/

#include <stdio.h>
#include "time_diff.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main(){
  struct timespec start, finish;
  long long int difference;   
  int account = 0;
  int i;

  int n = 5;

  clock_gettime(CLOCK_MONOTONIC, &start);

  void *add_penny();
  pthread_t t[n];
  for(i=0;i<n;i++){
    pthread_create(&t[i], NULL, add_penny, &account);
  }
  for(i=0;i<n;i++){
    pthread_join(t[i], NULL);
  }
  
  //  this fuction use to get the real time at the end
  clock_gettime(CLOCK_MONOTONIC, &finish);
  
//  this function use to calculate different between start and end time
  time_difference(&start, &finish, &difference);
  printf("accumulated %dp\n", account);
  printf("run lasted %lldns or %9.5lfs\n", difference, difference/1000000000.0);
  return 0;
} 

//add a penny to the bank balance
void *add_penny(int *balance) {
  int b = *balance;
  usleep(1000000);
  b = b + 1;
  *balance = b;
}

