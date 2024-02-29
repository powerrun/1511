#include <stdio.h>

int main(void) 
{
    int counter = 0, num = 0;
    printf("Enter number: ");
    scanf("%d", &num);

    while (num > 0 && counter <= num)
    {
        printf("%d\n", counter);
        counter++;
    }

    while (num < 0 && counter >= num)
    {
        printf("%d\n", counter);
        counter--;
    }

    return 0;
}
