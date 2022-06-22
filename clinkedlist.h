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

// description: creates a node with given value on the heap
// time complexity: O(1)
int SinglyLinkedList_create(struct SingleLinkNode** node, int val, struct SingleLinkNode* next)
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
void SinglyLinkedList_free(struct SingleLinkNode** head)
{
    struct SingleLinkNode* curr = *head;
    struct SingleLinkNode* dealloc = NULL;

    while (curr) {
        dealloc = curr;
        curr = curr->next;
        free(dealloc);
    }

    *head = NULL;
}

// description:
// - counts number of nodes in the linked list
// - result is passed using size parameter of the function
// - returns code:
//    - NULL_POINTER - if pointer to head node has value NULL
//    - EXIT_SUCCESS - if size of the linked list was determined successfully
// time complexity: O(n)
int SinglyLinkedList_size(struct SingleLinkNode* head, int* size)
{
    if (!head) return NULL_POINTER;

    struct SingleLinkNode* curr = head;
    *size = 1;

    while (curr->next) {
        (*size)++;
        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

// description:
// - determines sum of all values stored inside a linked list
// - result is passed using parameter sum of the function
// - returns code:
//    - NULL_POINTER - if pointer to head node has value NULL
//    - EXIT_SUCCESS - if sum of the values stored in linked list was determined successfully
// time complexity: O(n)
int SinglyLinkedList_sum(struct SingleLinkNode* head, int *sum) {
    if (!head) return NULL_POINTER;

    struct SingleLinkNode* curr = head;
    *sum = 0;

    while (curr) {
        (*sum)+=curr->data;
        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

// description: prints out value of each node in the linked list
// time complexity: O(n), where n is the size of the linked list
void SinglyLinkedList_display(struct SingleLinkNode* node)
{
    struct SingleLinkNode* curr = node;

    while (curr->next) {
        printf("%d, ", curr->data);
        curr = curr->next;
    }
    printf("%d\n", curr->data);
}

// description:
// - returns value of a node at given index
// - value at the index is passed using val parameter of the function
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_get(struct SingleLinkNode* head, int idx, int* val)
{
    if (idx<0) return INDEX_OUT_OF_BOUNDS;
    if (head==NULL) return NULL_POINTER;

    struct SingleLinkNode* curr = head;

    for (int i = 0; curr; i++) {
        if (i==idx) {
            *val = curr->data;
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }

    return INDEX_OUT_OF_BOUNDS;
}

// description:
// - places a node with given value at the end of the linked list
// - returns code:
//    - NULL_POINTER - if pointer to the head node has value NULL
//    - EXIT_FAILURE - if the new node cannot be created
//    - EXIT_SUCCESS - if new node was successfully appended to the linked list
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_append(struct SingleLinkNode* head, int val)
{
    if (head==NULL) return NULL_POINTER;

    // get to the end
    struct SingleLinkNode* curr = head;
    while (curr->next) curr = curr->next;

    // create last node
    struct SingleLinkNode* last = NULL;
    int err = SinglyLinkedList_create(&last, val, NULL);

    if (err) {
        log_error("Cannot create node", err);
        return EXIT_FAILURE;
    }

    // append
    curr->next = last;

    return EXIT_SUCCESS;
}

// description:
// - places new node with the value at given index
// - returns code:
//    - INDEX_OUT_OF_BOUNDS - if index passed is lower than 0 or greater than size-1
//    - NULL_POINTER - if pointer to the head pointer is NULL or head pointer itself is NULL
//    - EXIT_FAILURE - if the new node cannot be created
//    - EXIT_SUCCESS - if the value was successfully inserted
// time complexity: 0(n), where n is the size of the linked list
int SinglyLinkedList_insert(struct SingleLinkNode** head, int idx, int val)
{
    if (idx<0) return INDEX_OUT_OF_BOUNDS;
    if (head==NULL) return NULL_POINTER;
    if (*head==NULL) return NULL_POINTER;

    int err;
    struct SingleLinkNode* curr = *head;

    // insert head
    if (idx==0) {
        struct SingleLinkNode* node = NULL;
        err = SinglyLinkedList_create(&node, val, curr);

        if (err) {
            log_error("Cannot create node", err);
            return EXIT_FAILURE;
        }

        *head = node;
        return EXIT_SUCCESS;
    }

    for (int i = 0; curr!=NULL; i++) {

        // insert node
        if (i+1==idx) {
            struct SingleLinkNode* node = NULL;
            err = SinglyLinkedList_create(&node, val, curr->next);

            if (err) {
                log_error("Cannot create node", err);
                return EXIT_FAILURE;
            }

            curr->next = node;
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }

    return INDEX_OUT_OF_BOUNDS;
}

// description:
// - removes node at the given index from the linked list
// - returns code:
//    - INDEX_OUT_OF_BOUNDS - if index passed is lower than 0 or greater than size-1
//    - NULL_POINTER - if pointer to the head pointer node is NULL or head pointer itself is NULL
//    - EXIT_SUCCESS - if node was successfully deleted
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_delete(struct SingleLinkNode** head, int idx)
{
    if (idx<0) return INDEX_OUT_OF_BOUNDS;
    if (head==NULL) return NULL_POINTER;
    if (*head==NULL) return NULL_POINTER;

    struct SingleLinkNode* curr = *head;
    struct SingleLinkNode* remove = NULL;

    // delete head
    if (idx==0) {
        remove = *head;
        *head = curr->next;
        remove->next = NULL;

        SinglyLinkedList_free(&remove);
        return EXIT_SUCCESS;
    }

    for (int i = 0; curr; i++) {

        // delete node
        if (i+1==idx) {
            remove = curr->next;
            curr->next = remove->next;
            remove->next = NULL;

            SinglyLinkedList_free(&remove);
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }

    return INDEX_OUT_OF_BOUNDS;
}

// description:
// - stores value true in parameter contains if the linked list contains given value, false otherwise
// - result is passed using parameter contains of the function
// - returns code:
//    - NULL_POINTER - if pointer to the head node has value NULL
//    - EXIT_SUCCESS - if function ran successfully
// time complexity: O(n), where n is the size of the linked list
int SinglyLinkedList_contains(struct SingleLinkNode* head, int val, bool* contains)
{
    if (head==NULL) return NULL_POINTER;

    *contains = false;
    struct SingleLinkNode* curr = head;

    while (curr) {
        if (curr->data==val) {
            *contains = true;
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

// description:
// - find maximum value stored in the linked list
// - result is passed using max parameter of the function
// - returns code:
//    - NULL_POINTER - if pointer to head node has value NULL
//    - EXIT_SUCCESS - if max value stored in the linked list was determined successfully
// time complexity: O(n)
int SinglyLinkedList_max(struct SingleLinkNode* head, int* max) {
    if (!head) return NULL_POINTER;

    *max = head->data;
    struct SingleLinkNode* curr = head->next;

    while(curr) {
        if (*max < curr->data)
            *max = curr->data;

        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

#endif //CCODE_CLINKEDLIST_H
