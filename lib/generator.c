#include "generator.h"

Array gen_arr(size_t size) {
    Array arr;
    arr.arr = NULL;
    arr.len = 0;
    Elector *el;
    for (size_t i = 0; i < size; i++) {
        el = gen_struc();
        append(&arr, el);
    }
    return arr;
}

Elector *gen_struc() {
    Elector *res = (Elector *)malloc(sizeof(Elector));
    res->name = gen_name();
    char new_id[8] = "FOO-123";
    char *tmp = new_id;
    while (*tmp != '-') {
        *tmp++ = gen_letter();
    }
    tmp++;
    while (*tmp != 0) {
        *tmp++ = gen_digit();
    }
    strcpy(res->id, new_id);
    res->age = gen_age();
    return res;
}

char *gen_name() {
    srand(rand());
    size_t length = rand() % 100;
    char *name = (char *)malloc((length + 1) * sizeof(char));
    char *tmp = name;
    for (size_t i = 0; i < length; i++) {
        *tmp = gen_char();
        tmp++;
    }
    *tmp = 0;
    return name;
}

char gen_char() {
    char result = random() % 128;
    while (32 > result || result > 126) {
        result = random() % 128;
    }
    return result;
}

char gen_letter() {
    char result = gen_char();
    while (result < 'A' || (result > 'Z' && result < 'a') || result > 'z') {
        result = gen_char();
    }
    return result;
}

char gen_digit() {
    char result = gen_char();
    while (result < '0' || result > '9') {
        result = gen_char();
    }
    return result;
}

int gen_age() {
    int result = random() % 100500;
    return result;
}
