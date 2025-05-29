#include "tests.h"

// одинаковые числа
START_TEST(test_more) {
  {
    // числа одинаковые, степень второго больше
    s21_decimal value_1 = {{3211110, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal value_2 = {{3211110, 0, 0, 0b00000000001111000000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // числа разные, после нормализации 2е округляется
    s21_decimal value_1 = {{981, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal value_2 = {{9803, 0, 0, 0b00000000000111010000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // разные числа одна степень
    s21_decimal value_1 = {{4413499, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {{448022, 0, 0, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // разные числа одна степень, отрицателные
    s21_decimal value_1 = {{4413499, 0, 0, 0b10000000000000010000000000000000}};
    s21_decimal value_2 = {{448022, 0, 0, 0b10000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, разная степень
    s21_decimal value_1 = {{0, 1, 0, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {{0, 1, 0, 0b00000000000001010000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // одинаковые числа с разными знаками
    s21_decimal value_1 = {{4597, 3453, 34415, 0}};
    s21_decimal value_2 = {{4597, 3453, 34415, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // одинаковые числа и степени и знаки
    s21_decimal value_1 = {{4597, 3453, 34415, MASK_MINUS}};
    s21_decimal value_2 = {{4597, 3453, 34415, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // числа разные, знаки тоже
    s21_decimal value_1 = {{4597, 3453, 34415, 0}};
    s21_decimal value_2 = {{44597, 123453, 23434415, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // разные числа и знаки
    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{DEC_MIN}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // все разное
    s21_decimal value_1 = {{DEC_ZERO}};
    s21_decimal value_2 = {{DEC_MIN}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // все разное
    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // 0.0000000000000000000000000001 и 0
    s21_decimal value_1 = {{1, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal value_2 = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }
  {
    // 0 и -0.0000000000000000000000000001
    s21_decimal value_1 = {{DEC_ZERO}};
    s21_decimal value_2 = {{1, 0, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }

  // is_less - возвращает FALSE
  {
    // разные мантисы, одинаковые знаки и степени
    s21_decimal value_1 = {{448, 919, 11, 0b10000000000001101000000000000000}};
    s21_decimal value_2 = {{448, 919, 21, 0b10000000000001101000000000000000}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая, оба отрицатеьные
    s21_decimal value_1 = {{23, 1, 875640, MASK_MINUS}};
    s21_decimal value_2 = {{23, 1, 875640, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа разные, но после нормализации 2е округляется, 30я степень
    s21_decimal value_1 = {{180, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal value_2 = {{18041, 0, 0, 0b00000000000111100000000000000000}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа одинаковые но записаны по разному => они равны и FALSE
    s21_decimal value_1 = {{78, 0, 0, 0}};
    s21_decimal value_2 = {
        {780000000, 0, 0, 0b00000000000001110000000000000000}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа одинаковые но записаны по разному
    s21_decimal value_1 = {{0, 2000, 0, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {{0, 200, 0, 0b00000000000000100000000000000000}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{DEC_MAX}};
    s21_decimal value_2 = {{DEC_MAX}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{DEC_ZERO}};
    s21_decimal value_2 = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {{875, 41215, 12, MASK_MINUS}};
    s21_decimal value_2 = {{875, 41215, 12, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // числа одинаковые, степень одинаковая
    s21_decimal value_1 = {
        {65211, 90, 1313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {
        {65211, 90, 1313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
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
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // нули с разными знаками
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{0, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // нули с разными степенями
    s21_decimal value_1 = {{0, 0, 0, 0b00000000000011110000000000000000}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, одинаковые знаки, разный показатель степени
    s21_decimal value_1 = {{41, 2235, 318, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {{41, 2235, 318, 0b00000000000000100000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // разные мантисы, разные знаки, одинаковый показатель степени
    s21_decimal value_1 = {
        {4000, 123, 877, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {
        {4000, 123, 8747, 0b00000000000000110000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, оба отрицательные, разные показатели степени
    s21_decimal value_1 = {
        {324000, 11123, 6877, 0b10000000000000110000000000000000}};
    s21_decimal value_2 = {
        {324000, 11123, 6877, 0b10000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // разное все 1е отрицатеьлное 2е положительное
    s21_decimal value_1 = {{30, 1113, 677, 0b10000000000000110000000000000000}};
    s21_decimal value_2 = {
        {24000, 11123, 877, 0b00000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal value_1 = {{0, 10000, 0, 0b00000000000001110000000000000000}};
    s21_decimal value_2 = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal value_1 = {{91848, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{183, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal value_1 = {{11, 981, 313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {
        {211, 23000, 13, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, одинаковые степени, оба отрицательные
    s21_decimal value_1 = {
        {872112, 1, 3313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {{60211, 0, 313, 0b00000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, разные знаки
    s21_decimal value_1 = {{3111110, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{3111110, 0, 0, 0}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы, разный показатель степени
    s21_decimal value_1 = {{6663200, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {{6663200, 0, 0, 0}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal value_1 = {{0, 1000, 0, 0b00000000000001110000000000000000}};
    s21_decimal value_2 = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 0);
  }
  {
    // числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal value_1 = {{211, 10, 313, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {{211, 21, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_greater(value_1, value_2)), 1);
  }

  {
    // одинаковые мантисы, разные знаки, одна степень
    s21_decimal value_1 = {{0, 919, 0, 0}};
    s21_decimal value_2 = {{0, 919, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less(value_2, value_1)), 1);
  }
  {
    // одинаковые мантисы, разный показатель степени
    s21_decimal value_1 = {{4, 22, 518, 0}};
    s21_decimal value_2 = {{4, 22, 518, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_less(value_2, value_1)), 1);
  }
  {
    // разные мантисы (можно нормализовать), разный показатель степени
    s21_decimal value_1 = {{0, 1000, 0, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {{0, 2, 0, 0}};
    ck_assert_int_eq((s21_is_less(value_2, value_1)), 1);
  }

  {
    // числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal value_1 = {{1815, 0, 2, MASK_MINUS}};
    s21_decimal value_2 = {{183, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less(value_2, value_1)), 0);
  }
  {
    // числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal value_1 = {
        {21811, 0, 3131, 0b10000000000101000000000000000000}};
    s21_decimal value_2 = {
        {21811, 11, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less(value_2, value_1)), 0);
  }
  {
    // числа с разными мантисами, и степенями, оба отрицаьельные
    s21_decimal value_1 = {{2112, 1, 313, 0b10000000000011000000000000000000}};
    s21_decimal value_2 = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less(value_1, value_2)), 1);
  }
  {
    // нули с разными знаками
    s21_decimal value_1 = {{0, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{0, 0, 0, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less(value_2, value_1)), 0);
  }
  {
    // мелкое число и 0
    s21_decimal value_1 = {{1, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal value_2 = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_less(value_2, value_1)), 1);
  }
}
END_TEST

Suite *suite_s21_is_greater_less() {
  Suite *s = suite_create("is_equal");
  TCase *tc = tcase_create("is_equal_tc");

  tcase_add_test(tc, test_more);
  suite_add_tcase(s, tc);
  return s;
}
