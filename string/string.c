#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STR_LEN 2000

void strlwr(char *x)
{
    while (*x)
    {
        *x = tolower(*x);
        x++;
    }
}

void strupr(char *x)
{
    while (*x)
    {
        *x = toupper(*x);
        x++;
    }
}

int main()
{

    char mystr[34] = "I'm an example of function strchr";
    printf("%s\n", strchr(mystr, 's'));
    printf("%s\n", strstr(mystr, "fun"));

    char s1[10] = "Hello";
    char s2[10] = "World";
    strncat(s1, s2, 3);
    printf("Concatenation using strncat: %s\n", s1);

    char x[MAX_STR_LEN];

    printf("Please enter text to convert to lower:");
    fgets(x, MAX_STR_LEN, stdin);

    strlwr(x);

    printf("%sLen: %lu\n", x, strnlen(x, 30) - 1);

    return 0;
}
