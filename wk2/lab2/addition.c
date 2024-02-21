#include <stdio.h>

int main(void) {
    int students = 0, tutors = 0;
    printf("Please enter the number of students and tutors:");
    scanf("%d %d", &students, &tutors);
    printf("%d + %d = %d\n", students, tutors, students + tutors);

    return 0;
}