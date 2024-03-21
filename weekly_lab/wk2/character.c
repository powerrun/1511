#include <stdio.h>

int main(void)
{
    char character;
    printf("Enter a character: ");
    scanf("%c", &character);

    if (character >= 'a' && character <= 'z')
    {
        character = character - 'a' + 'A';
        printf("It's a lower case, the new letter is: %c\n", character);
    }
    else if (character >= 'A' && character <= 'Z')
    {
        character = character + ;
        printf("It's an upper case\n");
    }
    else
    {
        printf("U did't enter a character\n");
    }

    return 0;
}