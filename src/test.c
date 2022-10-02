#include "s21_matrix.h"

int main() {
  matrix_t A = {0};
  int res = s21_create_matrix(5, 5, &A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j;
    }
  }
  printf("create res = %d\n", res);
  s21_print_matrix(A);
  return 0;
}