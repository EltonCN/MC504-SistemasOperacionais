#include "../lib/anima_sem.c"
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

#define N 8
#define N_BONDS 8

volatile int h_in;
volatile int o_in;
volatile int age;


Semaphore h_entry;
Semaphore o_entry;
Semaphore state_lock;
Semaphore bond_entry;

void waitBarrier(int id)
{
    anima_printf("%02d WB\n", id);
}
 

void enterBarrier(int id)
{
    anima_printf("%02d ET\n", id);
}

void bond(int id)
{
    anima_printf("%02d BD\n", id);
}



void h_func(int id)
{
    for(int i = 0; i<N_BONDS/(N/4); i++)
    {
        waitBarrier(id);
        anima_sem_wait(id, &h_entry);
        enterBarrier(id);

        anima_sem_wait(id, &state_lock);
        h_in += 1;
        if(h_in == 2 && o_in == 1)
        {
            h_in = 0;
            o_in = 0;
            
            anima_sem_post(id, &bond_entry);
            anima_sem_post(id, &state_lock);
        }
        else
        {
            anima_sem_post(id, &state_lock);

            anima_sem_wait(id, &bond_entry);
            anima_sem_post(id, &bond_entry);
        }
        
        bond(id);

        anima_sem_post(id, &bond_entry);
        anima_sem_post(id, &h_entry);
    }
}

void o_func(int id)
{
    for(int i = 0; i<N_BONDS/(N/2); i++)
    {
        waitBarrier(id);
        anima_sem_wait(id, &o_entry);
        enterBarrier(id);

        anima_sem_wait(id, &state_lock);
        o_in += 1;
        if(h_in == 2 && o_in == 1)
        {
            h_in = 0;
            o_in = 0;
            
            anima_sem_post(id, &bond_entry);
            anima_sem_post(id, &state_lock);
        }
        else
        {
            anima_sem_post(id, &state_lock);
            anima_sem_wait(id, &bond_entry);
            anima_sem_post(id, &bond_entry);
        }
        
        bond(id);

        anima_sem_post(id, &o_entry);
    }
}

void thread_func(void* void_id)
{
    int id = (int) void_id;

    if(id < N/2)
    {
        h_func(id);
    }
    else
    {
        o_func(id);
    }
}

int main()
{
    printf("SCENARIO H2O %d\n", N);
    anima_init();

    anima_sem_init(&h_entry, 0, 2);
    anima_sem_init(&o_entry, 1, 1);
    anima_sem_init(&state_lock, 2, 1);
    anima_sem_init(&bond_entry, 3, 2);

    anima_sem_wait(-1, &bond_entry);
    anima_sem_wait(-1, &bond_entry);


    h_in = 0;
    o_in = 0;
    ciclo = 0;
   

    pthread_t thr[N];
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