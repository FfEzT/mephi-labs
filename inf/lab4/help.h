#ifndef _lib_help
#define _lib_help

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#include "./lib_scanf.h"

unsigned get_word_count(const char* const str);
char** fill_words(const char* const str, const unsigned count);
void str_delete_equals(char** const words, const unsigned count);
void free_words(char** words, unsigned* count);

#endif
