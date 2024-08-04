#ifndef _lib_scanf
#define _lib_scanf

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "./lib_try-catch.h"

// _BUFFER_SIZE of buffer in scanf & fscanf
#define _BUFFER_SIZE 32 // don't change (or change on get_str on "n = scanf("%..."
#define IS_SPACE(arg) ((arg) == ' ' || (arg) == '\t')

unsigned str_len(const char* str);
int get_num(jmp_buf* err, const char* s);
int get_i(jmp_buf* err, const char* s);
char* get_str(jmp_buf* err, const char* s); // don't forget to free alloc
char* get_str_file(jmp_buf* err, FILE* file);
char* trim(jmp_buf* err, char* str);

#endif
