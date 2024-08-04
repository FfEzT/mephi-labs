#ifndef _lib_list
#define _lib_list

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

#include "lib_try-catch.h"

#define CLASS unsigned char

// TODO add const
extern struct Node;
typedef struct Node Node;
struct Node {
    Node* next;
    CLASS data;
};

typedef struct {
    Node* first;
    Node* last;
    unsigned size;
} List;

List* list_init() {
    List* res = malloc(sizeof(List));
    if (res == NULL) throw(null_ptr);

    res->first = res->last = res->size = NULL;

    return res;
}

void list_print(List* list) {
    Node* temp = list->first;

    printf("Size: %d\n\n", list->size);
    for (unsigned i = 0;; ++i) {
        printf("list[%u]:%c\n", i, temp->data);
        if (temp->next == NULL) break;
        temp = temp->next;
    }
}

void list_push_front(List* list, CLASS value) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) throw(null_ptr);

    node->next = list->first;
    node->data = value;

    list->first = node;

    if (list->size == 0)
        list->last = node;

    ++list->size;
}

void list_push_back(List* list, CLASS value) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) throw(null_ptr);

    node->next = NULL;
    node->data = value;

    if (list->size == 0)
        list->first = node;
    else if (list->size >= 1)
        list->last->next = node;

    list->last = node;

    ++list->size;
}

void list_pop_front(List* list) {
    if (list->size > 0) {
        Node* temp = list->first->next;

        free(list->first);
        list->first = temp;

        --list->size;
    }
}

void list_pop_back(List* list) {
    if (list->size > 0) {
        Node* temp = list->first;
        
        while (temp->next != list->last)
            temp = temp->next;

        temp->next = NULL;
        free(list->last);
        list->last = temp;

        --list->size;
    }
}

// Check
void list_add(List* list, unsigned index, CLASS value) {
    //if (index >= list->size) return;
    
    Node* temp = list->first;
    
    for (unsigned i = 0; i < index - 1; ++i)
        temp = temp->next;

    Node* node = malloc(sizeof(Node));
    if (node == NULL) throw(null_ptr);

    node->next = temp->next;
    node->data = value;

    temp->next = node;
}

// Check (while != NULL)
void list_delete(List* list, unsigned index) {
    if (index >= list->size) return;

    Node* temp = list->first;

    for (unsigned i = 0; i < index; ++i) // mb index-1
        temp = temp->next;

    Node* deleted = temp->next;

    temp->next = deleted->next;

    --list->size;
    free(deleted);
}

Node* list_at(List* list, unsigned index) {
    if (index >= list->size) return NULL;
    
    Node* temp = list->first;
    for (unsigned i = 0; i <= index; ++i) temp = temp->next;

    return temp;
}

int list_search(List* list, CLASS value) {
    Node* temp = list->first;

    for (unsigned i = 0; temp->next; ++i)
        if (temp->data == value) return i;

    return -1;
}

unsigned list_get_size(List* list) {
    if (list->first == NULL) return 0;

    unsigned i = 1;
    Node* ptr = list->first;
    while (ptr->next != NULL) ptr = ptr->next, ++i;

    return i;
}

void list_free(List* list) {
    if (list->size == 1)
        free(list->first);
    else if (list->size > 1) {
        Node* first = list->first;
        Node* second = list->first->next;

        while (second->next != NULL) {
            free(first);
            first = second;
            second = second->next;
        }
    }

    free(list);
}

#endif
