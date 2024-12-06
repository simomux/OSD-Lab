#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int x = 0;
pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;


void *incrementX(void *id) {
  int *pi = (int *)id;
  int *ptr;
  int i;

  ptr = (int *) malloc( sizeof(int));
  if (ptr == NULL) {
    perror("Error allocating pointer\n");
    exit(-1);
  }

  pthread_mutex_lock(&MUTEX);

  for(i = 0; i < 10; i++) {
    x++;
    printf("Thread %d incremented x to: %i\n", *pi, x);
  }

  pthread_mutex_unlock(&MUTEX);
  
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
    perror("Wrong arguments!\n");
    exit(1);
  }

  NUM_THREADS = atoi(argv[1]);
  if (NUM_THREADS <= 0) {
    perror("Error, you can't have a < 0 amount of threads\n");
    exit(2);
  }

  thread=(pthread_t *) malloc(NUM_THREADS * sizeof(pthread_t));
  if (thread == NULL){
    perror("Error allocating thread array\n");
    exit(3);
  }
  taskids = (int *) malloc(NUM_THREADS * sizeof(int));
  if (taskids == NULL) {
    perror("Error allocating taskid array\n");
    exit(4);
  }

  for (i=0; i < NUM_THREADS; i++) {
    taskids[i] = i;
    printf("Sto per creare il thread %d-esimo\n", taskids[i]);
    if (pthread_create(&thread[i], NULL, incrementX, (void *) (&taskids[i])) != 0) {
      sprintf(error,"Error in main while creating thread %d\n", taskids[i]);
      perror(error);
      exit(5);
    }
    printf("Main successfully create thread %i id=%lu\n", i, thread[i]);
  }

  for (i=0; i < NUM_THREADS; i++) {
    int ris;
    pthread_join(thread[i], (void**) & p);
    ris= *p;
    printf("Pthread %d returns %d\n", i, ris);
  }

  exit(0);
}
