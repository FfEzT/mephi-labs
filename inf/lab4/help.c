#include "help.h"

unsigned get_word_count(const char* const str) {
    unsigned count = 0;
    for (unsigned i = 0;; ++i) {
        if (IS_SPACE(str[i])) ++count;
        else if (str[i] == '\0') return ++count;
    }
}

char** fill_words(const char* const str, const unsigned count) {
    char** words = malloc(sizeof(char*) * count);
    if (words == NULL) throw(null_ptr);

    unsigned i = 0;

    for (unsigned left = 0;; ++left) {
        for (unsigned right = left;; ++right) {
            if (IS_SPACE(str[right]) || str[right] == '\0') {
                words[i] = malloc(sizeof(char) * (right - left + 1));
                if (words[i] == NULL) throw(null_ptr);

                memcpy(words[i], str + left, right - left);
                words[i++][right - left] = '\0';
                left = right;
                break;
            }
        }

        if (str[left] == '\0') break;
    }

    return words;
}

static bool is_equal(const char* const a, const char* const b) {
    if (
        str_len(a) != str_len(b)
        ) return false;

    for (unsigned i = 0; a[i] != '\0'; ++i)
        if (a[i] != b[i]) return false;

    return true;
}

void str_delete_equals(char** const words, const unsigned count) {
    for (unsigned i = 0; i < count - 1; ++i) {
        bool flag = false;

        unsigned j;
        for (j = i + 1; j < count; ++j) {
            if (is_equal(words[i], words[j])) {
                flag = true;

                free(words[j]);
                words[j] = malloc(sizeof(char));
                if (words[j] == NULL) throw(null_ptr);

                words[j][0] = '\0';
            }
            else break;
        }
        if (flag) {
            free(words[i]);

            words[i] = malloc(sizeof(char));
            if (words[i] == NULL) throw(null_ptr);
            words[i][0] = '\0';

            flag = false;
            i = j - 1;
        }
    }
}

void free_words(char** words, unsigned* count) {
    for (unsigned i = 0; i < *count; ++i)
        free(words[i]);

    free(words);
    *count = 0;
}
