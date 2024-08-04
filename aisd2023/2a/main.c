#include "./lib/lib_scanf.h"
#include "./lib/stack.h"
#include "./lib/lib_try-catch.h"
#include "el.h"

enum {
	NOT_MATHEMATIC_EXPRESSION = 10,
	DELIT_NA_NILL_DAUN,
};

bool is_math_expr(const char*);
int calculate(const char*);
void fill_math(const char*, Stack*);

int main() {
	char* str = get_str("Input math expression > ");

	try printf(
		"Result: %d\n", 
		calculate(str)
	);
	catch(NOT_MATHEMATIC_EXPRESSION) 
		printf("Incorrect expression\n");
	catch(DELIT_NA_NILL_DAUN)
		printf("Why do u want to divide by Zero?\n");
	catch_all printf("lol");

	free(str);

	return 0;
}

void fill_math(const char* str, Stack* obj) {
	unsigned len = strlen(str);

	bool negative = false;
	for (unsigned i = 0; i < len; ++i) {
		if ( strchr("*+/", str[i]) != NULL ) {
			Stack_el* el = malloc(sizeof(Stack_el));
			el->type = OPERATION;
			el->data = str[i];

			stack_push(obj, el);
		}
		else if (str[i] == '-') {
			if ( strchr("\t ", str[i+1]) ) {
				Stack_el* el = malloc(sizeof(Stack_el));
				el->type = OPERATION;
				el->data = str[i];

				stack_push(obj, el);
			}
			else if (str[i+1] >= '0' && str[i+1] <= '9') negative = true;
		}
		else if (str[i] >= '0' && str[i] <= '9') {
			int res = 0;

			while (i < len && str[i] >= '0' && str[i] <= '9') {
				res *= 10;
				res += str[i++] - '0';
			}

			Stack_el* el = malloc(sizeof(Stack_el));
			el->type = NUMBER;

			if (negative) res *= -1, negative = false;
			
			el->data = res;

			stack_push(obj, el);
		}
	}
}

bool is_math_expr(const char* str) {
	for (unsigned i = 0; str[i] != '\0'; ++i)
		if ( strchr(" \t*-+/1234567890", str[i]) == NULL ) return false;

	return true;
}

int _calculate(Stack* math, Stack* nums) {
	while (math->size > 0) {
		Stack_el* el = stack_pop(math);
		short code_throw = 0;

		if (el->type == NUMBER) stack_push(nums, el);
		else if (el->type == OPERATION && nums->size > 1) {
			Stack_el* el1 = stack_pop(nums);
			Stack_el* el2 = stack_pop(nums);

			Stack_el* new = malloc(sizeof(Stack_el));
			new->type = NUMBER;

			if (el->data == '+') new->data = el1->data + el2->data; 
			else if (el->data == '-') new->data = el1->data - el2->data; 
			else if (el->data == '*') new->data = el1->data * el2->data; 
			else if (el->data == '/' && el2->data != 0) new->data = el1->data / el2->data; 
			else if (el->data == '/' && el2->data == 0) code_throw = DELIT_NA_NILL_DAUN;

			stack_push(nums, new);

			free(el1);
			free(el2);
			free(el);
			
		}
/*		else if (el->type == OPERATION && el->data == '-' && nums->size == 1) {
			Stack_el* el1 = stack_pop(nums);
			el1->data *= -1;

			stack_push(nums, el1);

			free(el);
		}*/
		else if (el->type == OPERATION && nums->size <= 1)
			free(el), code_throw = NOT_MATHEMATIC_EXPRESSION;

		if (code_throw) throw_(code_throw);
	}

	if (nums->size == 1) {
		Stack_el* tmp = stack_pop(nums);
		int res = tmp->data;

		free(tmp);

		return res;
	}
	else throw_(NOT_MATHEMATIC_EXPRESSION);
}

int calculate(const char* str) {
	int res; int code_throw = 0;

	if ( !is_math_expr(str) )
		throw(NOT_MATHEMATIC_EXPRESSION);

	Stack nums;
	stack_init(&nums);
	
	Stack math;
	stack_init(&math);
	fill_math(str, &math);

	try_ {
		res = _calculate(&math, &nums);
	}
	catch(NOT_MATHEMATIC_EXPRESSION) code_throw = NOT_MATHEMATIC_EXPRESSION;
	catch(DELIT_NA_NILL_DAUN) code_throw = DELIT_NA_NILL_DAUN;
	
	stack_free(&math, 1);
	stack_free(&nums, 1);

	if (code_throw) throw(code_throw);
	
	return res;
}
