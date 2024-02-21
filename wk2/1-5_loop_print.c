#include <stdio.h>

int main(void)
{
    int x = 0, y = 0;
    while(y < 5)
    {
        while(x < 5)
        {
            printf("%d ", x);
            x++;
        }
        printf("\n");
        x = 0;
        y++;
    }

    return 0;
}