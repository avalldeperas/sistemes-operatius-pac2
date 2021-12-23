#include <stdio.h>
#include <semaphore.h>

#define W_TIMES 6
#define P_TIMES 4

int main(int argc, char *argv[])
{
    sem_t sem1;

    sem_init(&sem1, 0, 10); // create semaphore with initial value of 10

    for (int i = 0; i < W_TIMES; i++) sem_wait(&sem1);

    for (int i = 0; i < P_TIMES; i++) sem_post(&sem1);

    printf("Current semaphore value is %d\n", sem_getvalue(&sem1, &semVal));

    return 0;
}
