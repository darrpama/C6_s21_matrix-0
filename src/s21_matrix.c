#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int err = s21_is_correct_to_create(rows, columns);
    if (err == OK) {
        result->matrix = (double **)calloc(rows, sizeof(double*));
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double *)calloc(columns, sizeof(double));
        }
        result->columns = columns;
        result->rows = rows;
    }
    return err;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
    }
    free(A->matrix);
}

int s21_is_correct_to_create(int rows, int columns) {
    int err = OK;
    if (rows < 1 || columns < 1) {
        err = NCORR;
    }
    return err;
}

int s21_check_matrix(matrix_t A) {
    int err = OK;
    if (A.rows < 1 || A.columns < 1 || A.matrix == NULL) {
        err = NCORR;
    }
    return err;
}

int s21_is_matrix_square(matrix_t A) {
    int err = OK;
    if (A.columns != A.rows) {
        err = NCORR;
    }
    return err;
}

int s21_size_eq(matrix_t A, matrix_t B) {
    int err = OK;
    if ((A.columns != B.columns) || (A.rows != B.rows)) {
        err = NCORR;
    }
    return err;
}

int s21_mult_corr(matrix_t A, matrix_t B) {
    int err = OK;
    if (A.columns != B.rows) {
        err = NCORR;
    }
    return err;
}

void s21_print_matrix(matrix_t A) {
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            printf("%lf ", A.matrix[i][j]);
        }
        printf("\n");
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int result = OK;
    int break_flag = 0;
    if (s21_size_eq(*A, *B) == OK, s21_check_matrix(*A) == OK, s21_check_matrix(*B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) < pow(10, -7)) {
                    result = INCORRECT;
                    break_flag = 1;
                    break;
                }
            }
            if (break_flag) break;
        }
    }
    else {
        result = FAILURE;
    }
    return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int result = OK;
}