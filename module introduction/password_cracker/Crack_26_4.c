#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <malloc.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 3 lowercase
  letters, hence the version name Lc3. Before you experiment with this program
  you should explore CommandLine.c to learn about problems with "dollars" and
  use EncryptSHA512.c to encrypt some passwords for testing.

  Compile with:
    cc -o CrackLc3 CrackLc3.c -lcrypt

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:
    ./CrackLc3 \$6\$KB\$Li6EthvFB7zQO6vkYMJoxKrjq6Cc1Vxi1sB.VKu776Pv4hE2qlS6B9TszFnbjQ95QnSJhWix37h26HOjvhG8H0 > results.txt

./Crack_26_4 \$6\$KB\$g3R7q143/KHCaRkLs1cDEnP3ZJ2vAfTD6BQ9ys0yswob8lXpRp.SnDzlYL1T0Lg0cemoP1eVbwTv4sOA0QO1m0 > crackwith4.txt

Answer is kevb
  Dr Kevan Buckley, University of Wolverhampton, 2017
******************************************************************************/

/**
 Required by lack of standard function in C.
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack a three letter lowercase password. All combinations
 that are tried are displayed and when the password is found, #, is put at the
 start of the line. Note that one of the most time consuming operations that
 it performs is the output of intermediate results, so performance experiments
 for this kind of  program should not include this.
*/

void crack(char *salt_and_encrypted){
  int x, y, z, ab;     // Loop counters
  int count=0;     // The number of combinations explored so far
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[5];   // The combination of letters currently being checked
  plain[4] = '\0'; // Put end of string marker on password
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='a'; x<='z'; x++){
    plain[0] = x;
    for(y='a'; y<='z'; y++){
      plain[1] = y;
      for(z='a'; z<='z'; z++){
        plain[2] = z;
        for(ab = 'a'; ab <= 'z'; ab++){
          plain[3] = ab;
          enc = (char *) crypt(plain, salt); //
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
            printf("#%-8d%s %s\n", count, plain, enc);
            exit(0);
          }
        }
      }
    }
  }
}

int main(int argc, char *argv[]){
  if(argc!=2){
    printf("This program requires you to provide an encrypted password\n");
    return 1;
  }

  if(strlen(argv[1])!=92){
    printf("Encrypted passwords should be 92 characters long including salt\n");
    return 1;
  }

  crack(argv[1]);

  return 0;
}
