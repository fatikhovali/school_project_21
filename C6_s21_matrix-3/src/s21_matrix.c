#include "s21_matrix.h"

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      error = 1;
    } else if (result->matrix != NULL) {
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
      error = 0;
    }
  } else if (rows < 1 || columns < 1 || result == NULL) {
    error = 1;
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = 1;
  int flag = 0;
  if ((A->columns == B->columns) && (A->rows == B->rows) && (A->columns > 0) &&
      (A->rows > 0)) {
    if (flag == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          double diff = A->matrix[i][j] - B->matrix[i][j];
          diff = fabs(diff);
          if (diff > 1e-6) {
            error = 0;
            flag = 1;
            ;
          }
        }
        if (error == 0) {
          flag = 1;
        }
      }
    }
  } else {
    error = 0;
  }
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A != NULL && B != NULL) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A != NULL && B != NULL) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A != NULL && B != NULL) {
    if (A->rows > 0 && B->columns > 0 && B->rows && A->columns > 0) {
      if (A->columns == B->rows) {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int q = 0; q < A->columns; q++) {
              result->matrix[i][j] += A->matrix[i][q] * B->matrix[q][j];
            }
          }
        }
      } else {
        error = 2;
      }
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A != NULL) {
    if (A->columns > 0 && A->rows > 0) {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (A != NULL) {
    if (A->rows == A->columns) {
      *result = determinant(A);
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int minor_func(int column, int row, matrix_t *A, matrix_t *result) {
  int l = 0;
  int m = 0;
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  for (int i = 0; i < result->rows; i++) {
    if (i == row) {
      l = 1;
    }
    m = 0;
    for (int j = 0; j < result->columns; j++) {
      if (j == column) {
        m = 1;
      }
      result->matrix[i][j] = A->matrix[i + l][j + m];
    }
  }
  return 0;
}

double determinant(matrix_t *A) {
  double result = 0;
  if (A->rows == 1)
    result = A->matrix[0][0];
  else if (A->rows == 2)
    result = (A->matrix[0][0] * A->matrix[1][1]) -
             (A->matrix[0][1] * A->matrix[1][0]);
  else {
    int znak = 1;
    for (int i = 0; i < A->rows; i++) {
      matrix_t B;
      minor_func(i, 0, A, &B);
      result += znak * A->matrix[0][i] * determinant(&B);
      znak *= -1;
      s21_remove_matrix(&B);
    }
  }
  return result;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A != NULL && A->rows > 0 && A->columns > 0) {
    error = 2;
    if (A->rows == A->columns) {
      double determinant;
      s21_determinant(A, &determinant);
      if (fabs(determinant - 0) > 1e-6) {
        matrix_t tmp;
        error = s21_calc_complements(A, &tmp);
        if (error == 0) {
          matrix_t tmp2;
          error = s21_transpose(&tmp, &tmp2);
          if (error == 0) {
            s21_mult_number(&tmp2, 1 / determinant, result);
          }
          s21_remove_matrix(&tmp2);
        }
        s21_remove_matrix(&tmp);
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

void complements_min(int i, int j, matrix_t *A, matrix_t *result) {
  int resI = 0;
  int resJ = 0;
  for (int k = 0; k < A->rows; k++) {
    for (int m = 0; m < A->columns; m++) {
      if (k != i && m != j) {
        result->matrix[resI][resJ] = A->matrix[k][m];
        if (resJ < (result->columns) - 1) {
          resJ++;
        } else {
          resJ = 0;
          resI++;
        }
      }
    }
  }
}

void calc_compl(matrix_t *A, matrix_t *result) {
  if (A->rows == 1) {
    result->matrix[0][0] = A->matrix[0][0];
  }
  if (A->rows == 2) {
    matrix_t B;
    s21_create_matrix(1, 1, &B);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        complements_min(i, j, A, &B);
        result->matrix[i][j] = B.matrix[0][0] * pow(-1, (i + j));
      }
    }
    s21_remove_matrix(&B);
  } else if (A->rows > 2) {
    matrix_t B;
    s21_create_matrix((A->rows) - 1, (A->columns) - 1, &B);
    double res = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        complements_min(i, j, A, &B);
        s21_determinant(&B, &res);
        result->matrix[i][j] = res * pow(-1, (i + j));
        res = 0;
      }
    }
    s21_remove_matrix(&B);
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if ((A != NULL) && (A->matrix != NULL) && (A->rows > 0) && (A->columns > 0)) {
    error = 0;
  } else {
    error = 2;
  }
  if (error == 0) {
    if (A->rows == A->columns) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (error == 0) {
        calc_compl(A, result);
      }
    } else {
      error = 2;
      result->matrix = NULL;
      result->rows = 0;
      result->columns = 0;
    }
  }
  return error;
}
