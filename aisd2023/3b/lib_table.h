#ifndef _lib_table
#define _lib_table

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/lib_try-catch.h"

// #define CLASS_TABLE void*
#define CLASS_TABLE unsigned

enum error_code {
	NO_DATA = 54802
};

typedef struct {
	long offset_data;
	long offset;
	char* key;
} KeySpace;

typedef struct {
	FILE* file;
	KeySpace** ks;
	unsigned size;
	unsigned capacity;
	char* name_file;
} Table;

bool table_init(Table*, char* file_name);
void table_new(Table*, unsigned capacity);
bool table_insert(Table*, const char* key, CLASS_TABLE data);
void table_delete(Table*, const char* key, unsigned index);
void table_delete_by_key(Table*, const char* key);
int table_get(const Table*, const char* key, unsigned index);
long table_get_by_key(const Table*, const char* key);
void table_free(Table*);
void print(Table*);

#endif
