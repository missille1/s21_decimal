#include "../s21_decimal.h"

/**
 * @brief Функция для сравнения чисел типа decimal ( val_1 <= val_2)
 *
 * @param value_1 число типа decimal
 * @param value_2 число типа decimal
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) || s21_is_less(value_1, value_2);
}
