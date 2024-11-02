#include "s21_grep.h"

int main(int argc, char *argv[]) {
  s21_grep(argc, argv);
  return 0;
}

void s21_grep(int argc, char **argv) {
  regex_t buffer;
  size_t buffer_size = 1000;
  FILE *fp = NULL;
  regmatch_t pmatch[1];
  char *str = NULL;
  int asd = -1, cflag, actual_file = 0, lengthstr = 0;
  flag fl = {0};
  input_flag(argc, argv, &fl);
  int number_template = optind;
  flag_e_f(&fl, argv, &actual_file, &number_template);
  int filecount = argc - actual_file;
  cflag_regex(&cflag, fl);
  regcomp(&buffer, arr, cflag);
  while (actual_file < argc) {
    fp = fopen(argv[actual_file], "rb");
    int count_str = 0, counter_str = 0;
    if (fp == NULL) {
      if (fl.s == 1) {
        exit(1);
      } else {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[actual_file]);
        actual_file++;
        continue;
      }
    } else {
      while ((lengthstr = getline(&str, &buffer_size, fp)) != -1) {
        int count = 0;
        char *tempstr = str;
        counter_str++;
        while (regexec(&buffer, tempstr, 1, pmatch, 0) == 0) {
          count = (count + 1);
          if (fl.o == 1) {
            flag_o(&filecount, &asd, &count_str, argv, &actual_file, pmatch,
                   tempstr);
          }
          tempstr += pmatch[0].rm_eo;
          asd = count_str;
        }
        flag_lar(count, &count_str, fl, str, argv, filecount, lengthstr,
                 actual_file, counter_str);
      }
      another_fl(fl, filecount, count_str, actual_file, argv, lengthstr, str);
      fclose(fp);
      count_str = 0;
    }
    actual_file++;
  }
  free(str);
  regfree(&buffer);
}

void cflag_regex(int *cflag, flag fl) {
  (*cflag) = REG_EXTENDED;
  if (fl.f == 1) {
    (*cflag) = REG_EXTENDED;
  } else {
    (*cflag) = REG_EXTENDED | REG_NEWLINE;
  }
  if (fl.i == 1) {
    (*cflag) = (*cflag) | REG_ICASE;
  }
}

void another_fl(flag fl, int filecount, int count_str, int actual_file,
                char **argv, int lengthstr, char *str) {
  if (fl.c == 1) {
    flag_c(&filecount, &count_str, &actual_file, argv, &lengthstr, str);
  }
  if (fl.l == 1) {
    if (count_str > 0) {
      printf("%s\n", argv[actual_file]);
    }
  }
}

void flag_lar(int count, int *count_str, flag fl, char *str, char **argv,
              int filecount, int lengthstr, int actual_file, int counter_str) {
  if (count > 0) {
    (*count_str)++;
  }
  if (fl.n == 1) {
    flag_n(&count, &filecount, argv, &lengthstr, str, &actual_file,
           &counter_str);
  } else if (fl.c == 1) {
  } else if (fl.l == 1) {
  } else if (fl.o == 1) {
  } else if (fl.v == 1) {
    flag_v(&count, &filecount, argv, &lengthstr, str, &actual_file);
  } else if (fl.h == 1) {
    if (count > 0) {
      printf("%s", str);
    }
  } else {
    flags(&count, &filecount, str, argv, &lengthstr, &actual_file);
  }
}

void flags(int *count, int *filecount, char *str, char **argv, int *lengthstr,
           int *actual_file) {
  if (*count > 0) {
    if (*filecount == 1) {
      printf("%s", str);
    } else if (*filecount > 1) {
      printf("%s:%s", argv[*actual_file], str);
    }
    if (str[*lengthstr - 1] != '\n') {
      printf("\n");
    }
  }
}

void flag_e_f(flag *fl, char **argv, int *actual_file, int *number_template) {
  if (fl->e >= 1 || fl->f >= 1) {
    *actual_file = *number_template;
    number_template--;
  } else {
    *actual_file = *number_template + 1;
    concat_template(argv[*number_template]);
  }
}

