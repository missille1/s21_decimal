#include "tests.h"

START_TEST(test_add) {
  {
    s21_decimal value_1 = {{115, 0, 0, 0}};
    s21_decimal value_2 = {{201, 0, 0, 0}};
    s21_decimal *result = NULL;

    ck_assert_int_eq((s21_mul(value_1, value_2, result)), ERROR);
  }
  {
    // оба положительные, степень одинаковая
    s21_decimal value_1 = {{115, 0, 0, 0}};
    s21_decimal value_2 = {{201, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal check = {{23115, 0, 0, 0}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // второе отрицательное и больше первого, степень одинаковая

    s21_decimal value_1 = {{99, 0, 0, 0}};
    s21_decimal value_2 = {{211, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal check = {{20889, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // второе отрицательное и меньше первого, степень одинаковая

    s21_decimal value_1 = {{318, 0, 0, 0}};
    s21_decimal value_2 = {{150, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal check = {{47700, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // первое отрицательное и меньше второго, степень одинаковая

    s21_decimal value_1 = {{420, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{518, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal check = {{217560, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // первое отрицательное и больше второго, степень одинаковая

    s21_decimal value_1 = {{783, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{618, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal check = {{483894, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // оба отрицательные , степень одинаковая

    s21_decimal value_1 = {{480, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{320, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal check = {{153600, 0, 0, 0}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // проверка на переполнение вверх

    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{320, 0, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{DEC_ZERO}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), TOO_BIG);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // проверка на переполнение вниз

    s21_decimal value_1 = {{DEC_MIN}};
    s21_decimal value_2 = {{320, 0, 0, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{DEC_ZERO}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), TOO_BIG);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value_1 = {{1, 0, 0, 0}};
    s21_decimal value_2 = {{165, 22, 6587456, 0}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{165, 22, 6587456, 0}};
    ck_assert_int_eq((s21_mul(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
}
END_TEST

Suite *suite_s21_mul() {
  Suite *s = suite_create("add");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, test_add);

  suite_add_tcase(s, tc);
  return s;
}