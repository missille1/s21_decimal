#include "../s21_decimal.h"

int bit_to_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal* buff) {
  int sum = 0;
  int remain = 0;
  // vars for bits of numbers
  int bit_1 = 0, bit_2 = 0;

  // run for each bit of numbers
  for (int bit = 0; bit < SIZE_96; bit++) {
    // get bits of numbers
    bit_1 = s21_get_bit(value_1, bit);
    bit_2 = s21_get_bit(value_2, bit);

    sum = bit_1 + bit_2;

    if (sum > 1) {
      s21_set_bit(buff, bit, remain);
      remain = 1;
    } else if (sum == 1) {
      s21_set_bit(buff, bit, !remain);
    } else {
      s21_set_bit(buff, bit, remain);
      remain = 0;
    }
  }
  return remain;
}

/**
 * @brief Функция для сложения округленных чисел типа decimal
 *
 * @param value_1 число типа decimal
 * @param value_2 число типа decimal
 * @param *result указатель на число типа decimal
 */
void add_round_numbers(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal* result) {
  s21_decimal remainder_1 = {{DEC_ZERO}};
  s21_decimal remainder_2 = {{DEC_ZERO}};
  s21_decimal res_1 = {{DEC_ZERO}};
  s21_decimal res_2 = {{DEC_ZERO}};
  s21_decimal divider = {{10, 0, 0, 0}};
  s21_decimal res = {{DEC_ZERO}};
  s21_decimal one = {{1, 0, 0, 0}};
  int remainder = 0;
  int is_even = 0;  // 0 = четное
  s21_div_with_r(value_1, divider, &res_1, &remainder_1);
  s21_div_with_r(value_2, divider, &res_2, &remainder_2);
  remainder = remainder_1.LOW + remainder_2.LOW;
  bit_to_bit(res_1, res_2, &res);
  if (remainder > 10) {
    bit_to_bit(res, one, &res);
    remainder /= 10;
  }
  is_even = s21_get_bit(*result, 0);
  if ((remainder == 5 && !is_even) || remainder > 5) {
    bit_to_bit(res, one, &res);
  }
  *result = s21_copy_decimal(res);
}

/**
 * @brief Функция для сложения чисел типа decimal
 *
 * @param value_1 число типа decimal
 * @param value_2 число типа decimal
 * @param *result указатель на число типа decimal
 * @return 0 - OK, 1 - TOO_BIG, 2 - TOO_SMALL
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int res = OK;
  s21_decimal buff = {{DEC_ZERO}};
  int scale = 0;

  scale = s21_normalization(&value_1, &value_2);

  // get signs of numbers
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  // if signs is equal
  if (sign_1 == sign_2) {
    // переменная для остатка и суммы битов
    int remain = 0;
    remain = bit_to_bit(value_1, value_2, &buff);
    if (remain) {
      if (scale > 0) {
        add_round_numbers(value_1, value_2, &buff);
        scale--;
      } else
        res = (sign_1) ? TOO_SMALL : TOO_BIG;
    }

    if (sign_1) s21_set_sign(&buff, 1);
    s21_set_scale(&buff, scale);
  }
  // if signs isn`t equal, call sub function
  else {
    s21_decimal copy = {{0, 0, 0, 0}};
    if (sign_1) {
      s21_negate(value_1, &copy);
      res = s21_sub(value_2, copy, &buff);
    } else {
      s21_negate(value_2, &copy);
      res = s21_sub(value_1, copy, &buff);
    }
  }

  if (!res) *result = s21_copy_decimal(buff);

  return res;
}
