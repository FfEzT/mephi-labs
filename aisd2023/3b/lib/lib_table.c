#include <limits.h>
#include <string.h>

#include "lib_table.h"

enum search_code_return {
	NO_RESULT = INT_MIN,
	AFTER_NILL,
	BEFORE_NILL
};

static int table_binary_search(const Table* table, const char* key) {
	if (table->size == 0) return NO_RESULT;
	
	unsigned left = 0, right = table->size-1;
	if ( strcmp(table->ks[left]->key, key) > 0 ) return BEFORE_NILL;

	while (right >= left) {
		unsigned index = (left+right)/2;

		if ( strcmp(table->ks[index]->key, key) == 0  ) return index;
		else if ( strcmp(table->ks[index]->key, key) > 0) right = index-1;
		else left = index+1;
	}
	
	return right == 0? AFTER_NILL : -(int)right;
}

static KeySpace* create_keySpace(const char* key, CLASS_TABLE data) {
	KeySpace* res = malloc(sizeof(KeySpace));
	res->key = (char*)key;
	res->ls = malloc(sizeof(List));
	list_init(res->ls);
	list_push_back(res->ls, data);

	return res;
}

void table_init(Table* a, unsigned capacity) {
	a->size = 0;
	a->capacity = capacity;
	a->ks = malloc(capacity * sizeof(KeySpace*));
}

bool table_insert(jmp_buf* err, Table* a, const char* _key, CLASS_TABLE data) {
	char* key = strdup(_key);

	int index = table_binary_search(a, key);
	if (index < 0 && a->size == a->capacity) return false;

	if (index == NO_RESULT)
		a->ks[0] = create_keySpace(key, data);
	else if (index == AFTER_NILL) {
		for (unsigned i = a->size; i > 1; --i)
			a->ks[i] = a->ks[i-1];

		a->ks[1] = create_keySpace(key, data);
	}
	else if (index == BEFORE_NILL) {
		for (unsigned i = a->size; i > 0; --i)
			a->ks[i] = a->ks[i-1];

		a->ks[0] = create_keySpace(key, data);
	}
	else if (index >= 0) {
		free(key);
		--(a->size);
		list_push_back(a->ks[index]->ls, data);
	}
	else if (index < 0) {
		index *= -1;

		for (int i = a->size; i > index+1; --i)
			a->ks[i] = a->ks[i-1];

		a->ks[index+1] = create_keySpace(key, data);
	}
	++(a->size);
	
	return true;
}

void table_delete_by_key(Table* table, const char* key, bool deep_free) {
	int index = table_binary_search(table, key);

	if (index < 0) return;

	list_free(table->ks[index]->ls, deep_free);
	free(table->ks[index]->ls);
	free(table->ks[index]->key);
	free(table->ks[index]);

	for (unsigned i = index; i < table->size-1; ++i)
		table->ks[i] = table->ks[i+1];
		
	--(table->size);
}

void table_delete(Table* table, const char* key, unsigned _index, bool deep_free) {
	int index = table_binary_search(table, key);

	if (index < 0) return;
	list_delete(table->ks[index]->ls, _index, deep_free);
}

void table_free(Table* table, bool deep_free) {
	for (unsigned i = 0; i < table->size; ++i) {
		list_free(table->ks[i]->ls, deep_free);
		free(table->ks[i]->ls);
		free(table->ks[i]->key);
		free(table->ks[i]);
	}
	free(table->ks);
	
	table->ks = NULL;
	table->capacity = table->size = 0;
}

CLASS_TABLE* table_get(const Table* table, const char* key, unsigned _index) {
	int index = table_binary_search(table, key);
	if (index < 0) return NULL;

	return list_at(table->ks[index]->ls, _index);
}

Table* table_get_by_index(const Table* table, unsigned index) {
	jmp_buf err;

	Table* res = malloc(sizeof(Table));
	table_init(res, table->capacity);

	for (unsigned i = 0; i < table->size; ++i) {
		unsigned* data = list_at(table->ks[i]->ls, index);

		if (data == NULL) continue;
		table_insert(&err, res, table->ks[i]->key, *data);
	}

	return res;
}

Table* table_get_by_key(const Table* table, const char* key) {
	jmp_buf err;
	
	Table* res = malloc(sizeof(Table));
	table_init(res, 1);

	int index = table_binary_search(table, key);
	if (index < 0) return NULL;

	for (Node* tmp = table->ks[index]->ls->first; tmp; tmp = tmp->next) {
		table_insert(
			&err,
			res,
			table->ks[index]->key,
			tmp->data
		);
	}

	return res;
}
