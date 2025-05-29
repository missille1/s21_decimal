#include "tests.h"

// одинаковые числа
START_TEST(test_is_equal) {
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{320, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{320, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа разные, но после нормализации 2е округляется
    s21_decimal value_1 = {{320, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal value_2 = {{3204, 0, 0, 0b00000000000111010000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа одинаковые но записаны по разному
    s21_decimal value_1 = {{320, 0, 0, 0}};
    s21_decimal value_2 = {{3200, 0, 0, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа одинаковые но записаны по разному
    s21_decimal value_1 = {{0, 1000, 0, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{DEC_MAX}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{DEC_ZERO}};
    s21_decimal value_2 = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{0, 0, 1, MASK_MINUS}};
    s21_decimal value_2 = {{0, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // числа одинаковые но записаны по разному
    // 1733237036125865400000000 ^ -8
    s21_decimal value_1 = {{0b10000111000100101101111000000000,
                            0b11110111110011101101100100010110,
                            0b00000000000000010110111100000110,
                            0b00000000000010000000000000000000}};
    s21_decimal value_2 = {{0b11110010011111111001001010011110,
                            0b00000000001111011001001110110010, 0,
                            0b00000000000000000000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // нули с разными знаками
    s21_decimal value_1 = {{0, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }
  {
    // нули с разными степенями
    s21_decimal value_1 = {{0, 0, 0, 0b00000000000001110000000000000000}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 1);
  }

  // is_not_equal - возвращает FALSE
  {
    // одинаковые мантисы, одинаковые знаки и степени
    s21_decimal value_1 = {{448, 919, 1, 0b10000000000001101000000000000000}};
    s21_decimal value_2 = {{448, 919, 1, 0b10000000000001101000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{23, 1, 875640, MASK_MINUS}};
    s21_decimal value_2 = {{23, 1, 875640, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа разные, но после нормализации 2е округляется
    s21_decimal value_1 = {{180, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal value_2 = {{18041, 0, 0, 0b00000000000111100000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые но записаны по разному
    s21_decimal value_1 = {{58, 0, 0, 0}};
    s21_decimal value_2 = {
        {580000000, 0, 0, 0b00000000000001110000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые но записаны по разному
    s21_decimal value_1 = {{0, 1000, 0, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {{0, 100, 0, 0b00000000000000100000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{DEC_MAX}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{DEC_ZERO}};
    s21_decimal value_2 = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{0, 1215, 1, MASK_MINUS}};
    s21_decimal value_2 = {{0, 1215, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // числа одинаковые но записаны по разному
    // 1733237036125865400000000 ^ -8
    s21_decimal value_1 = {{0b10000111000100101101111000000000,
                            0b11110111110011101101100100010110,
                            0b00000000000000010110111100000110,
                            0b00000000000010000000000000000000}};
    s21_decimal value_2 = {{0b11110010011111111001001010011110,
                            0b00000000001111011001001110110010, 0,
                            0b00000000000000000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // нули с разными знаками
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{0, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
  {
    // нули с разными степенями
    s21_decimal value_1 = {{0, 0, 0, 0b00000000000010110000000000000000}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 0);
  }
}
END_TEST
// числа не равны
START_TEST(test_not_equal) {
  // is_equal возвращает ошибку
  {
    // одинаковые мантисы, одинаковые знаки, разный показатель степени
    s21_decimal value_1 = {{4, 223, 18, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {{4, 223, 18, 0b00000000000000110000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, разные знаки, одинаковый показатель степени
    s21_decimal value_1 = {
        {4000, 123, 877, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {
        {4000, 123, 877, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, разные знаки, разные показатели степени
    s21_decimal value_1 = {
        {324000, 11123, 6877, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {
        {324000, 11123, 6877, 0b10000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // разное все
    s21_decimal value_1 = {{30, 1113, 677, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {
        {24000, 11123, 877, 0b10000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal value_1 = {{0, 10000, 0, 0b00000000000001110000000000000000}};
    s21_decimal value_2 = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, степень одинаковая
    s21_decimal value_1 = {{91848, 0, 1, MASK_MINUS}};
    s21_decimal value_2 = {{183, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, степень одинаковая
    s21_decimal value_1 = {{11, 981, 313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, и степенями
    s21_decimal value_1 = {{872112, 1, 13, 0b10000000000111000000000000000000}};
    s21_decimal value_2 = {{60211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, разные знаки
    s21_decimal value_1 = {{320, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{320, 0, 0, 0}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, разный показатель степени
    s21_decimal value_1 = {{3200, 0, 0, 0}};
    s21_decimal value_2 = {{3200, 0, 0, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal value_1 = {{0, 1000, 0, 0b00000000000001110000000000000000}};
    s21_decimal value_2 = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }

  {
    // числа с разными мантисами, степень одинаковая
    s21_decimal value_1 = {{313, 0, 1, MASK_MINUS}};
    s21_decimal value_2 = {{0, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, степень одинаковая
    s21_decimal value_1 = {{211, 1, 313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(value_1, value_2)), 0);
  }

  // is_not_equal - возвращает ОК
  {
    // одинаковые мантисы, разные знаки
    s21_decimal value_1 = {{0, 919, 0, MASK_MINUS}};
    s21_decimal value_2 = {{0, 919, 0, 0}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 1);
  }
  {
    // одинаковые мантисы, разный показатель степени
    s21_decimal value_1 = {{4, 22, 518, 0}};
    s21_decimal value_2 = {{4, 22, 518, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 1);
  }
  {
    // одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal value_1 = {{0, 1000, 0, 0b00000000000001110000000000000000}};
    s21_decimal value_2 = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 1);
  }

  {
    // числа с разными мантисами, степень одинаковая
    s21_decimal value_1 = {{184, 0, 1, MASK_MINUS}};
    s21_decimal value_2 = {{183, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 1);
  }
  {
    // числа с разными мантисами, степень одинаковая
    s21_decimal value_1 = {{211, 1, 313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 1);
  }
  {
    // числа с разными мантисами, и степенями
    s21_decimal value_1 = {{2112, 1, 313, 0b10000000000111000000000000000000}};
    s21_decimal value_2 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 1);
  }
  {
    // числа с одинаковыми мантисами, и степенями, но разными знаками
    s21_decimal value_1 = {{22, 0, 313, 0b00000000000101000000000000000000}};
    s21_decimal value_2 = {{22, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(value_1, value_2)), 1);
  }
}
END_TEST

Suite *suite_s21_is_equal() {
  Suite *s = suite_create("is_equal");
  TCase *tc = tcase_create("is_equal_tc");

  tcase_add_test(tc, test_is_equal);
  tcase_add_test(tc, test_not_equal);
  suite_add_tcase(s, tc);
  return s;
}
