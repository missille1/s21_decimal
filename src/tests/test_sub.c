#include "tests.h"

START_TEST(test_sub) {
  {
    // оба числа отрицателные, первое больше второго, степени равны
    s21_decimal value_1 = {{201, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{115, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal check = {{86, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_sub(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }

  {
    // оба числа положительные, первое больше второго, степени равны
    s21_decimal value_1 = {{201, 0, 0, 0}};
    s21_decimal value_2 = {{115, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal check = {{86, 0, 0, 0}};
    ck_assert_int_eq((s21_sub(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // оба числа положительные, первое меньше второго, степени равны
    s21_decimal value_1 = {{386, 0, 0, 0}};
    s21_decimal value_2 = {{405, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal check = {{19, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_sub(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // первое отрицательное и меньше второго, степени равны
    s21_decimal value_1 = {{386, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{405, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal check = {{791, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_sub(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // второе отрицательное и больше 1го, степени равны
    s21_decimal value_1 = {{386, 0, 0, 0}};
    s21_decimal value_2 = {{515, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal check = {{901, 0, 0, 0}};
    ck_assert_int_eq((s21_sub(value_1, value_2, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
    s21_sub(value_1, value_2, &result);
  }
  {
    // * 1000 сдвиг на 4
    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{6, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal result = {0};
    s21_decimal check = {{0b11111111111111111111111111111110, UINT_MAX,
                          UINT_MAX, 0b00000000000000000000000000000000}};

    ck_assert_int_eq((s21_sub(value_1, value_2, &result)), 0);

    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
}
END_TEST

Suite *suite_s21_sub() {
  Suite *s = suite_create("sub");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, test_sub);
  suite_add_tcase(s, tc);
  return s;
}
