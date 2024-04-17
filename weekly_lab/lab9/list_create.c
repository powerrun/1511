// Create a list from Command Line Arguments
// list_create.c
//
// A program which creates and prints a linked list 
// from command line arguments!

#include <stdio.h>
#include <stdlib.h>

struct node {
    char *data;
    struct node *next;
};

struct node *arguments_to_list(int argc, char *argv[]);
void free_list(struct node *head);
void print_list(struct node *head);

int main(int argc, char **argv) {
    struct node *head = arguments_to_list(argc, argv);
    print_list(head);
    free_list(head);

    return 0;
}

// Create linked list from argument values
struct node *arguments_to_list(int argc, char *argv[]) {
    struct node *head = NULL;
    struct node *current = NULL;

    for (int i = 1; i < argc; i++) {
        struct node *new_node = malloc(sizeof(struct node));

        new_node->data = argv[i];
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            current = new_node;
        }
        else {
            current->next = new_node;
            current = new_node;
        }
    }

    return head;
}

// Free the linked list from memory
void free_list(struct node *head) {
    while (head != NULL) {
        struct node *temp_current = head;
        head = head->next;
        free(temp_current);
    }
}

// Print the values of the linked list
void print_list(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("X\n");
}
