#include "tests.h"
START_TEST(test_negate) {
  {
    s21_decimal value = {{0, 0, 0, 0b00000000000001110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0, 0, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{4, 223, 18, 0b00000000000000010000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{4, 223, 18, 0b10000000000000010000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{4000, 123, 877, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{4000, 123, 877, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {
        {324000, 11123, 6877, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {
        {324000, 11123, 6877, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{30, 1113, 677, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{30, 1113, 677, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{0, 10000, 0, 0b00000000000001110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0, 10000, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{91848, 0, 1, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{91848, 0, 1, 0}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{11, 981, 313, 0b10000000000101000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{11, 981, 313, 0b00000000000101000000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{872112, 1, 13, 0b10000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{872112, 1, 13, 0b00000000000111000000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{320, 0, 0, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{320, 0, 0, 0}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{3200, 0, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{3200, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{0, 1000, 0, 0b00000000000001110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0, 1000, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }

  {
    s21_decimal value = {{313, 0, 1, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{313, 0, 1, 0}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{211, 1, 313, 0b10000000000101000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{211, 1, 313, 0b00000000000101000000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }

  {
    s21_decimal num = {{1, 0, 0, 2147483648u}};
    s21_decimal res = {{1, 0, 0, 0}};
    int error = 0;
    error = s21_negate(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }
  {
    s21_decimal num = {{1, 0, 0, 0}};
    s21_decimal res = {{1, 0, 0, 2147483648u}};
    int error = 0;
    error = s21_negate(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{1, 0, 0, 0}};
    int error = 0;
    error = s21_negate(num, NULL);
    ck_assert_int_eq(error, 1);
  }

  {
    s21_decimal x = {{32444, 100, 343253, -2145976320}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_negate(x, &z);
    char ourRes[1000], expect[1000] = "32444 100 343253 1507328";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{1, 1, 1, 917504}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_negate(x, &z);
    char ourRes[1000], expect[1000] = "1 1 1 2148401152";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{0, 0, 0, 917504}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_negate(x, &z);
    char ourRes[1000], expect[1000] = "0 0 0 2148401152";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }
}
END_TEST

Suite *suite_s21_negate() {
  Suite *s = suite_create("s21_negate");
  TCase *tc = tcase_create("s21_negate");

  tcase_add_test(tc, test_negate);
  suite_add_tcase(s, tc);
  return s;
}