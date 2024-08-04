#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lib_Btree.h"

typedef struct B_node {
	struct B_node* parent;
	struct B_node* next[4];
	Item* info[3];
	unsigned size;
} B_node;

typedef struct B_tree {
	B_node* root;
} B_tree;

static B_node* init_node();
static Item* init_item(const char* key, unsigned data);

static void swap(Item** a, Item** b);
static void sort2(Item** a, Item** b);
static void sort3(Item** a, Item** b, Item** c);
static void sort(B_node*);

static bool find(const B_node*, const char* key);
static bool is_leaf(B_node*);

static void insert_in_node(B_node*, Item*);
static void remove_in_node(B_node*, const char* key);
static void become_node2(B_node*, Item*, B_node* node1, B_node* node2);
static void free_node(B_node* a);

static B_node* split(B_node*);
static B_node* insert(B_node*, Item*, bool* status);
static B_node* redist(B_node* a);
static B_node* merge(B_node* a);
static B_node* fix(B_node* a);
static B_node* remove_(B_node* p, char* k, bool* status);

static void print(B_node*, char*);
static void print_(B_node*, unsigned tab, unsigned keys_num);
static B_node* search(B_node*, const char* key);
static B_node* search_min(B_node*);
static B_node* search_max(B_node*);

static unsigned max(unsigned a, unsigned b) {
	return a >= b? a:b;
}
static unsigned min(unsigned a, unsigned b) {
	return a >= b? b:a;
}
static int absolute(int a) {return a >= 0? a : -a;}
static unsigned hash(const char* a, const char* b) {
	unsigned res = 0,
			 lena = min( strlen(a), strlen(b) );

	for (unsigned i = 0; i < lena; ++i)
		res = (lena-i) * absolute(a[i]-b[i]);
	

	return res;
}


static B_node* init_node() {
	B_node* res = malloc(sizeof(B_node));
	res->parent = NULL;

	for (unsigned i = 0; i < 4; ++i) res->next[i] = NULL;
	for (unsigned i = 0; i < 3; ++i) res->info[i] = NULL;
	res->size = 0;

	return res;
}

static Item* init_item(const char* key, unsigned data) {
	Item* res = malloc(sizeof(Item));
	res->key = strdup(key);
	res->data = data;

	return res;
}



static void swap(Item** a, Item** b) {
	Item* temp = *a;
	*a = *b;
	*b = temp;
}

static void sort2(Item** a, Item** b) {
	if ( strcmp(a[0]->key, b[0]->key) > 0 ) swap(a, b);
}
static void sort3(Item** a, Item** b, Item** c) {
	if ( strcmp(a[0]->key, b[0]->key) > 0 ) swap(a, b);
	if ( strcmp(a[0]->key, c[0]->key) > 0 ) swap(a, c);
	if ( strcmp(b[0]->key, c[0]->key) > 0 ) swap(b, c);
}

static void sort(B_node* a) {
	switch (a->size) {
	case 1: return;

	case 2: 
		sort2(&a->info[0], &a->info[1]);
		break;

	case 3:
		sort3(&a->info[0], &a->info[1], &a->info[2]);
		break;			
	}		
}



static bool find(const B_node* a, const char* key) {
	for (unsigned i = 0; i < a->size; ++i) 
		if ( strcmp(key, a->info[i]->key) == 0 ) return true;

	return false;
}

static bool is_leaf(B_node* a) {
	for (unsigned i = 0; i < 4; ++i)
		if (a->next[i] != NULL) return false;

	return true;		
}



static void insert_in_node(B_node* a, Item* data) {
	a->info[a->size] = data;
	++a->size;
	sort(a);
}

static void remove_in_node(B_node* a, const char* key) {
	if (a->size >= 1 && strcmp(key, a->info[0]->key) == 0 ) {
		free(a->info[0]->key);
		free(a->info[0]);
		a->info[0] = a->info[1];
		a->info[1] = a->info[2];
		--a->size;
	}
	else if (a->size == 2 && strcmp(key, a->info[1]->key) == 0 ) {
		free(a->info[1]);
		a->info[1] = a->info[2];
		--a->size;
	}
}

