#include <stdio.h>
#include "clinkedlist.h"

int main()
{
    // create
    struct SinglyLinkedList list;
    int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = 10;
    int err = SinglyLinkedList_create(&list, vals, size);

    if (!err) {
        printf("Linked list:\n");
        SinglyLinkedList_display(&list);
    }
    else {
        log_error("Cannot create node", err);
    }

    // append
    err = SinglyLinkedList_append(&list, 30);

    if (!err) {
        printf("Append:\n");
        SinglyLinkedList_display(&list);
    }
    else {
        log_error("Cannot append node", err);
    }

    // insert
    err = SinglyLinkedList_insert(&list, 0, 40);

    if (!err) {
        printf("Insert:\n");
        SinglyLinkedList_display(&list);
    }
    else {
        log_error("Cannot insert node", err);
    }

    // delete
    err = SinglyLinkedList_delete(&list, 0);

    if (!err) {
        printf("Delete:\n");
        SinglyLinkedList_display(&list);
    }
    else {
        log_error("Cannot delete node", err);
    }

    // get
    int val;
    int idx = 1;
    err = SinglyLinkedList_get(&list, idx, &val);

    if (!err) {
        printf("Element at index %d is %d\n", idx, val);
    }
    else {
        log_error("Cannot get element", err);
    }

    // contains
    bool contains;
    val = 10;
    err = SinglyLinkedList_contains(&list, 10, &contains);

    if (!err) {
        printf("List contains value %d: %d\n", val, contains);
    }
    else {
        log_error("Cannot check if list contains value:", err);
    }

    // size
    err = SinglyLinkedList_size(&list, &size);

    if (!err) {
        printf("Size: %d\n", size);
    }
    else {
        log_error("Cannot determine size of the list", err);
    }

    // sum
    int sum;
    err = SinglyLinkedList_sum(&list, &sum);

    if (!err) {
        printf("Sum: %d\n", sum);
    }
    else {
        log_error("Cannot determine sum of values stored in the linked list", err);
    }

    // max
    int max;
    err = SinglyLinkedList_max(&list, &max);

    if (!err) {
        printf("Max: %d\n", max);
    }
    else {
        log_error("Cannot determine maximum value stored in the linked list", err);
    }

    // create
    struct SinglyLinkedList sorted_list;
    int sorted_vals[] = {3, 7, 9, 15, 20};
    size = 5;
    err = SinglyLinkedList_create(&sorted_list, sorted_vals, size);

    if (!err) {
        printf("Sorted list:\n");
        SinglyLinkedList_display(&sorted_list);
    }
    else {
        log_error("Cannot create linked list", err);
    }

    // sorted insert
    err = SinglyLinkedList_sorted_insert(&sorted_list, 21);

    if (!err) {
        printf("Sorted insert:\n");
        SinglyLinkedList_display(&sorted_list);
    }
    else {
        log_error("Cannot insert into sorted linked list", err);
    }

    // free
    SinglyLinkedList_free(&sorted_list);
    SinglyLinkedList_free(&list);
    return 0;
}
