#include "../s21_decimal.h"

/**
 * @brief Функция для поиска степени 2, в которую нужно будет возвести
 * делитель, что бы пройти одну иттерацию деления.
 *
 * @param value число типа decimal (делимое)
 * @param *divider указатель на число типа decimal (делитель)
 * @param *error_state указатель на int (статус ошибки)
 *
 * @return pow_two (степень 2)
 */
int find_shift(s21_decimal number, s21_decimal* divider, int* error_status) {
  // сдвиг будет равен степени 2ки, т.е. количеству умножений делителя на 2
  int pow_two = 0;
  *error_status = VALUE_OK;
  while (s21_is_greater_or_equal(number, *divider) && *error_status) {
    if (pow_two != 0) {
      *error_status = s21_shift_to_left(divider, 1);
      // сдвигаю делитель на 0, 1 , 2 и т.п. ( 2^0, 2^1 и т.п.)
    }
    pow_two++;
  }
  pow_two -= 2;
  // (- 1 т.к. в первой иттерации цикла не делаю сдвиг, -2 т.к.
  // увеличиваю счетчик, после сдвига)
  return pow_two;
}

/**
 * @brief Функция деления с остатком. РЕЗУЛЬТАТ - УКАЗАТЕЛЬ !!!!
 *
 * @param value_1 число типа decimal (делимое)
 * @param value_2 число типа decimal (делитель)
 * @param *result указатель на число типа decimal (целая часть деления)
 * @param *remainder указатель на число типа decimal (остаток)
 *
 * @return error_status (статус ошибки)
 * @note если невозможно умножить делимое на 10, что бы оно стало больше
 * делителя, то это ошибка.
 */
int s21_div_with_r(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result, s21_decimal* remainder) {
  if (s21_is_zero(value_2)) {
    return DIV_ZERO;
  }
  s21_decimal divider = {{0, 0, 0, 0}};  // делитель
  s21_decimal temp_result = {{DEC_ZERO}};
  int error_status = OK;
  int shift = 0;
  int shift_err = VALUE_OK;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  *remainder = s21_copy_decimal(value_1);
  divider = s21_copy_decimal(value_2);
  remainder->SIGN_POW = 0;  // нужно занулить, что бы попасть в цикл
  divider.SIGN_POW = 0;  // нужно занулить, для верного сравнения

  while (s21_is_greater_or_equal(*remainder, divider)) {
    shift = find_shift(*remainder, &divider, &shift_err);
    s21_set_bit(&temp_result, shift, 1);
    // если ОК , то сдвигаем делитель на 1 бит вправо (т.к. в поиске сдвига
    // было 1 лишнее смещение)
    if (shift_err) s21_shift_to_right(&divider, 1);
    s21_sub(*remainder, divider, remainder);
    // добавляю в резалт промежуточное число
    s21_add(*result, temp_result, result);

    // возвращаю temp_result и divider в исходные положения
    s21_set_bit(&temp_result, shift, 0);

    divider = s21_copy_decimal(value_2);
    divider.SIGN_POW = 0;
  }
  if (sign_1 != sign_2) s21_set_sign(result, 1);
  return error_status;
}

/**
 * @brief Функция деления. Выполняется до тех пор пока либо остаток не
 * равен 0, либо не забьется мантиса частного.
 *
 * @param value_1 число типа decimal (делимое)
 * @param value_2 число типа decimal (делитель)
 * @param *result указатель на число типа decimal (целая часть деления)
 *
 * @return error_status (статус ошибки)
 * @note РЕЗУЛЬТАТ - УКАЗАТЕЛЬ !!!!!
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (s21_is_zero(value_2)) return DIV_ZERO;

  int pow_1 = 0, pow_2 = 0, sign_1 = 0, sign_2 = 0, result_pow = 0,
      error_status = OK;
  s21_decimal remainder = {{DEC_ZERO}}, buff = {{DEC_ZERO}};
  s21_set_to_zero(result);  // на случай если в result, уже что-то есть

  pow_1 = s21_get_scale(value_1);
  pow_2 = s21_get_scale(value_2);

  if (s21_is_greater(value_2, value_1))
    if (!s21_can_shift(value_2, 1)) s21_normalization_down(&value_2, --pow_2);
  sign_1 = s21_get_sign(value_1);
  sign_2 = s21_get_sign(value_2);
  value_1.SIGN_POW = 0;
  value_2.SIGN_POW = 0;

  result_pow = pow_1 - pow_2;
  s21_div_with_r(value_1, value_2, result, &remainder);
  buff = s21_copy_decimal(*result);
  while (!s21_is_zero(remainder) && s21_mul_to_10(&buff)) {
    s21_mul_to_10(result);
    int can_mul_remainder = 1;
    can_mul_remainder = s21_mul_to_10(&remainder);
    if (!can_mul_remainder) s21_normalization_down(&value_2, --pow_2);
    result_pow++;
    buff = s21_copy_decimal(*result);
    s21_div_with_r(remainder, value_2, result, &remainder);
  }
  if (result_pow >= 0 && result_pow <= MAX_POW) {
    if (!s21_is_zero(remainder)) {
      *result = s21_bank(*result, remainder);
    }
    s21_set_scale(result, result_pow);
  } else if (result_pow < 0) {
    while (result_pow < 0 && error_status == OK) {
      if (s21_mul_to_10(result))
        result_pow++;
      else {
        error_status = sign_1 == sign_2 ? TOO_BIG : TOO_SMALL;
        s21_set_to_zero(result);
      }
    }
  } else if (result_pow <= MAX_POW * 2) {
    s21_set_scale(result, result_pow);
    s21_normalization_down(result, 28);
    if (s21_is_zero(*result)) {
      error_status = TOO_SMALL;
      result->SIGN_POW = 0;
    }
  } else
    error_status = TOO_SMALL;
  if (error_status == OK)
    if (sign_1 != sign_2) s21_set_sign(result, 1);

  return error_status;
}
