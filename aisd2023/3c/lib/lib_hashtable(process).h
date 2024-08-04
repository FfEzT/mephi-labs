#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 50000 // Size of hashtable

typedef unsigned long ul;
typedef struct Ht_item Ht_item;
typedef struct HashTable HashTable;

ul hash_function(char* str);

Ht_item* create_item(char* key, char* value);
HashTable* create_table(int size);
void free_item(Ht_item* item);
void free_table(HashTable* table);
void handle_collision(HashTable* table, unsigned long index, Ht_item* item);
void ht_insert(HashTable* table, char* key, char* value);
char* ht_search(HashTable* table, char* key);
void print_search(HashTable* table, char* key);
void print_table(HashTable* table);

struct Ht_item {
    char* key;
    char* value;
};

struct HashTable {
    Ht_item** items;
    int size;
    int count;
};

// TODO rewrite: bad hash function
ul hash_function(char* str) {
    ul i = 0;
    for (int j = 0; str[j]; ++j) i += str[j];

    return i % CAPACITY;
}

Ht_item* create_item(char* key, char* value) {
    Ht_item* item = (Ht_item*)malloc( sizeof(Ht_item) );
    if (item == NULL) exit(1); // stop TODO add throw

    item->key = (char*)malloc( strlen(key) + 1 );
    item->value = (char*)malloc( strlen(value) + 1 );

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

HashTable* create_table(int size) {
    HashTable* table = malloc( sizeof(HashTable) );
    if (table == NULL) exit(1); // stop TODO add throw
    
    table->size = size;
    table->count = 0;

    table->items = (Ht_item**)calloc(size * sizeof(Ht_item) );
    if (table->items == NULL) exit(1); // stop TODO add throw

    return table;
}

void free_item(Ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    for (int i = 0; i < table->size; ++i)
        free(table->items[i]);

    free(table->items);
    free(table);
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
}

void ht_insert(HashTable* table, char* key, char* value) {
    Ht_item* item = create_item(key, value);

    ul index = hash_function(key);

    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {
        // Hash Table Full
        if (table->count == table->size) {
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }
        // Insert
        else {
            table->items[index] = item;
            ++table->count;
        }
    }
    else {
        // Just update value
        if ( !strcmp(current_item->key, key) )
            strcpy(table->items[index]->value, value);
        // Collision
        // TODO
        else handle_collision(table, index, item);
    }
}

char* ht_search(HashTable* table, char* key) {
    // Searches the key in the hashtable
    Ht_item* item = table->items[ hash_function(key) ];

    if (item != NULL && !strcmp(item->key, key) ) return item->value;
    else return NULL;
}

void print_search(HashTable* table, char* key) {
    char* val;
    if ( (val = ht_search(table, key)) == NULL )
        printf("Key:%s does not exist\n", key);
    else printf("Key:%s, Value:%s\n", key, val);
}

void print_table(HashTable* table) {
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (table->items[i])
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);
    }
    printf("-------------------\n\n");
}
