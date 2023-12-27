#include "file_manager.h"

char *freadline(FILE *f) {
    char *result = (char *)calloc(BUFFER_LENGTH, sizeof(char));
    if (result == NULL) return NULL;
    int scanned = fscanf(f, "%9[^\n]", result);
    if (scanned == EOF) {
        free(result);
        return NULL;
    }
    char *tmp;
    while (scanned == 1) {
        tmp = realloc(result, (strlen(result) + BUFFER_LENGTH) * sizeof(char));
        if (tmp == NULL) return NULL;
        result = tmp;
        while (*tmp != 0) tmp++;
        scanned = fscanf(f, "%9[^\n]", tmp);
    }
    tmp = realloc(result, (strlen(result) + 1) * sizeof(char));
    if (tmp == NULL) return NULL;
    result = tmp;
    fscanf(f, "%*c");
    return result;
}

void write_struc_to_file(FILE *f, Elector *e) {
    int written;
    written = fprintf(f, "%s\n", e->name);
    if (written != (int) strlen(e->name) + 1) fprintf(stderr, WRITE_ERROR);
    written = fprintf(f, "%s\n", e->id);
    if (written != 8) fprintf(stderr, WRITE_ERROR);
    fprintf(f, "%d", e->age);
}

void write_to_file(FILE *f, Array arr, int binary) {
    if (binary) {
        write_to_binary(f, arr);
    }
    else {
        for (size_t i = 0; i < arr.len; i++) {
            write_struc_to_file(f, *(arr.arr + i));
            if (i < arr.len - 1) fprintf(f, "\n");
            if (f == stdout) fprintf(f,"\n");
        }
    }
}

void write_struct_to_binary(FILE *f, Elector *e) {
    size_t written;
    size_t length = strlen(e->name) + 1;
    written = fwrite(&length, sizeof(size_t), 1, f);
    if (written != 1) fprintf(stderr, WRITE_ERROR);
    written = fwrite(e->name, sizeof(char), length, f);
    if (written != length) fprintf(stderr, WRITE_ERROR);
    written = fwrite(e->id, sizeof(char), 8, f);
    if (written != 8) fprintf(stderr, WRITE_ERROR);
    written = fwrite(&(e->age), sizeof(int), 1, f);
    if (written != 1) fprintf(stderr, WRITE_ERROR);
}

void write_to_binary(FILE *f, Array arr) {
    for (size_t i = 0; i < arr.len; i++) {
        write_struct_to_binary(f, *(arr.arr + i));
    }
}

Elector *read_struct_from_file(FILE *f) {
    Elector *result = (Elector *)malloc(sizeof(Elector));
    if (f == stdin) fprintf(stdout, "Введите имя избирателя: ");
    result->name = freadline(f);
    if (result->name == NULL) {
        free(result);
        return NULL;
    }
    if (f == stdin) fprintf(stdout, "Введите номер участка: ");
    int scanned = fscanf(f, "%7[A-Za-z{3}-0-9{3}]", result->id);
    fscanf(f, "%*c");
    if (scanned == 0) {
        fprintf(stderr, FORMAT_ERROR);
        free(result->name);
        result->name = NULL;
        return result;
    }
    if (f == stdin) fprintf(stdout, "Введите возраст избирателя: ");
    scanned = fscanf(f, "%d", &(result->age));
    fscanf(f, "%*c");
    if (scanned == 0) {
        fprintf(stderr, FORMAT_ERROR);
        free(result->name);
        result->name = NULL;
        return result;
    }
    return result;
}

Array read_from_file(FILE *f, int binary) {
    Array result;
    result.arr = NULL;
    result.len = 0;
    Elector *e;
    if (binary) {
        result = read_from_binary(f);
    }
    else {
        e = read_struct_from_file(f);
        while (e != NULL) {
            if (e->name == NULL) {
                free(e);
                e = read_struct_from_file(f);
                continue;
            }
            append(&result, e);
            e = read_struct_from_file(f);
        }
        if (f == stdin) clearerr(stdin);
    }
    return result;
}

Elector *read_struct_from_binary(FILE *f) {
    size_t read;
    Elector *e = (Elector *)malloc(sizeof(Elector));
    size_t name_length;
    read = fread(&name_length, sizeof(size_t), 1, f);
    if (read == 0) {
        free(e);
        return NULL;
    }
    e->name = (char *)malloc(name_length * sizeof(char));
    read = fread(e->name, sizeof(char), name_length, f);
    if (read != name_length) fprintf(stderr, READ_ERROR);
    read = fread(e->id, sizeof(char), 8, f);
    if (read != 8) fprintf(stderr, READ_ERROR);
    read = fread(&(e->age), sizeof(int), 1, f);
    if (read != 1) fprintf(stderr, READ_ERROR);
    return e;
}

Array read_from_binary(FILE *f) {
    Array result;
    result.arr = NULL;
    result.len = 0;
    Elector *e = read_struct_from_binary(f);
    while (e != NULL) {
        append(&result, e);
        e = read_struct_from_binary(f);
    }

    return result;
}
