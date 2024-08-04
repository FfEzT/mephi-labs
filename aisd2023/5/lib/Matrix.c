#include <stdlib.h>
#include <stdio.h>

#include "Matrix.h"
#include "lib_list.h"

typedef struct Matrix {
	unsigned size;
	Array* arr;
	Array* ptr;	
} Matrix;

static int mini(int a, int b) {
	return a <= b ? a : b;
}

static int absolute(int a) {
	return a >= 0? a : -a;
}

static int search_index_point(Matrix* a, Point* el) {
	for (unsigned i = 0; i < a->size; ++i) {
		Point* lol = a->ptr->ptr[i];
		if (lol->cord[0] == el->cord[0] && lol->cord[1] == el->cord[1])
			return i;
	}
	return -1;
}

static Point* find_by_cords(Matrix* a, unsigned cord[2]) {
	for (unsigned i = 0; i < a->size; ++i) {
		Point* hz = a->ptr->ptr[i];

		if (hz->cord[0] == cord[0] && hz->cord[1] == cord[1])
			return hz;
	}
	return NULL;
}

Matrix* matr_init() {
	Matrix* res = malloc(sizeof(Matrix));

	res->size = 0;

	res->ptr = malloc(sizeof(Array));
	arr_init(res->ptr);
	
	res->arr = malloc(sizeof(Array));
	arr_init(res->arr);

	return res;
}

Matrix* matr_free(Matrix* a) {
	for (unsigned i = 0; i < a->size; ++i) {
		List* lol = a->arr->ptr[i];
		list_free(lol, 0);
	}
	
	arr_free(a->arr, 1);
	free(a->arr);

	arr_free(a->ptr, 1);
	free(a->ptr);

	free(a);

	return NULL;
}

void matr_show(Matrix* a) {
	for (unsigned row = 0; row < a->size; ++row) {
		List* ptr = a->arr->ptr[row];

		Array stack;
		arr_init(&stack);
		for (unsigned i = 0; i < ptr->size; ++i) 
			arr_insert(
				&stack,
				stack.count,
				*list_at(ptr, i)
			);

		/* sort */ {
			for (int i = 0; i < stack.count-1; ++i) {
				for (int j = 0; j < stack.count - i - 1; ++j) {
					if (stack.ptr[j] > stack.ptr[j+1]) {
						void* tmp = stack.ptr[j];
						stack.ptr[j] = stack.ptr[j+1];
						stack.ptr[j+1] = tmp;
					}
				}
			}
		}

		unsigned it_j = 0;
		for (unsigned column = 0; column < a->size; ++column) {
			if (stack.count != 0 && column == (unsigned)stack.ptr[it_j]) {
				it_j = (it_j+1) % stack.count;
				printf("1");
			}
			else printf("0");

			printf(" ");
		}
		arr_free(&stack, 0);		
		printf("\n");
	}

	for (unsigned i = 0; i < a->size; ++i) {
		Point* ptr = a->ptr->ptr[i];
		
		printf("Point %u(%u, %u), %u\n", i, ptr->cord[0], ptr->cord[1], ptr->type);
	}
}

bool matr_insert_v(Matrix* a, unsigned x, unsigned y, enum Type type) {
	unsigned temp[] = {x, y};

	if (find_by_cords(a, temp))
		return false;

	Point* new = malloc(sizeof(Point));
	new->cord[0] = x;
	new->cord[1] = y;
	new->type = type;
	
	arr_insert(a->ptr, a->size, new);

	List* _new = malloc(sizeof(List));
	list_init(_new);
	arr_insert(a->arr, a->size, _new);
	
	++a->size;

	return true;
}

bool matr_del_v(Matrix* a, unsigned num) {
	if (num >= a->size)
		return false;


	for (unsigned i = 0; i < a->size; ++i) {
		List* temp = a->arr->ptr[i];
		for (unsigned i = 0; i < temp->size; ++i) {
			void* tmp = *list_at(temp, i);

			if (tmp == (void*)num)
				list_delete(temp, i, 0);
		}
	}
	List* hz = a->arr->ptr[num];
	list_free(hz, 0);
	arr_delete(a->arr, num, 1);

	arr_delete(a->ptr, num, 1);

	--a->size;

	return true;
}

