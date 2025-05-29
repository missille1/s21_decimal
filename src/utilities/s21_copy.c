#include "../s21_decimal.h"

/**
 * @brief  Функция для копирования числа типа decimal
 *
 * @param value число типа decimal
 * @return скопированное число типа decmal (структуру s21_decimal)
 */
s21_decimal s21_copy_decimal(s21_decimal value) {
  s21_decimal for_copy = {{DEC_ZERO}};
  for (int i = 0; i <= BITS; i++) for_copy.bits[i] = value.bits[i];
  return for_copy;
}