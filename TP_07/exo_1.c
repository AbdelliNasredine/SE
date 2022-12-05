#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// BEGIN GLOBAL DEF
const int debug = 1;
const int N = 10;
char T[10];
pthread_t th1, th2;
sem_t vide;
sem_t plein;
sem_t mutex;
// END GLOBAL DEF

int lire(char ch[], int N) {
  int len;
  do {
    if (debug) printf("[@lire][debut]: ch = %s \n", ch);
    printf(
        "donnez une chaine de caractère de longueur comprise entre 1 et %d\n",
        N - 1);
    scanf("%s", ch);
    if (debug) printf("[@lire][fin]: len(ch) = %d, ch = %s \n", strlen(ch), ch);
    len = strlen(ch);
  } while (len >= N);
}

int randomlire(char ch[], int N) {
  int random_len = random() % (N - 1);
  for (int i = 0; i <= random_len; i++) ch[i] = 'A' + (random() % 26);
  return random_len;
}

void deposer(char ch[], int M, int ip) {
  int N = sizeof(T);
  if (debug) printf("[@deposer][debut]: ch = %s, M = %i \n", ch, M);
  for (int i = 0; i <= M; i++) T[(i + ip) % N] = ch[i];
  if (debug) printf("[@deposer][fin]: ch = %s, T = %s \n", ch, T);
}
char retirer(int ic) {
  if (debug) printf("[@retirer]: T[ic] = %c \n", T[ic]);
  return T[ic];
}
void traiter(char c) {
  if (debug) printf("[@traiter][debut]: c = %c \n", c);
  printf("[@traiter][traitement...]: %c \n", c);
}
void producteur() {
  if (debug) printf("[#producteur][debut]\n");
  int ip = 0, M;
  char ch[N];
  int count = 1;
  while (count > 0) {
    if (debug) printf("[#producteur][avant_lecture] \n");
    M = lire(ch, N);
    if (debug)
      printf("[#producteur][apres_lecture]: ip = %d, M = %d, ch = %s \n", ip, M,
             ch);
    for (int i = 1; i <= M; i++) sem_wait(&vide);
    sem_wait(&mutex);
    if (debug) printf("[#producteur][avant_deposer] \n");
    deposer(ch, M, ip);
    if (debug)
      printf("[#producteur][apres_deposer], T = %s, ch = %s \n", T, ch);
    sem_post(&mutex);
    for (int i = 0; i <= M - 1; i++) sem_post(&plein);
    ip = (ip + M) % 10;
    if (debug) printf("[#producteur][fin]: ip = %d \n", ip);
    count--;
  }
}
void consomateur() {
  int ic = 0;
  char c;
  do {
    if (debug) printf("[#consomateur][debut]\n");
    sem_wait(&plein);
    sem_wait(&mutex);
    if (debug)
      printf("[#consomateur][avant_retirer]: ic = %d, c = %c \n", ic, c);
    c = retirer(ic);
    if (debug)
      printf("[#consomateur][apres_retirer]: ic = %d, c = %c \n", ic, c);
    printf("%c \n", c);
    sem_post(&mutex);
    sem_post(&vide);
    traiter(c);
    ic = (ic + 1) % 10;
  } while (ic < 9);
  printf("[#consomateur][T]: T = %s \n", T);

  if (debug) printf("[#consomateur][fin]\n");
}
int main() {
  if (debug) printf("[@main][debut]\n");
  sem_init(&vide, 0, 10);
  sem_init(&plein, 0, 0);
  sem_init(&mutex, 0, 1);
  pthread_create(&th1, NULL, producteur, T);
  pthread_create(&th2, NULL, consomateur, T);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  if (debug) printf("[@main][fin]\n");
}