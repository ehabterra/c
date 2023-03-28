#include <stdio.h>

#define X 2
#define Y 3


int main()
{
    // int arr[X][Y] = {1, 2, 3, 4, 5, 6}; // Works also
    int arr[][Y] = {{1, 2, 3}, {4, 5, 6}};

    printf("sizeof(arr)=%lu, sizeof(arr[0])=%lu, sizeof(arr[0][0])=%lu\n", sizeof(arr), sizeof(arr[0]), sizeof(arr[0][0]));

    // for (int i = 0; i < X; i++)
    // {
    //     for (int j = 0; j < Y; j++)
    //     {
    //         printf("Enter value for disp[%d][%d]:", i, j);
    //         scanf("%d", &arr[i][j]);
    //     }
    // }

    for (int i = 0; i < X; i++)
    {
        printf("%p\n", arr[i]);

        for (int j = 0; j < Y; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}