#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float get_float();
float get_e();
float ln(float x, float n, int* it);
float absolut(float num);

int main() {
	float a = get_float();
	float e = get_e();
	int count_it;

	printf("%f", ln(a, e, &count_it) );
	printf("\n");
	printf("Iterations: %d", count_it);
	printf("\n");
	printf("%f", log(1 + a + a*a + a*a*a) );
	printf("\n");

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

float get_e() {
	float input;
	
	printf("Input positive E: ");
	int flag = scanf("%f", &input);
	while (getchar() != '\n') {}
	
	if (!flag || input <= 0) {
		printf("Error...\n");
		return get_e();
	}
	return input;
}

float ln(float x, float e, int* it) {
	float p = x, s = x;
	int i;

	for (i = 2;; ++i) {
		p *= x / i;
		if (i % 4 == 0) p *= (-3);


		s += p;
		if ( absolut(p) < e) {break;}
		if (i % 4 == 0) p /= (-3);
		p *= i;
	}
	
	*it = i;
	
	return s;
}

float absolut(float num) {
	return num >= 0? num : -num;
}
