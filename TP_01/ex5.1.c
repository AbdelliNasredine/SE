#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  int p = 1;
  while (p > 0) p = fork();
  printf("Hello World!\n");
  return 0;
}