#include <stdio.h>
#include <stdlib.h>
void main() {
  int p = fork();
  if (p > 0) exit(0);
  unsigned counter = 0xffffffff;
  while (counter--)
    ;
}