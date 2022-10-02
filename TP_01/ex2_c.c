#include <stdio.h>
#include <stdlib.h>
void main(int argc, char *argv[]) {
  int i;
  float s = 0;
  if (argc <= 1)
    exit(-1);
  else
    printf("%s\n", argv[1]);
  i = 0;
  while (argv[1][i] != '\0') {
    printf("%c\n", argv[1][i]);
    i++;
  }
}