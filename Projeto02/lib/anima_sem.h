#include <semaphore.h>


typedef struct Semaphore
{
    sem_t semaphore;
    int id;
} Semaphore;

void anima_init();
void anima_printf(const char *fmt, ...);
int anima_sem_wait(int id, Semaphore sem);
int anima_sem_post(int id, Semaphore sem);