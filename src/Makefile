OS := $(shell uname -s)
CC = gcc
CFLAGS = -O1 -Wall -Wextra -Werror -std=c11

ifeq ($(OS), Darwin)
	CHKFLAGS = -lcheck
else
	CHKFLAGS = -lcheck -lrt -lm -lpthread -lsubunit
endif

all: clean s21_matrix.a test check
	make clean
	rm s21_matrix.a

s21_matrix.a: s21_matrix.o
	ar rc s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

s21_matrix.o:
	$(CC) $(CFLAGS) -c s21_matrix.c

test.o:
	checkmk clean_mode=1 tests.check > a_test.c
	$(CC) $(CFLAGS) -c a_test.c -o test.o $(CHKFLAGS)
	rm a_test.c

test: test.o s21_matrix.o
	$(CC) $(CFLAGS) s21_matrix.o test.o -o test.out $(CHKFLAGS)
	./test.out

check:
	cp ../materials/linters/.clang-format .
	cppcheck *.c *.h
	clang-format -n *.c *.h

gcov_report: matrix_test.o s21_matrix.o
	chmod 777 tests.check
	checkmk clean_mode=1 tests.check > matrix_test.c
	$(CC) $(CFLAGS) --coverage -l check s21_matrix.c matrix_test.c -o test $(CHKFLAGS)
	./test
	lcov -t "./test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm matrix_test.c

matrix_test.o:
	chmod 777 tests.check
	checkmk clean_mode=1 tests.check > matrix_test.c
	$(CC) $(CFLAGS) -c matrix_test.c -o matrix_test.o $(CHKFLAGS)
	rm matrix_test.c

clean:
	@rm -rf *.o *.gcda *.gcno *.out *.gch *.info
	@rm -rf test
	@rm -rf report