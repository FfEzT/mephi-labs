#ifndef _lib_arr
#define _lib_arr

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "lib_scanf.h"

enum status {
    EXIT,
    REINIT,
    INSERT,
    DELETE,
    DATA_PROCESS,
    PRINT
};

typedef struct {
    int size;
    int count;
    int* ptr;
} Array;

Array* arr_init(int count);
void arr_free(Array*);
void arr_print(Array*);
void arr_insert(Array*, int index, int value);
void arr_delete(Array*, int index);
static void arr_check(Array*);

Array* arr_init(int count) {
    int size = count? count*2 : 1;

    Array* ptr = (Array*)malloc(sizeof(Array));
    if (!ptr) exit(1); // throw

    ptr->count = count;
    ptr->size = size;

    ptr->ptr = (int*)calloc(size, sizeof(int));
    if (!(ptr->ptr)) exit(1); // throw

    for (int i = 0; i < count; ++i) {
        char str[32];
        sprintf(str, "arr[%d] = ", i);

        ptr->ptr[i] = get_num(str);
    }

    return ptr;
}

void arr_free(Array* arr) {
    arr->count = arr->size = 0;
    free(arr->ptr);
    free(arr);
}

void arr_print(Array* arr) {
    printf("Size: %d\tCount: %d\n", arr->size, arr->count);

    for (int i = 0; i < arr->count; ++i)
        printf("arr[%d]: %d\n", i, arr->ptr[i]);
}

void arr_insert(Array* arr, int index, int value) {
    if (index >= arr->count) {
        arr->ptr[arr->count] = value;
        ++(arr->count);

        arr_check(arr);
    }
    else arr->ptr[index] = value;
}

void arr_delete(Array* arr, int index) {
    if (index >= arr->count) return;

    int* new_arr = (int*)calloc(arr->size, sizeof(int));
    if (!new_arr) exit(1); // throw

    //for (int i = 0; i < index; ++i) new_arr[i] = arr->ptr[i];
    memcpy(new_arr, arr->ptr, sizeof(int) * index);
    //for (int i = index+1, j = index; i < arr->count; ++i, ++j) new_arr[j] = arr->ptr[i];
    memcpy(
        new_arr + index,
        arr->ptr + index + 1,
        sizeof(int) * (arr->count - index - 1)
    );

    for (int i = arr->count - 1; i >= 0; --i) {
        if (!new_arr[i]) --(arr->count);
        else break;
    }

    free(arr->ptr);
    arr->ptr = new_arr;
    arr_check(arr);
}

static void arr_check(Array* arr) {
    if (arr->count < arr->size / 2) {
        int* new_arr = (int*)calloc(arr->size / 2 + 1, sizeof(int));
        if (!new_arr) exit(1); // throw

        arr->size = arr->size / 2 + 1;

        memcpy(new_arr, arr->ptr, sizeof(int) * arr->count);
        free(arr->ptr);
        arr->ptr = new_arr;
    }
    else if (arr->count == arr->size) {
        int* new_arr = (int*)calloc(arr->size * 2, sizeof(int));
        if (!new_arr) exit(1); // throw

        arr->size = arr->size * 2;

        memcpy(new_arr, arr->ptr, sizeof(int) * arr->count);
        free(arr->ptr);
        arr->ptr = new_arr;
    }
}

#endif
