#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/file_manager.h"
#include "lib/voters.h"
#include "lib/sort.h"

#define SUCCESS "\nДействие совершено!\n"
#define INPUT_MENU "Введите способ получения массива:\n\t(a)С клавиатуры\n\t(b)Из текстового файла\n\t(c)Из бинарного файла\nСпособ получения массива: "
#define OUTPUT_MENU "Введите способ вывода отсортированного массива:\n\t(a)На экран\n\t(b)В текстовый файл\n\t(c)В бинарный файл\nСпособ вывода массива: "
#define SORT_MENU "Введите способ сортировки:\n\t(a)\"Пузырёк\"\n\t(b)Сортировка двойным выбором\n\t(c)Быстрая сортировка\nСпособ сортировки: "
#define CMP_MENU "Введите поле сортировки массива:\n\t(a)Имя\n\t(b)Номер участка\n\t(c)Возраст\nПоле сортировки: "
#define REV_MENU "Введите направление сортировки:\n\t(a)Прямое\n\t(b)Обратное\nНаправление сортировки: "
#define STATE_ERROR "Ошибка: выбрано неверное состояние\nПовторите последовательность выбора заново\n"
#define FILENAME_ERROR "Ошибка: файла с таки названием не существует.\nПовторите последовательность выборов\n"
#define FILE_READ_ERROR "Ошибка: указанный файл пуст или формат всех данных в нём некорректен.\nПовторите последовательность выборов\n"

void sort(Array *a, void (*sorter)(Array*, int (*)(Elector*, Elector*), int), int (*cmp)(Elector*, Elector*), int reversed);

int main() {
    const char *error = NULL;
    char *filename = NULL;
    Array voters;
    voters.arr = NULL;
    FILE *in_file;
    FILE *out_file;
    int (*cmp)(Elector*, Elector*);
    void (*sorting) (Array*, int (*)(Elector*, Elector*), int);
    int binary_in = 0;
    int binary_out = 0; 
    int reversed;
    int scanned = 0;
    char state;
    printf(INPUT_MENU);
    scanned = scanf("%c", &state);
    if (scanned == EOF) return 0;
    while (scanned != EOF) {
        scanf("%*c");
        switch (state) {
            case 'a':
                in_file = stdin;
                break;
            case 'b':
                printf("Введите название файла: ");
                filename = freadline(stdin);
                in_file = fopen(filename, "r+");
                if (in_file == NULL) error = FILENAME_ERROR;
                break;
            case 'c':
                printf("Введите название файла: ");
                filename = freadline(stdin);
                in_file = fopen(filename, "r+b");
                binary_in = 1;
                if (in_file == NULL) error = FILENAME_ERROR;
                break;
            default:
                error = STATE_ERROR;
                break;
        }
        free(filename);
        filename = NULL;
        if (error != NULL) {
            binary_in = 0;
            fprintf(stderr, "%s", error);
            error = NULL;
            printf(INPUT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        voters = read_from_file(in_file, binary_in);
        if (voters.arr == NULL) {
            error = FILE_READ_ERROR;
            fprintf(stdout, "%s", error);
            printf(INPUT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        printf(OUTPUT_MENU);
        scanned = scanf("%c", &state);
        if (scanned == EOF) {
            free_array(&voters);
            return 0;
        }
        scanf("%*c");
        switch (state) {
            case 'a':
                out_file = stdout;
                break;
            case 'b':
                printf("Введите название файла: ");
                filename = freadline(stdin);
                out_file = fopen(filename, "w");
                break;
            case 'c':
                printf("Введите название файла: ");
                filename = freadline(stdin);
                out_file = fopen(filename, "wb");
                binary_out = 1;
                break;
            default:
                error = STATE_ERROR;
                break;
        }
        free(filename);
        filename = NULL;
        if (error != NULL) {
            binary_out = 0;
            fprintf(stderr, "%s", error);
            error = NULL;
            free_array(&voters);
            printf(INPUT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        printf(SORT_MENU);
        scanned = scanf("%c", &state);
        if (scanned == EOF) {
            free_array(&voters);
            return 0;
        }
        switch (state) {
            case 'a':
                sorting = bubble_sort;
                break;
            case 'b':
                sorting = double_selection_sort;
                break;
            case 'c':
                sorting = quicksort;
                break;
            default:
                error = STATE_ERROR;
                fprintf(stderr, STATE_ERROR);
                break;
        }
        scanf("%*c");
        if (error != NULL) {
            error = NULL;
            free_array(&voters);
            printf(INPUT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        printf(CMP_MENU);
        scanned = scanf("%c", &state);
        if (scanned == EOF) {
            free_array(&voters);
            return 0;
        }
        switch (state) {
            case 'a':
                cmp = name_cmp;
                break;
            case 'b':
                cmp = id_cmp;
                break;
            case 'c':
                cmp = age_cmp;
                break;
            default:
                error = STATE_ERROR;
                fprintf(stderr, STATE_ERROR);
                break;
        }
        scanf("%*c");
        if (error != NULL) {
            error = NULL;
            free_array(&voters);
            printf(INPUT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        printf(REV_MENU);
        scanned = scanf("%c", &state);
        if (scanned == EOF) {
            free_array(&voters);
            return 0;
        }
        switch (state) {
            case 'a':
                reversed = 0;
                break;
            case 'b':
                reversed = 1;
                break;
            default:
                error = STATE_ERROR;
                fprintf(stderr, STATE_ERROR);
                return 0;
                break;
        }
        scanf("%*c");
        if (error != NULL) {
            error = NULL;
            free_array(&voters);
            printf(INPUT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        sort(&voters, sorting, cmp, reversed);
        write_to_file(out_file, voters, binary_out);
        printf(SUCCESS);
        free_array(&voters);
        voters.arr = NULL;
        printf(INPUT_MENU);
        scanned = scanf("%c", &state);
    }
    if (in_file != NULL) fclose(in_file);
    if (out_file != NULL) fclose(out_file);
    return 0;
}

void sort(Array *a, void (*sorter)(Array*, int (*)(Elector*, Elector*), int), int (*cmp)(Elector*, Elector*), int reversed) {
    sorter(a, cmp, reversed);
}
