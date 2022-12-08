#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
sem_t mutex;
void prendre(int i) { printf("shaolin %d a pris la fourchette\n", i); }
void manger(int i) { printf("shaolin %d est entrain de manger\n", i); }
void reposer(int i) { printf("shaolin %d a repose la fourchette\n", i); }
void shaolin(int i) {
  sem_wait(&mutex);
  prendre(i);
  manger(i);
  reposer(i);
  sem_post(&mutex);
}
void main(int argc, char* argv[]) {
  sem_init(&mutex, 1, 1);
  // pthread_t threads[3];

  // for (int i = 0; i < 3; i++)
  //   threads[i] = pthread_create(&threads[i], NULL, shaolin, i);

  // for (int i = 0; i < 3; i++) pthread_join(threads[i], NULL);
  shaolin(atoi(argv[1]));

  // return 0;
}