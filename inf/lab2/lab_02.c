#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float get_float();
int get_num();
float ln(float x, int n);

int main() {
	float a = get_float();
	int n = get_num();

	printf("%f", ln(a, n) );
	printf("\n");
	printf("%f", log(1 + a + a*a + a*a*a) );

	return 0;
}

float get_float() {
	float input;
	
	printf("Input x (-1; 1]: ");
	int flag = scanf("%f", &input);
	while (getchar() != '\n') {}
	
	if (!flag || !(input <= 1.f && input > -1.f) ) {
		printf("Error...\n");
		return get_float();
	}
	return input;
}

int get_num() {
	float input;
	
	printf("Input natural N: ");
	int flag = scanf("%f", &input);
	while (getchar() != '\n') {}
	
	if (!flag || input <= 0 || ( input - (int)input > 0 ) ) {
		printf("Error...\n");
		return get_num();
	}
	return (int)input;
}

float ln(float x, int n) {
	float p = x, s = x;

	for (int i = 2; i <= n; ++i) {
		p *= x / i;
		if (i % 4 == 0) p *= (-3);
		
		s += p;
		if (i % 4 == 0) p /= (-3);
		p *= i;
	}

	return s;
}
