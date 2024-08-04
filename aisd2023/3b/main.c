#include <stdio.h>
#include <stdlib.h>

#include "lib_table.h"
#include "../lib/lib_scanf.h"

int dialog(jmp_buf*, const char* msgs[], const int N);

int d_insert(jmp_buf*, Table*);
int d_delete(jmp_buf*, Table*);
int d_delete_key(jmp_buf*, Table*);
int d_find(jmp_buf*, Table*);
int d_find_key(jmp_buf*, Table*);
int d_show(jmp_buf*, Table*);

int main() {
	jmp_buf _err;
	jmp_buf* err = &_err;
	bool ok = false;
	bool _ok = false;

	Table _t;
	Table* t = &_t;

	char* str;
	try(err) {
		str = get_str(err, "Name of file > ");
		_ok = true;
		if ( table_init(t, str) )
			table_new( t, get_i(err, "Capacity > ") );
		ok = true;
	}
	catch_all printf("Hm...\n");
	if (_ok) free(str);

	const char* msg[] = {
		"0. Quit",
		"1. Insert",
		"2. Delete",
		"3. Delete by Key",
		"4. Find",
		"5. Find by Key",
		"6. Show"
	};
	const int N = sizeof(msg)/sizeof(*msg);
	int (*fptr[])(jmp_buf*, Table*) = {
		NULL,
		d_insert,
		d_delete,
		d_delete_key,
		d_find,
		d_find_key,
		d_show
	};
	int rc = 0;

	try(err) while (rc = dialog(err, msg, N))
		if ( !fptr[rc](err, t) ) break;

	if (ok) table_free(t);

	printf("That's all\n");
	
	return 0;
}

int d_insert(jmp_buf* err, Table* t) {
	char* key = get_str(err, "Input key > ");
	table_insert(
		t,
		key,
		get_i(err, "Input val > ")
	);
	free(key);

	return 1;
}
int d_delete(jmp_buf* err, Table* t) {
	char* key = get_str(err, "Input key > ");
	table_delete(
		t,
		key,
		get_i(err, "Input index > ")
	);
	free(key);
	return 1;
}
int d_delete_key(jmp_buf* err, Table* t) {
	char* key = get_str(err, "Input key > ");
	table_delete_by_key(t, key);
	free(key);
	return 1;
}
int d_find(jmp_buf* err, Table* t) {
	char* key = get_str(err, "Input key > ");
	unsigned index = get_i(err, "Input index > ");

	printf("Data: %d\n",
		table_get(t, key, index)
	);
	
	free(key);

	return 1;
}
int d_find_key(jmp_buf* err, Table* t) {
	char* key = get_str(err, "Input key > ");

	bool deleted;
	unsigned data, version;
	long offset = table_get_by_key(t, key);
	free(key);

	if (offset == -1) {
		printf("LOL\n");
		return 1;
	}
	
	do {
		fseek(t->file, offset, SEEK_SET);
		fread(&deleted, sizeof(bool), 1, t->file);
		fread(&data, sizeof(unsigned), 1, t->file);
		fread(&version, sizeof(unsigned), 1, t->file);
		fread(&offset, sizeof(long), 1, t->file);

		if (!deleted) printf("%u(%u) ", data, version);
	} while (offset);
		
	return 1;
}

int d_show(jmp_buf* err, Table* t) {
	print(t);
	return 1;
}

int dialog(jmp_buf* _err, const char* msgs[], int N) {
	char* err = "";
	int rc;

	do {
		puts(err);
		err = "U a wrong. Please, repeate!";

		for (int i = 0; i < N; ++i) 
			puts(msgs[i]);

		rc = get_i(_err, "Make ur choice: --> ");
		printf("\n");
	} while (rc > N);

	return rc;
}
