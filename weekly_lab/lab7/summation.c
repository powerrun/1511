#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    
    // i start from 1 cause the first argument is the program's name
    for (int i = 1; i < argc; i++) {
        // convert each number in the char to an integer and calculate the sum
        sum += atoi(argv[i]);
    }

    printf("Sum: %d\n", sum);
    return 0;
}