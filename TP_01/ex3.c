#include <stdio.h>
/**
 *  TP01-EX03 : Program calling `fork`
 **/
int main() {
  int i;
  for (i = 0; i < 3; i++) {
    fork();
    printf("Hello World!\n");
  };
  return 0;
}