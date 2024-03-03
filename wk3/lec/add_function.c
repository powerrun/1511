#include <stdio.h>

#define TARGET 7

int add_dice(int die_one, int die_two);
void comparison(int sum);


int main(void)
{
    int die_one;
    int die_two;
    int sum = 0;

    printf("Enter the two dice rolls: ");
    while (scanf("%d %d", &die_one, &die_two) == 2)
    {
        sum = add_dice(die_one, die_two);
        comparison(sum);
        printf("Enter the two dice rolls: ");
    }

    return 0;
}


int add_dice(int die_one, int die_two)
{
    return die_one + die_two;
}


void comparison(int sum)
{
    if (sum > TARGET)
    {
        printf("The sum of the dice is greater than the targer number!\n");
    }
    else if (sum < TARGET)
    {
        printf("The sum of the dice is less than the targer number!\n");
    } else 
    {
        printf("You have guessed the number!!\n");
    }
}