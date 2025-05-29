#include "tests.h"

START_TEST(int_to_dec) {
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    int dst = 100;
    s21_from_int_to_decimal(dst, &dec);
    ck_assert_int_eq(dst, dec.LOW);
  }
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    s21_decimal res = {{2147483646, 0, 0, 0}};
    unsigned int dst = 2147483646;

    s21_from_int_to_decimal(dst, &dec);
    ck_assert_int_eq(s21_is_equal(dec, res), 1);
  }
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    s21_decimal res = {{10, 0, 0, MASK_MINUS}};
    unsigned int dst = -10;

    s21_from_int_to_decimal(dst, &dec);
    ck_assert_int_eq(s21_is_equal(dec, res), 1);
  }
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    s21_decimal res = {{0b01111111111111111111111111111111, 0, 0, 0}};
    unsigned int dst = 0b01111111111111111111111111111111;

    s21_from_int_to_decimal(dst, &dec);
    ck_assert_int_eq(s21_is_equal(dec, res), 1);
  }
  {
    s21_decimal dec = {0};
    int result;

    result = s21_from_int_to_decimal(0, &dec);
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_uint_eq(result, 0);

    result = s21_from_int_to_decimal(-0, &dec);
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_uint_eq(result, 0);
  }
  {
    s21_decimal dec = {0};
    int result;

    result = s21_from_int_to_decimal(INT_MAX, &dec);
    ck_assert_uint_eq(dec.bits[0], INT_MAX);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_uint_eq(result, 0);

    result = s21_from_int_to_decimal(INT_MIN, &dec);
    ck_assert_uint_eq(dec.bits[0], 2147483648);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 2147483648);
    ck_assert_uint_eq(result, 0);
  }
  {
    s21_decimal dec_1 = {0}, dec_2 = {0};
    int result;

    dec_1.bits[0] = 0b00000000000000000000000000000001;
    dec_1.bits[1] = 0b00000000000000000000000000000000;
    dec_1.bits[2] = 0b00000000000000000000000000000000;
    dec_1.bits[3] = 0b00000000000000000000000000000000;

    result = s21_from_int_to_decimal(1, &dec_2);

    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
    ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
    ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
    ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
  }
  {
    s21_decimal dec_1 = {0}, dec_2 = {0};
    int result;

    dec_1.bits[0] = 0b00000000000000000000000000000001;
    dec_1.bits[1] = 0b00000000000000000000000000000000;
    dec_1.bits[2] = 0b00000000000000000000000000000000;
    dec_1.bits[3] = 0b10000000000000000000000000000000;

    result = s21_from_int_to_decimal(-1, &dec_2);

    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
    ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
    ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
    ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
  }
  {
    s21_decimal dec = {0};
    int number = 499559;
    int result;

    dec.bits[0] = 0b00010001000010000010000010000001;
    dec.bits[1] = 0b01000100001110000001000000010000;
    dec.bits[2] = 0b00001000100100101000010001000100;
    dec.bits[3] = 0b10000000000000000000000000000000;

    result = s21_from_int_to_decimal(number, &dec);

    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(dec.bits[0], number);
    ck_assert_int_eq(dec.bits[1], 0);
    ck_assert_int_eq(dec.bits[2], 0);
    ck_assert_int_eq(dec.bits[3], 0);
  }
  {
    int result = s21_from_int_to_decimal(123456, NULL);
    ck_assert_int_eq(result, 1);
  }
  {
    s21_decimal dec = {0};
    int result;
    int values[12] = {-rand(), rand(), -rand(), rand(), -rand(), rand()};
    int i = _i;

    result = s21_from_int_to_decimal(values[i], &dec);
    ck_assert_uint_eq(dec.bits[0], abs(values[i]));
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], values[i] > 0 ? 0 : 2147483648);
    ck_assert_uint_eq(result, 0);
  }
  {
    s21_decimal decimal;
    s21_set_to_zero(&decimal);
    int i = -3000, res = 0;
    s21_from_int_to_decimal(i, &decimal);
    s21_from_decimal_to_int(decimal, &res);
    ck_assert_int_eq(i, res);
  }

  {
    s21_decimal x = {{0, 0, 0, 0}};
    s21_decimal y = {{15, 0, 0, 0}};
    int z = 15;
    s21_from_int_to_decimal(z, &x);
    char res1[1000], res2[1000];
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
             x.bits[2], x.bits[3]);
    snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
             y.bits[2], y.bits[3]);
    ck_assert_str_eq(res1, res2);
  }

  {
    s21_decimal x = {{0, 0, 0, 0}};
    s21_decimal y = {{15, 0, 0, 2147483648}};
    int z = -15;
    s21_from_int_to_decimal(z, &x);
    char res1[1000], res2[1000];
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
             x.bits[2], x.bits[3]);
    snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
             y.bits[2], y.bits[3]);
    ck_assert_str_eq(res1, res2);
  }

  {
    s21_decimal x = {{0, 0, 0, 0}};
    s21_decimal y = {{0, 0, 0, 0}};
    int z = 0;
    s21_from_int_to_decimal(z, &x);
    char res1[1000], res2[1000];
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
             x.bits[2], x.bits[3]);
    snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
             y.bits[2], y.bits[3]);
    ck_assert_str_eq(res1, res2);
  }

  {
    int src = 124;
    int error = 0;
    error = s21_from_int_to_decimal(src, NULL);
    ck_assert_int_eq(error, 1);
  }
}
END_TEST

Suite *suite_s21_int_to_dec() {
  Suite *s = suite_create("s21_int_to_dec");
  TCase *tc = tcase_create("s21_int_to_dec");

  tcase_add_test(tc, int_to_dec);
  suite_add_tcase(s, tc);
  return s;
}