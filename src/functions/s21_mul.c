#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;
  s21_decimal buff = {{DEC_ZERO}};
  bool negative = 0;
  bool positive = 0;

  if (!result)
    res = ERROR;
  else {
    s21_normalization(&value_1, &value_2);
    // get signs of numbers
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);

    if (sign_1 || sign_2) {
      if (sign_1 == sign_2)
        positive = 1;
      else
        negative = 1;
    }

    // if (sign_1 == sign_2 && sign_1) positive == 1;
    // else if ((sign_1 || sign_2) && sign_1 != sign_2) negative = 1;

    int bit_1 = 0, shift = 0;

    for (int bit = 0; bit < SIZE_96 && !res; bit++) {
      // get bits of numbers
      bit_1 = s21_get_bit(value_1, bit);
      if (bit_1) {
        if (s21_shift_to_left(&value_2, bit - shift)) {
          s21_add(buff, value_2, &buff);
          shift = bit;
        } else
          res = negative ? TOO_SMALL : TOO_BIG;
      }
    }
  }

  if (!res) {
    *result = s21_copy_decimal(buff);
    if (negative)
      s21_set_sign(result, 1);
    else if (positive)
      s21_set_sign(result, 0);
  }

  return res;
}