#include "./help.h"

int main(int argc, char** argv) {
    char* field = "id",
        *name_in_file="./in.t",
        *name_out_file="./result.txt";
    short way = ASC,
        algorithm = GrabSort,
        generation = 0;

    arg_get(argc, argv, &algorithm, &field, &way, &generation, &name_in_file, &name_out_file);

    if (!generation) {
        FILE* file_input = fopen(name_in_file, "r");
        FILE* file_output = fopen(name_out_file, "w");
        if (file_input == NULL) throw(open_file);

		char* temp = get_str_file(file_input);
        unsigned len = atoi(temp);
        free(temp);
        
        Piece* arr = malloc(len * sizeof(Piece));
        if (arr == NULL) throw(null_ptr);
        
        for (unsigned i = 0; i < len; ++i) {
            arr[i].id = get_str_file(file_input);
			char* temp = get_str_file(file_input);
            arr[i].count = atoi(temp);
            arr[i].name = get_str_file(file_input);

            free(temp);
        }

        int (*compare) (Piece*, Piece*) = compare_id_asc;
        if (strcmp(field, "id") == 0 && way == ASC)
            compare = compare_id_asc;
        else if (strcmp(field, "id") == 0 && way == DESC)
            compare = compare_id_desc;
        else if (strcmp(field, "count") == 0 && way == ASC)
            compare = compare_count_asc;
        else if (strcmp(field, "count") == 0 && way == DESC)
            compare = compare_count_desc;
        else if (strcmp(field, "name") == 0 && way == ASC)
            compare = compare_name_asc;
        else if (strcmp(field, "name") == 0 && way == DESC)
            compare = compare_name_desc;


		clock_t start = clock();
        if (algorithm == InsertSort)
            insort(arr, len, compare);
        else if (algorithm == GrabSort)
            grabsort(arr, len, compare);
        else qsort(arr, len, sizeof(Piece), (int (*)(const void*, const void*) )compare);
		printf(
			"%lf.15\n\n",
			(double)(clock() - start) / CLOCKS_PER_SEC
		);

        fprintf(file_output, "%d\n", len);
        for (int i = 0; i < len; ++i) {
            fprintf(file_output, "Id: %s\t\t", arr[i].id);
            fprintf(file_output, "Count: %d\t\t", arr[i].count);
            fprintf(file_output, "Name: %s\n", arr[i].name);
        }

		for (int i = 0; i < len; ++i) free(arr[i].id), free(arr[i].name);
		
        free(arr);
        fclose(file_input);
        fclose(file_output);
	}
    else if (generation) {
        FILE* file_output = fopen(name_out_file, "w");
        srand( time(NULL) );

        fprintf(file_output, "%d\n", generation);

        char* solution = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
        
        for (unsigned i = 0; i < generation; ++i) {
            for (unsigned i = 0; i < 8; ++i)
                fprintf(file_output, "%c", solution[(rand() % 62)]);
            fprintf(file_output, "\n");

            fprintf(file_output, "%u\n", rand()%1000+1);

            unsigned short len = rand() % 20 + 1;
            for (unsigned i = 0; i < len; ++i)
                fprintf(file_output, "%c", solution[(rand() % 62)]);
	        fprintf(file_output, "\n");
        }

        fclose(file_output);
    }
    return 0;
}
