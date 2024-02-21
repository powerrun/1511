#include <stdio.h>

int main(void) {
    int dividend, divisor;

    printf("Enter the dividend: ");
    scanf("%d", &dividend);
    printf("Enter the divisor: ");
    scanf("%d", &divisor);
    if (divisor == 0)
    {
        printf("Don't be silly!");
    }
    
    printf("%d divided by %d\n", dividend, divisor);

    printf("To the nearest integer: %d\n", dividend/divisor);
    printf("To 1 decimal place: %.1f\n", (float)dividend/divisor);
    printf("To 1 decimal place: %.5f\n", (float)dividend/divisor);
    printf("To 1 decimal place: %.20f\n", (float)dividend/divisor);

    return 0;
}