#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>

int slices = 0;
/* Codi a omplir */
Sem mutex = 1;
bool first = true;
bool havePizza = false;

estudiants() {
  while(TRUE) {
    wait(mutex);
    while( !havePizza ) {
      if( slices > 0 ) {
        slices--;
        havePizza = true;
      } else {
        if( first ) {
          /* Codi a omplir */
          first = false;
        }
        /* Codi a omplir */
      }
    } // end while !havePizza
    /* Codi a omplir */
    Study();
    havePizza = false;
  }
}

lliurament_de_pizzes() {
  while(TRUE) {
    /* Codi a omplir */
    makePizza();
    slices = S;
    first=true;
    /* Codi a omplir*/
    signal(mutex);
  }
}


int main (int argc, char *argv[])
{

}
