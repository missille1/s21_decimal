#include "tests.h"

START_TEST(test_floor) {
  {
    // 79228162514264337593543950335
    s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    // -79228162514264337593543950335
    s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    // 5.281877500950955839569596690
    s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x001B0000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x00000005, 0x0, 0x0, 0x00000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    // -5.281877500950955839569596690
    s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x00000006, 0x0, 0x0, 0x80000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    // -1.2297829382473034409
    s21_decimal dec1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x00000002, 0x0, 0x0, 0x80000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    // 1.2297829382473034409
    s21_decimal dec1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x00130000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x00000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x11111111}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;

    uint8_t flag = s21_floor(dec1, &result);
    ck_assert_int_eq(flag, 1);
  }
  {
    //  -0.0000000000000000000000000001
    s21_decimal dec1 = {{0x1, 0x0, 0x0, 0x801C0000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x80000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    //  0
    s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x00000000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x00000000}};

    uint8_t flag = s21_floor(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    //  0
    s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x00000000}};
    s21_decimal *result = NULL;

    uint8_t flag = s21_floor(dec1, result);
    ck_assert_int_eq(flag, 1);
  }
  {
    s21_decimal num = {{15, 0, 0, 65536}};
    s21_decimal res = {{1, 0, 0, 0}};
    int error = 0;
    error = s21_floor(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{19, 0, 0, 65536}};
    s21_decimal res = {{1, 0, 0, 0}};
    int error = 0;
    error = s21_floor(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{155, 0, 0, 131072}};
    s21_decimal res = {{1, 0, 0, 0}};
    int error = 0;
    error = s21_floor(num, &num);
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
    error = s21_floor(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{268435457, 1042612833, 542101086, 2149318656u}};
    s21_decimal res = {{2, 0, 0, 2147483648u}};
    int error = 0;
    error = s21_floor(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal num = {{0, 0, 0, 0}};
    int error = 0;
    error = s21_floor(num, NULL);
    ck_assert_int_eq(error, 1);
  }

  {
    s21_decimal num = {{21, 0, 0, MASK_MINUS}};
    s21_decimal res = {{3, 0, 0, MASK_MINUS}};
    s21_set_scale(&num, 1);
    int error = 0;
    error = s21_floor(num, &num);
    ck_assert_int_eq(num.bits[0], res.bits[0]);
    ck_assert_int_eq(num.bits[1], res.bits[1]);
    ck_assert_int_eq(num.bits[2], res.bits[2]);
    ck_assert_int_eq(num.bits[3], res.bits[3]);
    ck_assert_int_eq(error, 0);
  }

  {
    s21_decimal x = {{1, 2, 3, 917504}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_floor(x, &z);
    char ourRes[1000], expect[1000] = "553402 0 0 0";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{1, 2, 3, -2146566144}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_floor(x, &z);
    char ourRes[1000], expect[1000] = "553403 0 0 2147483648";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }

  {
    s21_decimal x = {{33, 2, 3000, -2146107392}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_floor(x, &z);
    char ourRes[1000], expect[1000] = "56 0 0 2147483648";
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(ourRes, expect);
  }
}
END_TEST

Suite *suite_s21_floor() {
  Suite *s = suite_create("s21_floor");
  TCase *tc = tcase_create("s21_floor");

  tcase_add_test(tc, test_floor);
  suite_add_tcase(s, tc);
  return s;
}
