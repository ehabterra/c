#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "../../queue/queue.h"

#define THREAD_NUM 10
#define MAX 256
#define TASK_NUM 200

typedef struct _Task
{
    void (*function)(struct _Task *task);
    int a, b;
    int result;
} Task;

Task taskQueue[MAX];
int taskCount = 0;
Task finishedQueue[MAX];
int finishedCount = 0;

pthread_t th[THREAD_NUM];
pthread_mutex_t mutexQueue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexFinished = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condQueue = PTHREAD_COND_INITIALIZER;
pthread_cond_t condFinished = PTHREAD_COND_INITIALIZER;

void executeTask(Task *task)
{
    task->function(task);
}

void *startThread(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&mutexQueue);
        while (taskCount == 0)
        {
            printf("waiting..\n");
            pthread_cond_wait(&condQueue, &mutexQueue);
        }

        // Get task from the queue
        // Task task = taskQueue[0];
        // for (int i = 0; i < taskCount - 1; i++)
        // {
        //     taskQueue[i] = taskQueue[i + 1];
        // }
        // taskCount--;
        Task *task = (Task *)dequeue((void **)taskQueue, &taskCount);
        pthread_mutex_unlock(&mutexQueue);

        // Execute task
        executeTask(task);

        pthread_mutex_lock(&mutexFinished);
        // finishedQueue[finishedCount] = task;
        // finishedCount++;
        enqueue((void **)finishedQueue, &finishedCount, task);
        pthread_mutex_unlock(&mutexFinished);
        pthread_cond_signal(&condFinished);
    }
}

void submitTask(Task *task)
{
    pthread_mutex_lock(&mutexQueue);
    // taskQueue[taskCount] = task;
    // taskCount++;
    enqueue((void **)taskQueue, &taskCount, task);
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}

void sum(Task *task)
{
    usleep(500000);
    int sum = task->a + task->b;
    task->result = sum;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&th[i], NULL, &startThread, NULL))
        {
            perror("Failed to create thread");
        }
    }

    srand(time(NULL));
    for (int i = 0; i < TASK_NUM; i++)
    {
        Task *task = malloc(sizeof(Task));
        task->a = rand() % 100 + 1;
        task->b = rand() % 100 + 1;
        task->function = sum;

        submitTask(task);
    }

    printf("count = %d\n", taskCount);

    pthread_mutex_lock(&mutexFinished);
    while (1)
    {
        while (finishedCount == 0)
        {
            pthread_cond_wait(&condFinished, &mutexFinished);
        }
        // Task task = finishedQueue[0];
        // for (int i = 0; i < finishedCount - 1; i++)
        // {
        //     finishedQueue[i] = finishedQueue[i + 1];
        // }
        // finishedCount--;
        Task *task = (Task *)dequeue((void **)finishedQueue, &finishedCount);
        printf("input: %d, %d result: %d\n", task->a, task->b, task->result);
        free(task);
    }
    pthread_mutex_unlock(&mutexFinished);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL))
        {
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexQueue);
    pthread_mutex_destroy(&mutexFinished);
    pthread_cond_destroy(&condQueue);
    pthread_cond_destroy(&condFinished);
    return 0;
}