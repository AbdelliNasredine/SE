#include <stdio.h>
#include <stdlib.h>
void main() {
  FILE* f;
  f = fopen("f.txt", "r");
  if (f == NULL) printf("fopenerror");
  while (getc(f) != EOF)
    ;
  fclose(f);
  printf("finished");
}