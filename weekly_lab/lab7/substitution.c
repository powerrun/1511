#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LENGTH 26

void substitution_cipher(char encryption_rule[LENGTH], int plaintext);

int main(int argc, char *argv[]) {
    int plaintext;
    char encryption_rule[LENGTH];

    // initialize the encryption rule
    for (int i = 0; i < LENGTH; i++)
    {
        encryption_rule[i] = argv[1][i];
    }

    printf("Enter text:\n");

    // Read the plaintext
    while ((plaintext = getchar()) != EOF)
    {
        if (isalpha(plaintext))
        {
            // Encrypt the plaintext
            substitution_cipher(encryption_rule, plaintext);
        }
        else
        {
            // Print it directly as it is not an alphabet
            printf("%c", plaintext);
        }
    }

    return 0;
}

void substitution_cipher(char encryption_rule[LENGTH], int plaintext) {
    char ciphertext;
    if (islower(plaintext))
    {
        ciphertext = encryption_rule[plaintext - 'a'];
    }
    else
    {   
        // Convert to uppercase aftr encrypt uppercase plaintext
        ciphertext = toupper(encryption_rule[plaintext - 'A']);
    }
    
    printf("%c", ciphertext);
}
