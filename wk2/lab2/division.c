#include <stdio.h>

int main(void) {
    int dividend = 0, divisor = 0;
    double result;

    printf("Enter the dividend: ");
    scanf("%d", &dividend);
    printf("Enter the divisor: ");
    scanf("%d", &divisor);
    if (divisor == 0)
    {
        printf("Don't be silly!");
    }
    
    printf("%d divided by %d\n", dividend, divisor);


    result = (float)dividend / divisor;
    printf("To the nearest integer: %d\n", dividend/divisor);
    printf("To 1 decimal place: %.1lf\n", result);
    printf("To 5 decimal places: %.5lf\n", result);
    printf("To 20 decimal places: %.20lf\n", result);

    return 0;
}