/**
 * @file anima_sem.h
 * @author EltonCN (elton.nascimento@students.ic.unicamp.br)
 * @brief Library to generate semaphores logs for reading in scenarios in Unity
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022 EltonCN
 * 
 */

#include <semaphore.h>

/**
 * @brief Semaphore struct. Contains its ID and the actual semaphore
 * 
 */
typedef struct Semaphore
{
    sem_t semaphore;
    int id;
} Semaphore;

/**
 * @brief Initiates the AnimaSemaphore library
 * 
 */
void anima_init();

/**
 * @brief 'printf' encapsulation with semaphore.
 * 
 */
void anima_printf(const char *fmt, ...);

/**
 * @brief Initializes a semaphore
 * 
 * @param sem Semaphore to initialize.
 * @param id ID of the semaphore.
 * @param value Start value for the semaphore
 */
void anima_sem_init(Semaphore *sem, int id, int value);

/**
 * @brief Semaphore wait
 * 
 * @param id Character waiting semaphore ID
 * @param sem Semaphore
 * @return int sem_wait return 
 */
int anima_sem_wait(int id, Semaphore *sem);

/**
 * @brief Semaphore post
 * 
 * @param id Character posting semaphore ID
 * @param sem Semaphore
 * @return int sem_post return 
 */
int anima_sem_post(int id, Semaphore *sem);