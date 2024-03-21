#include <stdio.h>

int main(void)
{
    char c = ' ', inversion = ' ';
    int shift = 0, capital = 0;

    printf("Please enter a character: ");
    scanf("%c", &c);
    if (c >= 'A' && c <= 'Z')
        capital = 1;
    printf("Would you like to invert the case? y or n: ");
    scanf(" %c", &inversion);
    printf("By how much would you like to shift the character? ");
    scanf("%d", &shift);

    if (inversion == 'n')
    {
        if (capital == 0)
            c = (c - 'a' + shift) % 26 + 'a';
        else if (capital == 1)
            c = (c - 'A' + shift) % 26 + 'A';
    }
    else if (inversion == 'y')
    {
        if (capital == 0)
            c = (c - 'a' + shift) % 26 + 'A';
        else if (capital == 1)
            c = (c - 'A' + shift) % 26 + 'a';
    }

    printf("The character is %c!\n", c);

    return 0;
}

// Personally, this is a workable but more difficult version to understand
// #include <stdio.h>

// int main(void)
// {
//     char c = ' ', inversion = ' ';
//     int shift = 0, capital = 0;

//     printf("Please enter a character: ");
//     scanf("%c", &c);
//     if (c >= 'A' && c <= 'Z')
//         capital = 1;
//     printf("Would you like to invert the case? y or n: ");
//     scanf(" %c", &inversion);
//     printf("By how much would you like to shift the character? ");
//     scanf("%d", &shift);

//     // shift c from 0 and keep strings within the alphabet table
//     if (capital == 0)
//         c = (c - 'a' + shift) % 26;
//     else if (capital == 1)
//         c = (c - 'A' + shift) % 26;

//     // inversion or not
//     if (inversion == 'n')
//     {
//         if (capital == 0)
//             c = c + 'a';
//         else if (capital == 1)
//             c = c + 'A';
//     }
//     else if (inversion == 'y')
//     {
//         if (capital == 0)
//             c = c + 'A';
//         else if (capital == 1)
//             c = c + 'a';
//     }

//     printf("The character is %c!\n", c);

//     return 0;
// }