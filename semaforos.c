#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define NR_LOOP 10000
static int counter = 0;
static void * thread_1_function(void* arg);
static void * thread_2_function(void* arg);

sem_t sem1;

int main(int argc, char *argv[])
{

    pthread_t thread_1, thread_2;
    sem_init(&sem1, 0, 1);

    pthread_create(&thread_1, NULL, *thread_1_function, NULL);
    pthread_create(&thread_2, NULL, *thread_2_function, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("counter = %d\n", counter);

    return 0;
}

static void * thread_1_function(void* arg){
  for(int i = 0; i < NR_LOOP; i++){
      sem_wait(&sem1);
      // zona crítica
      counter+= 1;
      //
      sem_post(&sem1);
  }
}

static void * thread_2_function(void* arg){
  for(int i = 0; i < NR_LOOP; i++){
      sem_wait(&sem1);
      // zona crítica
      counter-= 1;
      //
      sem_post(&sem1);
  }
}