Array* matr_get_near(Matrix* a, unsigned num) {
	if (num >= a->size) return NULL;


	Array* new = malloc(sizeof(Array));
	arr_init(new);
	
	Point* eq = a->ptr->ptr[num];
	for (unsigned i = 0; i < a->size; ++i) {
		if (i == num) continue;

		Point* ptr = a->ptr->ptr[i];

		if (eq->cord[0] == ptr->cord[0] && absolute(eq->cord[1] - ptr->cord[1]) == 1 ||
		    eq->cord[1] == ptr->cord[1] && absolute(eq->cord[0] - ptr->cord[0]) == 1 ) {
		 	arr_insert(new, new->count, ptr);   	
	    }
	}

	return new;
}

Array* matr_get_input(Matrix* a) {
	Array* new = malloc(sizeof(Array));
	arr_init(new);
	
	for (unsigned i = 0; i < a->size; ++i) {
		Point* ptr = a->ptr->ptr[i];

		if (ptr->type == START)
		 	arr_insert(new, new->count, ptr);   	
	}

	return new;
}

Array* matr_get_output(Matrix* a) {
	Array* new = malloc(sizeof(Array));
	arr_init(new);
	
	for (unsigned i = 0; i < a->size; ++i) {
		Point* ptr = a->ptr->ptr[i];

		if (ptr->type == END)
		 	arr_insert(new, new->count, ptr);   	
	}

	return new;
}

void matr_add_u(Matrix* a, unsigned from, Point* p_to) {
	int to = search_index_point(a, p_to);

	if (from == to)
		return;

	List* ar = a->arr->ptr[from];
	for (unsigned i = 0; i < ar->size; ++i) {
		int tmp = (int)*list_at(ar, i);
		if (tmp == to)
			return;
	}

	list_push_back(ar, (void*)to);
}

bool matr_del_u(Matrix* a, unsigned from, unsigned to) {
	if (from >= a->size || to >= a->size || from == to)
		return false;

	List* ar = a->arr->ptr[from];
	for (unsigned i = 0; i < ar->size; ++i) {
		unsigned tmp = (unsigned)*list_at(ar, i);

		if (tmp == to) {
			list_delete(ar, i, 0);
			return 1;
		}
	}

	return false;
}

bool matr_connect(Matrix* a, unsigned _from) {
	if (_from >= a->size)
		return false;
	
	{
		Point* aga = a->ptr->ptr[_from];
		if (aga->type == END) return true;
	}
	
	unsigned from = _from;
	bool status = false;

	enum Flag {
		CLEAR,
		BLACK
	};

	enum Flag* colour = calloc(a->size, sizeof(enum Flag));
	colour[from] = BLACK;

	Array dec;
	arr_init(&dec);

	do {
		List* arr = a->arr->ptr[from];

		for (unsigned i = 0; i < arr->size; ++i) {
			unsigned index = (unsigned)*list_at(arr, i);
			Point* b = a->ptr->ptr[index];
			if (b->type == END) {
				status = true;
				break;
			}
			
			if (colour[index] == CLEAR )
				arr_insert(&dec, dec.size, (void*)index);
		}

		if (dec.count) {
			from = (unsigned)dec.ptr[dec.count-1];
			arr_delete(&dec, dec.count-1, 0);
			colour[from] = BLACK;
		}
		else break;

		
		if (status) break;
	} while(1);

	arr_free(&dec, 0);
	free(colour);
	return status;
}

