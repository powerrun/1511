// #include <stdio.h>
// #include <stdlib.h>

// int main(int a, char *b[])
// {
//     // int sum = 0;
//     // for (int i = 0; i < a; i++)
//     // {
//     //     printf("a = %d, b[%d] = %s\n", a, i, b[i]);
//     //     sum += atoi(b[i]);
//     //     printf("sum = %d\n", sum);
//     // }

//     printf("size of sizeof(int) = %lu\n", sizeof(int));

//     return 0;
// }







// Goal: create a linked list 
// with elements 11, 8 and 7
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *create_node(int data, struct node *next);
void print_list(struct node *head);
struct node *insert_at_tail(int data, struct node *head);

int main(void) {
    // struct node *head = malloc(sizeof(struct node));
    // head->data = 7; // (*head).data = 7
    // head->next = NULL;

    // struct node *head2 = malloc(sizeof(struct node));
    // head2->data = 8;
    // head2->next = head;

    // // TODO: put it in function!
    // struct node *head3 = malloc (sizeof(struct node));
    // head3->data = 11;
    // head3->next = head2; // link node with 11 to node with 8

    struct node *head = create_node(7, NULL);
    head = create_node(8, head);
    head = create_node(11, head);

    // traverse the list and print out the list
    print_list(head);

    insert_at_tail(6, head);

    // check that the 6 has been aded to the tail of list
    print_list(head);

    return 0;
}

struct node *create_node(int data, struct node *next) {
    struct node *head = malloc(sizeof(struct node));
    head->data = data;
    head->next = next;

    // return that node
    return head;
}


void print_list(struct node *head) {
    struct node *current = head;
    while (current != NULL) { // while we have not reached the end of the list
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// insert a given value at the tail of a given list
struct node *insert_at_tail(int data, struct node *head) {
    // TODO empty list case
    
    struct node *new_node = create_node(data, NULL);
    
    struct node *current = head;
    // loop the current pointer until ????
    while (current->next != NULL) {
        current = current->next;
    }
    // at this pt, current->next == NULL
    // which means current is pointing at the last node
    current->next = new_node;
    return head;
}