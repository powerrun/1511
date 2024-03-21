#include <stdio.h>

int main(void)
{
    double dividend = 0, divisor = 0, result = 0;

    printf("Enter the dividend: ");
    scanf("%lf", &dividend);
    printf("Enter the divisor: ");
    scanf("%lf", &divisor);
    
    if (divisor != 0)
    {
        printf("%.0lf divided by %.0lf\n", dividend, divisor);

        result = dividend / divisor;
        printf("To the nearest integer: %.0lf\n", result);
        printf("To 1 decimal place: %.1lf\n", result);
        printf("To 5 decimal places: %.5lf\n", result);
        printf("To 20 decimal places: %.20lf\n", result);
    }
    else
    {
        printf("Don't be silly!\n");
    }

    return 0;
}