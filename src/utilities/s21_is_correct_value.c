#include "../s21_decimal.h"
/**
 * @brief  Функция для проверки числа типа decimal на корректность;
 * проверяет, что в битах 0-15 и 24-30 установлен 0
 *
 * @param value число типа decimal
 * @return 0 - error_status, 1 - ok
 */
bool s21_is_correct_value(s21_decimal value) {
  int error_status = VALUE_OK;
  int before_pow_mask = 0xFFFF;  // 00000000 00000000 11111111 11111111
  int pow = s21_get_scale(value);
  // проверяю что в битах с 0 по 15 и с 24 по 30й только 0
  // (если там все 0 , то умножение на маску тоже даст 0)

  if ((pow > MAX_POW || before_pow_mask & value.bits[3]) > 0 ||
      (((value.bits[3]) >> 24) & 0b01111111) > 0)
    error_status = VALUE_ERROR;

  return error_status;
}