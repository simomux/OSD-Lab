#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define NTIMES 10
#define NUM_THREADS 4
#define MATCHES 1
#define TOBACCO 2
#define PAPER 3

#define SEM_NAME "/semaphore_"


pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;
sem_t *SEM[NUM_THREADS];

int generate_rand(int n) {
  int random;

  random = rand() % n;
  random++;

  return random;
}

void *eseguiTabaccaio(void *id){
  int *pi = (int *)id;
  int *ptr;
  int i;
  int r;
  
  ptr = (int *) malloc(sizeof(int));
  if (ptr == NULL)
  {
      perror("Error allocating ptr\n");
      exit(-1);
  }

  srand(time(NULL));
  printf("Vendor-[Thread%d, id %lu] I'm coming\n", *pi, pthread_self());

  for (i = 0; i < NTIMES ; i++) {
    pthread_mutex_lock(&MUTEX);

    r = generate_rand(3);

    if (r == MATCHES) {
      printf("Vendor-[generated %d in iteration %i]: There's tobacco and paper on the table, so i can wake up the smoker that has matches\n", r, i);
    } else if (r == TOBACCO) {
      printf("Vendor-[generated %d in iteration %i]: There's paper and matches on the table, so i can wake up the smoker that has tobacco\n", r, i);
    } else {
      printf("Vendor-[generated %d in iteration %i]: There's tobacco and matches on the table, so i can wake up the smoker that has paper\n", r, i);
    }

    sem_post(SEM[r]);

    pthread_mutex_unlock(&MUTEX);

    sem_wait(SEM[0]);

  }

  *ptr = *pi;
  pthread_exit((void *) ptr);
}

void *eseguiFumatore(void *id) {
  int *pi = (int *)id;
  int *ptr;
  int i;

  ptr = (int *) malloc(sizeof(int));

  if (ptr == NULL) {
      perror("Error assigning ptr\n");
      exit(-1);
  }

  printf("Smoker-[Thread%d, id %lu] wants to smoke\n", *pi, pthread_self());

  for (i = 0; ; i++) {
    sem_wait(SEM[*pi]);
    pthread_mutex_lock(&MUTEX);

    if (*pi == MATCHES) {
      printf("Smoker-Matches: Takes tobacco and paper from the table, so it can make the sigarette\n");
    } else if (*pi == TOBACCO) {
      printf("Smoker-Tobacco: Takes paper and matches from the table, so it can make the sigarette\n");
    } else {
      printf("Smoker-Paper: Takes tobacco and matches from the table, so it can make the sigarette\n");
    }

    sem_post(SEM[0]);
    pthread_mutex_unlock(&MUTEX);
    sleep(5);
  }

  *ptr = *pi;
  pthread_exit((void *) ptr);
}

int main (int argc, char **argv) {
  pthread_t *thread;
  int *taskids;
  int i;
  int *p;
  char error[250];

  if (argc != 1 ) {
    sprintf(error,"Wrong amount of arguments\n");
    perror(error);
    exit(1);
  }
  
  thread=(pthread_t *) malloc(NUM_THREADS * sizeof(pthread_t));
  if (thread == NULL) {
    perror("Error allocating thread array\n");
    exit(2);
  }
  taskids = (int *) malloc(NUM_THREADS * sizeof(int));
  if (taskids == NULL) {
    perror("Error allocatin taskid array\n");
    exit(3);
  }

  char name[20];
  for(i = 0; i < NUM_THREADS; i++) {
    sprintf(name, "%s%d", SEM_NAME, i);
    SEM[i] = sem_open(name, O_CREAT, 0644, 0);
    if (SEM[i] == SEM_FAILED) {
      sprintf(error,"Error initializing %i semaphore", i);
      perror(error);
      exit(4);
    }
  }



  for (i=0; i < NUM_THREADS; i++) {
    taskids[i] = i;

    if (i == 0) {
      printf("Creating vendor thread %d\n", taskids[i]);
      if (pthread_create(&thread[i], NULL, eseguiTabaccaio, (void *) (&taskids[i])) != 0) {
        sprintf(error,"Error in main while creating vendor thread %d\n", taskids[i]);
        perror(error);
        exit(5);
      }
    } else {
   		printf("Creating smoker thread %d\n", taskids[i]);
      if (pthread_create(&thread[i], NULL, eseguiFumatore, (void *) (&taskids[i])) != 0) {
        sprintf(error,"Error in main while creating smoker thread %d\n", taskids[i]);
        perror(error);
        exit(6);
      }
	  }
	  printf("Main created thread %i with id=%lu\n", i, thread[i]);
  }

  for (i=0; i < NUM_THREADS; i++) {
    if (i == 0) {
      int ris;
      pthread_join(thread[i], (void**) & p);
      ris= *p;
      printf("Vendor-Pthread %d returns %d\n", i, ris);
    }
  }


  for(i = 0; i < NUM_THREADS; i++) {
    sprintf(name, "%s%d", SEM_NAME, i);
    sem_unlink(name);
  }

  exit(0);
}
