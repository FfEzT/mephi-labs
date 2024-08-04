#include <stdbool.h>

#include "lib_arr.h"

enum Type {
	START,
	END,
	NICE
};

typedef struct {
	unsigned cord[2];
	enum Type type;
} Point;

typedef struct Matrix Matrix;

Matrix* matr_init();
Matrix* matr_free(Matrix*);
void matr_show(Matrix* a);
bool matr_insert_v(Matrix* a, unsigned x, unsigned y, enum Type type);
bool matr_del_v(Matrix* a, unsigned num);
Array* matr_get_near(Matrix* a, unsigned num);
Array* matr_get_input(Matrix* a);
Array* matr_get_output(Matrix* a);
void matr_add_u(Matrix* a, unsigned from, Point* to);
bool matr_del_u(Matrix* a, unsigned from, unsigned to);
bool matr_connect(Matrix*, unsigned from);
Array* matr_path(Matrix*, Point* from, Point* to);
Array* matr_kaf12(Matrix*, Point* from);
Array* matr_all_point(Matrix*);
