#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

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

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_is_square(matrix_t matrix);
int s21_is_correct_to_create(int rows, int columns);

#endif //  SRC_S21_MATRIX_H_