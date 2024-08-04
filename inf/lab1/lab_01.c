#include <stdio.h>
#include <stdbool.h>

int search_eq_num(int f_num, int s_num);
void add_num(int* num, int digit);
bool search_num(int number, int digit);
int module(int num);

int main() {
	int m, n;

	printf("Please enter M and N --> ");
	scanf("%d %d", &m, &n);

	printf("Equal digits: %d \n\n", search_eq_num(m, n) );

	return 0;
}

int search_eq_num(int f_num, int s_num) {
	f_num = module(f_num);
	s_num = module(s_num);

	int result = 0;
	bool flag_0 = false;

	for (int i = 0; i < 10; ++i) {
		if ( search_num(f_num, i) == true &&
			 search_num(s_num, i) == true ) {
			if (i == 0) flag_0 = true;
			else add_num(&result, i);	 	
		 }
	}

	if (flag_0) add_num(&result, 0);

	return result;
}

void add_num(int* num, int digit) {
	*num *= 10;
	*num += digit;
}

bool search_num(int num, int digit) {
	while (num > 0) {
		if (num % 10 == digit) return true;
		else num /= 10;
	}
	
	return false;
}

int module(int num) {
	return num >= 0 ? num : (-1) * num;
}
