#include <stdio.h>
#include "clinkedlist.h"

int main()
{
    // create
    struct SingleLinkNode* head = NULL;
    int err = SinglyLinkedList_create(&head, 10, NULL);

    if (!err) {
        printf("Head node:\n");
        SinglyLinkedList_display(head);
    }
    else {
        log_error("Cannot create node", err);
    }

    // append
    err = SinglyLinkedList_append(head, 30);

    if (!err) {
        printf("Append:\n");
        SinglyLinkedList_display(head);
    }
    else {
        log_error("Cannot append node", err);
    }

    // insert
    err = SinglyLinkedList_insert(&head, 0, 40);

    if (!err) {
        printf("Insert:\n");
        SinglyLinkedList_display(head);
    }
    else {
        log_error("Cannot insert node", err);
    }

    // delete
    err = SinglyLinkedList_delete(&head, 0);

    if (!err) {
        printf("Delete:\n");
        SinglyLinkedList_display(head);
    }
    else {
        log_error("Cannot delete node", err);
    }

    // get
    int val;
    int idx = 1;
    err = SinglyLinkedList_get(head, idx, &val);

    if (!err) {
        printf("Element at index %d is %d\n", idx, val);
    }
    else {
        log_error("Cannot get element", err);
    }

    // contains
    bool contains;
    val = 10;
    err = SinglyLinkedList_contains(head, 10, &contains);

    if (!err) {
        printf("List contains value %d: %d\n", val, contains);
    }
    else {
        log_error("Cannot check if list contains value:", err);
    }

    // size
    int size;
    err = SinglyLinkedList_size(head, &size);

    if (!err) {
        printf("Size: %d\n", size);
    }
    else {
        log_error("Cannot determine size of the list", err);
    }

    // sum
    int sum;
    err = SinglyLinkedList_sum(head, &sum);

    if (!err) {
        printf("Sum: %d\n", sum);
    }
    else {
        log_error("Cannot determine sum of values stored in the linked list", err);
    }

    // max
    int max;
    err = SinglyLinkedList_max(head, &max);

    if (!err) {
        printf("Max: %d", max);
    } else {
        log_error("Cannot determine maximum value stored in the linked list", err);
    }

    // free
    SinglyLinkedList_free(&head);
    return 0;
}
