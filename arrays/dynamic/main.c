#include <stdio.h>
#include <stdlib.h>

int main()
{
    int input = 0, size = 2, i = 0;
    int *numbers = malloc(sizeof(int) * size);

    do
    {
        printf("Enter (-1 to quite): ");
        scanf("%d", &input);

        if (input == -1)
        {
            break;
        }

        if (i == size)
        {
            size *= 2;
            numbers = realloc(numbers, size);
            printf("Array new size = %d\n", size);
        }

        numbers[i] = input;

        i++;
    } while (input != -1);

    for (int j = 0; j < i; j++)
        printf("numbers[%d] = %d\n", j, numbers[j]);

    // deallocate heap
    free(numbers);
    return 0;
}