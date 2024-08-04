#include "../lib/lib_table.h"
#include "../lib/lib_scanf.h"

#define _FILE "a/abc"

int dialog(jmp_buf* _err, const char* msgs[], const int N);

int d_insert(jmp_buf*, Table* a);
int d_delete(jmp_buf*, Table* a);
int d_delete_key(jmp_buf*, Table* a);
int d_find(jmp_buf*, Table* a);
int d_find_key(jmp_buf*, Table* a);
int d_find_index(jmp_buf*, Table* a);
int d_show(jmp_buf*, Table* a);
int d_import(jmp_buf*, Table* a);


int main() {
	jmp_buf _err;
	jmp_buf* err = &_err;
	bool ok = false;

	Table _t;
	Table* t = &_t;

	try(err) {
		unsigned capacity = get_i(err, "Input capacity of table > ");
		table_init(t, capacity);
		ok = true;

		const char* msg[] = {
			"0. Quit",
			"1. Insert",
			"2. Delete",
			"3. Delete by Key",
			"4. Find",
			"5. Find by Key",
			"6. Find by Index",
			"7. Show",
			"8. Import"
		};
		const int N = sizeof(msg) / sizeof(*msg);
		int (*fptr[])(jmp_buf*, Table*) = {
			NULL,
			d_insert,
			d_delete,
			d_delete_key,
			d_find,
			d_find_key,
			d_find_index,
			d_show,
			d_import,
		};
		int rc = 0;
		

		while ( rc = dialog(err, msg, N) )
			if ( !fptr[rc](err, t) ) break;

	}
	if (ok) table_free(t, 0);
	

	printf("That's all\n");
	
	return 0;
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

int d_insert(jmp_buf* err, Table* a) {
	char* key = get_str(err, "Input key > ");
	table_insert(
		err,
		a,
		key,
		get_i(err, "Input val > ")
	);
	free(key);

	return 1;
}
int d_delete(jmp_buf* err, Table* a) {
	char* key = get_str(err, "Input key > ");
	table_delete(
		a,
		key,
		get_i(err, "Input index > "),
		0
	);
	free(key);

	return 1;
}
int d_delete_key(jmp_buf* err, Table* a) {
	char* key = get_str(err, "Input key > ");
	table_delete_by_key(
		a,
		key,
		0
	);
	free(key);

	return 1;
}
int d_find(jmp_buf* err, Table* t) {
	char* key = get_str(err, "Input key > ");
	unsigned* res = table_get(
		t,
		key,
		get_i(err, "Input index > ")
	);

	res? printf("%u\n", *res) : printf("No result\n");
	
	free(key);

	return 1;
}
int d_find_key(jmp_buf* err, Table* t) {
	char* key = get_str(err, "Input key > ");
	Table* res = table_get_by_key(
		t,
		key
	);
	d_show(err, res);
	
	if (res) table_free(res, 0), free(res);
		
	free(key);

	return 1;
}
int d_find_index(jmp_buf* err, Table* t) {
	Table* res = table_get_by_index(
		t,
		get_i(err, "Input index > ")
	);
	d_show(err, res);

	if (res) table_free(res, 0), free(res);

	return 1;
}
int d_show(jmp_buf* err, Table* t) {
	if (!t)	printf("NULL\n");	
	else for (unsigned i = 0; i < t->size; ++i) {
		printf("%s: ", t->ks[i]->key);

		Node* a = t->ks[i]->ls->first;
		for (; a; a = a->next) printf("%u ", a->data);
		
		printf("\n");					
	}

	return 1;
}
int d_import(jmp_buf* err, Table* t) {
	table_free(t, 0);

	FILE* a = fopen(_FILE, "r");

	char* _capacity = get_str_file(err, a); 
	int capacity = atoi(_capacity);
	free(_capacity);
	
	char* _size = get_str_file(err, a); 
	int size = atoi(_size);
	free(_size);
	
	table_init(t, capacity);

	for (int i = 0; i < size; ++i) {
		char* str = get_str_file(err, a);
		char* word = strtok(str, " ");
		char* key = strdup(word);
		word = strtok(NULL, " ");

		for (; word; word = strtok(NULL, " ") ) {
			table_insert(err,
				t,
				key,
				(unsigned)atoi(word)
			);
		}

		free(key);
		free(str);
	}

	fclose(a);

	return 1;
}

