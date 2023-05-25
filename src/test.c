#include <check.h>

#include "s21_matrix.h"

int N = 3;
int M = 2;
int T = 5;

START_TEST(test_create_matrix) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t res = {0};

  // ERROR
  ck_assert_int_eq(1, s21_create_matrix(-3, 3, &X));
  ck_assert_int_eq(1, s21_create_matrix(-1, -2, &Y));
  ck_assert_int_eq(1, s21_create_matrix(2, -2, &res));
  ck_assert_int_eq(1, s21_create_matrix(3, 0, &X));
  ck_assert_int_eq(1, s21_create_matrix(0, 2, &Y));

  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_create_matrix(N, N, err));

  // OK
  ck_assert_int_eq(0, s21_create_matrix(N, M, &X));
  ck_assert_int_eq(0, s21_create_matrix(M, M, &Y));
  ck_assert_int_eq(0, s21_create_matrix(M, N, &res));
  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_eq_matrix) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t res = {0};

  //  SUCCESS
  s21_create_matrix(M, M, &X);
  s21_create_matrix(M, M, &Y);
  s21_create_matrix(T, T, &res);

  ck_assert_int_eq(1, s21_eq_matrix(&X, &Y));
  ck_assert_int_eq(1, s21_eq_matrix(&res, &res));

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&res);

  // FAILURE
  matrix_t X1 = {0};
  matrix_t *err = NULL;

  s21_create_matrix(N, M, &X);
  s21_create_matrix(N, M, &X1);
  X.matrix[0][1] = 3.;
  s21_create_matrix(M, N, &Y);
  s21_create_matrix(T, T, &res);

  ck_assert_int_eq(0, s21_eq_matrix(&X, &Y));
  ck_assert_int_eq(0, s21_eq_matrix(&X, &X1));
  ck_assert_int_eq(0, s21_eq_matrix(err, &res));

  s21_remove_matrix(&X);
  s21_remove_matrix(&X1);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_sum_matrix) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t Z = {0};
  matrix_t C = {0};
  matrix_t res = {0};

  // //  OK
  s21_create_matrix(N, N, &Y);
  s21_create_matrix(N, N, &Z);

  ck_assert_int_eq(0, s21_sum_matrix(&Z, &Y, &res));
  ck_assert_int_eq(0, s21_sum_matrix(&res, &res, &X));

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&Z);
  s21_remove_matrix(&res);

  // // COMPUTING_ERROR
  s21_create_matrix(M, M, &X);
  s21_create_matrix(N, N, &Y);
  s21_create_matrix(N, N, &Z);
  s21_create_matrix(M, T, &C);
  s21_create_matrix(T, M, &res);

  ck_assert_int_eq(2, s21_sum_matrix(&X, &Y, &res));
  ck_assert_int_eq(2, s21_sum_matrix(&C, &res, &X));
  ck_assert_int_eq(2, s21_sum_matrix(&Z, &X, &C));
  ck_assert_int_eq(2, s21_sum_matrix(&C, &X, &res));

  // // MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_sum_matrix(err, &Y, &res));
  ck_assert_int_eq(1, s21_sum_matrix(&C, err, &X));

  s21_remove_matrix(&X);
  s21_remove_matrix(&res);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&Z);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t Z = {0};
  matrix_t C = {0};
  matrix_t res = {0};

  //  OK
  s21_create_matrix(N, N, &Y);
  s21_create_matrix(N, N, &Z);

  ck_assert_int_eq(0, s21_sub_matrix(&Z, &Y, &res));
  ck_assert_int_eq(0, s21_sub_matrix(&res, &res, &X));

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&Z);
  s21_remove_matrix(&res);

  // COMPUTING_ERROR
  s21_create_matrix(M, M, &X);
  s21_create_matrix(N, N, &Y);
  s21_create_matrix(N, N, &Z);
  s21_create_matrix(M, T, &C);
  s21_create_matrix(T, M, &res);

  ck_assert_int_eq(2, s21_sub_matrix(&X, &Y, &res));
  ck_assert_int_eq(2, s21_sub_matrix(&C, &res, &X));
  ck_assert_int_eq(2, s21_sub_matrix(&Z, &X, &C));
  ck_assert_int_eq(2, s21_sub_matrix(&C, &X, &res));

  // MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_sub_matrix(err, &Y, &res));
  ck_assert_int_eq(1, s21_sub_matrix(&C, err, &X));

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&Z);
  s21_remove_matrix(&C);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_mult_number) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t res = {0};

  s21_create_matrix(M, M, &X);
  s21_create_matrix(3, 3, &Y);
  Y.matrix[0][0] = 2.;
  Y.matrix[0][1] = 5.;
  Y.matrix[0][2] = 7.;
  Y.matrix[1][0] = 6.;
  Y.matrix[1][1] = 3.;
  Y.matrix[1][2] = 4.;
  Y.matrix[2][0] = 5.;
  Y.matrix[2][1] = -2.;
  Y.matrix[2][2] = -3.;

  //  SUCCESS
  ck_assert_int_eq(0, s21_mult_number(&X, M, &res));
  s21_remove_matrix(&X);
  s21_remove_matrix(&res);

  ck_assert_int_eq(0, s21_mult_number(&Y, N, &res));
  s21_remove_matrix(&Y);
  s21_remove_matrix(&res);

  //  MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_mult_number(err, T, &res));
}
END_TEST

