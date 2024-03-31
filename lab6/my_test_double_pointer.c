// #include <stdio.h>

// int main() {
//     int num = 1;
//     int *p = &num;
//     int *pp = &p;

//     // printf("num = %p\n", &num);
//     // printf("p = %p\n", p);
//     // printf("pp = %p\n", pp);

//     printf("num = %d\n", num);
//     printf("p = %d\n", *p);
//     printf("pp = %d\n", **pp);
// }


#include <stdio.h>

int main() {
    int num = 1;
    int *p = &num;
    int **pp = &p;

    // printf("num = %p\n", &num);
    // printf("p = %p\n", p);
    // printf("pp = %p\n", pp);

    printf("num = %d\n", num);
    printf("p = %d\n", *p);
    printf("pp = %d\n", **pp);
}