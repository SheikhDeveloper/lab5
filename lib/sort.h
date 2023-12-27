#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voters.h"

void swap(Array *arr, size_t ind1, size_t ind2);
int name_cmp(Elector *p1, Elector *p2);
int id_cmp(Elector *p1, Elector *p2);
int age_cmp(Elector *p1, Elector *p2);
void double_selection_sort(Array *voters, int (*cmp)(Elector*, Elector*), int reversed);
void bubble_sort(Array *voters, int (*cmp)(Elector*, Elector*), int reversed);
void quicksort(Array *voters, int (*cmp)(Elector*, Elector*), int reversed);

#endif
