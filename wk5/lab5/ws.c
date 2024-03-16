#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1025

int main(void) {
    char word[MAX_SIZE];

    printf("Input word: ");
    fgets(word, MAX_SIZE, stdin);

    printf("Word square is:\n");
    for (int i = strlen(word); i > 1; i--) {

        printf("%s", word);
    }

    return 0;
}