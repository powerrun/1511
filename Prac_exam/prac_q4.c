#include <stdio.h>

int main(void) {
    int nums[10000];
    int len = 0;
    while (scanf("%d", &nums[len]) == 1 && nums[len] != 0) {
        len++;
    }

    int i = 0;
    while (i < len) {
        printf("%d ", nums[i]);
        i += 2;
    }

    i = 1;
    while (i < len) {
        printf("%d ", nums[i]);
        i += 2;
    }

    printf("\n");
}
