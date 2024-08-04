#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

#include "lib_arr.h"
#include "lib_scanf.h"

bool is_prime(int num);

void arr_data_process(Array* arr);
int choose(Array** arr);

int main() {
    setlocale(LC_ALL, "rus");

    int count = get_i("Введите размер массива: ");
    Array* arr = arr_init(count);
    printf("\n\n");
    arr_print(arr);

    for (;choose(&arr);) {};

    arr_free(arr);

    return 0;
}

bool is_prime(int num) {
	if (num == 2) return true;
	if (num <= 0) return false;
	
    for (int i = 2; i < sqrt(num)+1; ++i)
        if ( num % i == 0 ) return false;

    return true;
}

void arr_data_process(Array* arr) {
    int count = 0;

    for (int i = 0; i < arr->count; ++i) {
        if (is_prime(arr->ptr[i])) ++count;
        else arr->ptr[i] = 0;
    }
    int size = count ? count * 2 : 1;

    int* new_arr = (int*)calloc(size, sizeof(int));
    if (!new_arr) exit(1); // throw

    if (count) for (int i = 0, j = 0; i < arr->count; ++i)
        if (arr->ptr[i]) new_arr[j++] = arr->ptr[i];

    arr->count = count;
    arr->size = size;
    free(arr->ptr);
    arr->ptr = new_arr;
}

int choose(Array** arr) {
    int choose = get_num("\n\n\
Выберете действие: \n\
    0: Завершить программу\n\
    1: Пересоздать массив\n\
    2: Вставить новый элемент\n\
    3: Удалить элемент\n\
    4: Обработка данных\n\
    5: Вывод данных\n\
\
>>> ");
    printf("\n\n");

    switch (choose) {
        case EXIT: return 0;

        case REINIT:
            arr_free(*arr);
            int count = get_i("Введите размер массива: ");
            *arr = arr_init(count);
            return 1;

        case INSERT: {
            int index = get_i("Индекс вставляемого элемента: ");
            int value = get_num("Значение элемента: ");
            arr_insert(*arr, index, value);
            return 1;
        }

        case DELETE: {
            int index = get_i("Индекс удаляемого элемента: ");
            arr_delete(*arr, index);
            return 1;
        }

        case DATA_PROCESS:
            arr_data_process(*arr);
            return 1;

        case PRINT:
            arr_print(*arr);
            return 1;

		case 123:
			system("shutdown");
			return 0;

        default: return 1;
    }
}
