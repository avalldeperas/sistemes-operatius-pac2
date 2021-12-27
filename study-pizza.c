#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>

int slices = 0;
Sem sem1 = 0;
Sem mutex = 1;
bool first = true, havePizza = false;

estudiants() {
  while(TRUE) { // mutex -
    wait(mutex);      // "Albert", "Fermi", "Marc"

    while( !havePizza ) {
      if( slices > 0 ) {              // eat pizza
        slices--;
        havePizza = true;
      } else {
        if( first ) {
          first = false;
          signal(sem1);               // ask for pizza
        }
        wait(mutex);                  // wait for pizza
      }

    } // end while !havePizza
    signal(mutex);
    Study();
    havePizza = false;
  }
}

lliurament_de_pizzes() {
  while(TRUE) {
    wait(sem1);                     // wait for student call
    makePizza();
    slices = S;
    first=true;
    havePizza = false;              // reset havePizza
    signal(mutex);                  // deliver pizza
  }
}


int main (int argc, char *argv[])
{
    
}
