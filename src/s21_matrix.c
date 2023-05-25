#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (!result || rows <= 0 || columns <= 0) {
    return MATRIX_INCORRECT;
  }
  // проверка на выделение памяти раз
  if ((result->matrix = (double **)calloc(rows, sizeof(double *)))) {
    result->columns = columns;
    result->rows = rows;
    for (int i = 0; i < rows; i++) {
      // проверка на выделение памяти два
      if (!(result->matrix[i] = (double *)calloc(columns, sizeof(double)))) {
        for (int j = 0; j < i; j++) {
          free(result->matrix[j]);
        }
        free(result->matrix);
        return MATRIX_INCORRECT;
      }
    }
  }
  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = FAILURE;
  if (s21_check_matrix(A) && s21_check_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      int stop_flag = 0;
      for (int i = 0; i < A->rows; i++) {
        if (stop_flag) {
          break;
        }
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) < 1e-7) {
            status = SUCCESS;
          } else {
            stop_flag = 1;
            status = FAILURE;
            break;
          }
        }
      }
    }
  }

  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_check_matrix(A) || !s21_check_matrix(B)) {
    return MATRIX_INCORRECT;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return COMPUTING_ERR;
  }
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_check_matrix(A) || !s21_check_matrix(B)) {
    return MATRIX_INCORRECT;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return COMPUTING_ERR;
  }

  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_check_matrix(A)) {
    return MATRIX_INCORRECT;
  }
  if (!(s21_create_matrix(A->rows, A->columns, result))) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_check_matrix(A) || !s21_check_matrix(B)) {
    return MATRIX_INCORRECT;
  }
  if (A->columns != B->rows) {
    return COMPUTING_ERR;
  }

  s21_create_matrix(A->rows, B->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < B->rows; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_check_matrix(A)) {
    return MATRIX_INCORRECT;
  }

  s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  if (!s21_check_matrix(A)) {
    return MATRIX_INCORRECT;
  }
  if (A->columns != A->rows) {
    return COMPUTING_ERR;
  }

  *result = 0;
  if (A->columns == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else if (A->columns == 1) {
    *result = A->matrix[0][0];
  } else {
    double tmp_d = 0.;
    int sign = 1;
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_make_minor(A, i, 0, A->rows, &tmp);
      s21_determinant(&tmp, &tmp_d);
      *result += sign * tmp_d * A->matrix[i][0];
      sign *= -1;
    }
    s21_remove_matrix(&tmp);
  }

  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_check_matrix(A)) {
    return MATRIX_INCORRECT;
  }
  if (A->columns != A->rows) {
    return COMPUTING_ERR;
  }

  int size = A->columns;
  s21_create_matrix(size, size, result);
  if (size == 1) {
    result->matrix[0][0] = 1;
    return OK;
  }

  matrix_t tmp = {0};
  s21_create_matrix(size - 1, size - 1, &tmp);
  double tmp_d;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      s21_make_minor(A, i, j, A->rows, &tmp);
      int sign = ((i + j) % 2 == 0) ? 1 : -1;
      if (OK == s21_determinant(&tmp, &tmp_d)) {
        result->matrix[i][j] = sign * tmp_d;
      }
    }
  }
  s21_remove_matrix(&tmp);

  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_check_matrix(A)) {
    return MATRIX_INCORRECT;
  }

  if (A->columns != A->rows) {
    return COMPUTING_ERR;
  }

  int size = A->columns;
  double tmp_d = 0.;
  s21_determinant(A, &tmp_d);
  if (fabs(tmp_d) < 1e-6) {
    return COMPUTING_ERR;
  }

  matrix_t tmp = {0};
  matrix_t transpose_tmp = {0};
  s21_create_matrix(size, size, result);
  s21_calc_complements(A, &tmp);
  s21_transpose(&tmp, &transpose_tmp);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result->matrix[i][j] = transpose_tmp.matrix[i][j] / tmp_d;
    }
  }
  s21_remove_matrix(&tmp);
  s21_remove_matrix(&transpose_tmp);

  return OK;
}

// SUPPORTING FUNCS

int s21_check_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL && A->columns > 0 && A->rows > 0) {
    return SUCCESS;
  }
  return FAILURE;
}

void s21_make_minor(matrix_t *A, int current_i, int current_j, int size,
                    matrix_t *res) {
  for (int i = 0, r = 0; i < size; i++) {
    for (int j = 0, c = 0; j < size; j++) {
      if (i != current_i && j != current_j) {
        res->matrix[r][c++] = A->matrix[i][j];
        if (c == size - 1) {
          c = 0;
          r++;
        }
      }
    }
  }
}

// void s21_show_matrix(matrix_t *A) {
//   for (int i = 0; i < A->rows; i++) {
//     for (int j = 0; j < A->columns; j++) {
//       printf("%lf ", A->matrix[i][j]);
//       if (j == A->columns - 1) {
//         printf("\n");
//       }
//     }
//   }
//   printf("\n");
// }
