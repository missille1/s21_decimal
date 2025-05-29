#include "tests.h"

START_TEST(test_div) {
  {
    s21_decimal x = {{310000000, 0, 0, 0}};
    s21_decimal y = {{1, 0, 0, 0}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_div(x, y, &z);
    char ourRes[1000], expect[1000] = "310000000 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
    s21_decimal y = {{2, 0, 0, 28 << 16}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 1);
  }

  {
    s21_decimal x = {{52525252, 0, 0, 0}};
    s21_decimal y = {{0, 0, 0, 0}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 3);
  }

  {
    s21_decimal x = {{52525252, 0, 0, 2147483648}};
    s21_decimal y = {{0, 0, 0, 0}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 3);
  }

  {
    s21_decimal x = {{52525252, 0, 0, 0}};
    s21_decimal y = {{0, 0, 0, 2147483648}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 3);
  }

  {
    s21_decimal x = {{52525252, 0, 0, 8845}};
    s21_decimal y = {{0, 0, 0, 10}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 3);
  }

  {
    s21_decimal x = {{52525252, 0, 0, 65465}};
    s21_decimal y = {{0, 0, 0, 9598595}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 3);
  }

  {
    s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, MASK_MINUS}};
    s21_decimal y = {{2, 0, 0, 28 << 16}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 2);
  }

  {
    s21_decimal x = {{5, 0, 50, MASK_MINUS}};
    s21_decimal y = {{5, 0, 0, MASK_MINUS}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 0);
  }

  {
    s21_decimal x = {{0, 0, 0, MASK_MINUS}};
    s21_decimal y = {{5, 0, 0, MASK_MINUS}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_set_scale(&y, 20);
    int err = 0;
    err = s21_div(x, y, &z);
    char ourRes[1000], expect[1000] = "0 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
    ck_assert_int_eq(err, 0);
  }

  {
    s21_decimal x = {{5, 0, 0, MASK_MINUS}};
    s21_decimal y = {{0, 0, 0, MASK_MINUS}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_set_scale(&y, 28);
    int err = 0;
    err = s21_div(x, y, &z);
    ck_assert_int_eq(err, 3);
  }

  {
    s21_decimal x = {{5, 0, 0, MASK_MINUS}};
    s21_decimal y = {{5, 0, 0, MASK_MINUS}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_set_scale(&x, 28);
    s21_set_scale(&y, 28);
    s21_div(x, y, &z);
    char ourRes[1000], expect[1000] = "1 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{1, 1, 1, 655360}};
    s21_decimal y = {{1, 1, 1, 655360}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_div(x, y, &z);
    char ourRes[1000], expect[1000] = "1 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{1, 1, 1, 655360}};
    s21_decimal y = {{1, 1, 1, 983040}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_div(x, y, &z);
    char ourRes[1000], expect[1000] = "100000 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{1, 1, 1, 983040}};
    s21_decimal y = {{1, 1, 1, -2146500608}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_div(x, y, &z);
    char ourRes[1000], expect[1000] = "1 0 0 2147483648";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }
  {
    // отрицательное, младшие биты, делится нацело
    s21_decimal value_1 = {{17, 0, 0, MASK_MINUS}};
    s21_decimal value_2 = {{5, 0, 0, 0}};
    s21_decimal check_result = {{34, 0, 0, 0b10000000000000010000000000000000}};

    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // отрицательное, средние биты, делится нацело
    s21_decimal value_1 = {{59, 0, 0, 0}};

    s21_decimal value_2 = {{4, 0, 0, 0}};
    s21_decimal check_result = {
        {1475, 0, 0, 0b00000000000000100000000000000000}};

    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // деление на 0

    s21_decimal value_1 = {{681, 0, 0, 0}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_decimal check_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), DIV_ZERO);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // деление большого числа (pow +- 0) на мелкое (pow +-20)
    // 51 881 467 793 207 459 855
    //  5 /10^15

    s21_decimal value_1 = {{15, 20, 45, 0}};
    s21_decimal value_2 = {{5, 0, 0, 0b00000000000011110000000000000000}};
    s21_decimal check_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), TOO_BIG);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // деление большого числа (pow +- 0) на мелкое (pow +-20)

    // 51 881 467 793 207 459 855 pow = 3
    //  3 /10^22

    s21_decimal value_1 = {{15, 20, 45, 0b00000000000000110000000000000000}};
    s21_decimal value_2 = {{3, 0, 0, 0b00000000000101100000000000000000}};
    s21_decimal check_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), TOO_BIG);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }

  {
    // деление большого числа (pow +- 0) на мелкое (pow +-20)
    // - 51 881 467 793 207 459 855
    //  5 /10^15
    s21_decimal value_1 = {{15, 20, 45, MASK_MINUS}};
    s21_decimal value_2 = {{5, 0, 0, 0b00000000000011110000000000000000}};
    s21_decimal check_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), TOO_SMALL);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // деление большого числа (pow +- 0) на мелкое (pow +-5), без
    // переполнения просто нацело 51 881 467 793 207 459 855
    //  5 /10^0
    // 10376293558641491971

    s21_decimal value_1 = {{0b00000000000000000000000000001111,
                            0b11010000000000000000000000010100, 0b10, 0}};
    s21_decimal value_2 = {{5, 0, 0, 0}};
    s21_decimal check_result = {{0b00000000000000000000000000000011,
                                 0b10010000000000000000000000000100, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }

  {
    // деление большого числа (pow +- 0) на мелкое (pow +-5), без
    // переполнения 51 881 467 793 207 459 855 на  5 /10^3
    // 10376293558641491971 / 10 ^-3 => 10376293558641491971000 / 10^0
    s21_decimal value_1 = {{0b00000000000000000000000000001111,
                            0b11010000000000000000000000010100, 0b10,
                            MASK_MINUS}};
    s21_decimal value_2 = {{5, 0, 0, 0b00000000000000110000000000000000}};
    s21_decimal check_result = {{0b00000000000000000000101110111000,
                                 0b10000000000000000000111110100000,
                                 0b1000110010, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // мантиса 1го числа меньше мантисы 2го числа

    s21_decimal value_1 = {{15, 0, 0, 0}};
    s21_decimal value_2 = {{25, 0, 0, 0}};
    s21_decimal check_result = {{6, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // мантиса 1го числа меньше мантисы 2го числа, и 2е число занимает всю
    // мантису 79 228 162 514 264 337 589 248 983 040
    // 79 228 162 514 264 337 593 543 950 335
    s21_decimal value_1 = {{0b0, 0b11111111111111111111111111111111,
                            0b11111111111111111111111111111111, 0}};
    s21_decimal value_2 = {{DEC_MAX}};
    s21_decimal check_result = {{0b11101111101100000011000110100001,
                                 0b00111110001001010000001001100000,
                                 0b00100000010011111100111001011110,
                                 0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {  // 4 на 6
    s21_decimal value_1 = {{4, 0, 0, 0}};
    s21_decimal value_2 = {{6, 0, 0, 0}};
    s21_decimal check_result = {{0b00001010101010101010101010101011,
                                 0b00101001011011100000000110010110,
                                 0b00010101100010101000100110010100,
                                 0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {
    // 8 на 9
    s21_decimal value_1 = {{8, 0, 0, 0}};
    s21_decimal value_2 = {{9, 0, 0, 0}};
    s21_decimal check_result = {{0b10111000111000111000111000111001,
                                 0b00110111001111010101011101110010,
                                 0b00011100101110001011011101110000,
                                 0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }
  {  // 0.6 на 9 - 0.0666666666666666666666666667 (pow 28)
    s21_decimal value_1 = {{6, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {{9, 0, 0, 0}};
    s21_decimal check_result = {{0b10011010101010101010101010101011,
                                 0b01101010100010110000000000101000,
                                 0b00000010001001110111010000101000,
                                 0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(value_1, value_2, &result)), OK);
    ck_assert_int_eq(check_result.bits[0], result.bits[0]);
    ck_assert_int_eq(check_result.bits[1], result.bits[1]);
    ck_assert_int_eq(check_result.bits[2], result.bits[2]);
    ck_assert_int_eq(check_result.bits[3], result.bits[3]);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    int return_value = s21_div(decimal1, decimal2, NULL);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 0x1C0001}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 0x1C8000}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 0x11C0000}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 0x401C0000}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal decimal2 = {{0, 0, 0, 0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }

  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }
  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }
  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0, 0, 0, 0x1C0001}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }
  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0, 0, 0, 0x1C8000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }
  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0, 0, 0, 0x11C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }
  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0, 0, 0, 0x401C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_ne(return_value, OK);
  }
  {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 0
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, DIV_ZERO);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -0
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, DIV_ZERO);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 0.0000000000000000000000000001
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, TOO_BIG);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -0.0000000000000000000000000001
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, TOO_SMALL);
  }

  {
    // 0.0000000000000000000000000001
    s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
    // -79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    s21_decimal result = {{DEC_ZERO}};
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, TOO_SMALL);
  }

  {
    // 1
    s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
    // 39614081257132168796771975168
    s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, TOO_SMALL);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 0.001
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, TOO_BIG);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -0.001
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, TOO_SMALL);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 7922816251426433759354395033.5
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -7922816251426433759354395033.5
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 26409387504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -26409387504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // очень сильная разница
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 39614081257132168798919458816
    s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
    // 1.9999999999999999998915797827
    s21_decimal decimal_check = {
        {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -39614081257132168798919458816
    s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    // -1.9999999999999999998915797827
    s21_decimal decimal_check = {
        {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162495817593524129366015
    s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    // 1.0000000002328306436538696289
    s21_decimal decimal_check = {
        {0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -79228162495817593524129366015
    s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -1.0000000002328306436538696289
    s21_decimal decimal_check = {
        {0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 10000000000000000000000000000
    s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -10000000000000000000000000000
    s21_decimal decimal_check = {
        {0x10000000, 0x3E250261, 0x204FCE5E, 0x80000000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 39614081266355.540835774234624
    s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
    // 1999999999534338.7126922607422
    s21_decimal decimal_check = {{0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0xD0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -39614081266355.540835774234624
    s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
    // -1999999999534338.7126922607422
    s21_decimal decimal_check = {
        {0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0x800D0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 1.9999999999999999999999999999
    s21_decimal decimal1 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
    // 8460.288
    s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 0.0002363985717743887678528201
    s21_decimal decimal_check = {{0x576D5AC9, 0xEC2BEAF0, 0x1F497, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 1.9999999999999999999999999999
    s21_decimal decimal1 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
    // -8460.288
    s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
    // -0.0002363985717743887678528201
    s21_decimal decimal_check = {{0x576D5AC9, 0xEC2BEAF0, 0x1F497, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 1.0000000000000000000000000001
    s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // -1429062841781896312709593009.2
    s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
    // -0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 1.0000000000000000000000000001
    s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 1429062841781896312709593009.2
    s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
    // 0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 1.0000000000000000000000000001
    s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 3656273013.5441854660747245473
    s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
    // 0.0000000002735025519964266099
    s21_decimal decimal_check = {{0x39191E73, 0x25F4C338, 0x0, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 1.0000000000000000000000000001
    s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // -3656273013.5441854660747245473
    s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
    // -0.0000000002735025519964266099
    s21_decimal decimal_check = {{0x39191E73, 0x25F4C338, 0x0, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // -0.001
    s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80030000}};
    // 8460.288
    s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
    // -0.0000001181992858871943839264
    s21_decimal decimal_check = {{0x6EA2BE20, 0x137232AD, 0x40, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // -0.001
    s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80030000}};
    // -8460.288
    s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
    // 0.0000001181992858871943839264
    s21_decimal decimal_check = {{0x6EA2BE20, 0x137232AD, 0x40, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // -0.001
    s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80030000}};
    // 8.000
    s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
    // -0.000125
    s21_decimal decimal_check = {{0x7D, 0x0, 0x0, 0x80060000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // -0.001
    s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80030000}};
    // -8.000
    s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
    // 0.000125
    s21_decimal decimal_check = {{0x7D, 0x0, 0x0, 0x60000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 4294967296
    s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
    // 0.000001969814300537109375
    s21_decimal decimal_check = {{0x78FFBB7F, 0x1B562FAB, 0x0, 0x180000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // -4294967296
    s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
    // -0.000001969814300537109375
    s21_decimal decimal_check = {{0x78FFBB7F, 0x1B562FAB, 0x0, 0x80180000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 8589934591
    s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
    // 0.0000009849071503832129703815
    s21_decimal decimal_check = {{0x386F8F87, 0xEB530E1E, 0x215, 0x1C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // -8589934591
    s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
    // -0.0000009849071503832129703815
    s21_decimal decimal_check = {{0x386F8F87, 0xEB530E1E, 0x215, 0x801C0000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 8460.288
    s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 2
    s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
    // 4230.144
    s21_decimal decimal_check = {{0x408C00, 0x0, 0x0, 0x30000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // -2
    s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
    // -4230.144
    s21_decimal decimal_check = {{0x408C00, 0x0, 0x0, 0x80030000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 1067.8384720176741640293091584
    s21_decimal decimal_check = {{0xDF08900, 0x9CD22B64, 0x2280F3EB, 0x190000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // -7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -1067.8384720176741640293091584
    s21_decimal decimal_check = {
        {0xDF08900, 0x9CD22B64, 0x2280F3EB, 0x80190000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // 0.5
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
    // 16920.576
    s21_decimal decimal_check = {{0x1023000, 0x0, 0x0, 0x30000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }

  {
    // 8460.288
    s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
    // -0.5
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
    // -16920.576
    s21_decimal decimal_check = {{0x1023000, 0x0, 0x0, 0x80030000}};
    s21_decimal result;
    int return_value = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(return_value, OK);
    ck_assert_uint_eq(decimal_check.bits[0], result.bits[0]);
    ck_assert_uint_eq(decimal_check.bits[1], result.bits[1]);
    ck_assert_uint_eq(decimal_check.bits[2], result.bits[2]);
    ck_assert_uint_eq(decimal_check.bits[3], result.bits[3]);
  }
}
END_TEST

Suite *suite_s21_div() {
  Suite *s = suite_create("div");
  TCase *tc = tcase_create("div_tc");

  tcase_add_test(tc, test_div);

  suite_add_tcase(s, tc);
  return s;
}
