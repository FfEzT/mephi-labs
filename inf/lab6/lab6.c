#include <stdio.h>
#include <locale.h>

#include "lib_list(process).h"
#include "lib_scanf.h"

void offset(Node* ptr) {
    char sym = ptr->data;
    Node* tmp = ptr;

    while (tmp->next != NULL) {
        if (IS_SPACE(tmp->next->data)) break;
        tmp = tmp->next;

        char c_tmp = tmp->data;
        tmp->data = sym;
        sym = c_tmp;
    }
    ptr->data = sym;
}

void get_string(List* ls) {
    printf("str > ");
    do {
        char a = getchar();
        if (a == '\n') break;

        list_push_back(ls, a);
    } while (1);
}

void del_spaces(List* ls) {
    Node* ptr = ls->first;

    while (ptr->next != NULL) {
        if (ptr == ls->first && IS_SPACE(ptr->data)) {
            Node* temp = ptr;
            ptr = ls->first = ptr->next;
            free(temp);
        }
        else if (IS_SPACE(ptr->data) && IS_SPACE(ptr->next->data)) {
            Node* temp = ptr->next;
            ptr->next = ptr->next->next;
            free(temp);
        }
        else ptr = ptr->next;
    }
    if (IS_SPACE(ptr->data)) {
        Node* temp = ls->first;
        while (temp->next->next != NULL) temp = temp->next;

        free(ptr);
        temp->next = NULL;
        ls->last = temp;
    }

    ls->size = list_get_size(ls);
}

int main() {

    List* ls = list_init();

    get_string(ls);
    unsigned n = get_i("N > ");
    del_spaces(ls);
    list_print(ls);

    main: {
        Node* ptr = ls->first;

        while (ptr->next != NULL) {
            Node* tmp = ptr;
            while (tmp->next != NULL) {
                if (IS_SPACE(tmp->next->data)) break;
                tmp = tmp->next;
            }
            for (unsigned i = 0; i < n; ++i) offset(ptr);

            if (tmp->next == NULL) break;
            else if (IS_SPACE(tmp->next->data)) ptr = tmp->next->next;
        }
    }

    list_print(ls);

    list_free(ls);
    return 0;
}
