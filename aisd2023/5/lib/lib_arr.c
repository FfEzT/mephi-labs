#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "./lib_arr.h"

static void arr_check(Array* arr) {
    if (arr->count < arr->size / 2) {
        CLASS_ARRAY* new_arr = calloc(arr->size / 2 + 1, sizeof(CLASS_ARRAY));

        arr->size = arr->size / 2 + 1;

        memcpy(new_arr, arr->ptr, sizeof(CLASS_ARRAY) * arr->count);
        free(arr->ptr);
        arr->ptr = new_arr;
    }
    else if (arr->count == arr->size) {
        CLASS_ARRAY* new_arr = calloc(arr->size * 2, sizeof(CLASS_ARRAY));

        arr->size = arr->size * 2;

        memcpy(new_arr, arr->ptr, sizeof(CLASS_ARRAY) * arr->count);
        free(arr->ptr);
        arr->ptr = new_arr;
    }
}


void arr_init(Array* ptr) {
    ptr->size = (ptr->count = 0)+1;
    ptr->ptr = calloc(ptr->size, sizeof(CLASS_ARRAY));
}

void arr_free(Array* arr, bool deep_free) {
    if (deep_free) for (unsigned i = 0; i < arr->count; ++i)
        free(arr->ptr[i]);

    arr->count = arr->size = 0;
    free(arr->ptr);
}

void arr_print(const Array* arr) {
    printf("Size: %d\tCount: %d\n", arr->size, arr->count);

    for (int i = 0; i < arr->count; ++i)
        printf("arr[%d]: %d\n", i, arr->ptr[i]);
}

void arr_insert(Array* arr, int index, CLASS_ARRAY value) {
    if (index >= arr->count) {
        arr->ptr[arr->count] = value;
        ++(arr->count);

        arr_check(arr);
    }
    else arr->ptr[index] = value;
}

void arr_delete(Array* arr, int index, bool deep_free) {
    if (index >= arr->count) return;

    if (deep_free) free(arr->ptr[index]);

    CLASS_ARRAY* new_arr = calloc(arr->size, sizeof(CLASS_ARRAY));

    memcpy(new_arr, arr->ptr, sizeof(CLASS_ARRAY) * index);
    memcpy(
        new_arr + index,
        arr->ptr + index + 1,
        sizeof(CLASS_ARRAY) * (arr->count - index - 1)
    );

    for (int i = arr->count - 1; i >= 0; --i) {
        if (!new_arr[i]) --(arr->count);
        else break;
    }

    free(arr->ptr);
    arr->ptr = new_arr;
    arr_check(arr);
}
