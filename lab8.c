#include <stdio.h>

int main()
{
    char s[9];
    s[8] = 0;
    for (int i = 0; i < 8; i++)
    {
        scanf("%c", &s[i]);
    }
    for (int i = 0; i < 8; i++)
    {
        printf("%c %o\n", s[i], s[i]);
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j += 2)
        {
            s[i] |= (1 << j);
        }
        printf("%c %o\n", s[i], s[i]);
    }
}