//
// Created by Tomáš Petříček on 20.06.2022.
//

#ifndef CCODE_CLINKEDLIST_H
#define CCODE_CLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"

struct SingleLinkNode {
    int data;
    struct SingleLinkNode* next;
};

struct SinglyLinkedList {
    struct SingleLinkNode* head;
    int size;
};

// description: creates a node with given value on the heap
// time complexity: O(1)
int SingleLinkNode_create(struct SingleLinkNode** node, int val, struct SingleLinkNode* next)
{
    if (node==NULL) return NULL_POINTER;

    *node = (struct SingleLinkNode*) malloc(sizeof(struct SingleLinkNode));

    if (node==NULL) return BAD_ALLOCATION;

    (*node)->data = val;
    (*node)->next = next;
    return EXIT_SUCCESS;
}

// description: releases heap memory of each node of the linked list
// time complexity: O(n), where n is the size of the linked list
void SingleLinkNode_free(struct SingleLinkNode** node)
{
    free(*node);
    *node = NULL;
}

void SinglyLinkedList_free(struct SinglyLinkedList* list)
{
    struct SingleLinkNode* curr = list->head;
    struct SingleLinkNode* dealloc = NULL;

    while (curr) {
        dealloc = curr;
        curr = curr->next;
        SingleLinkNode_free(&dealloc);
    }
}

// description:
// - places a node with given value at the end of the linked list
// - returns code:
//    - EMPTY - if linked list is empty
//    - EXIT_FAILURE - if the new node cannot be created
//    - EXIT_SUCCESS - if new node was successfully appended to the linked list
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_append(struct SinglyLinkedList* list, int val)
{
    if (list->size==0) return EMPTY;

    // get to the end
    struct SingleLinkNode* curr = list->head;
    while (curr->next) curr = curr->next;

    // create last node
    struct SingleLinkNode* last = NULL;
    int err = SingleLinkNode_create(&last, val, NULL);

    if (err) {
        log_error("Cannot create node", err);
        return EXIT_FAILURE;
    }

    // append
    curr->next = last;
    list->size++;
    return EXIT_SUCCESS;
}

