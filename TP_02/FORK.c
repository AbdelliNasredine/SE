#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int p;
  p = fork();
  if (p == 0)
    printf("%d je suis le processus fils de %d \n", getpid(), getppid());
  else if (p > 0)
    printf("%d je suis le processus pere de %d\n", getpid(), p);
  return 0;
}
