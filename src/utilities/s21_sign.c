#include "../s21_decimal.h"
/**
 * @brief  Функция для получения знака
 *
 * @param value число типа decimal
 * @return 0 либо 1 ( 0 - положительное число, 1 - отрицательное )
 */
int s21_get_sign(s21_decimal value) { return value.bits[3] >> 31 & MASK_ONE; }

// 0 - положительное,
// 1 - отрицательное.

/**
 * @brief  Функция для установки знака числу
 *
 * @param *value указатель на число типа decimal
 * @param sign_value 0 либо 1 - какой знак присвоить числу (1 - минус)
 */
void s21_set_sign(s21_decimal *value, int sign_value) {
  if (sign_value != s21_get_sign(*value)) {
    s21_negate(*value, value);
  }
}
