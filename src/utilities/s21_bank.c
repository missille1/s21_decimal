#include "../s21_decimal.h"

/**
 * @brief Функция для банковского округления
 *
 * @param value указатель на число типа decimal
 */
s21_decimal s21_bank(s21_decimal value, s21_decimal remainder) {
  s21_decimal result = {{DEC_ZERO}};
  s21_decimal divider = {{10, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal temp_remainder = {{DEC_ZERO}};
  s21_decimal temp_res = {{DEC_ZERO}};
  int is_odd;
  result = s21_copy_decimal(value);
  is_odd = s21_get_bit(value, 0);
  // нужно проверить число или цифра в ремаиндере
  if (remainder.HIGH > 0 || remainder.MEDIUM > 0 || remainder.LOW > 10) {
    // тут нужно искать старший разряд ремаиндера
    // делить на 10 пока возможно
    temp_remainder = s21_copy_decimal(remainder);
    while (s21_is_greater(remainder, divider)) {
      s21_div_with_r(remainder, divider, &temp_res, &temp_remainder);
      remainder = s21_copy_decimal(temp_res);
      s21_set_to_zero(&temp_res);
    }
  }
  if ((remainder.LOW == 5 && is_odd) || remainder.LOW > 5) {
    s21_add(result, one, &result);
  }

  return result;
}
