#ifndef _lib_scanf
#define _lib_scanf

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "./lib_try-catch.h"

#define SIZE 32 // don't change (or change on get_str on "n = scanf("%..."
#define IS_SPACE(arg) ((arg) == ' ' || (arg) == '\t')

unsigned str_len(const char* const str);
int get_num(const char* const s);
int get_i(const char* const s);
char* get_str(); // don't forget to free alloc
char* trim(char* str);

#endif
