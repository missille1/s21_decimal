#include "../s21_decimal.h"

/**
 * @brief  Функция для получения степени числа
 *
 * @param value число типа decimal
 * @return число от 0 до 255
 */
int s21_get_scale(s21_decimal value) {
  int mask = 0b11111111;
  // сдвигаю на 16 битов, что бы в bits[3] получить доступ к битам с 16 по
  // 23й в которых хранится показатель степени
  int pow = value.bits[3] >> 16;
  pow &= mask;
  return pow;
}

/**
 * @brief  Функция для установки степени числа
 *
 * @param *value указатель на  число типа decimal
 * @param power  степень, которую нужно установить
 * @return 0 - error_status, 1 - ok
 */
bool s21_set_scale(s21_decimal* value, int power) {
  int sign;
  bool error_status = VALUE_ERROR;

  // if (power >= 0 && power < 29) {
  if (power >= 0) {
    // копирую знак, что бы не потерять его
    error_status = VALUE_OK;
    sign = s21_get_sign(*value);
    // устанавливаю необходимую степень в нужное место
    power = power << 16;
    value->bits[3] = power;
    // устанавливаю скопированный знак
    s21_set_sign(value, sign);
  }
  return error_status;
}
