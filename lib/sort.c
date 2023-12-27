#include "sort.h"

int name_cmp(Elector *p1, Elector *p2) {
    int result = strcmp(p1->name, p2->name);
    return (result < 0);
}

int id_cmp(Elector *p1, Elector *p2) {
    int result = strcmp(p1->id, p2->id);
    return (result < 0);
}

int age_cmp(Elector *p1, Elector *p2) {
    return (p1->age < p2->age);
}

void swap(Array *arr, size_t ind1, size_t ind2) {
    Elector *tmp = *(arr->arr + ind1);
    *(arr->arr + ind1) = *(arr->arr + ind2);
    *(arr->arr + ind2) = tmp;
}

void swap_indices(size_t *ind1, size_t *ind2) {
    size_t tmp = *ind1;
    *ind1 = *ind2;
    *ind2 = tmp;
}

void double_selection_sort(Array *voters, int (*cmp)(Elector*, Elector*), int reversed) {
    size_t start, end;
    size_t max_index, min_index;
    size_t tmp;
    for (size_t i = 1; i <= (voters->len / 2); i++) {
        start = i - 1;
        end = voters->len - i;
        max_index = start;
        min_index = start;
        for (size_t j = start; j <= end; j++) {
            if (cmp(*(voters->arr + j), *(voters->arr + min_index))) {
                min_index = j;
            }
            if (cmp(*(voters->arr + max_index), *(voters->arr + j))) {
                max_index = j;
            }
        }
        if (reversed) {
            tmp = start;
            start = end;
            end = tmp;
        }
        swap(voters, min_index, start);
        swap_indices(&min_index, &start);
        if (max_index == min_index) max_index = start;
        swap(voters, max_index, end);
        swap_indices(&max_index, &end);
    }
}

void bubble_sort(Array *voters, int (*cmp)(Elector*, Elector*), int reversed) {
    for (size_t i = 0; i < voters->len; i++) {
        for (size_t j = 0; j < voters->len - 1; j++) {
            if (reversed) {
                if (cmp(*(voters->arr + j), *(voters->arr + j + 1))) {
                    swap(voters, j, j + 1);
                }
            }
            else {
                if (cmp(*(voters->arr + j + 1), *(voters->arr + j))) {
                    swap(voters, j, j + 1);
                }
            }
        }
    }
}

int *partition_inplace(Array *a, int first, int last, int (*cmp)(Elector*, Elector*), int reversed) {
    Elector *pivot = *(a->arr + first);
    while (1) {
        if (reversed) {
            while (cmp(pivot, *(a->arr + first))) {
                first++;
            }
            while (cmp(*(a->arr + last), pivot)) {
                last--;
            }
 
        }
        else {
            while (cmp(*(a->arr + first), pivot)) {
                first++;
            }
            while (cmp(pivot, *(a->arr + last))) {
                last--;
            }
        }
        if (first <= last) {
            swap(a, first, last);
            first++;
            last--;
        }
        if (first > last) {
            int *result = (int *)malloc(2 * sizeof(size_t));
            *result = last;
            *(result + 1) = first;
            return result;
        }
    }
}

void quicksort_rec(Array *a, int (*cmp)(Elector*, Elector*), int first, int last, int reversed) {
    int l,r;
    if (last - first <= 0) return;
    int *l_and_r = partition_inplace(a, first, last, cmp, reversed);
    l = *l_and_r;
    r = *(l_and_r + 1);
    free(l_and_r);
    quicksort_rec(a, cmp, first, l, reversed);
    quicksort_rec(a, cmp, r, last, reversed);
}

void quicksort(Array *voters, int (*cmp)(Elector*, Elector*), int reversed) {
    int first = 0;
    int last = voters->len - 1 ;
    quicksort_rec(voters, cmp, first, last, reversed);
}
