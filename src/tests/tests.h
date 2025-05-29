#ifndef S21_TESTS
#define S21_TESTS

#include <check.h>
#include <stdbool.h>
#include <stdio.h>

#include "../s21_decimal.h"

// Tests for us

Suite *suite_s21_add();
Suite *suite_s21_sub();
Suite *suite_s21_mul();
Suite *suite_s21_div();
Suite *suite_s21_truncate();
Suite *suite_s21_is_equal();
Suite *suite_s21_is_greater_less();
Suite *suite_s21_is_greater_or_equal_less();
Suite *suite_s21_int_to_dec();
Suite *suite_s21_dec_to_int();
Suite *suite_s21_float_to_dec();
Suite *suite_s21_dec_to_float();
Suite *suite_s21_round();
Suite *suite_s21_floor();
Suite *suite_s21_negate();

#endif