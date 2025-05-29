#include "tests.h"

void run_testcase(Suite *testcase) {
  SRunner *runner = srunner_create(testcase);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  srunner_ntests_failed(runner);
  srunner_free(runner);
}

void run_all_testcases() {
  Suite *list_cases[] = {suite_s21_add(),
                         suite_s21_sub(),
                         suite_s21_mul(),
                         suite_s21_div(),
                         suite_s21_truncate(),
                         suite_s21_is_equal(),
                         suite_s21_is_greater_less(),
                         suite_s21_is_greater_or_equal_less(),
                         suite_s21_int_to_dec(),
                         suite_s21_dec_to_int(),
                         suite_s21_float_to_dec(),
                         suite_s21_dec_to_float(),
                         suite_s21_round(),
                         suite_s21_floor(),
                         suite_s21_negate(),
                         NULL};

  for (int i = 0; list_cases[i] != NULL; i++) {
    run_testcase(list_cases[i]);
  }
}

int main() {
  run_all_testcases();
  return 0;
}
