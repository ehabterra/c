#include<stdio.h>

int test = 10;
    
int *testF() {
    return &test;
}

int main() {
    int num;
    float x = 0.655555f, y = 10.5f;
    long testCaseWithOtherParametersAndVariables = 0;

    printf("%f, %f, %ld\n", x, y, testCaseWithOtherParametersAndVariables);

    printf("Enter your age:");
    scanf("%d", &num);

    if (num < 18) {
        printf("You are not eligible to vote.\n");
    } else {
        printf("You can vote.\n");
    }

    printf("%d\n", test);

    return 0;
}