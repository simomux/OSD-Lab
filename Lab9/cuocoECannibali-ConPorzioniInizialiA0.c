#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define M 0

#define FULL_SEM_NAME "/full_sem"
#define EMPTY_SEM_NAME "/empty_sem"


pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;
sem_t *FULL;
sem_t *EMPTY;
int portions = M;	

void *eseguiCuoco (void* id) {
  int *pi = (int *)id;
  int *ptr;
  int i;

  ptr = (int *) malloc(sizeof(int));
  if (ptr == NULL) {
    perror("Error with ptr allocation\n");
    exit(-1);
  }


  for(i = 0; ; i++) {
    sem_wait(&EMPTY);
    printf("Chef-[Thread%d, id %lu] is filling the pot (iter. %d)\n", *pi, pthread_self(), i);
   	sleep(5);
    portions = M;
    sem_post(&FULL);
  }
}


void *eseguiCannibale(void *id) {
  int *pi = (int *)id;
  int *ptr;

  ptr = (int *) malloc(sizeof(int));
  if (ptr == NULL) {
      perror("Error with ptr allocation\n");
      exit(-1);
  }

  printf("Cannibal-[Thread%d, id %lu] is hungry\n", *pi, pthread_self());

  pthread_mutex_lock(&MUTEX);
  
  if (portions == 0) {
      sem_post(&EMPTY);
      sem_wait(&FULL);
  }
  
  portions--;
  printf("Cannibal-[Thread%d, id %lu] is eating\n", *pi, pthread_self());

  pthread_mutex_unlock(&MUTEX);
  sleep(5);
  printf("Cannibal-[Thread%d, id %lu] is going to sleep after eating\n", *pi, pthread_self());

  *ptr = *pi;
  pthread_exit((void *) ptr);
}


int main (int argc, char **argv) {
  pthread_t *thread;
  int *taskids;
  int i;
  int *p;
  int NUM_THREADS;
  char error[250];

  if (argc != 2 ) {
    sprintf(error,"Wrong arguments!\n");
    perror(error);
    exit(1);
  }

  NUM_THREADS = atoi(argv[1]);

  if (NUM_THREADS < portions+1) {
    sprintf(error,"Thread should be at least %d, but they are %d\n", portions+1, NUM_THREADS);
    perror(error);
    exit(2);
  }

  thread=(pthread_t *) malloc(NUM_THREADS * sizeof(pthread_t));
  if (thread == NULL) {
    perror("Error allocating threads array!\n");
    exit(3);
  }

  taskids = (int *) malloc(NUM_THREADS * sizeof(int));
  if (taskids == NULL) {
    perror("Error allocating taskids array!\n");
    exit(4);
  }

  FULL = sem_open(FULL_SEM_NAME, O_CREAT, 0644, 0);
  if (FULL == SEM_FAILED) {
    perror("Error initializing FULL semaphore");
    exit(5);
  }

  EMPTY = sem_open(EMPTY_SEM_NAME, O_CREAT, 0644, 1);
  if (EMPTY == SEM_FAILED) {
    perror("Error initializing EMPTY semaphore");
    exit(6);
  }

  for (i=0; i < NUM_THREADS; i++) {
    taskids[i] = i;

    if (i == 0) {
      printf("Creating chef thread %d\n", taskids[i]);
      if (pthread_create(&thread[i], NULL, eseguiCuoco, (void *) (&taskids[i])) != 0) {
        sprintf(error,"Error in main creting chef thread %d-esimo\n", taskids[i]);
        perror(error);
        exit(7);
      }
    } else {
      printf("Creating cannibal thread %d\n", taskids[i]);
      if (pthread_create(&thread[i], NULL, eseguiCannibale, (void *) (&taskids[i])) != 0) {
        sprintf(error,"Error in main creting cannibal thread %d-esimo\n", taskids[i]);
        perror(error);
        exit(8);
      }
    }

    printf("Created thread %i with id = %lu\n", i, thread[i]);
  }

  for (i=0; i < NUM_THREADS; i++) {
    int ris;
    if (i = 0) 
      printf("Can't wait for chef thread since it's an infinite loop!\n");
    else {
      pthread_join(thread[i], (void**) & p);
      ris= *p;
      printf("Cannibal-Pthread %d returns %d\n", i, ris);
    }
  }

  exit(0);
}
