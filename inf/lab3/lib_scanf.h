#ifndef _lib_scanf
#define _lib_scanf

#pragma warning(disable: 4996)

#include <stdio.h>

static int get_number(char* s, int i);
int get_num(char* s);
int get_i(char* s);

static int get_number(char* s, int is_natural) {
    float input;

    printf("%s", s);
    int flag = scanf("%f", &input);
    scanf("%*[^\n]");

    if (!flag || (input - (int)input > 0) || input < 0 && is_natural) {
        printf("Error...\n\n");
        return get_number(s, is_natural);
    }
    return (int)input;
}

int get_num(char* s) { return get_number(s, 0); }
int get_i(char* s) { return get_number(s, 1); }

#endif