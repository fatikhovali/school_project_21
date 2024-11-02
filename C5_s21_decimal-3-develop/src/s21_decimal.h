#include <math.h>
#include <stdio.h>
// #include <unistd.h>  // для дебага
#include <limits.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[7];
} s21_decimal_long;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_is_less(s21_decimal v1, s21_decimal v2);
int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_equal(s21_decimal v1, s21_decimal v2);
int s21_is_not_equal(s21_decimal v1, s21_decimal v2);
int s21_is_greater(s21_decimal v1, s21_decimal v2);
int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int inishial(s21_decimal *nomber, int i0, int i1, int i2, int i3);
int inishial_long(s21_decimal_long *nomber, int i0, int i1, int i2, int i3,
                  int i4, int i5, int i6);
void print_bin_decimal(s21_decimal dec);
void print_bin_decimal_long(s21_decimal_long dec);
int get_mashtab(s21_decimal dec);
int get_mashtab_long(s21_decimal_long dec);
int get_bit(s21_decimal dec, int bit);
void set_bit_0(s21_decimal *dec, int bit);
void set_bit_1(s21_decimal *dec, int bit);
int get_bit_long(s21_decimal_long dec, int bit);
void set_bit_0_long(s21_decimal_long *dec, int bit);
void set_bit_1_long(s21_decimal_long *dec, int bit);
int get_sign(s21_decimal dst);
int get_sign_long(s21_decimal_long dst);
int get_exp_in_float(float nom);
void set_accur(s21_decimal *dec, int accur);
void set_accur_long(s21_decimal_long *dec, unsigned int accur);
void set_znak(s21_decimal *dec, unsigned int znak);
void set_znak_long(s21_decimal_long *dec, unsigned int znak);
void zero_decimal(s21_decimal *dst);
void zero_decimal_long(s21_decimal_long *dst);
void print_bit_float(float fl);
int int_add_one_znak(s21_decimal nom1, s21_decimal nom2, s21_decimal *res);
int int_add_one_znak_long(s21_decimal_long nom1, s21_decimal_long nom2,
                          s21_decimal_long *res);
int int_sub(s21_decimal nom1, s21_decimal nom2, s21_decimal *res);
int int_sub_long(s21_decimal_long nom1, s21_decimal_long nom2,
                 s21_decimal_long *res);
s21_decimal int_div(s21_decimal nom1, s21_decimal nom2, s21_decimal *res);
s21_decimal_long int_div_long(s21_decimal_long nom1, s21_decimal_long nom2,
                              s21_decimal_long *res);
int is_less_long(s21_decimal_long v1, s21_decimal_long v2);
int is_less_or_equal_long(s21_decimal_long v1, s21_decimal_long v2);
void copy_decimal(s21_decimal a, s21_decimal *b);
void copy_decimal_long(s21_decimal_long a, s21_decimal_long *b);
void copy_long_in_decimal(s21_decimal_long a, s21_decimal *b);
void copy_decimal_in_long(s21_decimal a, s21_decimal_long *b);
int bits_sdvig(s21_decimal *a, int sdv);
int bits_sdvig_long(s21_decimal_long *a, int sdv);
void normalize_long(s21_decimal_long *a, s21_decimal_long *b);
int kratnost(s21_decimal_long a);
void normalaze_div_long(s21_decimal_long *a, s21_decimal_long *b);
s21_decimal_long int_div_long_int(s21_decimal_long nom1, s21_decimal_long nom2,
                                  s21_decimal_long *res);
int k_vo_razrydov(long long int a);
