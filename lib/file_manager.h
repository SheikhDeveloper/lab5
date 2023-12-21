#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "voters.h"

#define BUFFER_LENGTH 10
#define WRITE_ERROR "Ошибка записи в файл\n"
#define READ_ERROR "Ошибка чтения из файла\n"
#define FORMAT_ERROR "Ошибка формата ввода\n"
#include "voters.h"

char *freadline(FILE *f);
void write_struc_to_file(FILE *f, Elector *e);
void write_to_file(FILE *f, Array arr, int binary);
void write_struct_to_binary(FILE *f, Elector *e);
void write_to_binary(FILE *f, Array arr);
Elector *read_struct_from_file(FILE *f);
Array read_from_file(FILE *f, int binary);
Elector *read_struct_from_binary(FILE *f);
Array read_from_binary(FILE *f);

#endif
