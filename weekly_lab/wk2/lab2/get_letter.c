// Program which prints a letter depending on the user's request.
// by ...

#include <stdio.h>

int main(void) {

    char is_uppercase;
    printf("Uppercase: ");

    // TODO: scan is_uppercase
    scanf("%c", &is_uppercase);


    int index;
    printf("Index: ");

    // TODO: finish the program
    if (is_uppercase == 'y')
    {
        scanf("%d", &index);
        printf("The letter is %c\n", index + 'A');
    }
    else if (is_uppercase == 'n')
    {
        scanf("%d", &index);
        printf("The letter is %c\n", index + 'a');
    }

    return 0;
}