static void become_node2(B_node* a, Item* data, B_node* node1, B_node* node2) {
	a->info[0] = data;
	a->info[1] = a->info[2] = NULL;
	
	a->size = 1;

	a->next[0] = node1;
	a->next[1] = node2;
	a->next[2] = NULL;
	a->next[3] = NULL;
	a->parent = NULL;
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



static B_node* split(B_node* a) {
	if (a->size < 3) return a;

	B_node* x = init_node();
	x->info[0] = a->info[0];
	x->next[0] = a->next[0];
	x->next[1] = a->next[1];
	x->parent = a->parent;

	B_node* y = init_node();
	y->info[0] = a->info[2];
	y->next[0] = a->next[2];
	y->next[1] = a->next[3];

	x->parent = y->parent = a->parent;
	x->size = y->size = 1;

	if (x->next[0]) x->next[0]->parent = x;
	if (x->next[1]) x->next[1]->parent = x;
	if (y->next[0]) y->next[0]->parent = y;
	if (y->next[1]) y->next[1]->parent = y;

	if (a->parent) {
		insert_in_node(a->parent, a->info[1]);

		for (unsigned i = 0; i < 3; ++i)
			if (a->parent->next[i] == a)
				a->parent->next[i] = NULL;

		if (a->parent->next[0] == NULL) {
			a->parent->next[3] = a->parent->next[2];
			a->parent->next[2] = a->parent->next[1];
			a->parent->next[1] = y;
			a->parent->next[0] = x;
		}
		else if (a->parent->next[1] == NULL) {
			a->parent->next[3] = a->parent->next[2];
			a->parent->next[2] = y;
			a->parent->next[1] = x;
		}
		else {
			a->parent->next[3] = y;
			a->parent->next[2] = x;
		}

		B_node* tmp = a->parent;

		free(a);
		
		return tmp;
	}
	else {
		x->parent = y->parent = a;
		become_node2(a, a->info[1], x, y);

		return a;
	}
	
}

static B_node* insert(B_node* a, Item* data, bool* status) {
	if (!a) {
		B_node* res = init_node();
		res->size = 1;
		res->info[0] = data;

		return res;
	}

	*status = find(a, data->key);
	if (*status) {
		return a;
	}

	if ( is_leaf(a) )
		insert_in_node(a, data);
	else if ( strcmp(data->key, a->info[0]->key) < 0 )
		insert(a->next[0], data, status);
	else if ( a->size == 1 ||
	(a->size == 2 && strcmp(data->key, a->info[1]->key) < 0) )
		insert(a->next[1], data, status);
	else insert(a->next[2], data, status);

	return *status? a : split(a);
}

static B_node* redist(B_node* leaf) {
	B_node* parent = leaf->parent;
    B_node* next[] = {
        parent->next[0],
        parent->next[1],
        parent->next[2]
    };

    if ((parent->size == 2) && (next[0]->size < 2) && (next[1]->size < 2) && (next[2]->size < 2)) {
        if (next[0] == leaf) {
            parent->next[0] = parent->next[1];
            parent->next[1] = parent->next[2];
            parent->next[2] = NULL;

            insert_in_node(
                parent->next[0],
                init_item(
                    parent->info[0]->key,
                    parent->info[0]->data
                )
            );

            parent->next[0]->next[2] = parent->next[0]->next[1];
            parent->next[0]->next[1] = parent->next[0]->next[0];

            if (leaf->next[0] != NULL)
                parent->next[0]->next[0] = leaf->next[0];
            else if (leaf->next[1] != NULL)
                parent->next[0]->next[0] = leaf->next[1];

            if (parent->next[0]->next[0] != NULL)
                parent->next[0]->next[0]->parent = parent->next[0];

            remove_in_node(parent, parent->info[0]->key);
            free(next[0]);
        }
		else if (next[1] == leaf) {
            insert_in_node(
                next[0],
                init_item(
                    parent->info[0]->key,
                    parent->info[0]->data
                )
            );

            remove_in_node(parent, parent->info[0]->key);
            if (leaf->next[0] != NULL)
                next[0]->next[2] = leaf->next[0];
            else if (leaf->next[1] != NULL)
                next[0]->next[2] = leaf->next[1];

            if (next[0]->next[2] != NULL)
                next[0]->next[2]->parent = next[0];

            parent->next[1] = parent->next[2];
            parent->next[2] = NULL;

            free(next[1]);
        }
		else if (next[2] == leaf) {
            insert_in_node(
                next[1],
                init_item(
                    parent->info[1]->key,
                    parent->info[1]->data
                )
            );

            parent->next[2] = NULL;
            remove_in_node(parent, parent->info[1]->key);

            if (leaf->next[0] != NULL)
                next[1]->next[2] = leaf->next[0];
            else if (leaf->next[1] != NULL)
                next[1]->next[2] = leaf->next[1];

            if (next[1]->next[2] != NULL)
                next[1]->next[2]->parent = next[1];

            free(next[2]);
        }
    }
	else if ((parent->size == 2) && ((next[0]->size == 2) || (next[1]->size == 2) || (next[2]->size == 2))) {
        if (next[2] == leaf) {
            if (leaf->next[0] != NULL) {
                leaf->next[1] = leaf->next[0];
                leaf->next[0] = NULL;
            }

            insert_in_node(
                leaf,
                init_item(
                    parent->info[1]->key,
                    parent->info[1]->data
                )
            );

            if (next[1]->size == 2) {
                parent->info[1] = init_item(next[1]->info[1]->key, next[1]->info[1]->data);
                remove_in_node(next[1], next[1]->info[1]->key);
                leaf->next[0] = next[1]->next[2];
                next[1]->next[2] = NULL;
                if (leaf->next[0] != NULL) leaf->next[0]->parent = leaf;
            }
            else if (next[0]->size == 2) {
                {
                    free(parent->info[1]->key);
                    free(parent->info[1]);
                }
                parent->info[1] = next[1]->info[0];
                leaf->next[0] = next[1]->next[1];
                next[1]->next[1] = next[1]->next[0];
                if (leaf->next[0] != NULL) leaf->next[0]->parent = leaf;

                next[1]->info[0] = parent->info[0];
                parent->info[0] = init_item(next[0]->info[1]->key, next[0]->info[1]->data);
                remove_in_node(next[0], next[0]->info[1]->key);
                next[1]->next[0] = next[0]->next[2];
                if (next[1]->next[0] != NULL) next[1]->next[0]->parent = next[1];
                next[0]->next[2] = NULL;
            }
        }
        else if (next[1] == leaf) {
            if (next[2]->size == 2) {
                if (leaf->next[0] == NULL) {
                    leaf->next[0] = leaf->next[1];
                    leaf->next[1] = NULL;
                }

                insert_in_node(
                    next[1],
                    init_item(
                        parent->info[1]->key,
                        parent->info[1]->data
                    )
                );

                parent->info[1] = init_item(next[2]->info[0]->key, next[2]->info[0]->data);
                remove_in_node(next[2], next[2]->info[0]->key);
                next[1]->next[1] = next[2]->next[0];
                if (next[1]->next[1] != NULL) next[1]->next[1]->parent = next[1];
                next[2]->next[0] = next[2]->next[1];
                next[2]->next[1] = next[2]->next[2];
                next[2]->next[2] = NULL;
            }
            else if (next[0]->size == 2) {
                if (leaf->next[1] == NULL) {
                    leaf->next[1] = leaf->next[0];
                    leaf->next[0] = NULL;
                }

                insert_in_node(
                    next[1],
                    init_item(
                        parent->info[0]->key,
                        parent->info[0]->data
                    )
                );

                parent->info[0] = init_item(next[0]->info[1]->key, next[0]->info[1]->data);
                remove_in_node(next[0], next[0]->info[1]->key);
                next[1]->next[0] = next[0]->next[2];
                if (next[1]->next[0] != NULL)
                    next[1]->next[0]->parent = next[1];
                next[0]->next[2] = NULL;
            }
        }
        else if (next[0] == leaf) {
            if (leaf->next[0] == NULL) {
                leaf->next[0] = leaf->next[1];
                leaf->next[1] = NULL;
            }

            insert_in_node(
                next[0],
                init_item(
                    parent->info[0]->key,
                    parent->info[0]->data
                )
            );

            if (next[1]->size == 2) {
                parent->info[0] = init_item(next[1]->info[0]->key, next[1]->info[0]->data);
                remove_in_node(next[1], next[1]->info[0]->key);
                next[0]->next[1] = next[1]->next[0];
                if (next[0]->next[1] != NULL) next[0]->next[1]->parent = next[0];
                next[1]->next[0] = next[1]->next[1];
                next[1]->next[1] = next[1]->next[2];
                next[1]->next[2] = NULL;
            }
            else if (next[2]->size == 2) {
                {
                    free(parent->info[0]->key);
                    free(parent->info[0]);
                }
                parent->info[0] = next[1]->info[0];
                next[1]->info[0] = parent->info[1];
                parent->info[1] = init_item(next[2]->info[0]->key, next[2]->info[0]->data);
                remove_in_node(next[2], next[2]->info[0]->key);
                next[0]->next[1] = next[1]->next[0];
                if (next[0]->next[1] != NULL) next[0]->next[1]->parent = next[0];
                next[1]->next[0] = next[1]->next[1];
                next[1]->next[1] = next[2]->next[0];
                if (next[1]->next[1] != NULL) next[1]->next[1]->parent = next[1];
                next[2]->next[0] = next[2]->next[1];
                next[2]->next[1] = next[2]->next[2];
                next[2]->next[2] = NULL;
            }
        }
    }
	else if (parent->size == 1) {
        insert_in_node(
            leaf,
            init_item(
                parent->info[0]->key,
                parent->info[0]->data
            )
        );

        if (next[0] == leaf && next[1]->size == 2) {
            parent->info[0] = init_item(next[1]->info[0]->key, next[1]->info[0]->data);
            remove_in_node(next[1], next[1]->info[0]->key);

            if (leaf->next[0] == NULL) leaf->next[0] = leaf->next[1];

            leaf->next[1] = next[1]->next[0];
            next[1]->next[0] = next[1]->next[1];
            next[1]->next[1] = next[1]->next[2];
            next[1]->next[2] = NULL;
            if (leaf->next[1] != NULL) leaf->next[1]->parent = leaf;
        }
        else if (next[1] == leaf && next[0]->size == 2) {
            parent->info[0] = init_item(next[0]->info[1]->key, next[0]->info[1]->data);
            remove_in_node(next[0], next[0]->info[1]->key);

            if (leaf->next[1] == NULL)
                leaf->next[1] = leaf->next[0];

            leaf->next[0] = next[0]->next[2];
            next[0]->next[2] = NULL;
            if (leaf->next[0] != NULL)
                leaf->next[0]->parent = leaf;
        }
    }

    return parent;
}

static B_node* merge(B_node* leaf) {
	B_node* parent = leaf->parent;

    if (parent->next[0] == leaf) {
        insert_in_node(
        	parent->next[1],
        	init_item(parent->info[0]->key, parent->info[0]->data) 
        );
        
        parent->next[1]->next[2] = parent->next[1]->next[1];
        parent->next[1]->next[1] = parent->next[1]->next[0];

        if (leaf->next[0])
        	parent->next[1]->next[0] = leaf->next[0];
        else if (leaf->next[1])
        	parent->next[1]->next[0] = leaf->next[1];

        if (parent->next[1]->next[0])
        	parent->next[1]->next[0]->parent = parent->next[1];

        remove_in_node(parent, parent->info[0]->key);
        free(parent->next[0]);
        parent->next[0] = NULL;
    }
    else if (parent->next[1] == leaf) {
		insert_in_node(
        	parent->next[0],
        	init_item(parent->info[0]->key, parent->info[0]->data) 
        );

        if (leaf->next[0])
        	parent->next[0]->next[2] = leaf->next[0];
        else if (leaf->next[1])
        	parent->next[0]->next[2] = leaf->next[1];

        if (parent->next[0]->next[2])
        	parent->next[0]->next[2]->parent = parent->next[0];

        remove_in_node(parent, parent->info[0]->key);
        free(parent->next[1]);
        parent->next[1] = NULL;
    }

    if (!parent->parent) {
        B_node* tmp = NULL;
        if (parent->next[0])
        	tmp = parent->next[0];
        else tmp = parent->next[1];
        tmp->parent = NULL;
        free(parent);
        return tmp;
    }
    return parent;
}

static B_node* fix(B_node* leaf) {
	if (leaf->size == 0 && leaf->parent == NULL) {
		free(leaf);
				
		return NULL;
	}
	if (leaf->size != 0)
		return leaf->parent? fix(leaf->parent) : leaf;

	B_node* parent = leaf->parent;
	if (parent->next[0]->size == 2 ||
		parent->next[1]->size == 2 ||
		parent->size == 2)
		leaf = redist(leaf);
	else if (parent->size == 2 &&
		parent->next[2]->size == 2)
		leaf = redist(leaf);
	else leaf = merge(leaf);

	return fix(leaf);
}

static B_node* remove_(B_node* p, char* k, bool* status) {
	B_node* item = search(p, k);

	if (!item) {
		*status = false;
		return p;
	}

	B_node* min = NULL;
	min = strcmp(item->info[0]->key, k) == 0 ?
		search_min(item->next[1]):
		search_min(item->next[2]);

	if (min) {
		swap(
			(strcmp(k, item->info[0]->key) == 0?
				&item->info[0] : &item->info[1]),
			&min->info[0]);
		
		item = min;
	}
	remove_in_node(item, k);

	return fix(item);
}



static void print(B_node* a, char* key) {
	if (!a) return;

	for (int i = a->size; i >= 0; --i) {
		if ((unsigned)i < a->size && strcmp(a->info[i]->key, key) <= 0 )
			printf("%s: %u\n", a->info[i]->key, a->info[i]->data);
			
		print(a->next[i], key);
	}		
}

static void print_(B_node* a, unsigned tab, unsigned keys_num) {
	if (!a) return;

	for (unsigned i = 0; i < a->size+1; ++i) {
		print_(a->next[i], tab+1, i);

		if (i < a->size) {
			for (unsigned i = 0; i < tab; ++i)
				printf("\t");
			printf("%d - %s: %u\n", keys_num, a->info[i]->key, a->info[i]->data);
		}
	}		
}

static B_node* search(B_node* a, const char* key) {
	if (!a) return NULL;

	if ( find(a, key) ) return a;
	else if ( strcmp(key, a->info[0]->key) < 0 )
		return search(a->next[0], key);
	else if ( (a->size == 2 && strcmp(key, a->info[1]->key) < 0 ) ||
		a->size == 1 )
		return search(a->next[1], key);
	else if ( a->size == 2)
		return search(a->next[2], key);
	else return NULL;		
}

static B_node* search_min(B_node* a) {
	if (!a) return a;
	if (!(a->next[0])) return a;
	return search_min(a->next[0]);
}

static B_node* search_max(B_node* a) {
	if (!a) return a;

	if ( is_leaf(a) ) return a;
	if (a->size == 1)
		return search_max(a->next[1]);
	return search_max(a->next[2]);
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

void tree_print(const B_tree* a, char* key) {
	print(a->root, key);
}

void tree_print_(const B_tree* a) {
	print_(a->root, 0, 0);
}

bool tree_insert(B_tree* a, const char* key, unsigned data) {
	if (!a) return false;

	bool status = false;

	Item* item = init_item(key, data);

	a->root = insert(
		a->root,
		item, &status
	);
	if (status) {
		free(item->key);
		free(item);

		return false;
	}

	return true;
}

bool tree_delete(B_tree* a, char* key) {
	if (!a) return false;

	bool status = true;
	a->root = remove_(a->root, key, &status);
	 
	return status;
}

Item* tree_find_by_key(const B_tree* a, const char* key) {
	if (!a || !a->root) return NULL;

	B_node* res = search(a->root, key);
	if (res && res->size >= 1) {
		if (strcmp(res->info[0]->key, key) == 0)
			return res->info[0];
		else if (res->size == 2 && strcmp(res->info[1]->key, key) == 0)
			return res->info[1];
	}

	return NULL;
}

Item* tree_find(const B_tree* a, const char* key) {
	if (!a) return NULL;

	B_node* res_max = search_max(a->root);
	B_node* res_min = search_min(a->root);

	unsigned hash_min = hash(res_min->info[0]->key, key),
			 hash_max = res_max->size == 1?
			 				hash(res_max->info[0]->key, key):
			 				hash(res_max->info[1]->key, key);

	bool lol = max(hash_max, hash_min) == hash_max ? 1:0;

	if (lol)
		return res_max->size == 1? res_max->info[0] : res_max->info[1];
		
	return res_min->info[0];
}
