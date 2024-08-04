#include "stack.h"

void stack_init(Stack* obj) {
    obj->size = 0;
    obj->list = malloc(sizeof(List));

    list_init(obj->list);
}
void stack_free(Stack* obj, bool deep_free) {
    obj->size = 0;
    list_free(obj->list, deep_free);

    free(obj->list);
}

void stack_push(Stack* obj, CLASS_STACK data) {
    list_push_back(obj->list, data);
    obj->size = obj->list->size;
}
CLASS_STACK stack_pop(Stack* obj) {
    CLASS_STACK res = *list_at_last(obj->list);
    list_pop_back(obj->list, 0);
    
    obj->size = obj->list->size;

    return res;
}
