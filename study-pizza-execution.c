#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

int slices = 0;
sem_t sem1, mutex;
bool first = true, havePizza = false;

void Study(){
  printf("I am studying...\n");
  sleep(2);
}

void makePizza(){
  printf("Making pizza...\n");
  sleep(2);
}

void * estudiants(void* arg) {
  while(true) { // mutex -
    printf("Estudiant waiting...\n");
    sem_wait(&mutex);
    printf("Estudiant entered.\n");
    while( !havePizza ) {
      if( slices > 0 ) {                    // eat pizza
        printf("Eating pizza, slices = %d\n", slices);
        slices--;
        havePizza = true;
      } else {
        if( first ) {
          first = false;
          printf("No pizza, calling pizzeria.\n");
          sem_post(&sem1);                  // ask for pizza
        }
        sem_wait(&mutex);                   // wait for pizza
      }

    } // end while !havePizza
    sem_post(&mutex);
    Study();
    havePizza = false;
  }
}

void * lliurament_de_pizzes(void* arg) {
  while(true) {
    printf("Pizzeria waiting...\n");
    sem_wait(&sem1);                     // wait for student call
    makePizza();
    slices = 10;
    first=true;
    havePizza = false;                  // reset havePizza
    sem_post(&mutex);                   // deliver pizza
  }
}


int main (int argc, char *argv[])
{
  pthread_t student1, student2, student3, pizzeria;
  sem_init(&sem1, 0, 0);
  sem_init(&mutex, 0, 1);

  pthread_create(&student1, NULL, *estudiants, NULL);
  pthread_create(&student2, NULL, *estudiants, NULL);
  pthread_create(&student3, NULL, *estudiants, NULL);
  pthread_create(&pizzeria, NULL, *lliurament_de_pizzes, NULL);

  pthread_join(student1, NULL);
  pthread_join(student2, NULL);
  pthread_join(student3, NULL);
  pthread_join(pizzeria, NULL);
}
