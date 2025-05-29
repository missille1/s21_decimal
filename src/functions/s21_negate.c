#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error_status = ERROR;
  if (result != NULL && s21_is_correct_value(value)) {
    *result = s21_copy_decimal(value);
    // Если 1 меняем на 0, то используем исключающее или (^)
    // Если 0 меняем на 1, то используем логическое сложение (или, |)
    result->bits[3] = s21_get_sign(value) ? result->bits[3] ^ MASK_MINUS
                                          : result->bits[3] | MASK_MINUS;
    error_status = OK;
  }
  return error_status;
}
