OS := $(shell uname -s)
CC = gcc
CFLAGS = -O1 -Wall -Wextra -Werror -std=c11

ifeq ($(OS), Darwin)
	CHKFLAGS = -lcheck
else
	CHKFLAGS = -lcheck -lrt -lm -lpthread -lsubunit
endif

s21_matrix.o:
	$(CC) $(CFLAGS) -c s21_matrix.c

test.o:
	checkmk clean_mode=1 tests.check > a_test.c
	$(CC) $(CFLAGS) -c a_test.c -o test.o $(CHKFLAGS)

test: test.o s21_matrix.o
	$(CC) $(CFLAGS) s21_matrix.o test.o -o test.out $(CHKFLAGS)
	./test.out

clean:
	rm -rf *.o
	rm -rf *.out
	rm a_test.c