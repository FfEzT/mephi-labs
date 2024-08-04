#ifndef _lib_arr
#define _lib_arr

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#include "lib_try-catch.h"

#define CLASS_ARRAY void*

typedef struct {
    CLASS_ARRAY* ptr;
    int count;
    int size;
} Array;

void arr_init(Array*);
void arr_free(Array*, bool deep_free);
void arr_print(const Array*);
void arr_insert(Array*, int index, CLASS_ARRAY value);
void arr_delete(Array*, int index, bool deep_free);

#endif
