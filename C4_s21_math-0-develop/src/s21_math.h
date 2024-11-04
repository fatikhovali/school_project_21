#ifndef S21_MATH_H_
#define S21_MATH_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0
#define S21_EPS 1e-17
#define S21_PI 3.1415926535897932384626433833
#define S21_2PI 6.2831853071795864769
#define S21_MAX 1.7976931348623158e308
#define S21_EXP 2.7182818284590452353602874713526624
#define S21_IS_NAN(x) __builtin_isnan(x)
#define S21_IS_INF(x) __builtin_isinf_sign(x)
#define s21_LN10 2.30258509299404590109

int s21_abs(int x);
int num_isnan(double __X);
long double s21_ceil(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double privedenie_x(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double sum_atan(double x);
long double s21_acos(double x);
long double s21_fabs(double x);
long double s21_sqrt(double x);
long double s21_pow(double base, double exp);
long double s21_exp(double x);
long double s21_log(double x);

#endif  // S21_MATH_H_
