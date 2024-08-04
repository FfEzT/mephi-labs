#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "lib_scanf.h"

typedef struct {
	unsigned rows;
	unsigned* columns;
	int** data;
} Matrix;

Matrix* matrix_init();
void matrix_free(Matrix*);
void matrix_print(const Matrix* a);
void matrix_fill(Matrix*);
Matrix* matrix_cp(const Matrix*);

Matrix* process(const Matrix*);
int* maxim(const int* arr, unsigned size);
int* minim(const int* arr, unsigned size);

int main() {
	Matrix* obj = matrix_init();
	matrix_fill(obj);
	matrix_print(obj);
	printf("\n\n\n");

	Matrix* calculated = process(obj);
	
	matrix_print(calculated);
	printf("\n\n\n");

	matrix_free(obj);
	matrix_free(calculated);

	return 0;
}

Matrix* matrix_init() {
	Matrix* res = malloc(
		sizeof(Matrix)
	);
	res->rows = 0;
	res->columns = NULL;
	res->data = NULL;
	
	return res;
}
Matrix* matrix_cp(const Matrix* a) {
	Matrix* res = matrix_init();

	res->rows = a->rows;

	res->columns = malloc(
		sizeof(int) * a->rows
	);
	memcpy(
		res->columns,
		a->columns,
		sizeof(int) * a->rows
	);

	res->data = malloc(
		sizeof(int*) * a->rows
	);

	for (unsigned i = 0; i < a->rows; ++i) {
		res->data[i] = malloc(
			sizeof(int) * a->columns[i]
		);
		
		memcpy(
			res->data[i],
			a->data[i],
			sizeof(int) * a->columns[i]
		);
	}

	return res;
}

void matrix_free(Matrix* a) {
	for (unsigned i = 0; i < a->rows; ++i) free(a->data[i]);
	free(a->data);
	free(a->columns);
	free(a);
}

void matrix_fill(Matrix* a) {
	unsigned rows = get_i("Кол-во строк > ");
	a->rows = rows;

	a->columns = malloc(
		sizeof(int) * rows
	);
	a->data = malloc(
		sizeof(int*) * rows
	);
	for (unsigned i = 0; i < rows; ++i) {
		printf("Кол-во столбцов в %u строке > ", i);
		unsigned column = get_i("");
		a->columns[i] = column;
		a->data[i] = malloc(
			column * sizeof(int)
		);

		for (unsigned j = 0; j < column; ++j) {
			printf("[%u][%u]", i, j);
			a->data[i][j] = get_num(" > ");
		}
	}
}
void matrix_print(const Matrix* a) {
	for (unsigned i = 0; i < a->rows; ++i) {
		for (unsigned j = 0; j < a->columns[i]; ++j)
			printf("%5d\t", a->data[i][j]);
		
		printf("\n");
	}
}

Matrix* process(const Matrix* src) {
	Matrix* a = matrix_cp(src);
	
	for (unsigned i = 0; i < a->rows; ++i) {
		int* max = maxim(a->data[i], a->columns[i]);
		int* min = minim(a->data[i], a->columns[i]);

		int temp = *max;
		*max = *min;
		*min = temp;
	}

	return a;
}

int* maxim(const int* arr, unsigned size) {
	int* res = (int*)arr;
	for (unsigned i = 0; i < size; ++i)
		if (*res < arr[i]) res = (int*)&(arr[i]);

	return res;
}

int* minim(const int* arr, unsigned size) {
	int* res = (int*)arr;
	for (unsigned i = 0; i < size; ++i)
		if (*res > arr[i]) res = (int*)&(arr[i]);

	return res;
}