int SinglyLinkedList_create(struct SinglyLinkedList* list, int* arr, int size)
{
    if (size<1) return INVALID_ARGUMENT;

    list->size = 1;
    int err;
    struct SingleLinkNode* curr = NULL;

    err = SingleLinkNode_create(&curr, arr[0], NULL);

    if (err) {
        log_error("Cannot create node", err);
        return EXIT_FAILURE;
    }

    list->head = curr;

    for (int i = 1; i<size; i++) {
        err = SinglyLinkedList_append(list, arr[i]);

        if (err) {
            log_error("Cannot append node", err);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

// description:
// - retrieves size of the linked list
// - result is passed using size parameter of the function
// - returns code:
//    - EXIT_SUCCESS - if size of the linked list was determined successfully
// time complexity: O(1)
int SinglyLinkedList_size(struct SinglyLinkedList* list, int* size)
{
    *size = list->size;
    return EXIT_SUCCESS;
}

// description:
// - determines sum of all values stored inside a linked list
// - result is passed using parameter sum of the function
// - returns code:
//    - EMPTY - if linked list is empty
//    - EXIT_SUCCESS - if sum of the values stored in linked list was determined successfully
// time complexity: O(n)
int SinglyLinkedList_sum(struct SinglyLinkedList* list, int* sum)
{
    if (list->size==0) return EMPTY;

    struct SingleLinkNode* curr = list->head;
    *sum = 0;

    for (; curr; curr = curr->next)
        (*sum) += curr->data;

    return EXIT_SUCCESS;
}

// description: prints out value of each node in the linked list
// time complexity: O(n), where n is the size of the linked list
void SinglyLinkedList_display(struct SinglyLinkedList* list)
{
    if (list->size==0) return;

    struct SingleLinkNode* curr = list->head;

    for (; curr->next; curr = curr->next)
        printf("%d, ", curr->data);
    printf("%d\n", curr->data);
}

// description:
// - returns value of a node at given index
// - value at the index is passed using val parameter of the function
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_get(struct SinglyLinkedList* list, int idx, int* val)
{
    if (idx<0 || idx>list->size-1) return INDEX_OUT_OF_BOUNDS;
    if (list->size==0) return EMPTY;

    struct SingleLinkNode* curr = list->head;

    for (int i = 0; curr; i++, curr = curr->next)
        if (i==idx) {
            *val = curr->data;
            return EXIT_SUCCESS;
        }

    return INDEX_OUT_OF_BOUNDS;
}

// description:
// - places new node with the value at given index
// - returns code:
//    - INDEX_OUT_OF_BOUNDS - if index passed is lower than 0 or greater than size-1
//    - EMPTY - if linked list is empty
//    - EXIT_FAILURE - if the new node cannot be created
//    - EXIT_SUCCESS - if the value was successfully inserted
// time complexity: 0(n), where n is the size of the linked list
int SinglyLinkedList_insert(struct SinglyLinkedList* list, int idx, int val)
{
    if (idx<0 || idx>list->size-1) return INDEX_OUT_OF_BOUNDS;
    if (list->size==0) return EMPTY;

    int err;
    struct SingleLinkNode* curr = list->head;

    // insert head
    if (idx==0) {
        struct SingleLinkNode* node = NULL;
        err = SingleLinkNode_create(&node, val, curr);

        if (err) {
            log_error("Cannot create node", err);
            return EXIT_FAILURE;
        }

        list->head = node;
        list->size++;
        return EXIT_SUCCESS;
    }

    for (int i = 0; curr; i++, curr = curr->next)

        // insert node
        if (i+1==idx) {
            struct SingleLinkNode* node = NULL;
            err = SingleLinkNode_create(&node, val, curr->next);

            if (err) {
                log_error("Cannot create node", err);
                return EXIT_FAILURE;
            }

            curr->next = node;
            list->size++;
            return EXIT_SUCCESS;
        }

    return INDEX_OUT_OF_BOUNDS;
}

// description:
// - removes node at the given index from the linked list
// - returns code:
//    - INDEX_OUT_OF_BOUNDS - if index passed is lower than 0 or greater than size-1
//    - EMPTY - if linked list is empty
//    - EXIT_SUCCESS - if node was successfully deleted
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_delete(struct SinglyLinkedList* list, int idx)
{
    if (idx<0) return INDEX_OUT_OF_BOUNDS;
    if (list->size==0) return EMPTY;

    struct SingleLinkNode* curr = list->head;
    struct SingleLinkNode* remove = NULL;

    // delete head
    if (idx==0) {
        remove = list->head;
        list->head = curr->next;
        remove->next = NULL;

        SingleLinkNode_free(&remove);
        list->size--;
        return EXIT_SUCCESS;
    }

    for (int i = 0; curr; i++, curr = curr->next) {

        // delete node
        if (i+1==idx) {
            remove = curr->next;
            curr->next = remove->next;
            remove->next = NULL;

            SingleLinkNode_free(&remove);
            list->size--;
            return EXIT_SUCCESS;
        }
    }

    return INDEX_OUT_OF_BOUNDS;
}

// description:
// - stores value true in parameter contains if the linked list contains given value, false otherwise
// - result is passed using parameter contains of the function
// - returns code:
//    - EMPTY - if linked list is empty
//    - EXIT_SUCCESS - if function ran successfully
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_contains(struct SinglyLinkedList* list, int val, bool* contains)
{
    if (list->size==0) return EMPTY;

    *contains = false;
    struct SingleLinkNode* curr = list->head;

    for (; curr; curr = curr->next)
        if (curr->data==val) {
            *contains = true;
            return EXIT_SUCCESS;
        }

    return EXIT_SUCCESS;
}

// description:
// - find maximum value stored in the linked list
// - result is passed using max parameter of the function
// - returns code:
//    - EMPTY - if linked list is empty
//    - EXIT_SUCCESS - if max value stored in the linked list was determined successfully
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_max(struct SinglyLinkedList* list, int* max)
{
    if (list->size==0) return EMPTY;

    *max = list->head->data;
    struct SingleLinkNode* curr = list->head->next;

    for (; curr; curr = curr->next)
        if (*max<curr->data)
            *max = curr->data;

    return EXIT_SUCCESS;
}

// description:
// - inserts value in the linked list
// - linked list has to be sorted in ascending way
//    - EXIT_FAILURE - cannot create node to be inserted in the linked list
//    - EXIT_SUCCESS - if value was inserted successfully
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_sorted_insert(struct SinglyLinkedList* list, int val)
{
    // create new node
    struct SingleLinkNode* node;
    int err = SingleLinkNode_create(&node, val, NULL);

    if (err) {
        log_error("Cannot create node", err);
        return EXIT_FAILURE;
    }

    // increase list size
    list->size++;

    // empty list
    if (list->size==1) {
        list->head = node;
        return EXIT_SUCCESS;
    }

    struct SingleLinkNode* curr = list->head;

    // insert as head
    if (curr->data>val) {
        node->next = list->head;
        list->head = node;
        return EXIT_SUCCESS;
    }

    // move to correct position
    while (curr->next && curr->next->data<val)
        curr = curr->next;

    // insert
    node->next = curr->next;
    curr->next = node;
    return EXIT_SUCCESS;
}

// description: removes duplicates from sorted linked list
// time complexity: O(n), where n is the size of the linked list
void SinglyLinkedList_sorted_remove_duplicates(struct SinglyLinkedList* list)
{
    if (list->size<1) return;

    struct SingleLinkNode* curr = list->head;
    struct SingleLinkNode* next = list->head->next;

    while (next) {
        if (curr->data!=next->data) {
            curr = next;
            next = next->next;
        }
            // remove duplicate
        else {
            curr->next = next->next;
            SingleLinkNode_free(&next);
            next = curr->next;
        }
    }
}

// description: reverses order of nodes inside the link list
// time complexity: O(n), where n is the size of the linked list
void SinglyLinkedList_reverse(struct SinglyLinkedList* list)
{
    if (list->size<1) return;

    struct SingleLinkNode* curr = list->head;
    struct SingleLinkNode* temp = NULL;
    struct SingleLinkNode* head = NULL;

    while (curr) {
        temp = head;
        head = curr;
        curr = curr->next;
        head->next = temp;
    }

    list->head = head;
}

#endif //CCODE_CLINKEDLIST_H
