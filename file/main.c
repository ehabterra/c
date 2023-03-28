#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace(char *text, const char *old_text, const char *new_text)
{
    char output[200];

    char *t = strstr(text, old_text);
    if (t != NULL)
    {
        t += strlen(old_text);

        long new_len = strlen(new_text), t_len = strlen(t);

        printf("%s, len= %lu\n", t, t_len);

        for (int i = 0; i < new_len; i++)
        {
            output[i] = new_text[i];
        }
        for (int i = new_len; i < new_len + t_len; i++)
        {
            output[i] = t[i-new_len];
        }

        for (int i = 0; i < strlen(output); i++)
        {
            text[i] = output[i];
        }
        text[new_len + t_len] = '\0';
    }
}

int main()
{
    char c;

    char filename[200];

    printf("Enter file name: ");
    scanf("%s", filename);

    const char *home = getenv("HOME");
    if (home)
    {
        // Replace tilde at the beginning if exists with home env. variable
        replace(filename, "~", home);
    }

    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("can't open '%s' file\n", filename);
        exit(1);
    }

    while (1)
    {
        c = fgetc(fptr);
        if (c == EOF)
            break;

        printf("%c", c);
    }

    printf("\n");

    fclose(fptr);

    return 0;
}