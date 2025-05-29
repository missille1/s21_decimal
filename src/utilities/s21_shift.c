#include "../s21_decimal.h"
/**
 * @brief  Функция выбора bits'a в зависимости от нормера bit'a (low, mid, high)
 *
 * @param *bit - указательно на номер бита в числе
 * @param *arr_el - указательно на bits в стурктуре (low, middle, high)
 */
void s21_choose_bits(int* bit, int* arr_el) {
  if (*bit >= SIZE_64) {
    *arr_el = 2;
    *bit -= SIZE_64;
  } else if (*bit >= SIZE_32) {
    *arr_el = 1;
    *bit -= SIZE_32;
  }
}

/**
 * @brief  Функция сдвига всех битов в числе влево
 *
 * @param *value указатель на число типа decimal
 * @param shift количество битов, на которые нужно произвести сдвиг
 * @return 0 либо 1 ( 0 - ошибка, нельзя делать сдвиг, иначе переполнение,
 * 1 - все ОК, сдвиг произведен )
 */
bool s21_shift_to_left(s21_decimal* value, int shift) {
  if (shift == 0) return VALUE_OK;
  bool error_status = VALUE_OK;
  int temp_bit = 0;

  // проверка на переполнение вверх
  if (shift > SIZE_64) {
    if (value->HIGH != 0 || value->MEDIUM != 0 ||
        (value->LOW >> (SIZE_96 - shift)) > 0)
      error_status = VALUE_ERROR;
  } else if (shift > SIZE_32) {
    if (value->HIGH != 0 || (value->MEDIUM >> (SIZE_64 - shift)) != 0)
      error_status = VALUE_ERROR;
  } else if ((value->HIGH >> (SIZE_32 - shift)) > 0)
    error_status = VALUE_ERROR;

  for (int i = 2; i >= 0 && error_status; i--) {
    value->bits[i] <<= shift;
    if (i > 0) {
      for (int j = 0; j < shift; j++) {
        temp_bit = s21_get_bit(*value, SIZE_32 * (i - 1) + (SIZE_32 - 1 - j));
        s21_set_bit(value, SIZE_32 * i + shift - j - 1, temp_bit);
      }
    }
  }
  return error_status;
}

/**
 * @brief  Функция сдвига всех битов в числе вправо
 *
 * @param *value указатель на число типа decimal
 * @param shift количество битов, на которые нужно произвести сдвиг
 */
void s21_shift_to_right(s21_decimal* value, int shift) {
  int temp_bit = 0;
  for (int i = 0; i <= 2; i++) {
    value->bits[i] >>= shift;
    if (i < 2) {
      for (int j = 0; j < shift; j++) {
        temp_bit = s21_get_bit(*value, SIZE_32 * (i + 1) + j);
        s21_set_bit(value, SIZE_32 * i + (SIZE_32 - shift + j), temp_bit);
      }
    }
  }
}

/**
 * @brief  Функция для проверки, могу ли я сдвигать число влево на Х битов,
 * без потери значимой части
 *
 * @param value число типа decimal
 * @param bits количество битов, на которые нужно произвести сдвиг
 * @return 0 - ошибка, нельзя делать сдвиг, иначе переполнение,
 * 1 - все ОК, можно сдвигать
 */
bool s21_can_shift(s21_decimal value, int bits) {
  int count = 0;
  for (int i = 0; i < bits; i++) {
    if (s21_get_bit(value, SIZE_96 - 1 - i) == 0) {
      count++;
    }
  }
  return count == bits ? 1 : 0;
}