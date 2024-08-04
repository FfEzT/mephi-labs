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

static KeySpace* create_keySpace(const char* key) {
	KeySpace* res = malloc(sizeof(KeySpace));
	res->key = (char*)key;

	return res;
}

static void table_init_(Table* a, unsigned capacity) {
	a->size = 0;
	a->capacity = capacity;

	a->ks = malloc(capacity * sizeof(KeySpace*));
}

static bool _insert(Table* a, const char* _key, long offset, long offset_data) {
	char* key = strdup(_key);

	int index = table_binary_search(a, key);
	if (index < 0 && a->size == a->capacity) {
		free(key);
		return false;
	}

	KeySpace* temp = create_keySpace(key);

	temp->offset = offset;
	temp->offset_data = offset_data;
		
	if (index == NO_RESULT) {
		a->ks[0] = temp;
	}
	else if (index == AFTER_NILL) {
		for (unsigned i = a->size; i > 1; --i)
			a->ks[i] = a->ks[i-1];

		a->ks[1] = temp;
	}
	else if (index == BEFORE_NILL) {
		for (unsigned i = a->size; i > 0; --i)
			a->ks[i] = a->ks[i-1];

		a->ks[0] = temp;
	}
	else if (index < 0) {
		index *= -1;

		for (int i = a->size; i > index+1; --i)
			a->ks[i] = a->ks[i-1];

		a->ks[index+1] = temp;
	}
	++(a->size);
}

bool table_init(Table* a, char* str) {
	a->name_file = strdup(str);
	a->file = fopen(a->name_file, "rb+");

	unsigned capacity;
	bool is_new_file = !a->file;


	if (!is_new_file) {
		fseek(a->file, sizeof(unsigned), SEEK_SET);
		fread(&capacity, sizeof(unsigned), 1, a->file);
		table_init_(a, capacity);

		for (unsigned i = 0; i < capacity; ++i) {
			long offset, offset_data;
			fseek(a->file, sizeof(unsigned)*3 + i*sizeof(long), SEEK_SET);
			fread(&offset, sizeof(long), 1, a->file);

			if (offset == 0) continue;
			unsigned len;
			char* st;
			fseek(a->file, offset, SEEK_SET);
			fread(&len, sizeof(unsigned), 1, a->file);
			st = malloc(sizeof(char)*len);
			fread(st, sizeof(char), len, a->file);
			fread(&offset_data, sizeof(long), 1, a->file);
			
			_insert(a, st, offset, offset_data);

			free(st);
		}
	}
	else
		a->file = fopen(a->name_file, "w+b");

	return is_new_file;
}

void table_new(Table* a, unsigned capacity) {
	unsigned magic = 54802;
	long offset = 0;
	const unsigned nill = 0;

	fseek(a->file, 0, SEEK_SET);
	fwrite(&magic, sizeof(unsigned), 1, a->file);
	fwrite(&capacity, sizeof(unsigned), 1, a->file);
	fwrite(&nill, sizeof(unsigned), 1, a->file);

	for (unsigned i = 0; i < capacity; ++i)
		fwrite(&offset, sizeof(long), 1, a->file);

	table_init_(a, capacity);
}

bool table_insert(Table* a, const char* _key, CLASS_TABLE data) {
	const long nill = 0;
	const long one = 1;
		
	char* key = strdup(_key);

	int index = table_binary_search(a, key);
	if (index < 0 && a->size == a->capacity) {
		free(key);
		return false;
	}
	// if (data == NULL) throw(err, NO_DATA);

	if (index < 0) {
		KeySpace* temp = create_keySpace(key);
		
		if (index == NO_RESULT) {
			a->ks[0] = temp;
		}
		else if (index == AFTER_NILL) {
			for (unsigned i = a->size; i > 1; --i)
				a->ks[i] = a->ks[i-1];
	
			a->ks[1] = temp;
		}
		else if (index == BEFORE_NILL) {
			for (unsigned i = a->size; i > 0; --i)
				a->ks[i] = a->ks[i-1];
	
			a->ks[0] = temp;
		}
		else if (index < 0) {
			index *= -1;
	
			for (int i = a->size; i > index+1; --i)
				a->ks[i] = a->ks[i-1];
	
			a->ks[index+1] = temp;
		}

		increment_size: {
			++(a->size);
			fseek(a->file, 2*sizeof(unsigned), SEEK_SET);
			fwrite(&(a->size), sizeof(unsigned), 1, a->file);
		}

		rewrite_key_offset: {
			fseek(a->file, 0, SEEK_END);
			long offset = ftell(a->file);
			long isnt_empty;
			fseek(a->file, 3*sizeof(unsigned), SEEK_SET);
			
			for (unsigned i = 0; i < a->capacity; ++i) {
				fread(&isnt_empty, sizeof(long), 1, a->file);

				if (isnt_empty == 0) {
					fseek(a->file, -sizeof(long), SEEK_CUR);
					temp->offset = ftell(a->file);
					fwrite(&offset, sizeof(long), 1, a->file);

					break;
				}
			} // вышел из цикла = ошибка
		}

		write_key: {
			fseek(a->file, 0, SEEK_END);
			unsigned len = strlen(key)+1;
			fwrite(&len, sizeof(unsigned), 1, a->file);
			fwrite(key, sizeof(char), len, a->file);
			temp->offset_data = ftell(a->file)+sizeof(long);
			fwrite(&temp->offset_data, sizeof(long), 1, a->file);
		}

		write_item: {
			fwrite(&nill, sizeof(bool), 1, a->file); // is deleted
			fwrite(&data, sizeof(unsigned), 1, a->file); // data
			fwrite(&one, sizeof(unsigned), 1, a->file); // version
			fwrite(&nill, sizeof(long), 1, a->file); // offset of next item
		}
	}
	else {
		free(key);
		long offset = a->ks[index]->offset_data;
		unsigned version = 1;

		while (offset) {
			fseek(
				a->file,
				offset+sizeof(bool)+sizeof(unsigned)*2,
				SEEK_SET
			);
			fread(&offset, sizeof(long), 1, a->file);
			++version;
		}
		fseek(a->file, -sizeof(long), SEEK_CUR);
		offset = ftell(a->file);
		
		fseek(a->file, 0, SEEK_END);
		long pre_offset = ftell(a->file); 
		fseek(a->file, offset, SEEK_SET);
		fwrite(&pre_offset, sizeof(long), 1, a->file);

		write_item_: {
			fseek(a->file, 0, SEEK_END);
			fwrite(&nill, sizeof(bool), 1, a->file); // is deleted
			fwrite(&data, sizeof(unsigned), 1, a->file); // data
			fwrite(&version, sizeof(unsigned), 1, a->file); // version
			fwrite(&nill, sizeof(long), 1, a->file); // offset of next item
		}
	}
	
	return true;
}

