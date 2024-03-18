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

// bug code

// #include <stdio.h>
// #include <string.h>

// #define MAX_SIZE 1025

// int main(void) {
//     char word[MAX_SIZE];

//     printf("Input word: ");
//     fgets(word, MAX_SIZE, stdin);

//     printf("Word square is:\n");
//     for (int i = strlen(word); i > 1; i--) {

//         printf("%s", word);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>

// #define MAX_SIZE 1025

// int main(void) {
//     char word[MAX_SIZE];
//     char word_print;

//     printf("Input word: ");
//     fgets(word, MAX_SIZE, stdin);

//     printf("Word square is: \n");
//     for (int i = strlen(word); i > 2; i--) {
//         for (int j = 0; j < strlen(word)-1; j++) {
//             printf("%c", word[j]);
//         }
//         printf("\n");
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>

// #define MAX_LENGTH 1025 // Maximum length of input word, including null terminator

// int main() {
//     char word[MAX_LENGTH];

//     // Prompt user to enter a word
//     printf("Input word: ");

//     // Read input using fgets
//     if (fgets(word, sizeof(word), stdin) == NULL) {
//         printf("Error reading input.\n");
//         return 1;
//     }

//     // Remove newline character from input if present
//     size_t len = strlen(word);
//     // if (len > 0 && word[len - 1] == '\n')
//     //     word[len - 1] = '';

//     // Print the word square
//     printf("Word square is:\n");
//     for (size_t i = 0; i < len - 3; i++) {
//         printf("%s\n", word);
//     }

//     return 0;
// }
