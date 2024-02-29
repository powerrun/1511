#include <stdio.h>

int main(void) 
{
    int num;
    char layers;
    printf("How many layers: ");
    scanf("%d", &num);
    printf("Please enter layers: ");

    // int i = 0;
    // while (i < num)
    // {
    //     j = 0;
    //     scanf("%c", &layers);
    //     while (j < num)
    //     {
    //         printf("%c", layers);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }

    for (int i = 0, j = 0; i < num; i++)
    {
        scanf(" %c", &layers);
        for (j = 0; j < num; j++)
        {
            printf("%c", layers);
        }        
        printf("\n");
    }

    return 0;
}
