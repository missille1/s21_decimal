#include "../s21_decimal.h"

int s21_find_round_digit(s21_decimal value, int pow) {
  s21_decimal TEN = {{10, 0, 0, 0}};
  s21_decimal temp_r = s21_copy_decimal(value);
  s21_decimal remainder = {{DEC_ZERO}};
  s21_decimal result = {{DEC_ZERO}};
  s21_set_sign(&temp_r, 0);
  while (pow-- > 0) {
    s21_div_with_r(temp_r, TEN, &result, &remainder);
    temp_r = s21_copy_decimal(result);
    s21_set_to_zero(&result);
  }
  return remainder.LOW;
}