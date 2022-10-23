#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Please specify number of iterations as the first argument! \n");
    return -1;
  }
  int p, counter = 1, max_iterations = atoi(argv[1]);
  while (counter <= max_iterations) {
    printf("counteur = %d \n", counter);
    p = fork();
    if (p == 0)
      printf("\t%d je suis le processus fils de %d \n", getpid(), getppid());
    else if (p > 0)
      printf("\t%d je suis le processus pere de %d\n", getpid(), p);
    counter++;
  }

  return 0;
}
