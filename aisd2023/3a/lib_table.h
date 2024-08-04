#ifndef _lib_table
#define _lib_table

#include <stdlib.h>
#include <stdbool.h>

#include "lib_try-catch.h"
#include "lib_list.h"

// #define CLASS_TABLE void*
#define CLASS_TABLE unsigned

enum error_code {
	NO_DATA = 54802
};

typedef struct {
	List* ls;
	char* key;
} KeySpace;

typedef struct {
	KeySpace** ks;
	unsigned size;
	unsigned capacity;
} Table;

void table_init(Table*, unsigned capacity);
bool table_insert(jmp_buf*, Table*, const char* key, CLASS_TABLE data);
void table_delete(Table*, const char* key, unsigned index, bool deep_free);
void table_delete_by_key(Table*, const char* key, bool deep_free);
CLASS_TABLE* table_get(const Table*, const char* key, unsigned index);
Table* table_get_by_key(const Table*, const char* key);
Table* table_get_by_index(const Table*, unsigned index);
void table_free(Table*, bool deep_free);

#endif
