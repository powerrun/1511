#include <stdio.h>

#define NUM_ROWS 4
#define MAX_COLS 100

// Return the number of rows that add up to 0
int count_neutral_rows(int size, int array[NUM_ROWS][MAX_COLS]) {
    int result = 0;
    for (int i = 0; i < NUM_ROWS; i++) {
        int sum = 0;
        for (int j = 0; j < size; j++) {
            sum += array[i][j];
        }
        if (sum == 0) {
            result += 1;
        }
    }
    return result;
}

// This is a simple main function which could be used
// to test your count_neutral_rows function.
// It will not be marked.
// Only your count_neutral_rows function will be marked.


int main(void) {
    int test_array[NUM_ROWS][MAX_COLS] = {
        {1, 2, 3, -3, 0},
        {1, 2, 3, -3, -3},
        {1, 4, 3, -3, -2},
        {1, -2, 3, -3, -3}
    };

    int result = count_neutral_rows(MAX_COLS, test_array);
    printf("%d\n", result);

    return 0;
}