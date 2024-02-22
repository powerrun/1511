#include <stdio.h>

int main(void)
{
    char c = ' ', inversion = ' ';
    int shift = ' ';

    printf("Please enter a character: ");
    scanf("%c", &c);
    printf("Would you like to invert the case? y or n: ");
    scanf(" %c", &inversion);
    printf("By how much would you like to shift the character? ");
    scanf("%d", &shift);

    if (inversion == 'n')
    {
        c = c + shift;
    }
    else if (inversion == 'y')
    {
        if (c >= 'a' && c <= 'z')
            c = c - 'a' + 'A' + shift;
        else if (c >= 'A' && c <= 'Z')
            c = c - 'A' + 'a' + shift;
    }


    printf("The character is %c!\n", c);

    return 0;
}