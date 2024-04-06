#include <stdio.h>
#include <string.h>

#define MAX_SIZE 128

void remove_newline_char(char *str);

int main() {
    char search_term[MAX_SIZE];
    char search_list[MAX_SIZE];
    int count = 0;

    printf("Enter the search term: ");
    fgets(search_term, MAX_SIZE, stdin);
    remove_newline_char(search_term);

    printf("Enter the list of strings:\n");
    while (fgets(search_list, MAX_SIZE, stdin) != NULL) {
        remove_newline_char(search_list);
        
        if (strcmp(search_list, search_term) == 0) {
            count++;
        }
    }

    printf("There was %d occurrence(s) of the search term in the input.\n", count);

    return 0;
}

void remove_newline_char(char *str) {
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}