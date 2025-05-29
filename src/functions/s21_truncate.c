#include "../s21_decimal.h"

/**
 * @brief  Функция  Возвращает целые цифры указанного Decimal числа; любые
 * дробные цифры отбрасываются, включая конечные нули.
 *
 * @param value число типа decimal
 * @param *result указатель на число типа decimal, куда будет записана целая
 * часть исходного числа
 * @return 1 - ошибка -  нельзя выделить целую часть или result is NULL,
 * 0 - все ОК)
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal remainder = {{DEC_ZERO}};
  int error_status = OK;
  int pow = s21_get_scale(value);

  if (result != NULL && s21_is_correct_value(value) && pow <= 28) {
    // на случай если в result, уже что-то есть
    s21_set_to_zero(result);
    // степень 0 => у нас уже целая часть
    if (pow == 0) {
      *result = s21_copy_decimal(value);
    } else {
      // находим число на которое разделить, что бы получить целую часть и делим
      while (pow > 1) {
        s21_mul_to_10(&ten);
        pow--;
      }
      s21_div_with_r(value, ten, result, &remainder);
      // зануляю степень результату
      s21_set_scale(result, 0);
    }
  } else
    error_status = ERROR;
  return error_status;
}
