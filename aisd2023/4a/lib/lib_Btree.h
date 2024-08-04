#ifndef _lib_Btree
#define _lib_Btree

#include <stdbool.h>

typedef struct {
	char* key;
	unsigned data;
} Item;

typedef struct B_tree B_tree;

B_tree* tree_init();
void* tree_free(B_tree*);
void tree_print(const B_tree*, char*);
void tree_print_(const B_tree*);
bool tree_insert(B_tree*, const char* key, const unsigned data);
bool tree_delete(B_tree*, char* key);
Item* tree_find_by_key(const B_tree*, const char* key);
Item* tree_find(const B_tree*, const char* key);

#endif
