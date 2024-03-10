#include <stdio.h>

int main(void)
{
    char n;
    int return_val = scanf("%c", &n);
    while (return_val == 1)
    {
        if (n != 'a' && n != 'e' && n != 'i' &&
            n != 'o' && n != 'u')
        {
            printf("%c", n);
        }
        return_val = scanf("%c", &n);
    }

    return 0;
}