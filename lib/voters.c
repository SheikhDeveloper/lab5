#include "voters.h"

// Function that adds element to the end of the array expanding it by 1 (if array is empty, it is initialized)
int append(Array *arr, Elector *elem) {
    int insert_check = insert(arr, arr->len, elem);
    return insert_check;
}

/* Function that inserts element into the array by given index.
 * if the array is empty or the index is bigger than length of
 * the array, it adds element to the end of the array expanding 
 * it by 1 (if array is empty, it is initialized) */
int insert(Array *arr, size_t index, Elector *elem) {
    if (arr->arr == NULL) {
        arr->len = 1;
        arr->arr = (Elector **) malloc(arr->len * sizeof(Elector *));
        if (!(arr->arr)) return MEM_ACCESS_ERROR_CODE;
        arr->arr[arr->len - 1] = elem;
        return 0;
    }
    arr->len += 1;
    Elector **tmp;
    tmp = realloc(arr->arr, arr->len * sizeof(Elector *));
    if (!(tmp)) return MEM_ACCESS_ERROR_CODE;
    arr->arr = tmp;
    if (index > arr->len - 2) {
        *(arr->arr + arr->len - 1) = elem;
        return 0;
    }
    for (size_t i = arr->len - 1; i > index; i--) {
        *(arr->arr + i) = *(arr->arr + i - 1);
    }
    *(arr->arr + index) = elem;
    return 0;
}

/* Function that deletes the element from the array by the given index.
 * If the array is empty, function returns empty array error code */
int del_item(Array *a, size_t index) {
    for (size_t i = index; i < a->len - 1; i++) {
        *(a->arr + i) = *(a->arr + i + 1);
    }
    *(a->arr + a->len - 1) = 0;
    a->len -= 1;
    if (a->len == 0) {
        free(a->arr);
        a->arr = NULL;
        return 0;
    }
    Elector **tmp = realloc(a->arr, a->len * sizeof(Elector *));
    if (!(tmp)) return MEM_ACCESS_ERROR_CODE;
    a->arr = tmp;
    return 0;
}

void free_array(Array *a) {
    Elector *e;
    if (a-> arr == NULL) return;
    for (size_t i = 0; i < a->len; i++) {
        e = *(a->arr + i);
        free(e->name);
        free(e);
    }
    free(a->arr);
    a->len = 0;
}
