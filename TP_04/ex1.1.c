#include <stdio.h>
#include <stdlib.h>
int fib(int n) {
  if (n == 0) return 0;
  if (n <= 2) return 1;
  return fib(n - 1) + fib(n - 2);
}
void main() {
  fib(1000);
  printf("finished");
}
