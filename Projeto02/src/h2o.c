/**
 * @file h2o.c
 * @author EltonCN (elton.nascimento@students.ic.unicamp.br)
 * @brief Building H2O solution using semaphores. The output is printed for loading in Unity visualization scene.
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022 EltonCN
 * 
 */

#include "../lib/anima_sem.c"
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

#define N 8 //# Atoms (must be multiple of 2)
#define N_O_BOND 2 //# Bonds per O atom 

volatile int h_in; //H atoms inside the barrier (0, 1, 2)
volatile int o_in; //O atoms inside the barrier (0, 1)

Semaphore h_entry; //H entry barrier 
Semaphore o_entry; //O entry barrier 
Semaphore state_lock; //Global state lock
Semaphore bond_entry; //Bond area barrier

/**
 * @brief Waiting to be able to enter the barrier
 * 
 * Prints log output
 * 
 * @param id Thread id
 */
void waitBarrier(int id)
{
    anima_printf("%02d WB\n", id);
}
 
/**
 * @brief Entering the barrier
 * 
 * Prints log output
 * 
 * @param id Thread id 
 */
void enterBarrier(int id)
{
    anima_printf("%02d ET\n", id);
}

/**
 * @brief Bonding
 * 
 * Prints log output
 * 
 * @param id Thread id
 */
void bond(int id)
{
    anima_printf("%02d BD\n", id);
}


/**
 * @brief Function for H atoms threads
 * 
 * @param id Thread id
 */
void h_func(int id)
{
    for(int i = 0; i<2*N_O_BOND; i++)
    {
        //Entry barrier
        waitBarrier(id);
        anima_sem_wait(id, &h_entry);
        enterBarrier(id);

        //Bond barrier
        anima_sem_wait(id, &state_lock);
        h_in += 1;
        if(h_in == 2 && o_in == 1)
        {
            h_in = 0;
            o_in = 0;
            
            anima_sem_post(id, &bond_entry);
            anima_sem_post(id, &bond_entry);
        }
        else
        {
            anima_sem_post(id, &state_lock);
            anima_sem_wait(id, &bond_entry);
        }
        
        //Perform bond and exit
        bond(id);

        anima_sem_post(id, &h_entry);
    }
}

/**
 * @brief Function for O atoms threads
 * 
 * @param id Thread id
 */
void o_func(int id)
{
    for(int i = 0; i<N_O_BOND; i++)
    {
        //Entry barrier
        waitBarrier(id);
        anima_sem_wait(id, &o_entry);
        enterBarrier(id);

        //Bond barrier
        anima_sem_wait(id, &state_lock);
        o_in += 1;
        if(h_in == 2 && o_in == 1)
        {
            h_in = 0;
            o_in = 0;
            
            anima_sem_post(id, &bond_entry);
            anima_sem_post(id, &bond_entry);
            
        }
        else
        {
            anima_sem_post(id, &state_lock);
            anima_sem_wait(id, &bond_entry);
        }
        
        //Perform bond and exit

        bond(id);

        anima_sem_post(id, &state_lock);
        anima_sem_post(id, &o_entry);
    }
}

/**
 * @brief Thread function. Converts ID to int and selects if is an O or H atom.
 * 
 * @param void_id Thread id.
 */
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

    printf("%d TERMINOU\n", id);
}

int main()
{
    printf("SCENARIO H2O %d\n", N);
    anima_init();

    //Initialize the semaphores and variables
    anima_sem_init(&h_entry, 0, 2);
    anima_sem_init(&o_entry, 1, 1);
    anima_sem_init(&state_lock, 2, 1);
    anima_sem_init(&bond_entry, 3, 2);

    anima_sem_wait(-1, &bond_entry);
    anima_sem_wait(-1, &bond_entry);


    h_in = 0;
    o_in = 0;   

    //Start threads
    pthread_t thr[N];
    for (int i = 0; i < N; i++)
    {
        pthread_create(&thr[i], NULL, thread_func, (void*) i);
    }

    //Wait for threads end
    for (int i = 0; i < N; i++)
    {
        pthread_join(thr[i], NULL);
    }

    return 0;
}