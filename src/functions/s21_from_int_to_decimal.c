#include "../s21_decimal.h"

/**
 * @brief Конвертирует из типа int в decimal
 *
 * @param src число типа int на входе
 * @param dst указатель на результат конвертации типа decimal
 *
 * @return 0 - OK 1 - ERROR
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = OK;
  if (dst != NULL) {
    s21_set_to_zero(dst);
    if (src < 0) {
      s21_set_sign(dst, 1);
      src = -src;
    }
    dst->bits[0] = src;
  } else
    res = ERROR;
  return res;
}
