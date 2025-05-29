#include "../s21_decimal.h"

/**
 * @brief Округляет указанное Decimal число до ближайшего целого числа в сторону
 * отрицательной бесконечности.
 *
 * @param value число типа decimal на входе,
 * @param result указатель на число типа decimal
 *
 * @return 0 - OK 1 - ERROR
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = OK;
  int pow = s21_get_scale(value);
  if (result != NULL && s21_is_correct_value(value) && pow <= 28) {
    unsigned int sign = s21_get_sign(value);
    s21_decimal ONE = {{1, 0, 0, 0}};

    s21_set_to_zero(result);

    if (sign == 1) s21_negate(value, &value);

    s21_truncate(value, result);

    if (sign == 1) s21_add(*result, ONE, result);

    s21_set_scale(result, 0);

    if (sign == 1) s21_negate(*result, result);
  } else
    res = ERROR;
  return res;
}