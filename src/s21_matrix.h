#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

enum ERROR {
    OK,
    NCORR,
    CALCERR
};

int s21_is_correct_to_create(int rows, int columns);
int s21_check_matrix(matrix_t A);
int s21_is_matrix_square(matrix_t A);
int s21_size_eq(matrix_t A, matrix_t B);
int s21_mult_corr(matrix_t A, matrix_t B);
void s21_print_matrix(matrix_t A);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

#endif //  SRC_S21_MATRIX_H_