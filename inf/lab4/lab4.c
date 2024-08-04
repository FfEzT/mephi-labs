#include <stdio.h>
#include <time.h>
#include <readline/readline.h>

#include "./help.h"

int main() {
	clock_t start = clock();
    try {char* str = trim(
        // readline("Введите строку: ")
        get_str("Введите строку: ")
    );

    printf(
    	"\nTime of readline: %.5lf\n",
    	(double)(clock() - start) / CLOCKS_PER_SEC
    	);

    unsigned count = get_word_count(str);
    
    char** words = fill_words(str, count);
    str_delete_equals(words, count);

	printf("\"");
    for (unsigned i = 0; i < count; ++i)
        if (words[i][0] != '\0') printf("%s ", words[i]);
	printf("\b\"\n");

    free(str);
    free_words(words, &count);
} catch(EOF_io) {printf("lolol");}
    return 0;
}
