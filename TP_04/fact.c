#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fib(int n) {
  if (n == 0) return 0;
  if (n <= 2) return 1;
  return fib(n - 1) + fib(n - 2);
}

int main(int argc, char** argv) {
  if (argc < 2) exit(-1);
  int f = fib(atoi(argv[1]));
  printf("[parent][pid|%i]: finished , result = %i", getpid(), f);
}