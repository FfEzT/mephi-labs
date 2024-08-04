#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hashtable.h"

static unsigned get_hash(const HTable* table, unsigned key) {
	unsigned res = key;

	res += ~(res << 16);
	res ^= res >> 5;
	res += res << 3;
	res ^= res >> 13;
	res += ~(res << 9);
	res ^= res >> 17;


	return res%table->capacity;
}

inline static unsigned get_max(unsigned a, unsigned b) {
	return a>b? a:b;
}

void htable_init(HTable* table, unsigned capacity) {
	table->capacity = capacity;
	table->size = 0;

	table->ks = calloc(capacity, sizeof(KeySpace));
}

void htable_free(HTable* table) {
	for (unsigned i = 0; i < table->capacity; ++i) {
		if (table->ks[i].data != NULL) {
			if (table->ks[i].data->data != NULL)
				free(table->ks[i].data->data);
			free(table->ks[i].data);
		}
	}
	free(table->ks);
}

void htable_print(const HTable* table) {
	for (unsigned i = 0; i < table->capacity; ++i) {
		printf("%u", i);
		if (table->ks[i].data != NULL && table->ks[i].data->data != NULL)
			printf(
				"i: %u, key: %u, relise: %u, data: %s\n",
				i,
				table->ks[i].key,
				table->ks[i].relise,
				table->ks[i].data->data
			);
	}
}

bool htable_insert(HTable* table, unsigned key, char* data) {
	if (table->size == table->capacity) return false;

	unsigned hash = get_hash(table, key);
	if (table->ks[hash].data == NULL) {
		table->ks[hash].data = malloc(sizeof(Item));
		table->ks[hash].data->data = strdup(data);
		table->ks[hash].relise = 1;
		table->ks[hash].key = key;
	}
	else {
		unsigned index = hash;
		unsigned max = 0;
		bool hz = false;

		do {
			if (table->ks[index].key == key)
				max = get_max(max, table->ks[index].relise);

			if (table->ks[index].data->data == NULL && !hz)
				hash = index, hz = true;

			index = (index + 1) % table->capacity;
		} while (table->ks[index].data != NULL);

		if (!hz)
			hash = index, table->ks[hash].data = malloc(sizeof(Item));

		table->ks[hash].data->data = strdup(data);
		table->ks[hash].relise = max+1;
		table->ks[hash].key = key;
	}

	++table->size;

	return true;
}

bool htable_delete(HTable* table, unsigned key) {
	if (table->size == 0) return false;

	unsigned hash = get_hash(table, key);
	unsigned iterations = 1;
	do {
		if (table->ks[hash].key == key &&
			table->ks[hash].data != NULL &&
			table->ks[hash].data->data != NULL
		) {
			--table->size;
			
			free(table->ks[hash].data->data);
			table->ks[hash].data->data = NULL;
			
			if (table->ks[(hash+1) % table->capacity].data == NULL) {
				free(table->ks[hash].data);
				table->ks[hash].data = NULL;
			}
		}
		if (table->capacity < ++iterations) break;
		hash = (hash+1) % table->capacity;
	} while (table->ks[hash].data != NULL);

	return true;
}

char* htable_search(HTable* table, unsigned key, unsigned relise) {
	unsigned hash = get_hash(table, key);
	unsigned iterations = 1;
	char* res = NULL;

	do {
		if (table->ks[hash].key == key &&
			table->ks[hash].relise == relise &&
			table->ks[hash].data != NULL &&
			table->ks[hash].data->data != NULL
		) {
			res = strdup(table->ks[hash].data->data);
			break;
		}
		if (table->capacity < ++iterations) break;
		hash = (hash+1)%table->capacity;
	} while (table->ks[hash].data);

	return res;
}

HTable* htable_search_by_key(HTable* table, unsigned key) {
	HTable* res = malloc(sizeof(HTable));
	htable_init(res, table->capacity);

	unsigned hash = get_hash(table, key);
	unsigned iterations = 1;

	do {
		if (table->ks[hash].key == key &&
			table->ks[hash].data != NULL &&
			table->ks[hash].data->data != NULL
		) {
			char* data = strdup(table->ks[hash].data->data);
			htable_insert(res, key, data);
			free(data);
		}
		if (table->capacity < ++iterations) break;
		hash = (hash+1)%table->capacity;
	} while (table->ks[hash].data);

	return res;
}
