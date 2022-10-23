#include <stdio.h>
#include <unistd.h>
/**
 *  TP01-EX03 : Program calling `fork`
 **/
int main() {
  int i;
  printf("pid = %i!\n", getpid());
  for (i = 0; i < 3; i++) {
    fork();
    printf("hello world, pid = %i!\n, ppid = %i", getpid(), getppid());
  };
  return 0;
}