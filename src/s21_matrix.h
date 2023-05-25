#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

// OK
#define OK 0
// Ошибка, некорректная матрица
#define MATRIX_INCORRECT 1
// Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя
// провести вычисления и т.д.)
#define COMPUTING_ERR 2

/**
 * @brief matrix_t структура матрицы
 * @param matrix двумерная матрица
 * @param rows кол-во рядов
 * @param columns кол-во столбцов
 */
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/**
 * @brief Создание матрицы
 * @param rows кол-во рядов
 * @param columns кол-во столбцов
 * @param result указатель на результат созданной матрицы
 * @return Результирующий код
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);
/**
 * @brief Очистка матрицы
 * @param A указатель на очищаемую матрицу
 */
void s21_remove_matrix(matrix_t *A);
/**
 * @brief Сравнение матриц
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return Результирующий код
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);
/**
 * @brief Сложение матриц
 * @param A Первая матрица
 * @param B Вторая матрица
 * @param result Результирующая матрица
 * @return Результирующий код
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
/**
 * @brief Вычитание матриц
 * @param A Первая матрица
 * @param B Вторая матрица
 * @param result Результирующая матрица
 * @return Результирующий код
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
/**
 * @brief Умножение матрицы на число
 * @param A Первая матрица
 * @param number множитель
 * @param result Результирующая матрица
 * @return Результирующий код
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
/**
 * @brief Умножение матриц
 * @param A Первая матрица
 * @param B Вторая матрица
 * @param result Результирующая матрица
 * @return Результирующий код
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
/**
 * @brief Транспонирование матрицы
 * @param A Первая матрица
 * @param result Результирующая матрица
 * @return Результирующий код
 */
int s21_transpose(matrix_t *A, matrix_t *result);
/**
 * @brief Определитель матрицы (determinant)
 * @param A Первая матрица
 * @param result determinant
 * @return Результирующий код
 */
int s21_determinant(matrix_t *A, double *result);
/**
 * @brief Матрица алгебраических дополнений
 * @param A Первая матрица
 * @param result Результирующая матрица
 * @return Результирующий код
 */
int s21_calc_complements(matrix_t *A, matrix_t *result);
/**
 * @brief Обратная матрица
 * @param A Первая матрица
 * @param result Результирующая матрица
 * @return Результирующий код
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
//
//
void s21_show_matrix(matrix_t *A);
int s21_check_matrix(matrix_t *A);
void s21_make_minor(matrix_t *A, int current_i, int current_j, int size,
                    matrix_t *res);
#endif // SRC_S21_MATRIX_H_