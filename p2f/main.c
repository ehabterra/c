#include<stdio.h>

int sum(int a, int b) {
    return a + b;
}

int main() {
    int (*p2f)(int,int) = sum;

    int c = p2f(5,6);
    int d = sum(5,6);

    printf("p2f = %d\n", c);
    printf("sum = %d\n", d);

    return 0;
}