#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Definicions i inicialització de variables compartides*/
#define true 1
int n_orxates = 0;
semaphore sem1, sem2, sem3, sem4, sem5, sem6;

void cambrer() {
  int tmp, i;
  while (true) {
    sem_wait(sem2); // espera a que hagi de servir...
    sem_wait(sem5);
    tmp = n_orxates;
    n_orxates = 0;
    sem_signal(sem5);

    for (i=0; i<tmp; i++) {
      sem_wait(sem1);
      servir_orxata();
    }

    sem_signal(sem3); // totes les orxates servides!
  }
}

// arriben a l'orxateria i demanen orxata a cambrer
void client(){
  anar_a_la_orxateria();
  sem_wait(sem4); // demanar x orxata a cambrer
  sem_wait(sem5); // ?
  n_orxates = quantes_orxates();
  sem_signal(sem5); // DONE
  sem_signal(sem2); // ?
  sem_wait(sem3); // waits all orxates servides --> continue executing
  sem_signal(sem4); // DONE
  prendre_orxates();
}
// passa orxates al cambrer
void orxater(){
  int preparades = 0;
  while(true){
    preparar_orxata();
    sem_signal(sem1); // orxata done!
    sem_wait(sem6); // INC preparades
    preparades++;
    sem_signal(sem6);
  }
}


int main() {
   // orxater orxata DONE signal --> cambrer consumeix wait
  sem_create(sem1, 0, 1);
  // client ja ha fet petició (signal) --> cambrer pot servir (wait)
  sem_create(sem2, 0, 0);
  // cambrer ha servit totes orxates (signal) --> client pot continuar exexutant (wait)
  sem_create(sem3, 0, 0);
  // exlusió mútua; garanteix que només 1 client pugui fer peticions.
  sem_create(sem4, 0, 1);
  // exclusió mútua: n_orxates entre client/cambrer --> NO FA FALTA
  sem_create(sem5, 0, 1);
  // exclusió mútua: preparades només de l'orxater --> NO FA FALTA
  sem_create(sem6, 0, 1);
}
