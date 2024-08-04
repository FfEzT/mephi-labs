#include <malloc.h>
#include <string.h>

#include "./lib_scanf.h"

unsigned str_len(const char* str) {
    unsigned count = 0;
    for (unsigned i = 0; str[i] != '\0'; ++i) ++count;
    return count;
}

static int get_number(jmp_buf* err, const char* s, int is_natural) {
    long double input;

    printf("%s", s);
    int flag = scanf("%Lf", &input);
    scanf("%*[^\n]");

    if (flag == EOF) throw(err, EOF_io);
    else if (!flag || (input - (int)input > 0) || input < 0 && is_natural) {
        printf("Error...\n\n");
        return get_number(err, s, is_natural);
    }
    
    scanf("%*c");
    
    return input;
}

int get_num(jmp_buf* err, const char* s) { return get_number(err, s, 0); }
int get_i(jmp_buf* err, const char* s) { return get_number(err, s, 1); }

char* get_str(jmp_buf* err, const char* s) {
    printf("%s", s);

    char buf[_BUFFER_SIZE + 1];
    char* res = NULL;
    int len = 0, n;

    char str[_BUFFER_SIZE];
    do {
        n = scanf("%32[^\n]", buf);

        if (n < 0) {
            if (res) free(res);
            throw(err, EOF_io);
        }
        else if (n > 0) {
            int chunk = strlen(buf), str_len = len + chunk;
            char* temp = realloc(res, str_len + 1);

            if (temp == NULL) throw(err, null_ptr);
            res = temp;

            memcpy(res + len, buf, chunk);
            len = str_len;
        }
        else scanf("%*c");
    } while (n > 0);

    if (len > 0) res[len] = '\0';
    else res = calloc(1, sizeof(char));

    return res;
}

char* get_str_file(jmp_buf* err, FILE* file) {
    char buf[_BUFFER_SIZE + 1];
    char* res = NULL;
    int len = 0, n;

    // char str[_BUFFER_SIZE];
    do {
        n = fscanf(file, "%32[^\n]", buf);

        if (n < 0) {
            if (res) free(res);
            return NULL;
        }
        else if (n > 0) {
            int chunk = strlen(buf), str_len = len + chunk;
            char* temp = realloc(res, str_len + 1);

            if (temp == NULL) throw(err, null_ptr);
            res = temp;

            memcpy(res + len, buf, chunk);
            len = str_len;
        }
        else fscanf(file, "%*c");
    } while (n > 0);

    if (len > 0) res[len] = '\0';
    else res = calloc(1, sizeof(char));

    return res;
}



char* trim(jmp_buf* err, char* str) {
    const char _ = (char)1;
    unsigned len = str_len(str);

    if (len < 1) return str;

    // space on middle
    for (unsigned i = 0; str[i + 1] != '\0'; ++i) {
        if (
            IS_SPACE(str[i]) && IS_SPACE(str[i + 1])
            ) str[i] = _;
    }
    // space on start
    for (unsigned i = 0;; ++i) {
        if (
            !IS_SPACE(str[i]) &&
            str[i] != _
            ) break;
        else if (
            IS_SPACE(str[i])
            ) str[i] = _;
    }
    // space on end
    for (unsigned i = 0; str[i] != '\0'; ++i)
        if (str[i + 1] == '\0' && IS_SPACE(str[i])) str[i] = _;

    char* res = malloc(sizeof(char) * len);
    if (res == NULL) throw(err, null_ptr);

    // cpy
    unsigned j = 0;
    for (unsigned i = 0; str[i] != '\0'; ++i) {
        if (str[i] == _) continue;
        res[j++] = str[i];
    }

    char* temp = realloc(res, sizeof(char) * (j + 1));
    if (temp == NULL) throw(err, null_ptr);

    res = temp;
    res[j] = '\0';

    free(str);
    return res;
}
