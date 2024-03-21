#include <stdio.h>

int main(void)
{
    int num, power, result = 1;
    char type;
    printf("Enter instruction: ");
    int return_val = scanf(" %c", &type);
    
    while (return_val == 1)
    {
        if (type == 's')
        {
            scanf("%d", &num);
            result = num * num;
        }
        else if (type == 'p')
        {
            scanf("%d %d", &num, &power);
            for (int i = 0; i < power; i++)
            {
                result = result * num;
            }
        }
        printf("%d", result);
        
        printf("\nEnter instruction: ");
        return_val = scanf(" %c", &type);
        result = 1;
    }

    if (return_val != 1) {
        printf("\n");
    }

    return 0;
}