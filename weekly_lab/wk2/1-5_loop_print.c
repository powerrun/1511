#include <stdio.h>

int main(void)
{
    int x = 1, y = 0;
    while(y < 5)
    {
        while(x < 6)
        {
            printf("%d ", x);
            x++;
        }
        printf("\n");
        x = 1;
        y++;
    }

    return 0;
}