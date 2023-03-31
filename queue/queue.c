#include <stdio.h>
#include "queue.h"

// #define MAX __INT_MAX__

// int queue[MAX];
// int count;

// int main()
// {
//     enqueue((void**)queue, &count, (void *)1);
//     enqueue((void**)queue, &count, (void *)2);
//     enqueue((void**)queue, &count, (void *)3);
//     enqueue((void**)queue, &count, (void *)4);
//     enqueue((void**)queue, &count, (void *)5);

//     while (count != 0)
//     {
//         printf("%ld ", (long)dequeue((void**)queue, &count));
//     }

//     return 0;
// }

void enqueue(void **q, int *c, void *item)
{
    *(q + *c) = item;
    (*c)++;
}

void *dequeue(void **q, int *c)
{
    void *item = *q;

    for (int i = 0; i < *c - 1; i++)
    {
        *(q + i) = *(q + i + 1);
    }
    (*c)--;

    return item;
}