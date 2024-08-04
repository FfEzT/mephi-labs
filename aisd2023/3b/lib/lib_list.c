#include "lib_list.h"

void list_init(List* list) {
    list->size = 0;
    list->first = list->last = NULL;
}

void list_print(const List* list) {
    printf("Size: %d\n\n", list->size);
}

void list_push_front(List* list, CLASS_LIST value) {
    Node* node = malloc(sizeof(Node));

    node->next = list->first;
    node->data = value;

    list->first = node;

    if (list->size == 0)
        list->last = node;

    ++list->size;
}

void list_push_back(List* list, CLASS_LIST value) {
    Node* node = malloc(sizeof(Node));

    node->next = NULL;
    node->data = value;

    if (list->size == 0)
        list->first = node;
    else if (list->size >= 1)
        list->last->next = node;

    list->last = node;

    ++list->size;
}

void list_pop_front(List* list, bool deep_free) {
    if (list->size > 0) {
        Node* temp = list->first->next;

        if (deep_free) free(list->first->data);
        free(list->first);
        list->first = temp;

        --list->size;
    }
}

void list_pop_back(List* list, bool deep_free) {
    if (list->first == list->last) {
        if (deep_free) free(list->first->data);
        free(list->first);
        
        list->first = list->last = NULL;
        list->size = 0;
    }
    else if (list->size > 0) {
        Node* temp = list->first;
        
        while (temp->next != list->last)
            temp = temp->next;

        temp->next = NULL;

        if (deep_free) free(list->first->data);
        free(list->last);
        
        list->last = temp;

        --list->size;
    }
}

void list_add(List* list, unsigned index, CLASS_LIST value) {
    if (index >= list->size)
		list_push_back(list, value);
    else if (index == 0)
    	list_push_front(list, value);
    else {
	    Node* temp = list->first;

	    for (unsigned i = 0; i < index - 1; ++i)
	        temp = temp->next;

	    Node* node = malloc(sizeof(Node));

	    node->next = temp->next;
	    node->data = value;

	    temp->next = node;

	    ++(list->size);
	}
}

void list_delete(List* list, unsigned index, bool deep_free) {
    if (index >= list->size) return;
    else if (index == list->size - 1) list_pop_back(list, deep_free);
    else if (index == 0) list_pop_front(list, deep_free);
	else {
	    Node* temp = list->first;

	    for (unsigned i = 1; i < index; ++i)
	        temp = temp->next;

	    Node* deleted = temp->next;
	    temp->next = deleted->next;

	    --(list->size);

	    if (deep_free) free(deleted->data);
	    free(deleted);
	}
}

CLASS_LIST* list_at(const List* list, unsigned index) {
    if (index >= list->size) return NULL;
    
    Node* temp = list->first;
    for (unsigned i = 0; i < index; ++i) temp = temp->next;

    return &(temp->data);
}

CLASS_LIST* list_at_last(const List* list) {
    return list->size > 0? &(list->last->data) : NULL;
}

int list_search(const List* list, CLASS_LIST value) {
    Node* temp = list->first;

    for (unsigned i = 0; temp->next; ++i)
        if (temp->data == value) return i;

    return -1;
}

void list_free(List* list, bool deep_free) {
    if (list->size == 1) {
        if (deep_free) free(list->first->data);
        free(list->first);
    }
    else if (list->size > 1) {
        Node* first = list->first;
        Node* second = list->first->next;

        while (second != NULL) {
            if (deep_free) free(first->data);
            free(first);
            first = second;
            second = second->next;
        }
        if (deep_free) free(first->data);
        free(first);
    }

    list_init(list);
}
