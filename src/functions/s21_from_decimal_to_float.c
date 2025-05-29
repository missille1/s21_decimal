#include "../s21_decimal.h"

/**
 * @brief Конвертирует из типа decimal в float
 *
 * @param src число типа decimal на входе
 * @param dst указатель на результат конвертации типа float
 *
 * @return 0 - OK, 1 - ERROR
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = OK;

  if (dst != NULL && s21_is_correct_value(src)) {
    *dst = 0.0f;
    double temp = 0.0;
    for (int i = 0; i < SIZE_96; i++) temp += s21_get_bit(src, i) * pow(2, i);
    temp = temp * pow(10, -s21_get_scale(src));
    if (s21_get_sign(src)) temp = -temp;
    *dst = (float)temp;
  } else {
    res = ERROR;
  }
  return res;
}
