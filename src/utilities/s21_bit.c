#include "../s21_decimal.h"

/**
 * @brief Функция для получения значения бита
 *
 * @param value число типа decimal
 * @param bit порядковый номер бита в структуре decimal, значение которого
 * нужно получить
 * @return 0 или 1 ( что записанно в данном бите)
 */
int s21_get_bit(s21_decimal value, int bit) {
  // Переменная для обозначение номера элемента массива, в котором необходимо
  // получить значение
  int arr_el = 0;
  s21_choose_bits(&bit, &arr_el);
  int mask = MASK_ONE << bit;
  return (value.bits[arr_el] & mask) >> bit;
}

/**
 * @brief Функция для установки значения бита
 *
 * @param value число типа decimal
 * @param bit порядковый номер бита в структуре decimal, значение которого
 * нужно изменить
 * @param bit_value значение, которое нужно записать данному биту (0 или 1)
 */
void s21_set_bit(s21_decimal* value, int bit, int bit_value) {
  // Переменная для обозначение номера элемента массива, в котором необходимо
  // поменять значение
  int arr_el = 0;
  s21_choose_bits(&bit, &arr_el);

  unsigned int mask = MASK_ONE << bit;
  if (bit_value)
    value->bits[arr_el] |= mask;
  else {
    mask = ~mask;
    value->bits[arr_el] &= mask;
  }
}
