CC = -Wall -Wextra -Werror -std=c11 
GCOV = -fprofile-arcs -ftest-coverage
SRC = s21_decimal.c
LIBA = s21_decimal.a
TEST_L = -lcheck -lm -lpthread
B_PATH = ./
EXE = ./s21_test
OS = $(shell uname)


ifeq ($(OS),Linux) 
    det_OS = -lcheck -lm -lrt -lpthread -lsubunit
else
    det_OS = -lcheck -lm -lpthread
endif


test: clean s21_decimal.a
	gcc $(CC) s21_tests/tests.c s21_tests/s21_add_test.c s21_tests/s21_sub_test.c s21_tests/s21_div_test.c \
	s21_tests/s21_mul_test.c s21_tests/s21_mod_test.c s21_tests/s21_is_less_test.c s21_tests/s21_is_less_or_equal_test.c \
	s21_tests/s21_is_greater_test.c s21_tests/s21_is_greater_or_equal_test.c \
	s21_tests/s21_is_equal_test.c s21_tests/s21_is_not_equal_test.c \
	s21_tests/s21_from_int_to_decimal_test.c s21_tests/s21_from_float_to_decimal_test.c  \
	s21_tests/s21_from_decimal_to_float_test.c s21_tests/s21_from_decimal_to_int_test.c \
	s21_tests/s21_floor_test.c s21_tests/s21_round_test.c s21_tests/s21_truncate_test.c \
	s21_tests/s21_negate_test.c \
	-L. s21_decimal.a  $(det_OS) -o s21_test
	./s21_test

all: s21_decimal.a test

s21_decimal.a:
	gcc -c s21_decimal.c s21_decimal.h
	ar rcs s21_decimal.a  s21_decimal.o
	ranlib s21_decimal.a

gcov_report:
	gcc s21_tests/*.c -fprofile-arcs -ftest-coverage s21_decimal.c  -o s21_test $(det_OS)
	./s21_test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

rebuild : clean all

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf *.info
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf report
	rm -rf s21_test
	rm -rf .clang-format
	rm -rf s21_decimal
	rm -rf s21_decimal.h.gch
	rm -rf s21_tests/*.h.gch

style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	clang-format -n s21_tests/*.c *.h

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov
