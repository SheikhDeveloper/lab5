#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/generator.h"
#include "lib/sort.h"
#include "lib/voters.h"
#include "lib/file_manager.h"

#define SORT_MENU "Введите способ сортировки:\n\t(a)\"Пузырёк\"\n\t(b)Сортировка двойным выбором\n\t(c)Быстрая сортировка\nСпособ сортировки: "
#define CMP_MENU "Введите поле сортировки массива:\n\t(a)Имя\n\t(b)Номер участка\n\t(c)Возраст\nПоле сортировки: "
#define REV_MENU "Введите направление сортировки:\n\t(a)Прямое\n\t(b)Обратное\nНаправление сортировки: "
#define OUTPUT_MENU "Выберете файл, в который необходимо выводить результаты сортировок:\n\t(a)текстовый файл\n\t(b)бинарный файл\n\t(c)никуда не выводить\nТип файла: "
#define STATE_ERROR "Ошибка: выбрано неверное состояние\nПовторите последовательность выбора заново\n"
#define INP_FORMAT_ERROR "Ошибка: некорректный формат ввода\nПовторите ввод: "

int get_size(size_t *num);

int main() {
    const char *error = NULL;
    double time_spent;
    void (*sort)(Array*, int (*)(Elector*, Elector*), int);
    int (*cmp)(Elector*, Elector*);
    int reversed, scanned;
    char state;
    size_t arr_size, arr_amount;
    clock_t begin, end;
    Array arr;
    char *filename;
    FILE *out_file = NULL;
    int binary_out = 0;
    printf(SORT_MENU);
    scanned = scanf("%c", &state);
    while (scanned != EOF) {
        time_spent = 0.0;
        switch (state) {
            case 'a':
                sort = bubble_sort;
                break;
            case 'b':
                sort = double_selection_sort;
                break;
            case 'c':
                sort = quicksort;
                break;
            default:
                error = STATE_ERROR;
                fprintf(stderr, STATE_ERROR);
                break;
        }
        scanf("%*c");
        if (error != NULL) {
            error = NULL;
            printf(SORT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        printf(CMP_MENU);
        scanned = scanf("%c", &state);
        if (scanned == EOF) return 0;
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
            printf(SORT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        printf(REV_MENU);
        scanned = scanf("%c", &state);
        if (scanned == EOF) return 0;
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
                break;
        }
        scanf("%*c");
        if (error != NULL) {
            error = NULL;
            printf(SORT_MENU);
            scanned = scanf("%c", &state);
            continue;
        }
        printf(OUTPUT_MENU);
        scanned = scanf("%c", &state);
        if (scanned == EOF) return 0;
        scanf("%*c");
        switch (state) {
            case 'a':
                printf("Введите название файла: ");
                filename = freadline(stdin);
                if (filename == NULL) return 0;
                out_file = fopen(filename, "w");
                break;
            case 'b':
                printf("Введите название файла: ");
                filename = freadline(stdin);
                if (filename == NULL) return 0;
                out_file = fopen(filename, "wb");
                binary_out = 1;
                break;
            case 'c':
                filename = NULL;
                break;
            default:
                error = STATE_ERROR;
                break;
        }
        if (filename) {
            free(filename);
            filename = NULL;
        }
        printf("Введите количество элементов в генерируемых массивах: ");
        scanned = get_size(&arr_size);
        if (scanned == EOF) {
            if (out_file != NULL) fclose(out_file);
            return 0;
        }
        printf("Введите количество генерируемых массивов: ");
        scanned = get_size(&arr_amount);
        if (scanned == EOF) {
            if (out_file != NULL) fclose(out_file);
            return 0;
        }
        for (size_t i = 0; i < arr_amount; i++) {
            arr = gen_arr(arr_size);
            begin = clock();
            sort(&arr, cmp, reversed);
            end = clock();
            if (out_file != NULL) {
                write_to_file(out_file, arr, binary_out);
                if (i < arr_amount - 1) fprintf(out_file, "\n\n");
            }
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            free_array(&arr);
        }
        printf("Среднее время сортировки: %lf c\n", time_spent / arr_amount);
        if (out_file != NULL) {
            fclose(out_file);
            binary_out = 0;
        }
        printf(SORT_MENU);
        scanned = scanf("%c", &state);
    }
}

int get_size(size_t *num) {
    int scanned = scanf("%zu", num);
    if (scanned == EOF) return EOF;
    while (scanned != 1) {
        printf(INP_FORMAT_ERROR);
        scanned = scanf("%zu", num);
        if (scanned == EOF) return EOF;
    }
    scanf("%*c");
    return 0;
}
