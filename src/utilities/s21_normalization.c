#include "../s21_decimal.h"

/**
 * @brief Функция для умножеия числа на 10 (только число мантисы)
 *
 * @param *value указатель на число типа decimal
 * @return 0 - error_status, 1 - OK
 */
int s21_mul_to_10(s21_decimal* value) {
  // x* 10 = x * 8 + x* 2== x << 3 + x << 1;
  // добавил проверку на то можно ли умножать число на 10, не приведет ли это
  // к переполнению, нужно еще проверять, не приведет ли к переполнению
  // сложение

  int error_status = VALUE_OK;
  int can_add = 1;
  s21_decimal shift_eight = {{DEC_ZERO}};
  s21_decimal shift_two = {{DEC_ZERO}};
  s21_decimal buff = {{DEC_ZERO}};

  shift_two = s21_copy_decimal(*value);
  shift_eight = s21_copy_decimal(*value);
  if (s21_can_shift(*value, 3)) {
    s21_shift_to_left(&shift_eight, 3);
    s21_shift_to_left(&shift_two, 1);
  } else
    error_status = VALUE_ERROR;
  if (error_status) can_add = s21_add(shift_eight, shift_two, &buff);
  // если can_add либо 1 либо 2 (TOO_BIG, TOO_SMALL - это ошибка)
  if (can_add) {
    error_status = VALUE_ERROR;

  }
  // если можно сделать сложение
  else {
    *value = s21_copy_decimal(buff);
  }

  return error_status;
}

/**
 * @brief Функция для умножеия числа не 10 (только числа (мантисы))
 *
 * @param *value указатель на число типа decimal
 * @param pow значение степени к которому нужно привести
 * @return 1 - VALUE_OK , 0 - VALUE ERROR
 */
int s21_normalization_up(s21_decimal* value, int pow) {
  // что бы нормализовать число, нужно его само умножить на 10 N раз и
  // увеличить степень
  if (pow > 28) return VALUE_ERROR;
  int current_scale = s21_get_scale(*value);
  int need_multiplications = pow - current_scale;
  int error_status = VALUE_OK;
  for (int i = 0; i < need_multiplications && error_status; i++) {
    s21_set_scale(value, 0);
    error_status = s21_mul_to_10(value);
    if (error_status) current_scale++;
  }
  // если ошибки не произошло, то ставлю нужную степень, иначе, ту на сколько
  // смог умножить
  if (error_status)
    s21_set_scale(value, pow);
  else
    s21_set_scale(value, current_scale);

  return error_status;
}

/**
 * @brief Функция для умножеия числа не 10 (только числа (мантисы))
 *
 * @param *value указатель на число типа decimal
 * @param need_pow значение степени к которому нужно привести
 * @note если нормализация требует большего кол-ва сдвигов чем разрядов в
 * числе, то число станет 0
 */
void s21_normalization_down(s21_decimal* value, int need_pow) {
  // я должен разделить числитель на 10, в знаменателе уменьшить степень на 1
  //   если число в числителе не делится на 10 нацело, значит я должен
  //   отбросить отстаток и округлить
  s21_decimal divider = {{10, 0, 0, 0}}, remainder = {{DEC_ZERO}};
  s21_decimal result = {{DEC_ZERO}}, temp_res = {{DEC_ZERO}};
  s21_decimal five = {{5, 0, 0, 0}}, one = {{1, 0, 0, 0}};
  int pow = s21_get_scale(*value);
  int sign = s21_get_sign(*value);

  // блок, для того что бы просто разделить число - получить нужную целую часть.
  int need_divisions = pow - need_pow;
  for (int i = 1; i < need_divisions; i++) {
    s21_mul_to_10(&divider);
  }
  temp_res = s21_copy_decimal(*value);
  temp_res.SIGN_POW = 0;
  s21_div_with_r(*value, divider, &result, &remainder);
  *value = s21_copy_decimal(result);
  value->SIGN_POW = 0;

  // сначала зануляю (на случай если нижние или средние разряды заполнены)
  // возвращаю divider к 10, и буду делить на 10 в цикле, что бы найти верный
  // остаток длинной 1 цифру.
  s21_set_to_zero(&divider);
  s21_set_to_zero(&result);
  divider.LOW = 10;
  while (need_divisions-- > 0) {
    s21_div_with_r(temp_res, divider, &result, &remainder);
    temp_res = s21_copy_decimal(result);
    s21_set_to_zero(&result);
  }

  // округление
  if (!s21_is_zero(remainder) && s21_is_greater_or_equal(remainder, five)) {
    s21_add(*value, one, value);
  }
  if (!s21_is_zero(*value)) {
    s21_set_scale(value, need_pow);
    s21_set_sign(value, sign);
  }
}

int s21_normalization(s21_decimal* value_1, s21_decimal* value_2) {
  // get scales of numbers
  int scale_1 = s21_get_scale(*value_1);
  int scale_2 = s21_get_scale(*value_2);

  if (scale_1 > scale_2) {
    s21_normalization_up(value_2, scale_1);
    scale_2 = s21_get_scale(*value_2);
    if (scale_1 != scale_2) {
      // берем текущее значение степени у value_2
      scale_2 = s21_get_scale(*value_2);
      s21_normalization_down(value_1, scale_2);
    }
  } else if (scale_1 < scale_2) {
    s21_normalization_up(value_1, scale_2);
    scale_1 = s21_get_scale(*value_1);
    if (scale_1 != scale_2) {
      // берем текущее значение степени у value_1
      scale_1 = s21_get_scale(*value_1);
      s21_normalization_down(value_2, scale_1);
    }
  }
  // возвращаем общую нормализованную степень
  scale_1 = s21_get_scale(*value_1);
  return scale_1;
}
