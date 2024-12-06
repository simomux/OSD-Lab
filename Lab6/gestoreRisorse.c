#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define RESOURCES 5
#define SEM_NAME "/custom_semaphore"

typedef enum {false, true} Boolean;

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;
sem_t *RESOURCE_MANGAER;
int m = RESOURCES;
Boolean FREE[RESOURCES];


int richiesta() {
  int i;

  sem_wait(RESOURCE_MANGAER);
  pthread_mutex_lock(&MUTEX);

  for (i = 0; i < RESOURCES; i++) {
    if (FREE[i]) {
      FREE[i] = false;
      break;
    }
  }
  
  pthread_mutex_unlock(&MUTEX);

  return i;
}

void rilascio(int x) {
  pthread_mutex_lock(&MUTEX);
  
  FREE[x] = true;

  pthread_mutex_unlock(&MUTEX);
  sem_post(RESOURCE_MANGAER);
}

void *esegui(void *id) {
  int *pi = (int *)id;
  int *ptr;
  int x;

  ptr = (int *) malloc( sizeof(int));
  if (ptr == NULL) {
    perror("Error allocating ptr\n");
    exit(-1);
  }

  x = richiesta();

  printf("Thread%d id=%lu got resource in index %d\n", *pi, pthread_self(), x);
  sleep(5);

  rilascio(x);

  *ptr = x;
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

  RESOURCE_MANGAER = sem_open(SEM_NAME, O_CREAT, 0644, m);
  if (RESOURCE_MANGAER == SEM_FAILED) {
    perror("Error initializing RESOURCE_MANGAER semaphore");
    exit(5);
  }

  for (i=0; i < m; i++)
  	FREE[i] = true;

  for (i=0; i < NUM_THREADS; i++) {
    taskids[i] = i;
    printf("Creating thread %d\n", taskids[i]);
    if (pthread_create(&thread[i], NULL, esegui, (void *) (&taskids[i])) != 0) {
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

  sem_unlink(SEM_NAME);

  exit(0);
}
