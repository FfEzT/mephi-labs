#include "help.h"

void print(Piece* obj) {
    printf(
        "ID: %8s\tcount: %d\tname: %s",
        obj->id,
        obj->count,
        obj->name);
}

int compare_id_asc(Piece* item_1, Piece* item_2) {
    int t = strcmp(item_1->id, item_2->id);
    if (t > 0) return 1;
    if (t < 0) return -1;
    return 0;
}
int compare_id_desc(Piece* item_1, Piece* item_2) {
    int t = strcmp(item_1->id, item_2->id);
    if (t > 0) return -1;
    if (t < 0) return 1;
    return 0;
}
int compare_count_asc(Piece* item_1, Piece* item_2) {
    if (
        (item_1->count - item_2->count) > 0) return 1;
    if (
        (item_1->count - item_2->count) < 0) return -1;
    return 0;
}
int compare_count_desc(Piece* item_1, Piece* item_2) {
    if (
        (item_1->count - item_2->count) < 0) return 1;
    if (
        (item_1->count - item_2->count) > 0) return -1;
    return 0;
}
int compare_name_asc(Piece* item_1, Piece* item_2) {
    int t = strcmp(item_1->id, item_2->id);
    if (t > 0) return 1;
    if (t < 0) return -1;
    return 0;
}
int compare_name_desc(Piece* item_1, Piece* item_2) {
    int t = strcmp(item_1->id, item_2->id);
    if (t > 0) return -1;
    if (t < 0) return 1;
    return 0;
}

void insort(Piece* items, int size, int(*comp)(Piece*, Piece*)) {
    for (int i = 1; i < size; ++i) {
        int sorted = i - 1;

        while (sorted > -1 && comp(&(items[sorted]), &(items[sorted + 1])) > 0) {
            Piece temp = items[sorted];
            items[sorted] = items[sorted + 1];
            items[sorted + 1] = temp;
            --sorted;
        }
    }
}
void grabsort(Piece* items, int size, int(*comp)(Piece*, Piece*)) {
	const float koeff = 1.23;

	int hs = 1,
		space = size,
		j;

	while (space > 1 || hs) {
		space /= koeff;

		if (space < 1) space = 1;
		hs = 0;

		for (int i = 0; i < size-space ; ++i) {
			j = i + space;

			if (
				comp(&(items[i]), &(items[j])) > 0
			) {
				Piece temp = items[i];
				items[i] = items[j];
				items[j] = temp;

				hs = 1;	
			}
		}
	}
}

void arg_get(int argc, char** argv,
    short* alg, char** field,
    short* way,
    short* generation,
    char** input, char** output) {
    int res;

    while (
        (res = getopt(argc, argv, "a:f:w:g:i:o:"))
        != -1) {
        switch (res) {
        case 'a': {
            if (strcmp(optarg, "gs") == 0)
                *alg = GrabSort;
            else if (strcmp(optarg, "is") == 0)
                *alg = InsertSort;
            break;
        }
        case 'f': {
            *field = optarg;
            break;
        }
        case 'w': {
            if (strcmp(optarg, "desc") == 0 || strcmp(optarg, "DESC") == 0)
                *way = DESC;
            break;
        }
        case 'i': {
            *input = optarg;
            break;
        }
        case 'o': {
            *output = optarg;
            break;
        }
        case 'g': {
            *generation = atoi(optarg);
            break;
        }
        case '?': break; //TODO
        default: break; //TODO
        }
    }
}
