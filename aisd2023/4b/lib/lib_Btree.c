#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lib_Btree.h"

typedef struct B_node {
	struct B_node* parent;
	struct B_node* next[3];
	Item* info[2];
	unsigned size;
} B_node;

typedef struct B_tree {
	B_node* root;
} B_tree;

static B_node* init_node() {
	B_node* res = malloc(sizeof(B_node));
	res->parent = NULL;
	for (unsigned i = 0; i < 3; ++i) res->next[i] = NULL;
	for (unsigned i = 0; i < 2; ++i) res->info[i] = NULL;
	res->size = 0;

	return res;
}

static void free_node(B_node* a) {
	if (!a) return;
		
	for (unsigned i = 0; i < 3; ++i)
		free_node(a->next[i]);

	for (unsigned i = 0; i < a->size; ++i) {
		free(a->info[i]->key);		
		free(a->info[i]);		
	}

	free(a);
}

static void print(B_node* a) {
	if (!a) return;

	for (unsigned i = 0; i < a->size+1; ++i) {
		print(a->next[i]);
		printf("%s: %u\n", a->info[i]->key, a->info[i]->data);
	}		
}

static void print_(B_node* a, unsigned tab) {
	if (!a) return;

	for (unsigned i = 0; i < tab; ++i) printf("\t");
	
	for (unsigned i = 0; i < a->size+1; ++i) {
		print_(a->next[i], tab+1);
		if (i == a->size) break;
		printf("%s: %u\n", a->info[i]->key, a->info[i]->data);
	}		
}

// TODO check
static B_node* node_find_by_key(const B_node* a, const char* key) {
	if (!a) return NULL;

	unsigned i = 0;
	for (; i < a->size+1; ++i) {
		if (i == a->size) break;
		
		if ( strcmp(a->info[i]->key, key) == 0 )
			return NULL;
		else if ( strcmp(a->info[i]->key, key) < 0 )
			break;
	}

	return a->next[i]? node_find_by_key(a->next[i], key) : (B_node*)a;
}

// TODO check
static Item* find_by_key(const B_node* a, const char* key) {
	if (!a) return NULL;
	
	unsigned i = 0;
	bool is_find = false;
	for (; i < a->size+1; ++i) {
		if (i == a->size) break;
		
		if ( strcmp(a->info[i]->key, key) == 0 ) {
			is_find = true;
			break;
		}
		else if ( strcmp(a->info[i]->key, key) < 0 ) break;
	}

	if (is_find) return a->info[i];
	return find_by_key(a->next[i], key);
}

inline B_tree* tree_init() {
	B_tree* res = malloc(sizeof(B_tree));
	res->root = NULL;

	return res;
}

void* tree_free(B_tree* a) {
	if (a) {
		free_node(a->root);
		free(a);
	}

	return NULL;
}

bool tree_insert(B_tree* a, const char* key, const unsigned data) {
	if (!a) return false;

	if (!a->root) {
		B_node* ptr = init_node();
		a->root = ptr;

		ptr->size = 1;
		ptr->info[0]->key = strdup(key);
		ptr->info[0]->data = data;
	}

	B_node* ptr = node_find_by_key(a->root, key);
	if (!ptr) return false;

		
}

void tree_print_(const B_tree* a) {
	if (!a) return;
	print_(a->root, 0);
}

void tree_print(const B_tree* a) {
	if (!a) return;
	print(a->root);
}

// TODO
bool tree_delete(B_tree* a, const char* key) {
	if (!a) return false;

	Item* test = find_by_key(a->root, key);
	if (!test) return false;
}


Item* tree_find_by_key(const B_tree* a, const char* key) {
	if (!a) return NULL;
	return find_by_key(a->root, key);	
}

// TODO максимально противоположный найти
Item* tree_find(const B_tree* a, const char* key) {
	if (!a) return NULL;
}
