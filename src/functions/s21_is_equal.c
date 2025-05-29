#include "../s21_decimal.h"

/**
 * @brief Функция для сравнения чисел типа decimal
 *
 * @param value_1 число типа decimal
 * @param value_2 число типа decimal
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = VALUE_OK;

  if (!(s21_is_zero(value_1) && s21_is_zero(value_2))) {
    // get signs of values
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);

    // if signs are equal
    if (sign_1 == sign_2) {
      s21_normalization(&value_1, &value_2);  // ТУТ добавил

      // сравниваем значения пока не будет различий или конца массива
      for (int i = 0; i < 3 && result; i++)
        if (value_1.bits[i] != value_2.bits[i]) result = VALUE_ERROR;
    }
    // if signs aren`t equal
    else
      result = VALUE_ERROR;
  }

  return result;
}
