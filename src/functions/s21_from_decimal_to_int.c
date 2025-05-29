#include "../s21_decimal.h"

/**
 * @brief Конвертирует из типа decimal в int
 *
 * @param src число типа decimal на входе
 * @param dst указатель на результат конвертации типа int
 *
 * @return 0 - OK 1 - ERROR
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = OK;

  if (dst && !src.bits[1] && !src.bits[2]) {
    if (s21_get_sign(src) == 1)
      *dst = -1 * (int)(src.bits[0] / pow(10, s21_get_scale(src)));
    else
      *dst = (int)(src.bits[0] / pow(10, s21_get_scale(src)));
  } else
    res = ERROR;

  return res;
}