#include <stdlib.h>
#include <string.h>

#include "lib/lib_scanf.h"
#include "lib/Matrix.h"

int dialog(jmp_buf* _err, const char* msg[], const int N);
int d_show(jmp_buf* err, Matrix* a);
int d_insert_v(jmp_buf* err, Matrix* a);
int d_delete_v(jmp_buf* err, Matrix* a);
int d_insert_u(jmp_buf* err, Matrix* a);
int d_delete_u(jmp_buf* err, Matrix* a);
int d_nice(jmp_buf* err, Matrix* a); // обход
int d_deicstra(jmp_buf* err, Matrix* a);
int d_secret(jmp_buf* err, Matrix* a); // special operation
int import(jmp_buf*, Matrix *a);

int main() {
	const char* msg[] = {
		"0. End",
		"1. Show",
		"2. Insert V",
		"3. Delete V",
		"4. Insert U",
		"5. Delete U",
		"6. Hz (обход)",
		"7. Dejctsraraseasda",
		"8. Special operation",
		"9. Import"
	};
	const int N = sizeof(msg)/sizeof(*msg);
	int (*fptr[])(jmp_buf*, Matrix*) = {
		NULL,
		d_show,
		d_insert_v,
		d_delete_v,
		d_insert_u,
		d_delete_u,
		d_nice,
		d_deicstra,
		d_secret,
		import
	};
	int rc = 0;

	jmp_buf _err;
	jmp_buf* err = &_err;

	Matrix* a = matr_init();

	try(err) do {
		rc = dialog(err, msg, N);
		if (fptr[rc]) fptr[rc](err, a);
	} while (rc);

	a = matr_free(a);

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

int d_show(jmp_buf* err, Matrix* a) {
	matr_show(a);

	return 1;
}

int d_insert_v(jmp_buf* err, Matrix* a) {
	int x = get_i(err, "x > "),
		y = get_i(err, "y > "),
		type;
	char* type_s = get_str(err, "type > ");

	if (strcmp(type_s, "start") == 0)
		type = START;
	else if (strcmp(type_s, "end") == 0)
		type = END;
	else type = NICE;
	free(type_s);

	matr_insert_v(a, x, y, type);

	return 1;
}

int d_delete_v(jmp_buf* err, Matrix* a) {
	matr_show(a);

	matr_del_v(a, get_i(err, "Choose V > ") );

	return 1;
}

int d_insert_u(jmp_buf* err, Matrix* a) {
	matr_show(a);

	unsigned from = get_i(err, "Choose from V > ");
	
	Array* list = matr_get_near(a, from);

	if (list && list->count != 0) {
		for (int i = 0; i < list->count; ++i) {
			Point* b = list->ptr[i];
			printf("%u: (%u, %u) %u\n", i, b->cord[0], b->cord[1], b->type);
		}

		int to = 0;
		do to = get_i(err, "Choose to V > ");
		while(to >= list->count);
		
		matr_add_u(
			a,
			from,
			list->ptr[to]
		);

		arr_free(list, 0);
		free(list);
	}

	return 1;
}
int d_delete_u(jmp_buf* err, Matrix* a) {
	matr_show(a);
	matr_del_u(
		a,
		get_i(err, "Choose from V > "),
		get_i(err, "Choose to V > ")
	);

	return 1;
	
}

int d_nice(jmp_buf* err, Matrix* a) {
	printf(
		"%d\n",
		matr_connect(a, get_i(err, "Choose from V > ") )
	);

	return 1;
}

int d_deicstra(jmp_buf* err, Matrix* a) {
	Array* list = matr_get_input(a);
	
	if (list && list->count != 0) {
		for (int i = 0; i < list->count; ++i) {
			Point* b = list->ptr[i];
			printf("%u: (%u, %u) %u\n", i, b->cord[0], b->cord[1], b->type);
		}

		int from;
		do from = get_i(err, "Choose from V > ");
		while(from >= list->count);

		Array* out = matr_get_output(a);

		if (out || out->count != 0) {
			for (int i = 0; i < out->count; ++i) {
				Point* b = out->ptr[i];
				printf("%u: (%u, %u) %u\n", i, b->cord[0], b->cord[1], b->type);
			}

			int to = 0;
			do to = get_i(err, "Choose to V > ");
			while(to >= list->count);

			{
				Array* res = matr_path(a, list->ptr[from], out->ptr[to]);
				
				if (res) {
					for (int i = res->count-1; i >= 0; --i)
						printf("%u ", (unsigned)res->ptr[i]);
				
					arr_free(res, 0);
					free(res);
				}
			}
		}
		if (out) {
			arr_free(out, 0);
			free(out);
		}
	}
	if (list) {
		arr_free(list, 0);
		free(list);
	}

	return 1;
}
int d_secret(jmp_buf* err, Matrix* a) {
	Array* list = matr_get_input(a);
		
	if (list && list->count != 0) {
		for (int i = 0; i < list->count; ++i) {
			Point* b = list->ptr[i];
			printf("%u: (%u, %u) %u\n", i, b->cord[0], b->cord[1], b->type);
		}

		int from;
		do from = get_i(err, "Choose from V > ");
		while(from >= list->count);

		{
			Array* res = matr_kaf12(a, list->ptr[from]);
			
			if (res) {
				// printf("Size %u\n", res->count);
				
				for (int i = res->count; i >= 0; --i)
					printf("%u ", (unsigned)res->ptr[i]);
			
				arr_free(res, 0);
				free(res);
			}
		}
	}
	
	if (list) {
		arr_free(list, 0);
		free(list);
	}

	return 1;
}

int import(jmp_buf*, Matrix *a) {
	FILE* file = fopen("abc", "r");

	int count;
	{
		char* n = get_str_file(0, file);
		count = atoi(n);
		free(n);
	}

	for (int i = 0; i < count; ++i) {
		char* n = get_str_file(0, file);

		matr_insert_v(
			a,
			atoi( strtok(n, " ") ),
			atoi( strtok(0, " ") ),
			(enum Type)atoi( strtok(0, " ") )
		);
		
		free(n);
	}

	{
		char* n = get_str_file(0, file);
		count = atoi(n);
		free(n);
	}

	Array* r = matr_all_point(a);

	for (int i = 0; i < count; ++i) {
		char* n = get_str_file(0, file);

		matr_add_u(
			a,
			atoi( strtok(n, " ") ),
			r->ptr[ atoi( strtok(0, "") ) ]
		);
		
		free(n);
	}

	fclose(file);	
}







