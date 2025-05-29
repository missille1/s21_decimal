#include "tests.h"

START_TEST(test_truncate) {
  {
    // отрицательное, без дробной части
    // -320 -> -320
    s21_decimal value_1 = {{320, 0, 0, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check_result = {{320, 0, 0, MASK_MINUS}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // 34,1 -> 34
    s21_decimal value_1 = {{341, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal check_result = {{34, 0, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // 4 294 967 296, 000 -> 4 294 967 296
    s21_decimal value_1 = {{0, 1000, 0, 0b00000000000000110000000000000000}};
    s21_decimal check_result = {{0, 1, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }

  {
    // 40,5 -> 40
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal value_1 = {{405, 0, 0, 0b10000000000000010000000000000000}};
    s21_decimal check_result = {{40, 0, 0, 0b10000000000000000000000000000000}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // нет целой части (десятичная дробь с целой частью 0)
    // 0,4 -> 0

    s21_decimal value_1 = {{40, 0, 0, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check_result = {{0, 0, 0, 0}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // 11001000000000000000000000000000000000000000000000000000000000000000000000
    // 14 757 395 258 967 641 292, 800 -> 14 757 395 258 967 641 292
    s21_decimal value_1 = {{0, 0, 800, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check_result = {{0b11001100110011001100110011001100,
                                 0b11001100110011001100110011001100, 0, 0}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // 00000000000000000000000100111001 = 313
    //  00000000000000000000000011010011 =211
    // 5 773 830 8, 95 071 089 656 019 -> 5 773 830 8 (14 степень)
    s21_decimal value_1 = {{211, 0, 313, 0b00000000000011100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check_result = {{0b00000011011100010000010001000100, 0, 0, 0}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // 00000000000000000000000100111001 = 313
    //  00000000000000000000000011010011 =211
    // -5 7, 73 830 895 071 089 656 019 -> -57 (20 степень)
    s21_decimal value_1 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check_result = {{57, 0, 0, MASK_MINUS}};

    ck_assert_int_eq((s21_truncate(value_1, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    s21_decimal value_1 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    s21_decimal *result = NULL;

    ck_assert_int_eq((s21_truncate(value_1, result)), ERROR);
  }
  //   00000000000000000000000000000000
}
END_TEST

Suite *suite_s21_truncate() {
  Suite *s = suite_create("truncate");
  TCase *tc = tcase_create("truncate_tc");

  tcase_add_test(tc, test_truncate);

  suite_add_tcase(s, tc);
  return s;
}
