CC = gcc
CFLAGS = -Wextra -Werror -Wall

all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c s21_grep.c

clean:
	rm -rf s21_grep.o
	rm -rf s21_grep