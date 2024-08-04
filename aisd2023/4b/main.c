#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lib/lib_scanf.h"
#include "lib/lib_Btree.h"

void timing(
	jmp_buf* err, B_tree* a,
	int (*fptr)(jmp_buf*, B_tree*)
);
void gen(jmp_buf* err);

int dialog(jmp_buf* _err, const char* msg[], const int N);
int d_insert(jmp_buf* err, B_tree* a);
int d_delete(jmp_buf* err, B_tree* a);
int d_find(jmp_buf* err, B_tree* a);
int d_find_key(jmp_buf* err, B_tree* a);
int d_show(jmp_buf* err, B_tree* a);
int d_show_tree(jmp_buf* err, B_tree* a);
int d_import(jmp_buf* err, B_tree* a);

int main() {
	const char* msg[] = {
		"0. End",
		"1. Show",
		"2. Insert",
		"3. Delete",
		"4. Find",
		"5. Find (key)",
		"6. Import",
		"7. Show(hm)"
	};
	const int N = sizeof(msg)/sizeof(*msg);
	int (*fptr[])(jmp_buf*, B_tree*) = {
		NULL,
		d_show,
		d_insert,
		d_delete,
		d_find,
		d_find_key,
		d_import,
		d_show_tree
	};
	int rc = 0;

	jmp_buf _err;
	jmp_buf* err = &_err;

	B_tree* a = tree_init();

	try(err) do {
		rc = dialog(err, msg, N);
		if (rc && rc != 54802) timing(
			err,
			a,
			fptr[rc]	
		);
		else if (rc == 54802) gen(err);
	} while (rc);

	a = tree_free(a);


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
	} while (rc > N && rc != 54802);

	return rc;
}

void timing(
	jmp_buf* err, B_tree* a,
	int (*fptr)(jmp_buf*, B_tree*) )
{
	time_t start = clock();
	
	fptr(err, a);

	printf(
		"\ntime: %.3F\n\n",
		(double)(clock()-start)/CLOCKS_PER_SEC
	);
}

void gen(jmp_buf* err) {
	int num = get_i(err, "num > ");

	FILE* file = fopen("abc", "w");

	fprintf(file, "%d\n", num);

	const char* solution = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	int len = strlen(solution);

	srand( time(0) );

	for (int i = 0; i < num; ++i) {
		int len_key = rand()%14+1;
		for (int i = 0; i < len_key; ++i)
			fprintf(file, "%c", solution[rand()%len]);
			
		fprintf(file, " %u\n", rand()%10000);
	}

	fclose(file);
}

int d_insert(jmp_buf* err, B_tree* a) {
	char* key = get_str(err, "key > ");
	int data = get_i(err, "data > ");

	tree_insert(a, key, data);

	free(key);

	return 1;
}

int d_delete(jmp_buf* err, B_tree* a) {
	char* key = get_str(err, "key > ");

	tree_delete(a, key);

	free(key);

	return 1;
}

// TODO
int d_find(jmp_buf* err, B_tree* a) {
	char* key = get_str(err, "key > ");
	
	free(key);

	return 1;
}

// TODO
int d_find_key(jmp_buf* err, B_tree* a) {
	char* key = get_str(err, "key > ");
	
	free(key);
	
	return 1;
}

int d_show(jmp_buf* err, B_tree* a) {
	tree_print(a);
	return 1;
}

int d_show_tree(jmp_buf* err, B_tree* a) {
	tree_print_(a);
	return 1;
}

int d_import(jmp_buf* err, B_tree* a) {
	FILE* file = fopen("abc", "r");

	char* _size = get_str_file(err, file);
	int size = atoi(_size);
	free(_size);

	for (int i = 0; i < size; ++i) {
		char* str = get_str_file(err, file);
		char* word = strtok(str, " ");
		char* key = strdup(word);
		word = strtok(NULL, " ");

		tree_insert(
			a,
			key,
			atoi(word)
		);

		free(key);
		free(str);
	}
	fclose(file);

	return 1;
}
