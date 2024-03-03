#include <stdio.h>

struct coordinates
{
    int x;
    int y;
};

int main(void)
{
    int counter = 0;
    struct coordinates pair;
    printf("Enter size: ");
    scanf("%d", &counter);

    for (pair.x = 0; pair.x < counter; pair.x++)
    {
        for (pair.y = 0; pair.y < counter; pair.y++)
        {
            printf("(%d, %d) ", pair.x, pair.y);
        }
        if (pair.y >= counter)
        {
            printf("\n");
        }
    }
    return 0;
}