#include <stdio.h>

int main(void) {
    int number;
    int scanf_return;

    printf("Enter a number");
    scanf_return = scanf("%d", &number);
    printf("The value of scanf_return is %d\n", scanf_return);

    if(number % 2 == 0) {
        printf("Even\n");
    } 
    else
    {
        printf("Odd\n");
    }
}