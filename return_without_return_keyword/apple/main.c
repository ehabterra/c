#include <stdio.h>

int get_value()
{
    // this variable will be in assembly -8(%rbp) and return value will 
    // be -4(%rbp). Thus, moved to the previous stack variable by adding 
    // 1 to the pointer to be able to get return value and replace it.
    int value; 

    *(&value + 1) = 10; // similar to `asm("movl $10, -4(%rbp)");`
}

int main()
{

    printf("get value: %d\n", get_value());
}
