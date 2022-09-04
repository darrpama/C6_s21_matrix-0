#include <s21_matrix.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int err = s21_is_correct_to_create(rows, columns);
    if (err = OK) {
        result->matrix = (double **)calloc(rows*sizeof(double*));
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double *)calloc(columns*sizeof(double));
        }
        result->columns = columns;
        result->rows = rows;
    }
    return err;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->columns; i++) {
        free(A[i]);
    }
    free(A);
}

int s21_is_square(matrix_t A) {
    int err = s21_is_correct(A);
}

int s21_is_correct_to_create(int rows, int columns) {
    int err = OK;
    if (rows < 1 || columns < 1) {
        err = NCORR;
    }
    return err;
}