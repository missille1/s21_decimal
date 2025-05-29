#include "../s21_decimal.h"

/**
 * @brief Функция для сравнения чисел типа decimal ( val_1 < val_2)
 *
 * @param value_1 число типа decimal
 * @param value_2 число типа decimal
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = VALUE_ERROR;

  // get signs of values
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  // if value_1 - negative and value_2 - positive
  if (sign_1 == 1 && sign_2 == 0) result = VALUE_OK;

  // if signs are equal
  else if (sign_1 == sign_2) {
    int flag = 1;
    s21_normalization(&value_1, &value_2);
    // сравниваем значения пока первое не превышает второе
    for (int i = 2; i >= 0 && flag; i--) {
      if (value_1.bits[i] < value_2.bits[i]) {
        result = VALUE_OK;
        flag = 0;
      } else if (value_1.bits[i] > value_2.bits[i])
        flag = 0;
    }
    if (sign_1 && !flag) result = result ^ 1;
  }

  return result;
}