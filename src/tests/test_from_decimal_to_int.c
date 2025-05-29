#include "tests.h"

START_TEST(dec_to_int) {
  {
    s21_decimal val = {{123456789, 0, 0, 0}};
    s21_set_scale(&val, 5);
    int res = 1234;
    int tmp = 0;
    int *dst = &tmp;
    s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(*dst, res);
  }
  {
    s21_decimal val = {{123456789, 0, 0, 0}};
    int res = 123456789;
    int tmp = 0;
    int *dst = &tmp;
    s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(*dst, res);
  }
  {
    s21_decimal val = {{123456789, 0, 0, 0}};
    s21_set_sign(&val, 1);
    int res = -123456789;
    int tmp = 0;
    int *dst = &tmp;
    s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(*dst, res);
  }
  {
    s21_decimal val = {{1, 1, 0, 0}};
    int tmp = 0;
    int *dst = &tmp;
    int err = s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(err, 1);
    ck_assert_int_eq(tmp, 0);
  }
  {
    s21_decimal val = {{0, 0, 1, 0}};
    int tmp = 0;
    int *dst = &tmp;
    int err = s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(err, 1);
    ck_assert_int_eq(tmp, 0);
  }
}
END_TEST

Suite *suite_s21_dec_to_int() {
  Suite *s = suite_create("s21_dec_to_int");
  TCase *tc = tcase_create("s21_dec_to_int");

  tcase_add_test(tc, dec_to_int);
  suite_add_tcase(s, tc);
  return s;
}
