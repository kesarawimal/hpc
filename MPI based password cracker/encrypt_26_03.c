#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <mpi.h>
#include <time.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code.
  Compile with:
    mpicc -o CrackAZ99-With-Data-mpi CrackAZ99-With-Data-mpi.c -lcrypt 
  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:
    mpiexec -n 8 ./CrackAZ99-With-Data-mpi
  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/

int n_passwords = 4;
int rank, size;

char *encrypted_passwords[] = {
  "$6$KB$0G24VuNaA9ApVG4z8LkI/OOr9a54nBfzgQjbebhqBZxMHNg0HiYYf1Lx/HcGg6q1nnOSArPtZYbGy7yc5V.wP/",
  "$6$KB$e0HAHUeBkbmMUYH50qM6XOcuMh5NIh4wWqaF5veFJ8lCCXO2WikTvJXMRUhQAE.L0c583VnKDUYYsz4hdRSPx.",
  "$6$KB$/g6qkCh2GqH3qbb9VpoY.LaOEfiuD3JQ9xt49hYMEGHxCWq26lsspDwYankcFID6OY2/pGKIa2ysBWzvaK87D0",
  "$6$KB$QIT0aY3OjXyMz7/0u/Evwrzcb44AwaQbsRFPZ3UeT8df8LoJzpDI8ULgvKw5ZfZJui3nj0k3OtkGaB/znQwrU1"
};

/**
 Required by lack of standard function in C.  
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the
 start of the line. Note that one of the most time consuming operations that
 it performs is the output of intermediate results, so performance experiments
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void crack(char *salt_and_encrypted) {
	int x, y, z;     // Loop counters
	char salt[7];    // String used in hashing the password. Need space for \0
	char plain[7];   // The combination of letters currently being checked
	char *enc;       // Pointer to the encrypted password
	int count = 0;   // The number of combinations explored so far

	substr(salt, salt_and_encrypted, 0, 6);

	for(x='a'; x<='z'; x++){
    plain[0] = x;
    for(y='a'; y<='z'; y++){
      plain[1] = y;
      for(z='a'; z<='z'; z++){
        plain[2] = z;
        enc = (char *) crypt(plain, salt); //
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          
    printf("\n \n PASSWORD CRACKED : %s is MATCHING\n", plain);
    exit(0);
        } else {
          printf("%s is mismatching \n", enc);
      //printf("wrong\n");
        }
      }
    }
  }
  printf("%d analyzed\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
   long long int *difference) {
   long long int ds = finish->tv_sec - start->tv_sec;
   long long int dn = finish->tv_nsec - start->tv_nsec;

      if (dn < 0) {
	ds--;
	dn += 1000000000;
	}
	   *difference = ds * 1000000000 + dn;
	   return !(*difference > 0);
}

int main(int argc, char *argv[]){
   struct timespec start, finish;
   long long int time_elapsed;

   clock_gettime(CLOCK_MONOTONIC, &start);
   int i;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank > 0) {
		for (i = 0; i < n_passwords; i < i++) {
			crack(encrypted_passwords[i]);
		}
	}
   MPI_Finalize();
   clock_gettime(CLOCK_MONOTONIC, &finish);
   time_difference(&start, &finish, &time_elapsed);
   printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed / 1.0e9));

  return 0;
}