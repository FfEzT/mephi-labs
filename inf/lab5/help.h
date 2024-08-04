#ifndef _helpa
#define _helpa

#include <stdlib.h>
#include <time.h>
#include <getopt.h>

#include "lib_scanf.h"

typedef struct {
    char* id;
    int count;
    char* name;
} Piece;

enum sort {
	GrabSort,
	InsertSort
};

enum Way {
	ASC,
	DESC
};

void print(Piece* obj);

int compare_id_asc(Piece* item_1, Piece* item_2);
int compare_id_desc(Piece* item_1, Piece* item_2);
int compare_count_asc(Piece* item_1, Piece* item_2);
int compare_count_desc(Piece* item_1, Piece* item_2);
int compare_name_asc(Piece* item_1, Piece* item_2);
int compare_name_desc(Piece* item_1, Piece* item_2);

void insort(Piece* items, int size, int(*comp)(Piece*, Piece*));
void grabsort(Piece* items, int size, int(*comp)(Piece*, Piece*));

void arg_get(int argc, char** argv,
	short* alg, char** field,
	short* way, short* generation,
	char** input, char** output);


#endif
