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
//  0 - square
//  1 - not square
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
    int err = SUCCESS;
    int break_flag = 0;
    if (s21_size_eq(*A, *B) || s21_check_matrix(*A) || s21_check_matrix(*B)) {
        err = FAILURE;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) < pow(10, -7)) {
                    err = FAILURE;
                    break_flag = 1;
                    break;
                }
            }
            if (break_flag) break;
        }
    }
    return err;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = OK;
    if (s21_check_matrix(*A) || s21_check_matrix(*B)) {
        err = NCORR;
    } else if (s21_size_eq(*A, *B)) {
        err = CALCERR;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; i < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    }
    return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = OK;
    if (s21_check_matrix(*A) || s21_check_matrix(*B)) {
        err = NCORR;
    } else if (s21_size_eq(*A, *B)) {
        err = CALCERR;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; i < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
    }
    return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int err = OK;
    if (s21_check_matrix(*A)) {
        err = NCORR;
    } else if (number != number || number == S21_INF || number == -S21_INF) {
        err = CALCERR;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; i < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number; 
            }
        }
    }
    return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = OK;
    double temp = 0;
    if (s21_check_matrix(*A) || s21_check_matrix(*B)) {
        err = NCORR;
    } else if (s21_mult_corr(*A, *B)) {
        err = CALCERR;
    } else {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++) {
                    temp += A->matrix[i][k] * B->matrix[k][j];
                }
                result->matrix[i][j] = temp;
                temp = 0;
            }
        }
    }
    return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int err = OK;
    if (s21_check_matrix(*A)) {
        err = NCORR;
    } else {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int err = OK;
    if (s21_check_matrix(*A)) {
        err = NCORR;
    } else if (s21_is_matrix_square(*A) || A->rows == 1) {
        err = CALCERR;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        double det_res = 0;
        matrix_t minor = {NULL, 0, 0};
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                create_minor(&minor, A, i, j);
                s21_determinant(&minor, &det_res);
                det_res *= pow(-1, i + j);
                result->matrix[i][j] = det_res;
            }
        }
        s21_remove_matrix(&minor);
    }
    return err;
}

int s21_determinant(matrix_t *A, double *result) {
    int err = OK;
    if (s21_check_matrix(*A)) {
        err = NCORR;
    } else if (s21_is_matrix_square(*A)) {
        err = CALCERR;
    } else {
        double temp = 0, res = 0;
        if (A->rows == 1) {
            *result = A->matrix[0][0];
        } else if (A->rows == 2) {
            *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        } else {
            matrix_t minor = {NULL, 0, 0};
            s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
            for (int j = 0; j < A->columns - 1; j++) {
                create_minor(&minor, A, 0, j);
                s21_determinant(&minor, &temp);
                res += A->matrix[0][j] * temp * pow(-1, j);
                *result = res;
            }
            s21_remove_matrix(&minor);
        }
    }
    return err;
}

int create_minor(matrix_t *minor, matrix_t *A, int row, int column) {
    int flag_str = 0, flag_cln = 0;
    for (int k = 0; k < A->rows - 1; k++) {
        if (k >= row) {
            flag_str = 1;
        } else {
            flag_str = 0;
        }
        for (int h = 0; h < A->columns - 1; h++) {
            if (h >= column) {
                flag_cln = 1;
            } else {
                flag_cln = 0;
            }
            minor->matrix[k][h] = minor->matrix[k + flag_str][h + flag_cln];
        }
    }
}

s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int err = 0;
    double determinant = 0;
    if (s21_check_matrix(*A)) {
        err = NCORR;
    } else if (s21_is_matrix_square(*A)) {
        err = CALCERR;
    } else {
        s21_determinant(*A, determinant);
        if (determinant == 0) {
            err = CALCERR;
        } else {
            if (A->rows == 1) {
                s21_create_matrix(1, 1, result);
                result->matrix[0][0] = 1 / (A->matrix[0][0]);
            } else {
                matrix_t complements = {NULL, 0, 0};
                matrix_t tr_complements = {NULL, 0, 0};
                s21_calc_complements(A, &complements);
                s21_transpose(&complements, &tr_complements);
                s21_mult_number(&tr_complements, 1 / determinant, result);
                s21_remove_matrix(&complements);
                s21_remove_matrix(&tr_complements);
            }
        }
    }
    return err;
}
