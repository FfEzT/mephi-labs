#ifndef _lib_stack
#define _lib_stack

#include "stdbool.h"

#include "lib_arr.h"
#include "lib_list(process).h"

#define CLASS_STACK void*

typedef struct {
    union {
        List* list;
        Array* arr;
    };
    unsigned size;
} Stack;

void stack_init(Stack*);
void stack_free(Stack*, bool deep_free);
void stack_push(Stack*, CLASS_STACK data);
CLASS_STACK stack_pop(Stack*);

#endif
