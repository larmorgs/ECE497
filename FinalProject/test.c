#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() { 
  char out[] = "HelloWorld";
  char in[10];
  FILE *fp;
  
  fp = fopen("/dev/example", "rw");
  if (fp == NULL) {
    return 1;
  }
  
  fwrite(out, 1, 10, fp);
  
  fread(in, 1, 10, fp);
  
  fclose(fp);
  
  printf("Output: %s\n", out);
  printf("Input: %s\n", in);
}