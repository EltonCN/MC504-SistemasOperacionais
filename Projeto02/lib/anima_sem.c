#include "anima_sem.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdarg.h>

sem_t print_sem;

void anima_init()
{
    sem_init(&print_sem, 0, 1);
}

void anima_printf(const char *fmt, ...)
{
    sem_wait(&print_sem);

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    sem_post(&print_sem);
}


int anima_sem_wait(int id, Semaphore sem)
{
    anima_printf("%02d WT %02d\n", id, sem.id);

    int result = sem_wait(&sem.semaphore);

    anima_printf("%02d US %02d\n", id, sem.id);
    
    return result;

}

int anima_sem_post(int id, Semaphore sem)
{
    int result = sem_post(&sem.semaphore);

    anima_printf("%02d PT %02d\n", id, sem.id);
    
    return result;
}