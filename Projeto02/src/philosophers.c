#include "../lib/anima_sem.c"
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

#define N 5
#define pseudo_max 100

Semaphore forks[N];
volatile int eated = 0;
volatile int ready = 0;

void think(int id)
{
    anima_printf("%02d TH\n", id);
}

void eat(int id)
{
    anima_printf("%02d ET\n", id);
    eated += 1;
}

void thread_func(void* void_id)
{
    int id = (int) void_id;

    if(id == 4)
    {
        ready = 1;
    }

    while(ready == 0)
    {

    }
    

    while(eated < pseudo_max)
    {
        think(id);

        if(id % 2 == 0)
        {
            anima_sem_wait(id, &forks[id]);
            anima_sem_wait(id, &forks[(id+1)%N]);
        }
        else
        {
            anima_sem_wait(id, &forks[(id+1)%N]);
            anima_sem_wait(id, &forks[id]);
        }

        eat(id);

        anima_sem_post(id, &forks[(id+1)%N]);
        anima_sem_post(id, &forks[(id)%N]);
    }
    
    

}

void main()
{
    pthread_t thr[N];
    anima_init();

    printf("SCENARIO PHILOSOPHERS 5\n");

    for (int i = 0; i < N; i++)
    {
        sem_t *sem = &forks[i].semaphore;
        forks[i].id = i;
        sem_init(sem, 0, 1);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_create(&thr[i], NULL, thread_func, (void*) i);
    }
    

    for (int i = 0; i < N; i++)
    {
        pthread_join(thr[i], NULL);
    }
    

    return 0;
}