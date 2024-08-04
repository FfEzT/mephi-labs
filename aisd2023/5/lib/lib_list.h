#ifndef _lib_list
#define _lib_list

#include <stdbool.h>

#define CLASS_LIST void*

typedef struct Node {
    struct Node* next;
    CLASS_LIST data;
} Node;
typedef struct {
    Node* first;
    Node* last;
    unsigned size;
} List;

void list_init(List*);
void list_print(const List* list);
void list_push_front(List* list, CLASS_LIST value);
void list_push_back(List* list, CLASS_LIST value);
void list_pop_front(List* list, bool deep_free);
void list_pop_back(List* list, bool deep_free);
void list_add(List* list, unsigned index, CLASS_LIST value);
void list_delete(List* list, unsigned index, bool deep_free);
CLASS_LIST* list_at(const List* list, unsigned index);
CLASS_LIST* list_at_last(const List* list);
int list_search(const List* list, CLASS_LIST value);
void list_free(List* list, bool deep_free);

#endif
