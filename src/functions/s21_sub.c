#include "../s21_decimal.h"

// дополнительная функция в которой непосредственно происходит вычитание.
// возвращает число децимал !
s21_decimal s21_submition(s21_decimal value_1, s21_decimal value_2) {
  int first_bit, second_bit;
  int bit_index = 0, k = 0;
  s21_decimal result = {{0, 0, 0, 0}};
  while (bit_index < SIZE_96) {
    first_bit = s21_get_bit(value_1, bit_index);
    second_bit = s21_get_bit(value_2, bit_index);

    if (first_bit > second_bit)
      s21_set_bit(&result, bit_index, 1);
    else if (first_bit == second_bit)
      s21_set_bit(&result, bit_index, 0);

    else {
      s21_set_bit(&result, bit_index, 1);
      k = bit_index + 1;
      while (s21_get_bit(value_1, k) != 1) {
        s21_set_bit(&value_1, k, 1);
        k++;
      }
      s21_set_bit(&value_1, k, 0);
    }

    bit_index++;
  }
  return result;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // степень после нормализации
  int scale = 0;
  // 1. сравниваем знаки
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  // 0 - положительное 1 - отрицательное
  // если знаки различны, то результатом будет сложение
  if (sign_1 != sign_2) {
    if (!sign_1 && sign_2) {
      // делаю второе положительным, выполняю сложение
      // +  |  -   |   a - (-b) =>  a + b
      s21_set_sign(&value_2, 0);
      s21_add(value_1, value_2, result);
    } else {
      // -   |  +  |   - a - b  =>  - (a + b)
      // делаю первое положительным, выполняю сложение, результат делаю
      // отрицательным
      s21_set_sign(&value_1, 0);
      s21_add(value_1, value_2, result);
      s21_set_sign(result, 1);
    }
  }
  // знаки одинаковые
  else {
    // и если степени различны, то нужно сделать нормализацию
    scale = s21_normalization(&value_1, &value_2);
    // +  |  +  |   a - b
    if (!sign_1 && s21_is_greater_or_equal(value_1, value_2)) {
      // первое положительное и ≥ второго
      *result = s21_submition(value_1, value_2);
    } else if (!sign_1 && s21_is_less(value_1, value_2)) {
      // первое положительное и < второго => из второго вычитаю первое, и
      // знак "-" результату
      *result = s21_submition(value_2, value_1);
      s21_set_sign(result, 1);
    }
    // if (sign_1 && sign_2)
    else {
      // -   |  -   |   - a - (-b)  =>  - a + b => b - a
      s21_set_sign(&value_1, 0);
      s21_set_sign(&value_2, 0);
      if (s21_is_less_or_equal(value_1, value_2)) {
        *result = s21_submition(value_2, value_1);
      } else {
        *result = s21_submition(value_1, value_2);
      }
      s21_set_sign(result, 1);
    }
    // устанавливаю результату порядок
    s21_set_scale(result, scale);
  }

  return OK;
}
