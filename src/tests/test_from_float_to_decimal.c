#include "tests.h"

int check_result(float f, s21_decimal *check) {
  int flag;
  s21_decimal result = {0};
  flag = s21_from_float_to_decimal(f, &result);
  if (!flag) {
    ck_assert_int_eq(result.bits[0], check->bits[0]);
    ck_assert_int_eq(result.bits[1], check->bits[1]);
    ck_assert_int_eq(result.bits[2], check->bits[2]);
    ck_assert_int_eq(result.bits[3], check->bits[3]);
  }
  return flag;
}

START_TEST(float_to_dec) {
  {
    float f = 10.0;
    s21_decimal result;
    s21_decimal check = {{10, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, 0);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
  }
  {
    float f = 3e15;
    s21_decimal result;
    s21_decimal check = {{1234567, 0x0, 0x0, 0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, 0);
    ck_assert_int_eq(s21_is_equal(result, check), 0);
  }
  {
    float f = 0.0123;
    s21_decimal result;
    s21_decimal check = {{123, 0x0, 0x0, 0}};
    s21_set_scale(&check, 4);

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, 0);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
  }
  {
    float f = -0.0f;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);

    ck_assert_int_eq(code, OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    float f = 2.28401628E-19f;
    s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}};
    ck_assert_int_eq(check_result(f, &decimal_check), OK);
  }
  {
    float f = 5.92141241E+23f;
    s21_decimal decimal_check = {{0x0, 0xa800000, 0x7D64, 0x0}};
    ck_assert_int_eq(check_result(f, &decimal_check), OK);
  }
  {
    s21_decimal dec = {0};
    float f = 1e-30f;
    s21_from_float_to_decimal(f, &dec);
    ck_assert_int_eq(dec.bits[0], 0);
    ck_assert_int_eq(dec.bits[1], 0);
    ck_assert_int_eq(dec.bits[2], 0);
    ck_assert_int_eq(dec.bits[3], 0);
  }
}
END_TEST

Suite *suite_s21_float_to_dec() {
  Suite *s = suite_create("s21_float_to_dec");
  TCase *tc = tcase_create("s21_float_to_dec");

  tcase_add_test(tc, float_to_dec);
  suite_add_tcase(s, tc);
  return s;
}