void table_delete_by_key(Table* table, const char* key) {
	int index = table_binary_search(table, key);

	if (index < 0) return;


	const unsigned nill = 0;

	fseek(table->file, table->ks[index]->offset, SEEK_SET);
	fwrite(&nill, sizeof(unsigned), 1, table->file);

	free(table->ks[index]->key);
	free(table->ks[index]);

	for (unsigned i = index; i < table->size-1; ++i)
		table->ks[i] = table->ks[i+1];
		
	--(table->size);
	fseek(table->file, sizeof(int)*2, SEEK_SET);
	fwrite(&table->size, sizeof(int), 1, table->file);
}

void table_delete(Table* table, const char* key, unsigned _index) {
	const int nill = 1;

	int bin = table_binary_search(table, key);

	if (bin < 0) return;
	long offset;
	unsigned index;
	fseek(
		table->file,
		table->ks[bin]->offset_data+sizeof(bool)+sizeof(unsigned),
		SEEK_SET
	);
	fread(&index, sizeof(unsigned), 1, table->file);

	while (index != _index) {
		fread(&offset, sizeof(long), 1, table->file);
		if (!offset) break;
	
		fseek(
			table->file,
			offset+sizeof(bool)+sizeof(unsigned),
			SEEK_SET
		);
		fread(&index, sizeof(unsigned), 1, table->file);
	}

	if (index == _index) {
		fseek(
			table->file,
			-(sizeof(unsigned)*2 + sizeof(bool) ),
			SEEK_CUR
		);
		fwrite(&nill, sizeof(bool), 1, table->file);
	}
}

void table_free(Table* table) {
	fclose(table->file);
	for (unsigned i = 0; i < table->size; ++i) {
		free(table->ks[i]->key);
		free(table->ks[i]);
	}
	free(table->ks);
	free(table->name_file);

	
	table->ks = NULL;
	table->capacity = table->size = 0;
}

// TODO
int table_get(const Table* table, const char* key, unsigned _index) {
	int bin = table_binary_search(table, key);
	if (bin < 0) return -1;

	long offset = table->ks[bin]->offset_data;
	unsigned index;
	bool flag;

	while (offset) {
		fseek(
			table->file,
			offset+sizeof(bool)+sizeof(unsigned),
			SEEK_SET
		);
		fread(&index, sizeof(unsigned), 1, table->file);

		if (index >= _index) {
			fseek(table->file, sizeof(long), SEEK_CUR);
			break;
		}
		
		fread(&offset, sizeof(long), 1, table->file);
	}
	
	if (index != _index) return -1;
	
	fseek(
		table->file,
		-( sizeof(long) + sizeof(unsigned)*2 + sizeof(bool) ),
		SEEK_CUR
	);
	fread(&flag, sizeof(bool), 1, table->file);

	if (flag) return -1;
	fread(&index, sizeof(unsigned), 1, table->file);

	return index;
}

long table_get_by_key(const Table* table, const char* key) {
	int index = table_binary_search(table, key);
	if (index < 0) return -1;

	return table->ks[index]->offset_data;
}

void print(Table* a) {
	for (unsigned i = 0; i < a->size; ++i) {
		printf("%s: ", a->ks[i]->key);

		bool deleted;
		unsigned data, version;
		long offset = a->ks[i]->offset_data;
		
		while (offset) {
			fseek(a->file, offset, SEEK_SET);
			fread(&deleted, sizeof(bool), 1, a->file);
			fread(&data, sizeof(unsigned), 1, a->file);
			fread(&version, sizeof(unsigned), 1, a->file);
			fread(&offset, sizeof(long), 1, a->file);

			if (!deleted) printf("%u(%u) ", data, version);
		}

		printf("\n");
	}
}
