#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum ERROR { OK, NCORR, CALCERR };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_is_correct_to_create(int rows, int columns);
int s21_check_matrix(matrix_t A);
int s21_is_matrix_square(matrix_t A);
int s21_size_eq(matrix_t A, matrix_t B);
int s21_mult_corr(matrix_t A, matrix_t B);
void s21_print_matrix(matrix_t A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
void create_minor(matrix_t *minor, matrix_t *A, int row, int column);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  //  SRC_S21_MATRIX_H_