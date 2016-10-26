#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int readRandom() {
  int f = open("/dev/random", O_RDONLY);
  int *i = malloc(4);
  read(f,i,4);
  int n = *i;
  free(i);
  close(f);
  return n;
}

int main() {
  // Setting umask
  umask(0000);
 
  int arr[10];
  int i;

  // 1. Populating Array
  printf("Generating random numbers...\n");
  for (i = 0; i < 10; i++) {
    arr[i] = readRandom();
    printf("random %d: %d\n", i, arr[i]);
  }

  // 2. Writing Array
  printf("Writing numbers to file...\n");
  int f = open("somenumbers.txt", O_CREAT | O_WRONLY, 0644);
  int n = write(f,arr,40);
  close(f);

  // 3. Reopen File
  printf("Reading numbers to new array...\n");
  int f2 = open("somenumbers.txt", O_RDONLY);
  int arr2[10];
  read(f2, arr2, 40);
  close(f2);

  // 4. Verify Contents
  printf("Verifying values...\n");
  for (i = 0; i < 10; i++)
    printf("random %d: %d\n", i, arr2[i]);
  
  return 0;
}
