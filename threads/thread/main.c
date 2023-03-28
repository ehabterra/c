#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 5

pthread_t th[THREAD_NUM];
//pthread_cond_t 

void *routine(void *args)
{
    int *x = (int *)args;

    printf("%d\tthread value: %d \n", *x, rand() % THREAD_NUM + 1);
    sleep(1);
    printf("%d\tslept for 2 seconds\n", *x);

    free(x);
    return 0;
}

int main()
{
    srand(time(NULL));

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));

        *a = i;

        if (pthread_create(&th[i], NULL, &routine, (void *)a))
        {
            printf("failed to create thread\n");
        }
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL))
        {
            printf("failed to join thread\n");
        }
    }

    return 0;
}