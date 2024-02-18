#include <stdio.h>

int main(void) {
    // declare a variable of type int
    // first state what type of variable - int, double or char
    int number = 13;

    // If I want to print out a value that is inside a variable,
    // I will use a format specifier ---- %d (int)
    printf("The variable number is %d \n", number);
    printf("%d\n", number);
    
    //
    int number_two =42;
    printf("2nd variable number is %d\n", number_two);

    // declare a char and initialise it
    char character = 's';
    printf("the variable character is %d\n", character);
    printf("The character is %c\n", character);

    //
    double decimal = 5165.4852;
    printf("%.4lf\n", decimal);
    printf("%.4f\n", decimal);

    //Scan
    int answer = 0;
    int answer_2 = 0;
    printf("Type two number to scan in: ");
    scanf("%d %d", &answer, &answer_2);
    printf("%d, %d\n", answer, answer_2);

    // change decimal
    printf("type a decimal to scan:");
    scanf("%lf", &decimal);
    //The reason why there's no need to add a space before %lf in the scanf function, unlike the previous example with %c, is because %lf automatically skips any leading whitespace characters, including newline characters. This means that if the user had previously entered input that included a newline character (like pressing enter), scanf with %lf would ignore this newline character and wait for the user's actual input.
    printf("%.4lf\n", decimal);

    //change character
    char hoho;
    printf("type something: ");
    scanf(" %c", &hoho);
    // The space before %c is a crucial part of this code. Without it, if the user had previously entered input that included a newline character (like pressing enter), scanf would consume this newline character as the next input, without waiting for the user to type anything. By adding a space before %c, scanf is instructed to skip any leading whitespace characters, including newline characters, ensuring that it waits for the user's actual input.
    printf("%c\n", hoho);
    

    /* 我得到了下面的结果，
    "The variable number is 13 
    13
    2nd variable number is 42
    the variable character is 115
    The character is s
    5165.4852
    5165.4852
    Type two number to scan in: 21 2
    21, 2
    type a decimal to scan:12.21
    12.2100
    type something:"
    
    
    每一次type something: 出现后，我都来不及输入任何内容，程序就直接结束了。
    
    
    但是如果我注释掉前面的代码，仅保留
    char hoho;
    printf("type something: ");
    scanf("%c", &hoho);
    printf("%c\n", hoho);
    这一段代码，我就可以输入内容了。这是为什么呢？

    */

    return 0;
}