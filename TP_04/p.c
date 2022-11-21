#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  /**
   * Practicing with scheduler related sys calls
   */
  printf("%i", sched_rr_get_interval());
}