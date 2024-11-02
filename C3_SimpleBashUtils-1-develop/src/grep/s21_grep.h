#ifndef _SRC_GREP_GREP_H_
#define _SRC_GREP_GREP_H_

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flag;

void concat_template(char *template);
void read_flag_f(char *qaz, char **argv);
void input_flag(int argc, char **argv, flag *fl);
void several_e(flag *fl, int *actual_file, int number_template, char **argv);
void flag_c(int *filecount, int *count_str, int *actual_file, char **argv,
            int *lengthstr, char *str);
void flag_v(int *count, int *filecount, char **argv, int *lengthstr, char *str,
            int *actual_file);
void flag_n(int *count, int *filecount, char **argv, int *lengthstr, char *str,
            int *actual_file, int *counter_str);
void flag_o(int *filecount, int *asd, int *count_str, char **argv,
            int *actual_file, regmatch_t *pmatch, char *tempstr);
void flag_e_f(flag *fl, char **argv, int *actual_file, int *number_template);
void flags(int *count, int *filecount, char *str, char **argv, int *lengthstr,
           int *actual_file);
void flag_lar(int count, int *count_str, flag fl, char *str, char **argv,
              int filecount, int lengthstr, int actual_file, int counter_str);
void another_fl(flag fl, int filecount, int count_str, int actual_file,
                char **argv, int lengthstr, char *str);
void cflag_regex(int *cflag, flag fl);
void s21_grep(int argc, char **argv);

char *arr = NULL;

#endif  // _SRC_GREP_GREP_H_