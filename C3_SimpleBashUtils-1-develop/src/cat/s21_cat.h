#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_file(int *eflag, int *tflag, int length, int *vflag, char *buffer);
void flags(int argc, char **argv, int *bflag, int *nflag, int *sflag,
           int *eflag, int *tflag, int *vflag, int *qqflag);
void read_file(int argc, char **argv, int *bflag, int *nflag, int *sflag,
               int *eflag, int *tflag, int *vflag, int *qqflag, char *buffer);

#endif  // S21_CAT_H_