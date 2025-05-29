#include "../s21_decimal.h"

/**
 * @brief Округляет указанное Decimal число до ближайшего целого числа.
 *
 * @param value число типа decimal на входе
 * @param result указатель на число типа decimal
 *
 * @return 0 - OK 1 - ERROR
 */
int s21_round(s21_decimal value, s21_decimal *result) {
  int res = OK;
  int pow = s21_get_scale(value);
  if (result != NULL && s21_is_correct_value(value) && pow <= 28) {
    s21_set_to_zero(result);
    int sign = s21_get_sign(value), exp = s21_get_scale(value);
    s21_decimal digit_for_compare = {0}, temp_result = {0},
                ONE = {{1, 0, 0, 0}};
    // Пишет в резалт обрезанное валуе (12.1 -> 12)
    s21_truncate(value, result);
    // Обнуление знаков
    s21_set_sign(result, 0);
    s21_set_sign(&value, 0);

    // Создаем временную ТМП2 (12)
    temp_result = s21_copy_decimal(*result);

    s21_normalization_up(&temp_result, exp);

    // оно пишется в конечную хрень, но еще не все
    s21_sub(value, temp_result, &digit_for_compare);

    int r = s21_find_round_digit(value, exp);

    // тут все кончилось
    if (r >= 5) s21_add(*result, ONE, result);
    s21_set_sign(result, sign);
  } else
    res = ERROR;
  return res;
}