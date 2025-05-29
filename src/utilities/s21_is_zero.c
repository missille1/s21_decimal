#include "../s21_decimal.h"

/**
 * @brief  Функция проверки числа типа decimal на равенство 0
 *
 * @param value число типа decimal
 * @return 0 - error_status, 1 - ok
 */
bool s21_is_zero(s21_decimal value) {
  int res = VALUE_OK;
  for (int i = 0; i < BITS && res; i++)
    if (value.bits[i] != 0) res = VALUE_ERROR;
  return res;
}

/**
 * @brief  Функция для обнуления числа типа decimal
 *
 * @param *value указатель на  число типа decimal
 */
void s21_set_to_zero(s21_decimal* value) {
  for (int i = 0; i <= BITS; i++) value->bits[i] = 0;
}