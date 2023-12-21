#ifndef VOTERS_H
#define VOTERS_H

#include <stdio.h>
#include <stdlib.h>

#define MEM_ACCESS_ERROR_CODE -2 

typedef struct Voter {
    char *name;
    char id[8];
    int age;
} Elector;

typedef struct Array {
    Elector **arr;
    size_t len;
} Array;

int append(Array *voters, Elector *elem);
int insert(Array *voters, size_t ind, Elector *elem);
int del_item(Array *a, size_t index);
void free_array(Array *a);

#endif
