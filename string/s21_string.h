#ifndef SRC_S21_STRING_H
#define SRC_S21_STRING_H

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

/*
    (#s21_string) This is the unsigned integral type and is the result of the
   sizeof keyword.
*/
typedef long unsigned int s21_size_t;
#define s21_NULL (void *)0
#include "s21_sprintf.h"
//#include "s21_sscanf.h"

#define BUFF_SIZE 512


/*
    (#s21_string) This macro is the value of a null pointer constant.
*/
#define S21_NULL ((void *)0)

/*
   (#s21_string) Searches for the first occurrence of the character c (an
   unsigned char) in the first n bytes of the string pointed to, by the argument
   str.
*/
void *s21_memchr(const void *str, int c, s21_size_t n);

/*
   (#s21_string) Compares the first n bytes of str1 and str2.
*/
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

/*
   (#s21_string) Copies n characters from src to dest.
*/
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

/*
   (#s21_string) Another function to copy n characters from src to dest.
*/
void *s21_memmove(void *dest, const void *src, s21_size_t n);

/*
   (#s21_string) Copies the character c (an unsigned char) to the first n
   characters of the string pointed to, by the argument str.
*/
void *s21_memset(void *str, int c, s21_size_t n);

/*
   (#s21_string) Appends the string pointed to, by src to the end of the string
   pointed to by dest.
*/
char *s21_strcat(char *dest, const char *src);

/*
   (#s21_string) Appends the string pointed to, by src to the end of the string
   pointed to, by dest up to n characters long.
*/
char *s21_strncat(char *dest, const char *src, s21_size_t n);

/*
   (#s21_string) Searches for the first occurrence of the character c (an
   unsigned char) in the string pointed to, by the argument str.
*/
char *s21_strchr(const char *str, int c);

/*
   (#s21_string) Compares the string pointed to, by str1 to the string pointed
   to by str2.
*/
int s21_strcmp(const char *str1, const char *str2);

/*
   (#s21_string) Compares at most the first n bytes of str1 and str2.
*/
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

/*
   (#s21_string) Copies the string pointed to, by src to dest.
*/
char *s21_strcpy(char *dest, const char *src);

/*
   (#s21_string) Copies up to n characters from the string pointed to, by src to
   dest.
*/
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

/*
   (#s21_string) Calculates the length of the initial segment of str1 which
   consists entirely of characters not in str2.
*/
s21_size_t s21_strcspn(const char *str1, const char *str2);

/*
   (#s21_string) Searches an internal array for the error number errnum and
   returns a pointer to an error message string. You need to declare macros
   containing arrays of error messages for mac and linux operating systems.
   Error descriptions are available in the original library. Checking the
   current OS is carried out using directives.
*/
char *s21_strerror(int errnum);

/*
   (#s21_string) Computes the length of the string str up to but not including
   the terminating null character.
*/
s21_size_t s21_strlen(const char *str);

/*
   (#s21_string) Finds the first character in the string str1 that matches any
   character specified in str2.
*/
char *s21_strpbrk(const char *str1, const char *str2);

/*
   (#s21_string) Searches for the last occurrence of the character c (an
   unsigned char) in the string pointed to by the argument str.
*/
char *s21_strrchr(const char *str, int c);

/*
   (#s21_string) Calculates the length of the initial segment of str1 which
   consists entirely of characters in str2.
*/
s21_size_t s21_strspn(const char *str1, const char *str2);

/*
   (#s21_string) Finds the first occurrence of the entire string needle (not
   including the terminating null character) which appears in the string
   haystack.
*/
char *s21_strstr(const char *haystack, const char *needle);

/*
   (#s21_string) Breaks string str into a series of tokens separated by delim.
*/
char *s21_strtok(char *str, const char *delim);

/*
   (#s21_string) Reads formatted input from a string.
*/
int s21_sscanf(const char *str, const char *format, ...);

/*
   (#s21_string) Sends formatted output to a string pointed to, by str.
*/
int s21_sprintf(char *str, const char *format, ...);

/*
   (#s21_string) Returns a copy of string (str) converted to uppercase. In case
   of any error, return NULL
*/
void *s21_to_upper(const char *str);

/*
   (#s21_string) Returns a copy of string (str) converted to lowercase. In case
   of any error, return NULL
*/
void *s21_to_lower(const char *str);

/*
   (#s21_string) Returns a new string in which a specified string (str) is
   inserted at a specified index position (start_index) in the given string
   (src). In case of any error, return NULL
*/
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

/*
   (#s21_string) Returns a new string in which all leading and trailing
   occurrences of a set of specified characters (trim_chars) from the given
   string (src) are removed. In case of any error, return NULL
*/
void *s21_trim(const char *src, const char *trim_chars);

int s21_includes_exponent(const char *buffer);
long double s21_atof(const char *buffer);
long double s21_apply_exponent(long double res, const char *buffer);
int s21_case_insens_search(const char *buff, const char *pat);
int s21_includes_inf_nan(const char *buffer);
long double s21_return_nan_inf(const char *buffer);

unsigned long long int s21_strntollu(const char *string, char **endptr,
                                     int basis, int n_byte);

long double s21_strtold(const char *buffer);

int s21_atoi(const char *str);
int s21_antoi(const char *str, s21_size_t n);
long double s21_strtold(const char *buffer);

int s21_isdigit(char c);

#endif  // SRC_S21_STRING_H
