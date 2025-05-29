#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison and checks
#define VALUE_ERROR 0
#define VALUE_OK 1

// Arithmetic
#define OK 0
#define TOO_BIG 1
#define TOO_SMALL 2
#define DIV_ZERO 3

// Convertors and another
#define ERROR 1

#define MAX_POW 28

#define BITS 3
#define SIZE_32 32
#define SIZE_64 64
#define SIZE_96 96

#define MASK_MINUS 0x80000000
#define MASK_ZERO 0b0
#define MASK_ONE 0b1

#define LOW bits[0]
#define MEDIUM bits[1]
#define HIGH bits[2]
#define SIGN_POW bits[3]

#define DEC_ZERO 0, 0, 0, 0
#define DEC_MAX UINT_MAX, UINT_MAX, UINT_MAX, 0
#define DEC_MIN UINT_MAX, UINT_MAX, UINT_MAX, MASK_MINUS

#define S21_INT_MAX 2147483647
#define S21_INT_MIN -2147483648

#define S21_DEC_MAX 2e96 - 1

typedef struct {
  unsigned bits[BITS + 1];
} s21_decimal;

// Arithmetic Operators

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Convertors

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Utilities

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign_value);
int s21_get_scale(s21_decimal value);
bool s21_set_scale(s21_decimal *value, int power);
int s21_get_bit(s21_decimal value, int bit);
void s21_set_bit(s21_decimal *value, int bit, int bit_value);

s21_decimal s21_copy_decimal(s21_decimal value);
void s21_print_decimal(s21_decimal decimal_number);
bool s21_is_zero(s21_decimal value);
int s21_normalization_up(s21_decimal *value, int pow);
void s21_normalization_down(s21_decimal *value, int need_pow);
int s21_normalization(s21_decimal *value_1, s21_decimal *value_2);
int s21_mul_to_10(s21_decimal *value);
void s21_choose_bits(int *bit, int *arr_el);
bool s21_shift_to_left(s21_decimal *value, int shift);
void s21_shift_to_right(s21_decimal *value, int shift);
int find_shift(s21_decimal number, s21_decimal *divider, int *error_status);
int s21_div_with_r(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result, s21_decimal *remainder);
void s21_set_to_zero(s21_decimal *value);
bool s21_can_shift(s21_decimal value, int bits);
s21_decimal s21_bank(s21_decimal value, s21_decimal remainder);
int s21_find_round_digit(s21_decimal value, int pow);
bool s21_is_correct_value(s21_decimal value);

#endif