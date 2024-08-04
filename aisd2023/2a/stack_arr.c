#include "./stack.h"

void stack_init(Stack* obj) {
    obj->size = 0;
    obj->arr = malloc(sizeof(Array));

    arr_init(obj->arr);
}
void stack_free(Stack* obj, bool deep_free) {
    obj->size = 0;
    arr_free(obj->arr, deep_free);

    free(obj->arr);
}

void stack_push(Stack* obj, CLASS_STACK data) {
    arr_insert(obj->arr, obj->arr->count, data);
    obj->size = obj->arr->count;
}

CLASS_STACK stack_pop(Stack* obj) {
    CLASS_STACK res = obj->arr->ptr[obj->arr->count-1];
    arr_delete(obj->arr, obj->arr->count-1, 0);
    
    obj->size = obj->arr->count;

    return res;
}
