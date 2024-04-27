#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    int data;
};

int mixed(struct node *head);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = mixed(head);
    printf("%d\n", result);

    return 0;
}

// mixed should return 1 if list contains both even and odd numbers
// mixed should return 0 otherwise
int mixed(struct node *head) {
    struct node *cur = head;
    int even = 0;
    int odd = 0;

    while (cur != NULL) {
        if (cur->data % 2 == 0) {
            even++;
        } else {
            odd++;
        }
        cur = cur->next;
    }

    if (even > 0 && odd > 0) {
        return 1;

    } else {
        return 0;
    }
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof(struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}