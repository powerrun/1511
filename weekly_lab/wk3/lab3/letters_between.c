#include <stdio.h>

int main(void)
{
    char start, end;
    int distance;
    int reverse = 0;

    printf("Please enter starting letter: ");
    scanf(" %c", &start);
    printf("Please enter target letter: ");
    scanf(" %c", &end);

    if (start > end) {
        reverse = 1;
        distance = start - end;        
    } else {
        distance = end - start;
    }
    
    if (distance == 13) {
        reverse = 0;
    }
    else if (distance > 13) {
        reverse = 1;
    }

    while (reverse == 1 && start != end) 
    {
        if (start > 'Z' && start < 'a') {
            start = 'z';
        } else if (start < 'A') {
            start = 'Z';
        }
        printf("%c", start);
        start--;
    }

    while (reverse == 0 && start != end) 
    {
        if (start > 'Z' && start < 'a') {
            start = 'A';
        } else if (start > 'z') {
            start = 'a';
        }
        printf("%c", start);
        start++;
    }

    printf("%c\n", end);
    return 0;
}