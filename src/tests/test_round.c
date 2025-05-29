#include "tests.h"

START_TEST(test_round1) {
  {
    s21_decimal num = {{15, 0, 0, 65536}};
    s21_decimal res = {{2, 0, 0, 0}};
    int error = 0;
    error = s21_round(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{149, 0, 0, 131072}};
    s21_decimal res = {{1, 0, 0, 0}};
    int error = 0;
    error = s21_round(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{25, 0, 0, 65536}};
    s21_decimal res = {{3, 0, 0, 0}};
    int error = 0;
    error = s21_round(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{251, 0, 0, 131072}};
    s21_decimal res = {{3, 0, 0, 0}};
    int error = 0;
    error = s21_round(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{2818572289u, 2606532082u, 1355252715,
                        1835008}};  // 2.5000000000000000000000000001
    s21_decimal res = {{3, 0, 0, 0}};
    int error = 0;
    error = s21_round(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{2818572289u, 2606532082u, 1355252715,
                        2149318656u}};  // 2.5000000000000000000000000001
    s21_decimal res = {{3, 0, 0, 2147483648u}};
    int error = 0;
    error = s21_round(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{15, 0, 0, 2147549184u}};
    s21_decimal res = {{2, 0, 0, 2147483648u}};
    int error = 0;
    error = s21_round(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{1, 0, 0, 0}};
    int error = 0;
    error = s21_round(num, NULL);
    ck_assert_int_eq(error, 1);
  }

  {
    s21_decimal x = {{1, 2, 3, 917504}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_round(x, &z);
    char ourRes[1000], expect[1000] = "553402 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{10, 100, 3, 1376256}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_round(x, &z);
    char ourRes[1000], expect[1000] = "0 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{16, 100, 3, 851968}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_round(x, &z);
    char ourRes[1000], expect[1000] = "5534023 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal dec1 = {0};
    s21_decimal *result = NULL;

    ck_assert_int_eq(s21_round(dec1, result), 1);
  }
  {
    s21_decimal dec1 = {{0, 0, 0, 0b11000000110000001100000011000000}};
    s21_decimal result = {{0, 0, 0, 0}};

    ck_assert_int_eq(s21_round(dec1, &result), 1);
  }
  {
    // 79228162514264337593543950335
    s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);
    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    // -79228162514264337593543950335
    s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    // 5.281877500950955839569596690
    // 5 281 877 500 950 939 420 195 926 289
    s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x001B0000}};
    s21_decimal dec2 = {{0x00000005, 0x0, 0x0, 0x00000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    // -5.281877500950955839569596690
    s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111,
                         0b10000000000110110000000000000000}};
    s21_decimal dec2 = {{0x00000005, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    // -1.2297829382473034409
    s21_decimal dec1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
    s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    // 1.2297829382473034409
    s21_decimal dec1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x00130000}};
    s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x00000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    // тут некорректный децимал
    s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x11111111}};
    s21_decimal result = {0};
    int flag = s21_round(dec1, &result);
    ck_assert_int_eq(flag, 1);
  }
  {
    //  -0.0000000000000000000000000001
    s21_decimal dec1 = {{0x1, 0x0, 0x0, 0x801C0000}};
    s21_decimal dec2 = {{0x00000000, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  -0
    s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x80000000}};
    s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  0
    s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x00000000}};
    s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x00000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  -0.00000000000000
    s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x800E0000}};
    s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  1.0
    s21_decimal dec1 = {{0xA, 0x0, 0x0, 0x00010000}};
    s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x00000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  -1.0
    s21_decimal dec1 = {{0xA, 0x0, 0x0, 0x80010000}};
    s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  -15.674
    s21_decimal dec1 = {{0x00003D3A, 0x0, 0x0, 0x80030000}};
    s21_decimal dec2 = {{0x00000010, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  -1.5674
    s21_decimal dec1 = {{0x00003D3A, 0x0, 0x0, 0x80040000}};
    s21_decimal dec2 = {{0x00000002, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }
  {
    //  -15.5
    s21_decimal dec1 = {{0x0000009B, 0x0, 0x0, 0x80010000}};
    s21_decimal dec2 = {{0x00000010, 0x0, 0x0, 0x80000000}};

    s21_decimal result = {0};

    s21_round(dec1, &result);

    ck_assert_int_eq(s21_is_equal(result, dec2), 1);
  }

  {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

    int code = s21_round(decimal, NULL);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }

  {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, ERROR);
  }
}
END_TEST

Suite *suite_s21_round() {
  Suite *s = suite_create("s21_round");
  TCase *tc = tcase_create("s21_round");

  tcase_add_test(tc, test_round1);
  suite_add_tcase(s, tc);
  return s;
}
