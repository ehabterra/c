#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#endif

#define THREAD_NUM 11
#define SEM_LOCK_NUM 5

#ifdef __APPLE__
dispatch_semaphore_t semaphore;
#else
sem_t semaphore;
#endif

void *routine(void *args)
{
#ifdef __APPLE__
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
#else
    sem_wait(&semaphore);
#endif
    
    sleep(1);
    printf("Hello from thread %d\n", *(int *)args);
#ifdef __APPLE__
    dispatch_semaphore_signal(semaphore);
#else
   sem_post(&semaphore);
#endif    
    free(args);

    return NULL;
}

int main()
{
    pthread_t th[THREAD_NUM];
#ifdef __APPLE__
    semaphore = dispatch_semaphore_create(SEM_LOCK_NUM);
#else
    sem_init(&semaphore, 0, SEM_LOCK_NUM);
#endif

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
        {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }

#ifndef __APPLE__
    sem_destroy(&semaphore);
#endif

    return 0;
}