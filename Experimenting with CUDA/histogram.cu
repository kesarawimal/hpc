6CS005 - High Performance Computing
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cuda_runtime_api.h>

/*****************************************************************************

 This version enables the number of blocks to be varied, as opposed to the 
 number of threads per block being varied in the previous version. This
 version has had a change to the main method to vary the number of blocks of
 threads. Every time it iterates it increases the number of blocks. The 
 results are very interesting and might not be what you expect. You can think 
 of it as being very similar to the car wash problem talked about in the 
 lecture. You might want to do some more formal testing where each experiment
 is performed multiple times and the means taken.  

 To compile:
    nvcc -o war_and_peace_05 war_and_peace_05.cu -lrt


  Dr K A Buckley, University of Wolverhampton, 2018

*****************************************************************************/

long int host_n_bytes, *dev_n_bytes;
int n_bins = 256;
unsigned char *host_data, *dev_data;
int *host_bins, *dev_bins;
int n_blocks;

/**
  Given two time structures calculate the difference between them. Result
  is returned through the third parameter. Function returns 0 on success.
*/

int time_difference(struct timespec *start, struct timespec *finish, 
  long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

/**
  Allocates memory for the book data and histogram and loads the book data
  from file. You need to have downloaded the file for this function to work.
*/

void load_data(char *file_name){
  cudaError_t error;
  long bytes_read;
  struct stat stbuf;
 
  if(stat(file_name, &stbuf) == -1){
    fprintf(stderr, "Problem accessing file status\n");
    exit(0);
  }
  host_n_bytes = stbuf.st_size;

  host_data = (unsigned char *) malloc(sizeof(unsigned char) * host_n_bytes);
  host_bins = (int *) malloc(sizeof(int) * n_bins);
  
  FILE *f = fopen(file_name, "r");
  if(!f){
    fprintf(stderr, "Problem opening file\n");
    exit(1);        
  }

  bytes_read = fread(host_data, 1, host_n_bytes, f);
  if(bytes_read != host_n_bytes){
    fprintf(stderr, "Problem reading file. Not enough data read.\n");
    exit(1);        
  }
  fclose(f);  

  error = cudaMalloc(&dev_data, host_n_bytes); 
  if(error){
    fprintf(stderr, "malloc of dev_data %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }

  error = cudaMalloc(&dev_bins, sizeof(int) * n_bins); 
  if(error){
    fprintf(stderr, "malloc of dev_bins %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
  
  error = cudaMalloc(&dev_n_bytes, sizeof(long int)); 
  if(error){
    fprintf(stderr, "malloc of n_bytes %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
  
  error = cudaMemcpy(dev_data, host_data, host_n_bytes, 
    cudaMemcpyHostToDevice);
  if(error){
    fprintf(stderr, "copy from host_data to dev_data %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
  
  error = cudaMemcpy(dev_n_bytes, &host_n_bytes, sizeof(long int), 
    cudaMemcpyHostToDevice);
  if(error){
    fprintf(stderr, "copy from host_n_bytes to dev_n_bytes %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
}

/**
  Iterates through the characters in the data incrementing the appropriate 
  histogram bins.
*/

__global__ void kernel_n_256(unsigned char *data, 
                             int *bins, long int *n_bytes){
  int i, j, k, stride, start;
  i = threadIdx.x;
  k = blockIdx.x;
  stride = gridDim.x;
  start = blockIdx.x;
  
  printf("thread %d,%d starting at %d using stride %d\n", i, k, start, stride);
  
  for(j=start;j<*n_bytes;j+=stride){
    if(data[j] == i){
      atomicAdd(&bins[i], 1);
    }
  }   
}

/**
  Launch threads. Each one will look for the particular character that it is
  associated with and adjust the required histogram bin.
*/

void compute_histogram(){
  cudaError_t error;

  kernel_n_256 <<<n_blocks, 256>>>(dev_data, dev_bins, dev_n_bytes);
  error = cudaGetLastError();

  if(error){
    fprintf(stderr, "Kernel launch returned %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
  error = cudaThreadSynchronize();
  if(error){
    fprintf(stderr, "Thread synchonize returned %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
}

/**
  Time the calculation of the histogram then output and check the results.
*/

void run() {
  int i;
  cudaError_t error;
  struct timespec start, finish;   
  long long int time_elapsed;
 
  clock_gettime(CLOCK_MONOTONIC, &start);
  compute_histogram();
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  
  error = cudaMemcpy(host_bins, dev_bins, n_bins * sizeof(int), 
    cudaMemcpyDeviceToHost);
  if(error){
    fprintf(stderr, "copy from dev_bins to host_bins %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }  
  printf("\nresults\n========\n");
  int count = 0;
  for(i=0;i<n_bins;i++){
    if(i>=32 && i<127) {
      printf("%3d: %c: %d\n", i, i, host_bins[i]);
    }
    count += host_bins[i];
  }

  printf("\n%d records were found in bins\n", count);
  if(count != host_n_bytes){
    printf("Results are incorrect\n");
    printf("%ld bytes from %ld are missing\n", 
      host_n_bytes - count, host_n_bytes);
  } else {
    printf("results are correct\n");
  }
  printf("run took %0.9lfs\n", (time_elapsed/1.0e9)); 
}

/**
  Sets all histogram bins to zero so that the program can repeatedly
  calculate the histogram to measure performance.
*/

void clear_results(){
  cudaError_t error;
  error = cudaMemset(dev_bins, 0, n_bins * sizeof(int));
  if(error){
    fprintf(stderr, "Mem set of dev_bins returned %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
}

/**
  Free up all memory that was dynamically allocated.
*/

void cleanup(){
  cudaError_t error;
  
  error = cudaFree(dev_data);
    if(error){
    fprintf(stderr, "Free dev_data returned %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }
  error = cudaFree(dev_bins);
  if(error){
    fprintf(stderr, "Free dev_bins returned %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }  
  error = cudaFree(dev_n_bytes);
  if(error){
    fprintf(stderr, "Free dev_n_bytes returned %d %s\n", error,
      cudaGetErrorString(error));
    exit(1);
  }  
  free(host_data);
  free(host_bins);
}

int main(int argc, char * argv[]){
  int i;
  
  if(argc != 2){
    fprintf(stderr, "You need to specify the path/file name of the book\n");
    exit(1);
  }

  load_data(argv[1]);
  for(i=1;i<128;i++){
    n_blocks = i;
    clear_results();
    run();
  }
  
  cleanup();
}