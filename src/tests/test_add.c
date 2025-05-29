#include "tests.h"

START_TEST(test_add) {
  {
    // оба положительные, степень одинаковая
    s21_decimal value_1 = {{115, 0, 0, 0}};
    s21_decimal value_2 = {{201, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal check = {{316, 0, 0, 0}};
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), 0);
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
    s21_decimal check = {{112, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), 0);
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
    s21_decimal check = {{168, 0, 0, 0}};
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), 0);
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
    s21_decimal check = {{98, 0, 0, 0}};
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), 0);
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
    s21_decimal check = {{165, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), 0);
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
    s21_decimal check = {{800, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), 0);
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
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), TOO_BIG);
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
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), TOO_SMALL);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // сложение 2х Максмальных децималов, в 1й степени => после сложения они
    // округляются 15845632502852867518708790067
    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{DEC_MAX}};
    s21_set_scale(&value_1, 1);
    s21_set_scale(&value_2, 1);
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b00110011001100110011001100110011,
                          0b00110011001100110011001100110011,
                          0b110011001100110011001100110011, 0}};
    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 7000000000000000000000000.2 + 0.10000000000000000000000001 ( 1 и 26
    // степени)
    // 7000000000000000000000000.3
    // 70 000 000 000 000 000 000 000 003
    // 70 000 000 000 000 000 000 000 003 000
    s21_decimal value_1 = {
        {0b00000110000000000000000000000010, 0b10011010100011000000100011111010,
         0b1110011110011100010011, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b01001010000000000000000000000001, 0b00010110000101000000000101001000,
         0b10000100010110010101, 0b00000000000110100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000101110111000,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000001000000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 7000000000000000000000000000.6 + 0.90000000000000000000000001 ( 1 и
    // 26 степени) 7000000000000000000000000001.5
    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b00000000000110100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000000000001111,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 7000000000000000000000000000.6 + 0.090000000000000000000000001
    // ( 1 и 27 степени)

    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b00000000000110110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000000000000111,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }

  {
    // 7000000000000000000000000.2 + (-0.10000000000000000000000001 )( 1 и
    // 26 степени)
    s21_decimal value_1 = {
        {0b00000110000000000000000000000010, 0b10011010100011000000100011111010,
         0b1110011110011100010011, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b01001010000000000000000000000001, 0b00010110000101000000000101001000,
         0b10000100010110010101, 0b10000000000110100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000001111101000,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000001000000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 7000000000000000000000000000.6 + (-0.090000000000000000000000001) ( 1
    // и 27 степени) второе нормализуется  в -0.1  => результат как в
    // предыдущем тесте. 7000000000000000000000000.1
    // 6999999999999999999999999999.7 70 000 000 000 000 000 000 000 003 70
    // 000 000 000 000 000 000 000 003 000
    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b10000000000110110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000000000000101,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 7000000000000000000000000000.6 + (-0.90000000000000000000000001 ) ( 1
    // и 26 степени) 7000000000000000000000000000.7 70 000 000 000 000 000
    // 000 000 003 70 000 000 000 000 000 000 000 003 000
    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b10000000000110100000000000000000}};

    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01101111111111111111111111111101,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    // s21_print_decimal(result);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
}
END_TEST

Suite *suite_s21_add() {
  Suite *s = suite_create("add");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, test_add);
  suite_add_tcase(s, tc);
  return s;
}
