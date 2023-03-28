#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define FILLING_THREAD_NUM 2
#define CONSUME_THREAD_NUM 6
#define FUELS 5
#define FILL 25
#define CONSUME 40

pthread_t thFilling[FILLING_THREAD_NUM];
pthread_t thConsume[CONSUME_THREAD_NUM];
pthread_mutexattr_t mutexFuelAttr;
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel = PTHREAD_COND_INITIALIZER;
pthread_attr_t attr;

int fuel = 0;

void *fill(void *args)
{
    for (int i = 0; i < FUELS; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        // Testing recursive lock
        pthread_mutex_lock(&mutexFuel);

        fuel += FILL;
        printf("%lu\tfilled fuel... %d\n", (long)pthread_self(), fuel);

        pthread_mutex_unlock(&mutexFuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast(&condFuel);
        usleep(1000000);
    }

    return 0;
}

void *consume(void *args)
{
    pthread_mutex_lock(&mutexFuel);

    while (fuel < CONSUME)
    {
        // printf("no fuel..\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
    }

    fuel -= CONSUME;
    printf("consumed fuel... %d\n", fuel);

    pthread_mutex_unlock(&mutexFuel);

    return 0;
}

void createThreads(pthread_t *th, const pthread_attr_t *__restrict__ _Nullable attr, int count, void *_Nullable routine(void *_Nullable), void *__restrict__ _Nullable args)
{

    for (int i = 0; i < count; i++)
    {
        if (pthread_create(th + i, attr, routine, args))
        {
            perror("failed to create thread");
        }
    }
}

void joinThreads(pthread_t *th, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (pthread_join(*(th + i), NULL))
        {
            perror("failed to join thread");
        }
    }
}

int main()
{
    pthread_attr_init(&attr);

    pthread_mutexattr_init(&mutexFuelAttr);

    pthread_mutexattr_settype(&mutexFuelAttr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutexFuel, &mutexFuelAttr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    createThreads(thFilling, &attr, FILLING_THREAD_NUM, &fill, NULL);
    createThreads(thConsume, &attr, CONSUME_THREAD_NUM, &consume, NULL);

    // joinThreads(thFilling, FILLING_THREAD_NUM);
    // joinThreads(thConsume, CONSUME_THREAD_NUM);

    // pthread_cond_destroy(&condFuel);
    // pthread_mutexattr_destroy(&mutexFuelAttr);
    // pthread_mutex_destroy(&mutexFuel);
    // pthread_attr_destroy(&attr);

    printf("--- main thread exit ---\n");
    pthread_exit(0);
    // return 0;
}
