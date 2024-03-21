#include <stdio.h>

int tea_drinking[7] = {3, 2, 1, 2, 1, 3, 5};

int main(void)
{
    int i = 0;
    while (i < 7){
        printf("%d ", tea_drinking[i]);
        i++;
    }

    return 0;
}