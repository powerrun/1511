#include <stdio.h>

int main() {
    char command;
    int return_val = scanf(" %c", &command);
    printf("return_val: %d\n", return_val);
    
    char c2;
    int return_val2 = scanf(" %c %c", &command, &c2);
    printf("return_val2: %d\n", return_val2);

    return 0;
}