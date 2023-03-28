#include <stdio.h>

int get_value()
{
    // add value to register from memory: `movl -4(%rbp), %eax`
    int value = 10; 

    asm("movl %0, %%eax"
    :               // Output
    :"m" (value)    // Input
    );
}

int main()
{
    printf("get value: %d\n", get_value());
}
