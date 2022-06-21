//
// Created by Tomáš Petříček on 20.06.2022.
//

#ifndef CCODE_CLINKEDLIST_H
#define CCODE_CLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

struct Node {
    int data;
    struct Node* next;
};

int Node_create(struct Node** node, int data, struct Node* next)
{
    if (node==NULL) return NULL_POINTER;

    *node = (struct Node*) malloc(sizeof(struct Node));

    if (node==NULL) return BAD_ALLOCATION;

    (*node)->data = data;
    (*node)->next = next;
    return EXIT_SUCCESS;
}

void Node_free(struct Node** head)
{
    struct Node* curr = *head;
    struct Node* dealloc = NULL;

    while (curr!=NULL) {
        dealloc = curr;
        curr = curr->next;
        free(dealloc);
    }

    *head = NULL;
}

// time complexity: O(n)
void Node_display(struct Node* node)
{
    struct Node* curr = node;

    while (curr->next!=NULL) {
        printf("%d, ", curr->data);
        curr = curr->next;
    }
    printf("%d\n", curr->data);
}

int Node_get(struct Node* head, int idx, int* val)
{
    if (idx<0) return INDEX_OUT_OF_BOUNDS;
    if (head==NULL) return NULL_POINTER;

    struct Node* curr = head;

    for (int i = 0; curr!=NULL; i++) {
        if (i==idx) {
            *val = curr->data;
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }

    return INDEX_OUT_OF_BOUNDS;
}

// time complexity: O(n)
int Node_append(struct Node* head, int val)
{
    if (head==NULL) return NULL_POINTER;

    // get to the end
    struct Node* curr = head;
    while (curr->next!=NULL) curr = curr->next;

    // create last node
    struct Node* last = NULL;
    int err = Node_create(&last, val, NULL);

    if (err) {
        log_error("Cannot create node", err);
        return EXIT_FAILURE;
    }

    // append
    curr->next = last;

    return EXIT_SUCCESS;
}

// time complexity: 0(n)
int Node_insert(struct Node** head, int idx, int val)
{
    if (head==NULL) return NULL_POINTER;
    if (*head==NULL) return NULL_POINTER;
    if (idx<0) return INDEX_OUT_OF_BOUNDS;

    int err;
    struct Node* curr = *head;

    // insert head
    if (idx==0) {
        struct Node* node = NULL;
        err = Node_create(&node, val, curr);

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
            struct Node* node = NULL;
            err = Node_create(&node, val, curr->next);

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

int Node_delete(struct Node** head, int idx)
{
    if (idx<0) return INDEX_OUT_OF_BOUNDS;
    if (head==NULL) return NULL_POINTER;
    if (*head==NULL) return NULL_POINTER;

    struct Node* curr = *head;
    struct Node* dealloc = NULL;

    // delete head
    if (idx==0) {
        dealloc = *head;
        *head = curr->next;
        dealloc->next = NULL;

        Node_free(&dealloc);
        return EXIT_SUCCESS;
    }

    for (int i = 0; curr!=NULL; i++) {

        // delete node
        if (i+1==idx) {
            dealloc = curr->next;
            curr->next = dealloc->next;
            dealloc->next = NULL;

            Node_free(&dealloc);
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }

    return INDEX_OUT_OF_BOUNDS;
}

#endif //CCODE_CLINKEDLIST_H
