#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 ** *********************************
 ** Déclaration des variable globales
 ** *********************************
 ** N (int) = Taille de tompon
 ** T (char[]) = Tompon
 ** mutex, plein, vide = Sémaphores
 ** th1 , th2 = Threads
 ** *********************************
 */
const int N = 10;
char T[10];
sem_t mutex, plein, vide;
pthread_t th1, th2;

/**
 ** *********************************
 ** Fonction Lire
 ** *********************************
 ** Construit, dans ch, une chaîne de
 ** caractères de longueur comprise
 ** entre 1 et N inclusivement (1 <= len(ch) < N).
 ** Elle retourne la longueur de la chaîne. ( len(ch) )
 ** *********************************
 */
int lire(char ch[], int N) {
  int len;
  do {
    printf(
        "[Producteur]: donnez une chaine de caractère de longueur comprise "
        "entre 1 et %d\n",
        N - 1);
    scanf("%s", ch);
    len = strlen(ch);
    if (len >= N) {
      printf(
          "[Producteur]: la longueur de chaine de caractère doit étre "
          "comprise entre 1 et %d \n",
          N - 1);
    }
  } while (len >= N);
}

/**
 ** *********************************
 ** Fonction Deposer (char ch[], int M, int ip)
 ** *********************************
 ** Insère, dans le tampon T, la chaîne
 ** de caractères ch.
 ** M est la longueur de la chaîne.
 ** *********************************
 */
void deposer(char ch[], int M, int ip) {
  int N = sizeof(T);
  for (int i = 0; i <= M; i++) T[(i + ip) % N] = ch[i];
}

/**
 ** *********************************
 ** Fonction Retirer (int ic)
 ** *********************************
 ** Retire un caractère du tampon T.
 ** *********************************
 */
char retirer(int ic) { return T[ic]; }

/**
 ** *********************************
 ** Fonction Retirer (char c)
 ** *********************************
 ** Traite le caractère.
 ** *********************************
 */
void traiter(char c) { printf("[Consomateur][@traiter]: %c \n", c); }

/**
 ** *********************************
 ** Fonction Producteur
 ** *********************************
 ** Produit plusieurs ressources à la fois
 ** *********************************
 */
void producteur() {
  printf("[Producteur]: Debut \n");
  int ip = 0, M;
  char ch[N];
  while (1) {
    M = lire(ch, N);
    for (int i = 1; i <= M; i++) sem_wait(&vide);
    sem_wait(&mutex);
    deposer(ch, M, ip);
    sem_post(&mutex);
    for (int i = 0; i <= M - 1; i++) sem_post(&plein);
    ip = (ip + M) % 10;
  }
}

/**
 ** *********************************
 ** Fonction Consomateur
 ** *********************************
 ** Consomme une seule ressource à la fois
 ** *********************************
 */
void consomateur() {
  printf("[Consomateur]: Debut \n");
  int ic = 0;
  char c;
  while (1) {
    sem_wait(&plein);
    sem_wait(&mutex);
    c = retirer(ic);
    sem_post(&mutex);
    sem_post(&vide);
    traiter(c);
    ic = (ic + 1) % 10;
  }
}

/**
 ** *********************************
 ** Fonction Main
 ** *********************************
 ** Point d'entre de programme
 ** *********************************
 */
void main() {
  // Initialisation des sémaphore
  sem_init(&vide, 0, 10);
  sem_init(&plein, 0, 0);
  sem_init(&mutex, 0, 1);

  // Creation et lancement des threads
  int err1 = pthread_create(&th1, NULL, producteur, T);
  int err2 = pthread_create(&th2, NULL, consomateur, T);

  // Vérification (si les threads sont creés correctement)
  if (err1 && err2) {
    printf("Erreur: La création des threads a échoué");
    return;
  }

  // Attendre le termination des threads
  err1 = pthread_join(th1, NULL);
  err2 = pthread_join(th2, NULL);

  // Vérification (si les threads sont términer correctement)
  if (err1 && err2) {
    printf("Erreur: La terminition des threads a échoué");
    return;
  }
}