Array* matr_path(Matrix* a, Point* _from, Point* _to) {
	const int infinity = 100000;
	
	int from = search_index_point(a, _from);
	unsigned to = search_index_point(a, _to);

	int* distance = calloc(a->size, sizeof(int));
	for (unsigned i = 0; i < a->size; ++i)
		distance[i] = infinity;

	distance[from] = 0;

	int* colour = calloc(a->size, sizeof(int));
	enum COLOR {
		WHITE,
		BLACK
	};
	for (unsigned i = 0; i < a->size; ++i)
		colour[i] = WHITE;
	colour[from] = BLACK;

	Array* stack = malloc(sizeof(Array));
	arr_init(stack);
	arr_insert(stack, 0, (void*)from);

	do {
		List* ptr = a->arr->ptr[from];
		for (unsigned i = 0; i < ptr->size; ++i) {
			unsigned tmp = (unsigned)*list_at(ptr, i);

			if (colour[tmp] != BLACK) {
				arr_insert(stack, stack->size, (void*)tmp);
				distance[tmp] = mini(distance[tmp], distance[from]+1);
			}
		}

		int tmp_min = infinity;
		int it = -1;
		int hushe = -1;
		for (unsigned i = 0; i < stack->count; ++i) {
			if (tmp_min > distance[ (unsigned)stack->ptr[i]] ) {
				it = (unsigned)stack->ptr[i];
				hushe = i;
				tmp_min = distance[ (unsigned)stack->ptr[i] ];
			}
		}

		// printf("debug min: %d it %d hushe %d\n", tmp_min, it, hushe);

		if (tmp_min == infinity) break; // TODO mb delete

		from = it;
		colour[from] = BLACK;
		arr_delete(stack, hushe, 0);
		
		// printf("nice deb stack size %d \n", stack->count);
	} while(stack->count);

	arr_free(stack, 0);
	arr_init(stack);

	if (distance[to] != infinity) {
		bool flag = true;
		while (flag) {
			/*for (unsigned i = 0; i < a->size; ++i)
				printf("%d ", distance[i]);
			printf("\n");*/
			
			for (unsigned i = 0; i < a->size; ++i) {
				if (i == to) continue;
				
				if (distance[i] == distance[to] - 1) {
					List* ptr = a->arr->ptr[i];
					bool zabulil = false;
					for (unsigned j = 0; j < ptr->size; ++j) {
						unsigned tmp = (unsigned)*list_at(ptr, j);
						if (tmp == to) {
							zabulil = true;
							break;
						}
					}

					if (zabulil) {
						arr_insert(stack, stack->size, (void*)to);
						to = i;
						break;
					}					
				}
				else if (i == a->size - 1) {
					flag = false;
					break;
				}
			}
		}
	}
	else {
		arr_free(stack, 0);
		free(stack);
		stack = NULL;
	}

	free(colour);
	free(distance);

	return stack;
}

Array* matr_kaf12(Matrix* a, Point* _from) {
		const int infinity = 100000;
	
	int from = search_index_point(a, _from);

	int* distance = calloc(a->size, sizeof(int));
	for (unsigned i = 0; i < a->size; ++i)
		distance[i] = infinity;

	distance[from] = 0;

	int* colour = calloc(a->size, sizeof(int));
	enum COLOR {
		WHITE,
		BLACK
	};
	for (unsigned i = 0; i < a->size; ++i)
		colour[i] = WHITE;
	colour[from] = BLACK;

	Array* stack = malloc(sizeof(Array));
	arr_init(stack);
	arr_insert(stack, 0, (void*)from);

	do {
		List* ptr = a->arr->ptr[from];
		for (unsigned i = 0; i < ptr->size; ++i) {
			unsigned tmp = (unsigned)*list_at(ptr, i);

			if (colour[tmp] != BLACK) {
				arr_insert(stack, stack->size, (void*)tmp);
				distance[tmp] = mini(distance[tmp], distance[from]+1);
			}
		}

		int tmp_min = infinity;
		int it = -1;
		int hushe = -1;
		for (unsigned i = 0; i < stack->count; ++i) {
			if (tmp_min > distance[ (unsigned)stack->ptr[i]] ) {
				it = (unsigned)stack->ptr[i];
				hushe = i;
				tmp_min = distance[ (unsigned)stack->ptr[i] ];
			}
		}

		// printf("debug min: %d it %d hushe %d\n", tmp_min, it, hushe);

		if (tmp_min == infinity) break; // TODO mb delete

		from = it;
		colour[from] = BLACK;
		arr_delete(stack, hushe, 0);
		
		// printf("nice deb stack size %d \n", stack->count);
	} while(stack->count);


	arr_free(stack, 0);
	free(stack);
	stack = NULL;

	unsigned to;
	unsigned minimal = infinity;
	for (unsigned i = 0; i < a->size; ++i) {
		Point* ptr = a->ptr->ptr[i];
		if (
			ptr->type == END &&
			distance[i] != infinity &&
			minimal != mini(minimal, distance[i])
		) {
			minimal = mini(minimal, distance[i]);
			to = i;	
		}
	}

	if (minimal != infinity) {
		Point* _to = a->ptr->ptr[to];
		stack = matr_path(a, _from, _to);
	}

	free(colour);
	free(distance);

	return stack;
}

Array* matr_all_point(Matrix* a) {
	return a->ptr;
}
