#include <stdio.h>
#include "clinkedlist.h"

int main()
{
    // create
    struct Node* head = NULL;
    int err = Node_create(&head, 10, NULL);

    if (!err) {
        printf("Head node:\n");
        Node_display(head);
    }
    else {
        log_error("Cannot create node", err);
    }

    // append
    err = Node_append(head, 30);

    if (!err) {
        printf("Append:\n");
        Node_display(head);
    }
    else {
        log_error("Cannot append node", err);
    }

    // insert
    err = Node_insert(&head, 0, 40);

    if (!err) {
        printf("Insert:\n");
        Node_display(head);
    }
    else {
        log_error("Cannot insert node", err);
    }

    // delete
    err = Node_delete(&head, 0);

    if (!err) {
        printf("Delete:\n");
        Node_display(head);
    }
    else {
        log_error("Cannot delete node", err);
    }

    // get
    int val;
    int idx = 1;
    err = Node_get(head, idx, &val);

    if (!err) {
        printf("Element at index %d is %d\n", idx, val);
    }
    else {
        log_error("Cannot get element", err);
    }

    // contains
    bool contains;
    val = 10;
    err = Node_contains(head, 10, &contains);

    if (!err) {
        printf("List contains value %d: %d\n", val, contains);
    }
    else {
        log_error("Cannot check if list contains value:", err);
    }

    int size;
    err = Node_size(head, &size);

    if (!err) {
        printf("Linked list size is: %d", size);
    }
    else {
        log_error("Cannot determine size of the list", err);
    }

    // free
    Node_free(&head);
    return 0;
}
