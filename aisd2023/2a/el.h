#ifndef _el
#define _el

typedef enum {
	OPERATION, NUMBER
} Status;

typedef struct {
	int data;
	Status type;
} Stack_el;

#endif
