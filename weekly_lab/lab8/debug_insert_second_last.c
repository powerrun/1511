#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int data;
};

#define MAX_INIT_LIST_LEN 100

struct node *insert_second_last(int value, struct node *head);
struct node *array_to_list(int len, int array[]);
void print_list(struct node *head);
int get_list_length(struct node *head);

// DO NOT EDIT MAIN
int main(void) {
    // Need to read in a number of ints into an array
    printf("How many numbers in initial list?: ");
    int list_size = 0;
    scanf("%d", &list_size);
    int initial_elems[MAX_INIT_LIST_LEN] = {0};
    int n_read = 0;
    while (n_read < list_size && scanf("%d", &initial_elems[n_read])) {
        n_read++;
    }

    // create linked list from first set of inputs
    struct node *head = NULL;
    if (n_read > 0) {
        // list has elements
        head = array_to_list(n_read, initial_elems);
    }

    printf("Enter the value to insert: ");
    int value;
    scanf("%d", &value);

    struct node *new_head = insert_second_last(value, head);
    print_list(new_head);

    return 0;
}

// DO NOT EDIT
// Gets the length of a linked lists
int get_list_length(struct node *head) {
    int length = 0;
    struct node *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// Insert a new node containing a new value at the second last position 
// of the linked list.
// The head of the new list is returned.
struct node *insert_second_last(int new_data, struct node *head) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    }
    else if (head->next == NULL) {
        new_node->next = head;
        return new_node;
    }

    struct node *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;

    return head;
}

// DO NOT EDIT
// create linked list from array of strings
struct node *array_to_list(int len, int array[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        n->next = head;
        n->data = array[i];
        head = n;
        i -= 1;
    }   
    return head;
}

// DO NOT EDIT
// print linked list
void print_list(struct node *head) {
    printf("[");    
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}
