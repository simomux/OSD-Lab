#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *PrintHello(void *id) {
  int *pi = (int *)id;
  int *ptr;

  ptr = (int *) malloc( sizeof(int));
  if (ptr == NULL) {
      perror("Error allocating ptr\n");
      exit(-1);
  }

  printf("Thread %d started: Hello World! Id: %lu\n", *pi, pthread_self());
  /* pthread vuole tornare al padre un valore intero, ad es 1000+id */
  *ptr = 1000+*pi;
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
    perror("Error! Number of threads can't be < 1\n");
    exit(2);
  }

  thread=(pthread_t *) malloc(NUM_THREADS * sizeof(pthread_t));
  if (thread == NULL) {
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
    printf("Creating thread %d\n", taskids[i]);
    if (pthread_create(&thread[i], NULL, PrintHello, (void *) (&taskids[i])) != 0) {
      sprintf(error,"Error in main while creating thread %d\n", taskids[i]);
      perror(error);
      exit(5);
    }
    printf("Main successfully created thread %i with id=%lu\n", i, thread[i]);
  }

  for (i=0; i < NUM_THREADS; i++) {
    int ris;

    pthread_join(thread[i], (void**) & p);
    ris= *p;
    printf("Pthread %d returns %d\n", i, ris);
  }

  exit(0);
}