void flag_o(int *filecount, int *asd, int *count_str, char **argv,
            int *actual_file, regmatch_t *pmatch, char *tempstr) {
  if (*filecount > 1 && *asd != *count_str) {
    printf("%s:%.*s\n", argv[*actual_file],
           (int)(pmatch[0].rm_eo - pmatch[0].rm_so), tempstr + pmatch[0].rm_so);
  } else if (*filecount > 1 && *count_str == *asd) {
    printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
           tempstr + pmatch[0].rm_so);
  } else if (*filecount == 1) {
    printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
           tempstr + pmatch[0].rm_so);
  }
}

void flag_n(int *count, int *filecount, char **argv, int *lengthstr, char *str,
            int *actual_file, int *counter_str) {
  if (*count > 0) {
    if (*filecount == 1) {
      printf("%d:%s", *counter_str, str);
    } else if (*filecount > 1) {
      printf("%s:%d:%s", argv[*actual_file], *counter_str, str);
    }
    if (str[*lengthstr - 1] != '\n') {
      printf("\n");
    }
  }
}

void flag_v(int *count, int *filecount, char **argv, int *lengthstr, char *str,
            int *actual_file) {
  if (*count == 0) {
    if (*filecount == 1) {
      printf("%s", str);
    } else if (*filecount > 1) {
      printf("%s:%s", argv[*actual_file], str);
    }
    if (str[*lengthstr - 1] != '\n') {
      printf("\n");
    }
  }
}

void flag_c(int *filecount, int *count_str, int *actual_file, char **argv,
            int *lengthstr, char *str) {
  if (*filecount == 1) {
    printf("%d", *count_str);
  } else if (*filecount > 1) {
    printf("%s:%d", argv[*actual_file], *count_str);
  }
  if (str[*lengthstr - 1] != '\n') {
    printf("\n");
  }
}

void concat_template(char *template) {
  if (arr == NULL) {
    arr = malloc(sizeof(char) * (strlen(template) + 1));
    strcpy(arr, template);
  } else {
    arr = realloc(arr, sizeof(char) * (strlen(arr) + strlen(template) + 2));
    strcat(arr, "|");
    strcat(arr, template);
  }
}

void input_flag(int argc, char **argv, flag *fl) {
  int opt = 0, opt_index = 0;
  struct option long_options[] = {{NULL, 0, NULL, 0}};
  while ((opt = getopt_long(argc, argv, "e:ivcnlhsf:o", long_options,
                            &opt_index)) != -1) {
    switch (opt) {
      case 'e':
        fl->e++;
        concat_template(optarg);
        break;
      case 'i':
        fl->i = 1;
        break;
      case 'v':
        fl->v = 1;
        break;
      case 'c':
        fl->c = 1;
        fl->l = 0;
        fl->o = 0;
        break;
      case 'l':
        if (fl->c == 0) {
          fl->l = 1;
        }
        break;
      case 'n':
        fl->n = 1;
        break;
      case 'h':
        fl->h = 1;
        break;
      case 's':
        fl->s = 1;
        break;
      case 'f':
        fl->f = 1;
        read_flag_f(optarg, argv);
        break;
      case 'o':
        if (fl->l == 0 && fl->c == 0) {
          fl->o = 1;
        }
        break;
      case '?':
        fprintf(stderr, "usage: s21_grep [-eivclnhsfo] template [file_name]\n");
        exit(1);
    }
  }
}

void read_flag_f(char *qaz, char **argv) {
  FILE *fp = NULL;
  char *str = NULL;
  size_t str_size = 0;
  int length = 0;
  fp = fopen(qaz, "r");
  if (fp) {
    while ((length = getline(&str, &str_size, fp)) != -1) {
      if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
      }
      if (*str != '\0') {
        concat_template(str);
      } else {
        concat_template(".");
      }
    }
  } else {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], qaz);
  }
  fclose(fp);
  if (str) {
    free(str);
    str = NULL;
  }
}