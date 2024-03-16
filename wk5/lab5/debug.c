#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int main(void) {
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];

    // Read input from user
    printf("Enter the first string: ");
    fgets(str1, MAX_SIZE, stdin);

    printf("Enter the second string: ");
    fgets(str2, MAX_SIZE, stdin);

    // Check if the strings are equal
    if (strcmp(str1, str2) == 0) {
        printf("The strings are equal!\n");
    } else {
        printf("The strings are not equal!\n");
    }

    printf("The length of the first string is: %zu\n", strlen(str1));
    

    return 0;
}