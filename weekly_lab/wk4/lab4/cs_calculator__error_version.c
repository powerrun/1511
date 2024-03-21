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
            for (int i =1, result = 1; i < power; i++)
            {
                result = result * num;
            }
        }
        printf("%d", result);
        // why the result calculated by for loop from line 20 to 23 is not printed out? answer me by commenting below
        // The result calculated by the for loop is not printed out because the result variable is redeclared in the for loop.
        // but I think it's just a initialization of the result variable, so when we jump out the loop, the final result should be printed out. right?
        // The result variable is redeclared in the for loop, so the result variable in the for loop is a different variable from the result variable outside the for loop.
        // but why, we just use 'for (int i =1, result = 1;...' to initialize the result variable, so when we jump out the loop, the final result should be printed out. right?
        // gosh! that's why! so how to solve this problem?
        // We can solve this problem by removing the redeclaration of the result variable in the for loop.
        // so the final code is:
        //
        // else if (type == 'p')
        // {
        //     scanf("%d %d", &num, &power);
        //     result = 1;
        //     for (int i = 1; i <= power; i++)
        //     {
        //         result = result * num;
        // }
        // right?
        // Yes, that's right.
        // thx!!!! so I should print the result before jump out the loop or avoid initializing the result variable in the for loop, right?
        // Yes, that's right.

        printf("\nEnter instruction: ");
        return_val = scanf(" %c", &type);
    }

    return 0;
}