// Written by YOUR-NAME (YOUR-ZID), on TODAYS-DATE

#include <stdio.h>

void increment(int *ptr);

int main() {
    int num;
    printf("Please enter a number: ");
    scanf("%d", &num);
    int *ptr = &num;

    printf("Before increment: %d\n", *ptr);
    increment(ptr);
    printf("After increment: %d\n", *ptr);

    return 0;
}

void increment(int *ptr) {
    (*ptr)++;
}