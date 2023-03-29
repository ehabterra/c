#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#endif

#ifdef __APPLE__
dispatch_semaphore_t sem_full;
dispatch_semaphore_t sem_empty;
#else
sem_t sem_full;
sem_t sem_empty;
#endif

#define PROD_THREAD_NUM 1
#define CONS_THREAD_NUM 1
#define BUFFER 10

pthread_t prod_th[PROD_THREAD_NUM];
pthread_t cons_th[CONS_THREAD_NUM];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int buffer[BUFFER];
int count = 0;

void *producer(void *args)
{
    while (1)
    {
#ifdef __APPLE__
        dispatch_semaphore_wait(sem_empty, DISPATCH_TIME_FOREVER);
#else
        sem_wait(&sem_empty);
#endif
        pthread_mutex_lock(&mutex);
        int x = rand() % 100 + 1;
        buffer[count] = x;
        count++;
        // printf("Produce %d count: %d\n", x, count);
        pthread_mutex_unlock(&mutex);
#ifdef __APPLE__
        dispatch_semaphore_signal(sem_full);
#else
        sem_post(&sem_full);
#endif
    }
    return NULL;
}

void *consumer(void *args)
{
    while (1)
    {
#ifdef __APPLE__
        dispatch_semaphore_wait(sem_full, DISPATCH_TIME_FOREVER);
#else
        sem_wait(&sem_full);
#endif
        pthread_mutex_lock(&mutex);
        int x = buffer[--count];
        int c = count;
        pthread_mutex_unlock(&mutex);

        printf("Got %d count: %d\n", x, c);
#ifdef __APPLE__
        dispatch_semaphore_signal(sem_empty);
#else
        sem_post(&sem_empty);
#endif
    }
    return NULL;
}

int main()
{
    srand(time(NULL));

#ifdef __APPLE__
    sem_empty = dispatch_semaphore_create(BUFFER);
    sem_full = dispatch_semaphore_create(0);
#else
    sem_init(&sem_empty, 0, BUFFER);
    sem_init(&sem_full, 0, 0);
#endif

    // Create threads
    for (int i = 0; i < PROD_THREAD_NUM; i++)
    {
        if (pthread_create(&prod_th[i], NULL, &producer, NULL))
        {
            perror("failed to create producer thread");
        }
    }

    for (int i = 0; i < CONS_THREAD_NUM; i++)
    {
        if (pthread_create(&cons_th[i], NULL, &consumer, NULL))
        {
            perror("failed to create consumer thread");
        }
    }

    // Join
    for (int i = 0; i < PROD_THREAD_NUM; i++)
    {
        if (pthread_join(prod_th[i], NULL))
        {
            perror("failed to join producer thread");
        }
    }

    for (int i = 0; i < CONS_THREAD_NUM; i++)
    {
        if (pthread_join(cons_th[i], NULL))
        {
            perror("failed to join consumer thread");
        }
    }

    pthread_mutex_destroy(&mutex);

#ifndef __APPLE__
    sem_destroy(&sem_full);
    sem_destroy(&sem_empty);
#endif

    return 0;
}