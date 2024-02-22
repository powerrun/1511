#include <stdio.h>

int main(void) {
    int year = 0;

    while (1)
    {
        printf("Enter year: ");
        scanf("%d", &year);

        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
            printf("%d is a leap year.\n", year);
        } else {
            printf("%d is not a leap year.\n", year);
        }
    }
    

    // if(year % 4 == 0)
    // {
    //     if (year % 100 == 0 && year % 400 == 0)
    //     {
    //     printf("%d is a leap year.\n", year);
    //     }
    // }
    // else if (year % 100 != 0)
    // {
    //     printf("%d is a leap year.\n", year);
    // }
    // else
    // {
    //     printf("%d is not a leap year.\n", year);
    // }


    return 0;
}