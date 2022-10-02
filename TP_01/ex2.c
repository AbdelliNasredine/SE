#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  TP01-EX02 : Printing all values of `argv`, character by character
 **/
int main(int argc, char** argv) {
  if (argc <= 1) {
    exit(-1);
  }
  for (int i = 1; i < argc; i++) {
    char* arg = argv[i];
    for (int j = 0; j < strlen(arg); j++) printf("%c\n", (char)argv[i]);
  }
}