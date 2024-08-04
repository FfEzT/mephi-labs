#ifndef _lib_ht
#define _lib_ht

#include <stdbool.h>

typedef struct {
	char* data;
} Item;

typedef struct {
	Item* data;
	unsigned key;
	unsigned relise;
} KeySpace;

typedef struct {
	KeySpace* ks;
	unsigned size;	
	unsigned capacity;	
} HTable;

void htable_init(HTable*, unsigned capacity);
void htable_free(HTable*);
void htable_print(const HTable*);
bool htable_insert(HTable*, unsigned key, char* data);
bool htable_delete(HTable*, unsigned key);
void htable_import(HTable*);
char* htable_search(HTable*, unsigned key, unsigned relise);
HTable* htable_search_by_key(HTable*, unsigned key);

#endif
