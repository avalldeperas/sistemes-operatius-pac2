#include <stdio.h>
#include <semaphore.h>

#define W_TIMES 6
#define P_TIMES 4

int main(int argc, char *argv[])
{
    sem_t sem1;
    int semVal;

    sem_init(&sem1, 0, 10);

    for (int i = 0; i < W_TIMES; i++) sem_wait(&sem1);

    for (int i = 0; i < P_TIMES; i++) sem_post(&sem1);

    sem_getvalue(&sem1, &semVal);

    printf("Current semaphore value is %d\n", semVal);

    return 0;
}
