#include <stdlib.h>

#include "lib/lib_scanf.h"
#include "lib/hashtable.h"

#define _FILE "exe/abc"

int dialog(jmp_buf* _err, const char* msg[], const int N);

int d_insert(jmp_buf* err, HTable* a) {
	char* str = get_str(err, "data > ");
	htable_insert(
		a,
		get_i(err, "key > "),
		str
	);
	free(str);
	return 1;
}

int d_delete(jmp_buf* err, HTable* a) {
	htable_delete(
		a,
		get_i(err, "key > ")
	);
	return 1;
}

int d_find(jmp_buf* err, HTable* a) {
	char* res = htable_search(
		a, get_i(err, "key > "), get_i(err, "relise > ")
	);
	res? printf("res: %s\n", res) : printf("res: %p\n", res);

	free(res);
	return 1;
}

int d_find_key(jmp_buf* err, HTable* a) {
	HTable* res = htable_search_by_key(
		a, get_i(err, "key > ")
	);
	res? printf("res:\n"), htable_print(res) : printf("res: %p\n", res);
	htable_free(res);
	free(res);

	return 1;
}

int d_show(jmp_buf* err, HTable* a) {
	htable_print(a);
	return 1;
}

int d_import(jmp_buf* err, HTable* a) {
	htable_free(a);

	FILE* file = fopen(_FILE, "r");

	char* _capacity = get_str_file(err, file);
	int capacity = atoi(_capacity);
	free(_capacity);

	char* _size = get_str_file(err, file);
	int size = atoi(_size);
	free(_size);

	htable_init(a, capacity);

	for (int i = 0; i < size; ++i) {
		char* str = get_str_file(err, file);
		char* word = strtok(str, " ");
		unsigned key = (unsigned)atoi(word);
		word = strtok(NULL, " ");

		for (; word; word = strtok(NULL, " ")) {
			char* data = strdup(word);
			htable_insert(
				a,
				key,
				data
			);
			free(data);
		}
		free(str);
	}
	fclose(file);

	return 1;
}

int main() {
	const char* msg[] = {
		"0. End",
		"1. Insert",
		"2. Delete",
		"3. Find",
		"4. Find (key)",
		"5. Show",
		"6. Import"
	};
	const int N = sizeof(msg)/sizeof(*msg);
	int (*fptr[])(jmp_buf*, HTable*) = {
		NULL,
		d_insert,
		d_delete,
		d_find,
		d_find_key,
		d_show,
		d_import
	};
	int rc = 0;

	jmp_buf _err;
	jmp_buf* err = &_err;
	bool ok = false;
	
	HTable _a;
	HTable* a = &_a;

	try(err) {
		unsigned capacity;

		do {
			capacity = get_i(err, "Capacity > ");
		} while (capacity <= 0);

		htable_init(
			a,
			capacity
		);

		ok = true;

		while (rc = dialog(err, msg, N))
			if (!fptr[rc](err, a)) break;	
	}

	if (ok) htable_free(a);

	return 0;
}

int dialog(jmp_buf* _err, const char* msg[], const int N) {
	char* err = "";
	int rc;

	do {
		puts(err);
		err = "U a wrong. Repeate...";

		for (int i = 0; i < N; ++i)
			puts(msg[i]);

		rc = get_i(_err, "> ");
		printf("\n");
	} while (rc > N);

	return rc;
}
