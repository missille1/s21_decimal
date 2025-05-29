gcc = gcc 
flags = -Werror -Wall -Wextra -std=c11
check_flag = -lcheck
gcov_flags = -fprofile-arcs -ftest-coverage
valgrind_flags = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

files = ./functions/*.c ./utilities/*.c
test_files = ./tests/*.c
out_file = ./s21_decimal
library = ./s21_decimal.a

ifeq ($(shell uname -s), Linux)
	check_flag += -lm -lsubunit
	open=xdg-open
else
	open=open
endif

all: clang s21_decimal.a

s21_decimal.a:
	$(gcc) -c -g $(flags) $(files)
	ar rcs $(library) ./*.o 
	ranlib $(library)
	rm ./*.o

test: s21_decimal.a
	$(gcc) -g $(flags) $(test_files) $(library) -o $(out_file) $(check_flag)
	./s21_decimal
	
gcov_report:
	$(gcc) $(flags) $(gcov_flags) $(test_files) $(files) -o $(out_file) $(check_flag)
	./s21_decimal
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info 
	$(open) report/index.html
	make rm_gcov
	rm *.info

clean:
	-rm *.o
	-rm *.a
	-rm $(out_file)
	-rm $(library)
	-rm -rf report

rebuild:
	make clean
	make all

rm_gcov:
	rm *.gcno	
	rm *.gcda

rm_report:
	rm -rf report

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -i */*.c *.h

format_check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c *.h

valgrind: s21_decimal.a
	$(gcc) $(flags) $(test_files) $(library) -o $(out_file) $(check_flag)
	valgrind $(valgrind_flags) $(out_file)

rm_val:
	rm valgrind.txt