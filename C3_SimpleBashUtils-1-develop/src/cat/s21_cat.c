#include "s21_cat.h"

int main(int argc, char **argv) {
  char *buffer = NULL;
  int bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0, qqflag = 0;
  int vflag = 0;
  flags(argc, argv, &bflag, &nflag, &sflag, &eflag, &tflag, &vflag, &qqflag);
  read_file(argc, argv, &bflag, &nflag, &sflag, &eflag, &tflag, &vflag, &qqflag,
            buffer);
  return 0;
}

void print_file(int *eflag, int *tflag, int length, int *vflag, char *buffer) {
  for (int i = 0; i < length; i++) {
    if (buffer[i] == '\t') {
      if (*tflag == 1) {
        printf("^I");
        continue;
      }
    }
    if (buffer[i] == '\n' && *eflag) {
      printf("$");
    }
    if (*vflag) {
      if (buffer[i] >= 0 && buffer[i] < 32 && buffer[i] != '\n' &&
          buffer[i] != '\t') {
        char c;
        c = buffer[i] + 64;
        printf("^%c", c);
      } else if (buffer[i] == 127) {
        printf("^?");
      } else {
        printf("%c", buffer[i]);
      }
    } else {
      printf("%c", buffer[i]);
    }
  }
}

void flags(int argc, char **argv, int *bflag, int *nflag, int *sflag,
           int *eflag, int *tflag, int *vflag, int *qqflag) {
  int opt;
  while ((opt = getopt(argc, argv, "benstvET?")) != -1) {
    switch (opt) {
      case 'b':
        *bflag = 1;
        break;
      case 'n':
        *nflag = 1;
        break;
      case 'E':
        *eflag = 1;
        break;
      case 'e':
        *eflag = 1;
        *vflag = 1;
        break;
      case 's':
        *sflag = 1;
        break;
      case 'T':
        *tflag = 1;
        break;
      case 't':
        *tflag = 1;
        *vflag = 1;
        break;
      case 'v':
        *vflag = 1;
        break;
      case '?':
        *qqflag = 1;
        printf("usage: cat [-benstTEv] [file ...]\n");
        exit(1);
    }
  }
}

void read_file(int argc, char **argv, int *bflag, int *nflag, int *sflag,
               int *eflag, int *tflag, int *vflag, int *qqflag, char *buffer) {
  int length, lineNumber = 0, lastLineBlank = 0;
  FILE *fp = NULL;
  size_t buffersize = 0;
  int actualFile = optind;
  while (actualFile < argc) {
    if (*qqflag != 1) {
      if (argc > 1) {
        fp = fopen(argv[actualFile], "rb");
        if (fp == NULL) {
          fprintf(stderr, "%s: %s: No such file or directory", argv[0],
                  argv[actualFile]);
          exit(1);
        } else {
          while ((length = getline(&buffer, &buffersize, fp)) != -1) {
            if (*sflag == 1) {
              int currentLineBlank = (length <= 1) ? 1 : 0;
              if (lastLineBlank && currentLineBlank) {
                continue;
              }
              lastLineBlank = currentLineBlank;
            }
            if (*bflag) {
              if (length > 0 && buffer[0] != '\n') {
                lineNumber++;
                printf("%*d\t", 6, lineNumber);
              }
            } else if (*nflag) {
              lineNumber++;
              printf("%*d\t", 6, lineNumber);
            }
            print_file(eflag, tflag, length, vflag, buffer);
          }
          fclose(fp);
        }
        actualFile = actualFile + 1;
        lineNumber = 0;
      }
    }
  }
  if (buffer) {
    free(buffer);
    buffer = NULL;
  }
}
