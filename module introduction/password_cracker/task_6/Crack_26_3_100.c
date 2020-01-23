#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <crypt.h>
#include <ctype.h>

#define NCHAR 64
char *readline (FILE *fp, char **buffer);

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void crack(char *salt_and_encrypted){
  int x, y, z, bs;     // Loop counters
  int count=0;     // The number of combinations explored so far
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[4];   // The combination of letters currently being checked
  plain[3] = '\0'; // Put end of string marker on password
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='a'; x<='z'; x++){
    plain[0] = x;
    for(y='a'; y<='z'; y++){
      plain[1] = y;
      for(z='a'; z<='z'; z++){
        plain[2] = z;

        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
          break;
        }
      }
    }
  }
}

int main(int argc, char *argv[]){
	char *line = NULL;
    size_t idx = 0;
    FILE *fp =  fopen ("/home/raj/Downloads/password/task_6/Crack_26_3_100.txt", "r");

	int i, y;

    while (readline (fp, &line)) {  /* read each line in 'fp' */
    	for(i = 0; line[i] !='\0'; i++);

		if(i >= 92){
			//printf("%s\n", line);
              crack(line);
		}


        free (line);
        line = NULL;
    }
    if (fp != stdin) fclose (fp);
	return 0;
}

char *readline (FILE *fp, char **buffer)
{
    int ch;
    size_t buflen = 0, nchar = NCHAR;

    *buffer = malloc (nchar);
    if (!*buffer) {
        fprintf (stderr, "readline() error: virtual memory exhausted.\n");
        return NULL;
    }

    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
    {
        (*buffer)[buflen++] = ch;

        if (buflen + 1 >= nchar) {
            char *tmp = realloc (*buffer, nchar * 2);
            if (!tmp) {
                fprintf (stderr, "error: realloc failed, "
                                "returning partial buffer.\n");
                (*buffer)[buflen] = 0;
                return *buffer;
            }
            *buffer = tmp;
            nchar *= 2;
        }
    }
    (*buffer)[buflen] = 0;

    if (buflen == 0 && ch == EOF) {
        free (*buffer);
        *buffer = NULL;
    }

    return *buffer;
}