START_TEST(test_mult_matrix) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t Z = {0};
  matrix_t C = {0};
  matrix_t res = {0};

  //  OK
  s21_create_matrix(M, M, &X);
  s21_create_matrix(N, N, &Y);
  s21_create_matrix(N, N, &Z);
  s21_create_matrix(M, T, &C);

  ck_assert_int_eq(0, s21_mult_matrix(&Z, &Y, &res));
  s21_remove_matrix(&res);
  ck_assert_int_eq(0, s21_mult_matrix(&X, &C, &res));
  s21_remove_matrix(&res);

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&Z);
  s21_remove_matrix(&C);

  // COMPUTING_ERROR
  s21_create_matrix(M, M, &X);
  s21_create_matrix(N, N, &Z);
  s21_create_matrix(M, T, &C);

  ck_assert_int_eq(2, s21_mult_matrix(&C, &C, &res));
  s21_remove_matrix(&res);
  ck_assert_int_eq(2, s21_mult_matrix(&Z, &X, &res));
  s21_remove_matrix(&res);

  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);
  s21_remove_matrix(&C);

  // MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_mult_matrix(err, &Y, &res));
  ck_assert_int_eq(1, s21_mult_matrix(&C, err, &X));
}
END_TEST

START_TEST(test_transpose) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t res = {0};

  s21_create_matrix(M, M, &X);
  s21_create_matrix(N, N, &Y);

  //  OK
  ck_assert_int_eq(0, s21_transpose(&X, &res));
  s21_remove_matrix(&res);
  ck_assert_int_eq(0, s21_transpose(&Y, &res));
  s21_remove_matrix(&res);

  // MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_transpose(err, &res));

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
}
END_TEST

START_TEST(test_determinant) {
  double result = 0.;
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t res = {0};

  s21_create_matrix(M, N, &X);
  s21_create_matrix(M, M, &Y);
  s21_create_matrix(1, 1, &res);

  //  OK
  ck_assert_int_eq(0, s21_determinant(&res, &result));
  ck_assert_int_eq(0, s21_determinant(&Y, &result));

  // MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_determinant(err, &result));

  // COMPUTING_ERROR
  ck_assert_int_eq(2, s21_determinant(&X, &result));

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_calc_complements) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t C = {0};
  matrix_t res = {0};

  s21_create_matrix(M, N, &X);
  s21_create_matrix(M, M, &Y);
  s21_create_matrix(1, 1, &C);

  //  OK
  ck_assert_int_eq(0, s21_calc_complements(&Y, &res));
  s21_remove_matrix(&res);

  // // MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_calc_complements(err, &res));

  // // COMPUTING_ERROR
  ck_assert_int_eq(0, s21_calc_complements(&C, &res));
  s21_remove_matrix(&res);
  ck_assert_int_eq(2, s21_calc_complements(&X, &res));
  s21_remove_matrix(&res);

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_matrix) {
  matrix_t X = {0};
  matrix_t Y = {0};
  matrix_t C = {0};
  matrix_t res = {0};

  s21_create_matrix(M, N, &X);
  s21_create_matrix(T, T, &C);

  //  OK
  s21_create_matrix(3, 3, &Y);
  Y.matrix[0][0] = 2.;
  Y.matrix[0][1] = 5.;
  Y.matrix[0][2] = 7.;
  Y.matrix[1][0] = 6.;
  Y.matrix[1][1] = 3.;
  Y.matrix[1][2] = 4.;
  Y.matrix[2][0] = 5.;
  Y.matrix[2][1] = -2.;
  Y.matrix[2][2] = -3.;
  ck_assert_int_eq(0, s21_inverse_matrix(&Y, &res));
  s21_remove_matrix(&res);

  // MATRIX_INCORRECT
  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_inverse_matrix(err, &res));

  // COMPUTING_ERROR
  ck_assert_int_eq(2, s21_inverse_matrix(&X, &res));
  ck_assert_int_eq(2, s21_inverse_matrix(&C, &C));

  s21_remove_matrix(&X);
  s21_remove_matrix(&Y);
  s21_remove_matrix(&C);
  s21_remove_matrix(&res);
}
END_TEST

Suite *matrix_suite(void) {
  Suite *s = suite_create("matrix_testcase");
  TCase *tc_matrix = tcase_create("Core");

  suite_add_tcase(s, tc_matrix);
  tcase_add_test(tc_matrix, test_create_matrix);
  tcase_add_test(tc_matrix, test_eq_matrix);
  tcase_add_test(tc_matrix, test_sum_matrix);
  tcase_add_test(tc_matrix, test_sub_matrix);
  tcase_add_test(tc_matrix, test_mult_number);
  tcase_add_test(tc_matrix, test_mult_matrix);
  tcase_add_test(tc_matrix, test_transpose);
  tcase_add_test(tc_matrix, test_calc_complements);
  tcase_add_test(tc_matrix, test_determinant);
  tcase_add_test(tc_matrix, test_inverse_matrix);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = matrix_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// int ok = 999;
// matrix_t X = {0};
// matrix_t Y = {0};
// matrix_t res = {0};

// s21_create_matrix(3, 3, &X);
// X.matrix[0][0] = 1.;
// X.matrix[0][1] = 2.;
// X.matrix[0][2] = 3.;
// X.matrix[1][0] = 0.;
// X.matrix[1][1] = 4.;
// X.matrix[1][2] = 2.;
// X.matrix[2][0] = 5.;
// X.matrix[2][1] = 2.;
// X.matrix[2][2] = 1.;

// s21_create_matrix(3, 3, &Y);
// Y.matrix[0][0] = 2.;
// Y.matrix[0][1] = 5.;
// Y.matrix[0][2] = 7.;
// Y.matrix[1][0] = 6.;
// Y.matrix[1][1] = 3.;
// Y.matrix[1][2] = 4.;
// Y.matrix[2][0] = 5.;
// Y.matrix[2][1] = -2.;
// Y.matrix[2][2] = -3.;
// double t = 1.;
// ok = s21_inverse_matrix(&Y, &res);
// s21_show_matrix(&res);
