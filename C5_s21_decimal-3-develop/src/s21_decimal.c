#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    (*dst).bits[i] = 0;
  }
  (*dst).bits[3] = (src >= 0 ? 0 : 1 << 31);
  (*dst).bits[0] = src >= 0 ? src : (-1) * src;
  return 0;
}

void zero_decimal(s21_decimal *dst) {  // обнуление decimal
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

void zero_decimal_long(s21_decimal_long *dst) {
  for (int i = 0; i < 7; i++) {
    (*dst).bits[i] = 0;
  }
}

int s21_from_float_to_decimal(
    float src, s21_decimal *dst) {  // обрабоатть слишком большие числа
  int error = 0;
  zero_decimal(dst);
  set_znak(dst, src > 0 ? 0 : 1);
  if (src < 0) {
    src *= -1;
  }
  if (src < 1e-28 || src > 7.922816e+28 || fpclassify(src) == 1 || src != src ||
      fpclassify(src) == 0 || !dst) {
    error = 1;
  } else {
    unsigned int nomber = *((unsigned int *)(&src));
    int exp = get_exp_in_float(src);
    int smeshenie =
        0;  // хранить на сколько знаков сдвинули запятую, чтобы число стало иметь \
        хотя бы один разряд в целом
    if (exp > 95) {
      error = 1;
    }
    if (exp < -95) {
      for (; !((int)src); src *= 10, smeshenie++)
        ;
    }
    float normaliz =
        10.0f;  // на нее будем домнажать, чтобы получить в src 7 знаков
    int flag = 1;
    int razr_1 = k_vo_razrydov((long long int)src);
    if ((long long int)src > 9999999) {
      flag = 0;
      normaliz = 0.1f;
    }
    if (flag) {
      for (; (long long int)src < 1000000; smeshenie++, src *= normaliz) {
      }
    }
    if (!flag) {
      for (; (long long int)src > 10000000; src *= normaliz) {
        smeshenie--;
        flag++;
      }
    }
    src = (long long int)(src);
    exp = get_exp_in_float(src);
    set_bit_1(dst, exp);
    nomber = *((unsigned int *)(&src));
    int res = 0;
    for (int i = 22, k = 0x400000; i >= 0; i--, k >>= 1) {
      if (!!(nomber & k)) {
        set_bit_1(dst, exp + i - 23);
      } else {
        set_bit_0(dst, exp + i - 23);
      }
    }
    s21_decimal_long long_res = {0};
    s21_decimal_long del_10 = {0};
    s21_decimal_long ost = {0};
    s21_decimal_long musor = {0};
    del_10.bits[0] = 10;
    copy_decimal_in_long(*dst, &long_res);
    copy_decimal_long(int_div_long_int(long_res, del_10, &musor), &ost);
    while (ost.bits[0] == 0 && smeshenie > 0) {
      copy_decimal_long(musor, &long_res);
      copy_decimal_long(int_div_long_int(long_res, del_10, &musor), &ost);
      smeshenie--;
    }
    copy_long_in_decimal(long_res, dst);
    s21_decimal tmp_10 = {10, 0, 0, 0};
    int razr_2 = k_vo_razrydov((long long int)src);
    while (razr_1 > razr_2) {
      s21_mul(*dst, tmp_10, dst);
      smeshenie++;
      razr_2++;
    }
    set_accur(dst, smeshenie);
    if ((exp < -94) || (smeshenie > 28u)) {
      error = 1;
    }
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = 0;
  int now_bit = 63;  // счетчик, какой бит сейчас рассатриваем
  int bit_in_int = 0;  // количество уже сохраненных бит в dst
  int step = get_mashtab(src);
  if (src.bits[1] >> (step - 1) || src.bits[2]) {
    return 1;
  }
  while (src.bits[now_bit / 32] >> (now_bit % 32) == 0) {
    now_bit--;
  }
  for (now_bit; now_bit >= 0; now_bit--) {
    (*dst) = (*dst) | (src.bits[now_bit / 32] & (1 << (now_bit % 32)));
  }
  *dst /= pow(10, step);
  if (src.bits[3] >> 31) {
    *dst *= -1;
  }
  return 0;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  unsigned int result = 0;
  if (get_bit(src, 127)) {
    result = 1 << 31;
  }
  int i = 96;
  for (; i >= 0 && !get_bit(src, i); i--)
    ;  // ищем первую еденицу, которая не пишется в float
  i--;
  result = result | (i + 1 + 127) << 23;
  for (int k = 22; i >= 0 && k >= 0; i--, k--) {
    result = result | (get_bit(src, i) << k);
  }
  float res_tmp = *(float *)(&result);
  if (get_mashtab(src)) {
    res_tmp = res_tmp / pow(10, get_mashtab(src));
  }
  i = 0;
  while (k_vo_razrydov((long long int)res_tmp) > 7) {
    i++;
    res_tmp /= 10.0;
  }
  if (i > 0) {
    res_tmp = round(res_tmp);
    for (; i > 0; i--) {
      res_tmp *= 10.0;
    }
  }
  (*dst) = res_tmp;
  return error;
}
int inishial(s21_decimal *nomber, int i0, int i1, int i2, int i3) {
  (*nomber).bits[0] = i0;
  (*nomber).bits[1] = i1;
  (*nomber).bits[2] = i2;
  (*nomber).bits[3] = i3;
}

int inishial_long(s21_decimal_long *nomber, int i0, int i1, int i2, int i3,
                  int i4, int i5, int i6) {
  (*nomber).bits[0] = i0;
  (*nomber).bits[1] = i1;
  (*nomber).bits[2] = i2;
  (*nomber).bits[3] = i3;
  (*nomber).bits[4] = i4;
  (*nomber).bits[5] = i5;
  (*nomber).bits[6] = i6;
}

void print_bin_decimal(s21_decimal dec) {
  for (int i = 127; i >= 0; i--) {
    printf("%d", (dec.bits[i / 32] >> i % 32) & (1));
    if ((i - 1) % 32 == 31 && i != 127) {
      // printf("\n");
    }
  }
  printf("\n");
}

void print_bin_decimal_long(s21_decimal_long dec) {
  for (int i = 223; i >= 0; i--) {
    printf("%d", (dec.bits[i / 32] >> i % 32) & (1));
    if ((i - 1) % 32 == 31 && i != 223) {
      // printf("\n");
    }
  }
  printf("\n");
}

int get_mashtab(s21_decimal dec) {
  int res = ((dec.bits[3] >> 16) & 31);
  if (res > 28) {
    res = 0;
  }
  return res;
}
int get_mashtab_long(s21_decimal_long dec) {
  int res = ((dec.bits[6] >> 16) & 31);
  if (res > 28) {
    res = 0;
  }
  return res;
}

int get_bit(s21_decimal dec, int bit) {
  return (dec.bits[bit / 32]) >> (bit % 32) & 1;
}
void set_bit_0(s21_decimal *dec, int bit) {  // счет битов начинается с 0!
  (*dec).bits[bit / 32] = ((*dec).bits[bit / 32]) & (~(1 << (bit % 32)));
}
void set_bit_1(s21_decimal *dec, int bit) {  // счет битов начинается с 0!
  set_bit_0(dec, bit);
  (*dec).bits[bit / 32] = ((*dec).bits[bit / 32]) | ((1 << (bit % 32)));
}

int get_bit_long(s21_decimal_long dec, int bit) {
  return (dec.bits[bit / 32]) >> (bit % 32) & 1;
}
void set_bit_0_long(s21_decimal_long *dec,
                    int bit) {  // счет битов начинается с 0!
  (*dec).bits[bit / 32] = ((*dec).bits[bit / 32]) & (~(1 << (bit % 32)));
}
void set_bit_1_long(s21_decimal_long *dec,
                    int bit) {  // счет битов начинается с 0!
  set_bit_0_long(dec, bit);
  (*dec).bits[bit / 32] = ((*dec).bits[bit / 32]) | ((1 << (bit % 32)));
}

int get_sign(s21_decimal dst) {  // знак
  return !!((dst.bits[3] & (1u << 31)));
}
int get_sign_long(s21_decimal_long dst) {  // знак
  return !!(dst.bits[6] & (1u << 31));
}

int get_exp_in_float(float nom) {
  unsigned int nomber = *((unsigned int *)(&nom));
  return ((nomber >> 23) & 255) - 127;
}

void set_accur(s21_decimal *dec, int accur) {
  if (accur >= 0) {
    (*dec).bits[3] = ((*dec).bits[3]) & (0xFF00FFFF);
    (*dec).bits[3] = (*dec).bits[3] | ((accur) << 16);
  }
}

void set_accur_long(s21_decimal_long *dec, unsigned int accur) {
  (*dec).bits[6] = ((*dec).bits[6]) & (0xFF00FFFF);
  (*dec).bits[6] = (*dec).bits[6] | ((accur) << 16);
}

void set_znak(
    s21_decimal *dec,
    unsigned int znak) {  // znak  =0 если положительное, 1 если отрицательное
  (*dec).bits[3] = ((*dec).bits[3]) & (~(1u << 31));

  if (znak == 1) {
    (*dec).bits[3] = ((*dec).bits[3]) | (1u << 31);
  }
}
void set_znak_long(
    s21_decimal_long *dec,
    unsigned int znak) {  // znak  =0 если положительное, 1 если отрицательное
  (*dec).bits[6] = ((*dec).bits[6]) & (~(1u << 31));
  if (znak == 1) {
    (*dec).bits[6] = ((*dec).bits[6]) | (1u << 31);
  }
}

void print_bit_float(float fl) {
  int int_fl = *(unsigned int *)(&fl);
  for (unsigned i = 0x80000000; i; i >>= 1) {
    printf("%d", !!(i & int_fl));
  }
  printf("\n");
}
int int_add_one_znak(s21_decimal nom1, s21_decimal nom2, s21_decimal *res) {
  (*res).bits[0] = 5;
  int returnn = 0;
  zero_decimal(res);
  s21_decimal_long lres = {0};
  unsigned int dobavok = 0;
  for (int i = 0; i < 96; i++) {
    dobavok += get_bit(nom1, i) + get_bit(nom2, i);
    if ((dobavok % 2)) {
      set_bit_1_long(&lres, i);
    }
    dobavok /= 2;
  }
  if (dobavok) {
    set_bit_1_long(&lres, 96);
    returnn = 1;
  }
  if (!returnn) {
    for (int i = 0; i < 3; i++) {
      (*res).bits[i] = lres.bits[i];
    }
    (*res).bits[3] = nom1.bits[3];
  }
  return returnn;
}

// для идеальных условий
int int_add_one_znak_long(s21_decimal_long nom1, s21_decimal_long nom2,
                          s21_decimal_long *res) {
  int returnn = 0;
  for (int i = 0; i < 7; i++) {
    (*res).bits[i] = 0;
  }
  unsigned int dobavok = 0;
  s21_decimal_long nom_1 = {0};
  s21_decimal_long nom_2 = {0};
  for (int k = 0; k < 7; k++) {
    nom_1.bits[k] = nom1.bits[k];
    nom_2.bits[k] = nom2.bits[k];
  }
  for (int i = 0; i < 192; i++) {
    dobavok += get_bit_long(nom_1, i) + get_bit_long(nom_2, i);
    if ((dobavok % 2)) {
      set_bit_1_long(res, i);
    }
    dobavok /= 2;
  }
  if (dobavok) {
    returnn = 1;
  }
  (*res).bits[6] = nom_1.bits[6];
  return returnn;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result) {  // готова вся
  int error = 0;
  s21_decimal_long long_res = {0};
  s21_decimal_long long_buffer = {
      0};  // хранит число, получившееся после умножения g бита на value_1
  unsigned int mul = 0;  // хранит результат умнодения двух битов на каждом шаге
  if ((!value_1.bits[0] && !value_1.bits[1] && !value_1.bits[2]) ||
      (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2])) {
    zero_decimal(result);
    set_znak(result, get_sign(value_1) ^ get_sign(value_2));
  } else {
    if (value_1.bits[0] == 1 && !value_1.bits[1] && !value_1.bits[2] &&
        !get_sign(value_1)) {
      copy_decimal_in_long(value_2, &long_res);
    } else if (value_2.bits[0] == 1 && !value_2.bits[1] && !value_2.bits[2] &&
               !get_sign(value_2)) {
      copy_decimal_in_long(value_1, &long_res);
    } else if (value_1.bits[0] == 1 && !value_1.bits[1] && !value_1.bits[2] &&
               get_sign(value_1)) {
      copy_decimal_in_long(value_2, &long_res);
    } else if (value_2.bits[0] == 1 && !value_2.bits[1] && !value_2.bits[2] &&
               get_sign(value_2)) {
      copy_decimal_in_long(value_1, &long_res);
    } else {
      for (int g = 0; g < 96; g++) {
        zero_decimal_long(&long_buffer);
        for (int i = 0; i < 96; i++) {
          mul = get_bit(value_1, i) & get_bit(value_2, g);
          if (mul) {
            set_bit_1_long(&long_buffer, g + i);
          }
        }
        if (long_res.bits[5] < 1073741823) {
          int_add_one_znak_long(long_res, long_buffer, &long_res);
        }
      }
    }
    int znak = get_bit(value_1, 127) ^ get_bit(value_2, 127);
    mul = (get_mashtab(value_1) + get_mashtab(value_2));
    while ((long_res.bits[3] || long_res.bits[4] || long_res.bits[5] ||
            mul > 28) &&
           mul > 0) {
      mul--;
      s21_decimal_long tmp_10 = {0};
      s21_decimal_long ost = {0};
      s21_decimal_long musor = {0};
      tmp_10.bits[0] = 10;
      copy_decimal_long(int_div_long_int(long_res, tmp_10, &long_res), &ost);
      if (ost.bits[0] == 5) {
        copy_decimal_long(int_div_long_int(long_res, tmp_10, &musor), &tmp_10);
        if (!kratnost(tmp_10)) {
          s21_decimal_long tmp_1 = {1, 0, 0, 0, 0, 0, 0};
          normalize_long(&tmp_1, &long_res);
          int_add_one_znak_long(long_res, tmp_1, &long_res);
        }
      } else if (ost.bits[0] > 4) {
        s21_decimal_long tmp_1 = {1, 0, 0, 0, 0, 0, 0};
        normalize_long(&tmp_1, &long_res);
        int_add_one_znak_long(long_res, tmp_1, &long_res);
      }
    }
    if (long_res.bits[3] != 0 || long_res.bits[4] != 0 ||
        long_res.bits[5] != 0 || mul < 0 || mul > 29) {
      if (!znak) {
        error = 1;
      } else {
        error = 2;
      }
    } else {
      if (mul <= 28) {
        copy_long_in_decimal(long_res, result);
        set_accur(result, mul);
        set_znak(result, znak);
      } else {
        error = 1;
      }
    }
  }
  return error;
}

int s21_mul_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result) {  // готова вся
  int error = 0;
  s21_decimal_long long_res = {0};
  s21_decimal_long long_buffer = {
      0};  // хранит число, получившееся после умножения g бита на value_1
  unsigned int mul = 0;  // хранит результат умнодения двух битов на каждом шаге
  for (int g = 0; g < 191; g++) {
    zero_decimal_long(&long_buffer);
    for (int i = 0; i < 191; i++) {
      mul = get_bit_long(value_1, i) & get_bit_long(value_2, g);
      if (mul) {
        set_bit_1_long(&long_buffer, g + i);
      }
    }
    int_add_one_znak_long(long_res, long_buffer, &long_res);
  }
  for (int k = 0; k < 6; k++) {
    (*result).bits[k] = long_res.bits[k];
  }
  mul = (get_mashtab_long(value_1) + get_mashtab_long(value_2));
  set_accur_long(result, mul);
  if (get_bit_long(value_1, 223) != get_bit_long(value_2, 223)) {
    set_bit_1_long(result, 223);
  }
  return error;
}

int int_sub(s21_decimal nom1, s21_decimal nom2, s21_decimal *res) {
  int sub_bit = 0;
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  copy_decimal(nom1, &num1);
  copy_decimal(nom2, &num2);
  for (int i = 0; i < 96; i++) {
    sub_bit = get_bit(num1, i) - get_bit(num2, i);
    if (sub_bit > 0) {
      set_bit_1(res, i);
    } else if (!sub_bit) {
      set_bit_0(res, i);
    } else {
      int now_bit = 0;
      int index_now_bit = i + 1;
      while (!get_bit(num1, index_now_bit) && index_now_bit < 96) {
        set_bit_1(&num1, index_now_bit);
        index_now_bit++;
      }
      set_bit_0(&num1, index_now_bit);
      set_bit_1(res, i);
    }
  }
}
// для идеальных условий
int int_sub_long(s21_decimal_long nom1, s21_decimal_long nom2,
                 s21_decimal_long *res) {
  int sub_bit = 0;
  s21_decimal_long num1 = {0};
  s21_decimal_long num2 = {0};
  copy_decimal_long(nom1, &num1);
  copy_decimal_long(nom2, &num2);
  for (int i = 0; i < 192; i++) {
    sub_bit = get_bit_long(num1, i) - get_bit_long(num2, i);
    if (sub_bit > 0) {
      set_bit_1_long(res, i);
    } else if (sub_bit == 0) {
      set_bit_0_long(res, i);
    } else if (sub_bit < 0) {
      int now_bit = 0;
      int index_now_bit = i + 1;
      while (!get_bit_long(num1, index_now_bit)) {
        set_bit_1_long(&num1, index_now_bit);
        index_now_bit++;
      }
      set_bit_0_long(&num1, index_now_bit);
      set_bit_1_long(res, i);
    }
  }
  (*res).bits[6] = num1.bits[6];
}

// для идеальных условий
s21_decimal int_div(s21_decimal nom1, s21_decimal nom2, s21_decimal *res) {
  if (nom2.bits[0] || nom2.bits[1] || nom2.bits[2]) {
    s21_decimal int_chast = {0};
    s21_decimal_long result = {0};
    s21_decimal nom2_copy = {0};
    s21_decimal_long _2_in_step = {
        0};  // будет возводится в степень=количеству \
        сдвигов, чтобы хранить целое число для прибавления к результату
    copy_decimal(nom2, &nom2_copy);
    int znak = get_sign(nom1) ^ get_sign(nom2);
    set_bit_0(&nom1, 127);
    set_bit_0(&nom2, 127);
    while (s21_is_less_or_equal(nom2, nom1)) {
      copy_decimal(nom2, &nom2_copy);
      zero_decimal_long(&_2_in_step);
      _2_in_step.bits[0] = 1;
      while (1) {
        bits_sdvig(&nom2_copy, 1);
        bits_sdvig_long(&_2_in_step, 1);
        if (!s21_is_less_or_equal(nom2_copy, nom1)) {
          bits_sdvig(&nom2_copy, -1);
          bits_sdvig_long(&_2_in_step, -1);
          break;
        }
      }
      int_add_one_znak_long(result, _2_in_step, &result);
      int_sub(nom1, nom2_copy, &nom1);
    }
    if (!result.bits[3] && !result.bits[4] && !result.bits[5]) {
      copy_long_in_decimal(result, res);
    }
    set_znak(res, znak);
  }

  return nom1;
}

s21_decimal_long int_div_long(s21_decimal_long nom1, s21_decimal_long nom2,
                              s21_decimal_long *res) {
  s21_decimal_long int_chast = {0};
  s21_decimal_long result = {0};
  s21_decimal_long nom2_copy = {0};
  s21_decimal_long _2_in_step = {0};  // будет возводится в степень=количеству \
    сдвигов, чтобы хранить целое число для прибавления к результату
  copy_decimal_long(nom2, &nom2_copy);
  int znak = !(get_sign_long(nom1) == get_sign_long(nom2));  // верно
  set_bit_0_long(&nom1, 223);
  set_bit_0_long(&nom2, 223);
  while (is_less_or_equal_long(nom2, nom1)) {
    copy_decimal_long(nom2, &nom2_copy);
    zero_decimal_long(&_2_in_step);
    _2_in_step.bits[0] = 1;
    while (1) {
      bits_sdvig_long(&nom2_copy, 1);
      bits_sdvig_long(&_2_in_step, 1);
      if (!is_less_or_equal_long(nom2_copy, nom1)) {
        bits_sdvig_long(&nom2_copy, -1);
        bits_sdvig_long(&_2_in_step, -1);
        break;
      }
    }
    int_add_one_znak_long(result, _2_in_step, &result);
    int_sub_long(nom1, nom2_copy, &nom1);
  }
  copy_decimal_long(result, res);
  set_znak_long(res, znak);
  return nom1;
}

// копия, целочисленное деление
s21_decimal_long int_div_long_int(s21_decimal_long nom1, s21_decimal_long nom2,
                                  s21_decimal_long *res) {
  s21_decimal_long int_chast = {0};
  s21_decimal_long result = {0};
  s21_decimal_long nom2_copy = {0};
  s21_decimal_long _2_in_step = {0};  // будет возводится в степень=количеству \
    сдвигов, чтобы хранить целое число для прибавления к результату
  copy_decimal_long(nom2, &nom2_copy);
  int znak = !(get_sign_long(nom1) == get_sign_long(nom2));  // верно
  nom1.bits[6] = 0;
  nom2.bits[6] = 0;
  while (is_less_or_equal_long(nom2, nom1)) {
    copy_decimal_long(nom2, &nom2_copy);
    zero_decimal_long(&_2_in_step);
    _2_in_step.bits[0] = 1;
    while (1) {
      bits_sdvig_long(&nom2_copy, 1);
      bits_sdvig_long(&_2_in_step, 1);
      if (!is_less_or_equal_long(nom2_copy, nom1)) {
        bits_sdvig_long(&nom2_copy, -1);
        bits_sdvig_long(&_2_in_step, -1);
        break;
      }
    }
    int_add_one_znak_long(result, _2_in_step, &result);
    int_sub_long(nom1, nom2_copy, &nom1);
  }
  copy_decimal_long(result, res);
  set_znak_long(res, znak);
  return nom1;
}

void copy_decimal(s21_decimal a, s21_decimal *b) {
  for (int i = 0; i < 4; i++) {
    (*b).bits[i] = a.bits[i];
  }
}

void copy_decimal_long(s21_decimal_long a, s21_decimal_long *b) {
  for (int i = 0; i < 7; i++) {
    (*b).bits[i] = a.bits[i];
  }
}

void copy_long_in_decimal(s21_decimal_long a, s21_decimal *b) {
  for (int i = 0; i < 3; i++) {
    (*b).bits[i] = a.bits[i];
  }
  (*b).bits[3] = a.bits[6];
}

void copy_decimal_in_long(s21_decimal a, s21_decimal_long *b) {
  for (int i = 0; i < 3; i++) {
    (*b).bits[i] = a.bits[i];
  }
  (*b).bits[6] = a.bits[3];
}

int bits_sdvig(s21_decimal *a, int sdv) {  // делает >>
  int error = 0;
  if (sdv == -1) {
    for (int i = 0; i < 95; i++) {
      if (get_bit(*a, i + 1)) {
        set_bit_1(a, i);
      } else {
        set_bit_0(a, i);
      }
    }
    set_bit_0(a, 95);
  } else if (!get_bit(*a, 95)) {
    for (int i = 95; i > 0; i--) {
      if (get_bit(*a, i - 1)) {
        set_bit_1(a, i);
      } else {
        set_bit_0(a, i);
      }
    }
    set_bit_0(a, 0);
  } else {
    error = 1;
  }
  return error;
}

int bits_sdvig_long(s21_decimal_long *a, int sdv) {  // делает >> / <<
  int error = 0;
  if (sdv == -1) {
    for (int i = 0; i < 191; i++) {
      if (get_bit_long(*a, i + 1)) {
        set_bit_1_long(a, i);
      } else {
        set_bit_0_long(a, i);
      }
    }
    set_bit_0_long(a, 191);
  } else if (!get_bit_long(*a, 191)) {
    for (int i = 191; i > 0; i--) {
      if (get_bit_long(*a, i - 1)) {
        set_bit_1_long(a, i);
      } else {
        set_bit_0_long(a, i);
      }
    }
    set_bit_0_long(a, 0);
  } else {
    error = 1;
  }
  return error;
}

int is_less_or_equal_long(s21_decimal_long v1, s21_decimal_long v2) {
  int result = is_less_long(v1, v2);
  if (!result) {
    result = 1;
    s21_decimal_long val_1 = {0};
    s21_decimal_long val_2 = {0};
    copy_decimal_long(v1, &val_1);
    copy_decimal_long(v2, &val_2);
    normalize_long(&val_1, &val_2);
    for (int i = 0; i < 7; i++) {
      if (val_1.bits[i] != val_2.bits[i]) {
        result = 0;
      }
    }
  }
  return result;
}

// сравнения
int s21_is_less(s21_decimal v1, s21_decimal v2) {
  int exit = 0;
  int res = s21_is_equal(v1, v2);
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  copy_decimal_in_long(v1, &val_1);
  copy_decimal_in_long(v2, &val_2);
  normalize_long(&val_1, &val_2);
  if (!res) {
    if (get_bit_long(val_1, 223) == 1 && get_bit_long(val_2, 223) == 0) {
      res = 1;
      exit = 1;
    }
    if (get_bit_long(val_1, 223) == get_bit_long(val_2, 223)) {
      for (int i = 191; i >= 0 && !exit; i--) {
        if (get_bit_long(val_1, i) == 1 && get_bit_long(val_2, i) == 0) {
          res = 0;
          exit = 1;
        }
        if (get_bit_long(val_1, i) == 0 && get_bit_long(val_2, i) == 1) {
          res = 1;
          exit = 1;
        }
      }
      if (get_sign_long(val_1)) {
        res = !res;
      }
    }
  } else {
    res = 0;
  }
  return res;
}

int is_less_long(s21_decimal_long v1, s21_decimal_long v2) {
  int exit = 0;
  int res = 1;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  copy_decimal_long(v1, &val_1);
  copy_decimal_long(v2, &val_2);
  normalize_long(&val_1, &val_2);
  if (get_bit_long(val_1, 223) == 1 && get_bit_long(val_2, 223) == 0) {
    res = 1;
    exit = 1;
  }
  if (get_bit_long(val_1, 223) == get_bit_long(val_2, 223)) {
    for (int i = 191; i >= 0 && !exit; i--) {
      if (get_bit_long(val_1, i) == 1 && get_bit_long(val_2, i) == 0) {
        res = 0;
        exit = 1;
      }
      if (get_bit_long(val_1, i) == 0 && get_bit_long(val_2, i) == 1) {
        res = 1;
        exit = 1;
      }
    }
    if (get_sign_long(val_1)) {
      res = !res;
    }
  }
  return res;
}

int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2) {
  int result = s21_is_less(v1, v2);
  if (!result) {
    result = 1;
    s21_decimal_long val_1 = {0};
    s21_decimal_long val_2 = {0};
    copy_decimal_in_long(v1, &val_1);
    copy_decimal_in_long(v2, &val_2);
    normalize_long(&val_1, &val_2);
    for (int i = 0; i < 7; i++) {
      if (val_1.bits[i] != val_2.bits[i]) {
        result = 0;
      }
    }
  }
  return result;
}

int s21_is_greater(s21_decimal v1, s21_decimal v2) {
  int res = s21_is_less_or_equal(v1, v2);
  return !res;
}

int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2) {
  int res = s21_is_greater(v1, v2);
  if (!res) {
    res = s21_is_equal(v1, v2);
  }
  return res;
}

int s21_is_equal(s21_decimal v1, s21_decimal v2) {
  int res = 1;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  copy_decimal_in_long(v1, &val_1);
  copy_decimal_in_long(v2, &val_2);
  normalize_long(&val_1, &val_2);
  if (get_sign(v1) != get_sign(v2)) {
    res = 0;
  } else {
    for (int i = 0; i < 7; i++) {
      if (val_1.bits[i] != val_2.bits[i]) {
        res = 0;
      }
    }
  }
  return res;
}

int s21_is_not_equal(s21_decimal v1, s21_decimal v2) {
  return !s21_is_equal(v1, v2);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_decimal_long res = {0};
  copy_decimal_in_long(value_1, &val_1);
  copy_decimal_in_long(value_2, &val_2);
  normalize_long(&val_1, &val_2);
  if (get_bit_long(val_1, 223) == get_bit_long(val_2, 223)) {
    int_add_one_znak_long(val_1, val_2, &res);
    if (get_bit_long(val_1, 223)) {
      set_bit_1_long(&res, 223);
    } else {
      set_bit_0_long(&res, 223);
    }
    set_accur_long(&res, get_mashtab_long(val_1));
    int znak = get_sign_long(res);
    int smeshenie = get_mashtab_long(res);
    while (res.bits[3] || res.bits[4] || res.bits[5]) {
      smeshenie--;
      s21_decimal_long tmp_10 = {0};
      s21_decimal_long ost = {0};
      s21_decimal_long musor = {0};
      tmp_10.bits[0] = 10;
      copy_decimal_long(int_div_long_int(res, tmp_10, &res), &ost);
      if (ost.bits[0] > 4) {
        copy_decimal_long(int_div_long_int(res, tmp_10, &musor), &tmp_10);
        if (!kratnost(tmp_10)) {
          s21_decimal_long tmp_1 = {1, 0, 0, 0, 0, 0, 0};
          normalize_long(&tmp_1, &res);
          int_add_one_znak_long(res, tmp_1, &res);
        }
      }
    }
    if (!res.bits[3] && !res.bits[4] && !res.bits[5] && smeshenie >= 0 &&
        smeshenie < 29) {
      copy_long_in_decimal(res, result);
      set_accur(result, smeshenie);
    } else if (znak) {
      error = 2;
    } else {
      error = 1;
    }
  } else {
    int znak = get_bit(value_1, 127);
    if (!znak) {
      znak = 2;
    }
    int znak_1 = get_sign(value_1);
    int znak_2 = get_sign(value_2);
    set_bit_0(&value_1, 127);
    set_bit_0(&value_2, 127);
    if (s21_is_less(value_2, value_1) && znak == 2) {
      znak = 0;
    } else {
      znak = 1;
    }
    if (s21_is_less_or_equal(value_2, value_1)) {
      error = s21_sub(value_1, value_2, result);
    } else {
      error = s21_sub(value_2, value_1, result);
      znak_1 = znak_2;
    }
    if (znak_1) {
      set_bit_1(result, 127);
    }
  }
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_decimal_long res = {0};
  int znak_1 = get_sign(value_1);
  int znak_2 = get_sign(value_2);
  set_bit_0(&value_1, 127);
  set_bit_0(&value_2, 127);
  copy_decimal_in_long(value_1, &val_1);
  copy_decimal_in_long(value_2, &val_2);
  int smeshenie = 0;
  if (znak_1 != znak_2) {
    normalize_long(&val_1, &val_2);
    int_add_one_znak_long(val_1, val_2, &res);
    if (get_bit_long(val_1, 223)) {
      set_bit_1_long(&res, 223);
    } else {
      set_bit_0_long(&res, 223);
    }
    set_accur_long(&res, get_mashtab_long(val_1));
    int znak = get_sign_long(res);
    smeshenie = get_mashtab_long(res);

  } else {
    if (!s21_is_less_or_equal(value_2, value_1)) {
      copy_decimal_in_long(value_2, &val_1);
      copy_decimal_in_long(value_1, &val_2);
      znak_1 = !znak_2;  //  znak_1 будет показателем знака для результата
    }
    normalize_long(&val_1, &val_2);
    int_sub_long(val_1, val_2, &res);
    set_znak_long(&res, znak_1);
    smeshenie = get_mashtab_long(res);
  }
  while (res.bits[3] || res.bits[4] || res.bits[5]) {
    smeshenie--;
    s21_decimal_long tmp_10 = {0};
    s21_decimal_long ost = {0};
    s21_decimal_long musor = {0};
    tmp_10.bits[0] = 10;
    copy_decimal_long(int_div_long_int(res, tmp_10, &res), &ost);
    if (ost.bits[0] > 4) {
      copy_decimal_long(int_div_long_int(res, tmp_10, &musor), &tmp_10);
      if (!kratnost(tmp_10)) {
        s21_decimal_long tmp_1 = {1, 0, 0, 0, 0, 0, 0};
        normalize_long(&tmp_1, &res);
        int_add_one_znak_long(res, tmp_1, &res);
      }
    }
  }
  if (!res.bits[3] && !res.bits[4] && !res.bits[5] && smeshenie >= 0 &&
      smeshenie < 29) {
    copy_long_in_decimal(res, result);
    set_accur(result, smeshenie);
    int i = -1;
    int accur = get_mashtab(*result);
    set_accur(result, accur);
    set_znak(result, znak_1);
  } else if (znak_1) {
    error = 2;
  } else {
    error = 1;
  }
  return error;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_decimal_long res = {0};
  copy_decimal_in_long(value_1, &val_1);
  copy_decimal_in_long(value_2, &val_2);
  int accur_1 = get_mashtab(value_1);
  int accur_2 = get_mashtab(value_2);
  int znak = get_sign(value_1) ^ get_sign(value_2);
  s21_decimal_long val_1_10 = {0};
  s21_decimal_long tmp_10 = {10, 0, 0, 0, 0, 0, 0};
  s21_decimal_long nom_10 = {0};
  val_1.bits[6] = 0;
  copy_decimal_long(val_1, &val_1_10);
  s21_mul_long(val_1_10, tmp_10, &val_1_10);
  for (; error < 6; error++) {
    if (val_2.bits[error]) {
      break;
    }
  }
  if (error < 6) {
    while (val_1_10.bits[5] < 134217727) {
      copy_decimal_long(val_1_10, &val_1);
      s21_mul_long(val_1_10, tmp_10, &val_1_10);
      accur_1++;
    }
    set_accur_long(&val_1, 0);
    set_accur_long(&val_2, 0);
    int smeshenie = (-1) * accur_1 + accur_2;
    if (smeshenie < 0) {
      smeshenie *= -1;
    }
    error = 0;
    copy_decimal_long(int_div_long(val_1, val_2, &res), &val_1);
    inishial_long(&tmp_10, 10, 0, 0, 0, 0, 0, 0);
    while (!res.bits[3] && !res.bits[4] && !res.bits[5]) {
      s21_mul_long(val_1, tmp_10, &val_1);
      s21_mul_long(res, tmp_10, &res);
      inishial_long(&tmp_10, 0, 0, 0, 0, 0, 0, 0);
      copy_decimal_long(int_div_long(val_1, val_2, &tmp_10), &val_1);
      int_add_one_znak_long(res, tmp_10, &res);
      inishial_long(&tmp_10, 10, 0, 0, 0, 0, 0, 0);
      smeshenie += 1;
    }
    inishial_long(&tmp_10, 10, 0, 0, 0, 0, 0, 0);
    inishial_long(&val_1, 0, 0, 0, 0, 0, 0, 0);
    while (res.bits[3] || res.bits[4] || res.bits[5] || smeshenie > 28) {
      smeshenie--;
      copy_decimal_long(int_div_long(res, tmp_10, &res),
                        &val_1);  // результат пишет в nom_10 чтобыв не
                                  // использовать новую переменную
    }
    inishial_long(&nom_10, 1, 0, 0, 0, 0, 0, 0);
    if (val_1.bits[0] > 4) {
      int_add_one_znak_long(res, nom_10, &res);
    }
    inishial_long(&nom_10, 0, 0, 0, 0, 0, 0, 0);
    copy_decimal_long(res, &nom_10);
    copy_decimal_long(int_div_long(nom_10, tmp_10, &nom_10),
                      &val_1);  // результат пишет в nom_10 чтобыв не
                                // использовать новую переменную
    while (!val_1.bits[0] && !val_1.bits[1] && !val_1.bits[2] &&
           !val_1.bits[3] && !val_1.bits[4] && !val_1.bits[5] &&
           smeshenie > 0) {
      copy_decimal_long(nom_10, &res);
      smeshenie--;
      copy_decimal_long(int_div_long(nom_10, tmp_10, &nom_10),
                        &val_1);  // результат пишет в nom_10 чтобыв не
                                  // использовать новую переменную
    }
    if (!res.bits[3] && !res.bits[4] && !res.bits[5] && smeshenie >= 0 &&
        smeshenie < 29) {
      copy_long_in_decimal(res, result);
      set_accur(result, smeshenie);
      set_znak(result, znak);
    } else if (znak) {
      error = 2;
    } else {
      error = 1;
    }
  } else {
    error = 3;
  }
  return error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_long tmp = {0};
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_decimal_long res = {0};
  int znak = get_sign(value_1);
  if (value_1.bits[0] == 1 && !value_1.bits[1] && !value_1.bits) {
    if (get_sign(value_1)) {
      s21_negate(value_2, result);
    } else {
      copy_decimal(value_2, result);
    }
  } else if (value_2.bits[0] == 1 && !value_2.bits[1] && !value_2.bits) {
    if (get_sign(value_2)) {
      s21_negate(value_1, result);
    } else {
      copy_decimal(value_1, result);
    }
  } else if (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2]) {
    error = 3;
  } else {
    set_bit_0(&value_1, 127);
    set_bit_0(&value_2, 127);
    if (s21_is_less(value_2, value_1)) {
      copy_decimal_in_long(value_1, &val_1);
      copy_decimal_in_long(value_2, &val_2);
      normalize_long(&val_1, &val_2);
      copy_decimal_long(int_div_long_int(val_1, val_2, &tmp), &res);
      int accur = get_mashtab(value_2) - get_mashtab(value_1);
      if (get_mashtab(value_2) > get_mashtab(value_1)) {
        accur = get_mashtab(value_2);
      } else {
        accur = get_mashtab(value_1);
      }
      set_accur_long(&res, accur);
      set_znak_long(&res, znak);
      copy_long_in_decimal(res, result);
    } else if (s21_is_equal(value_1, value_2)) {
      inishial(result, 0, 0, 0, 0);
      set_znak(result, znak);
    } else {
      copy_decimal(value_1, result);
      set_znak(result, znak);
    }
  }
  return error;
}

void normalize_long(s21_decimal_long *a, s21_decimal_long *b) {
  int accur_1 = get_mashtab_long(*a);
  int accur_2 = get_mashtab_long(*b);
  int razn_accur = accur_1 - accur_2;
  s21_decimal_long int_10 = {0};
  int_10.bits[0] = 10;
  if (razn_accur > 0) {
    for (int i = 0; i < razn_accur; i++) {
      s21_mul_long(*b, int_10, b);
    }
    set_accur_long(b, accur_1);
  }
  if (razn_accur < 0) {
    for (int i = 0; i < (-1) * razn_accur; i++) {
      s21_mul_long(*a, int_10, a);
    }
    set_accur_long(a, accur_2);
  }
}

int kratnost(s21_decimal_long a) {  //  return 0-false, 1-true;
  s21_decimal_long tmp_2 = {
      2, 0, 0, 0, 0, 0,
  };
  s21_decimal_long ost = {0};
  copy_decimal_long(a, &ost);
  normalize_long(&tmp_2, &ost);
  copy_decimal_long(int_div_long(ost, tmp_2, &ost), &ost);
  int i = 0;
  for (; i < 6; i++) {
    if (ost.bits[i] != 0) {
      break;
    }
  }
  if (i < 5) {
    i = 0;
  } else {
    i = 1;
  }
  return i;
}

void normalaze_div_long(s21_decimal_long *a, s21_decimal_long *b) {
  int accur_1 = get_mashtab_long(*a);
  int accur_2 = get_mashtab_long(*b);
  int znak_1 = get_sign_long(*a);
  int znak_2 = get_sign_long(*b);
  (*a).bits[6] = 0;
  (*b).bits[6] = 0;
  s21_decimal_long tmp_10 = {10, 0, 0, 0, 0, 0, 0};
  while (is_less_long(*a, *b)) {
    s21_mul_long(*a, tmp_10, a);
    accur_1++;
  }
  set_accur_long(a, accur_1);
  set_accur_long(b, accur_2);
  set_znak_long(a, znak_1);
  set_znak_long(b, znak_2);
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = !get_sign(value);
  copy_decimal(value, result);
  set_znak(result, error);
  error = 0;
  return error;
}

int k_vo_razrydov(long long int a) {
  int res = 0;
  if (a < 0) {
    a *= -1;
  }
  while (a > 0) {
    res++;
    a /= 10;
  }
  return res;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (value.bits[0] || value.bits[1] || value.bits[2]) {
    int znak = get_sign(value);
    s21_truncate(value, result);
    if (get_sign(value) && get_mashtab(value) > 0) {
      s21_decimal tmp_1 = {1, 0, 0, 0};
      int_add_one_znak(*result, tmp_1, result);
    }
    set_znak(result, znak);
    error = 0;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  copy_decimal(value, result);
  if (value.bits[0] || value.bits[1] || value.bits[2]) {
    error = get_mashtab(value) - 1;
    if (error + 1 > 0) {
      s21_decimal tmp_10 = {10, 0, 0, 0};
      s21_decimal ost = {0};
      int znak = get_sign(value);
      value.bits[3] = 0;
      while (error--) {
        int_div(value, tmp_10, &value);
      }
      copy_decimal(int_div(value, tmp_10, result), &ost);
      if (ost.bits[0] > 4) {
        inishial(&tmp_10, 1, 0, 0, 0);
        int_add_one_znak(*result, tmp_10, result);
      }
      set_accur(result, 0);
      set_znak(result, znak);
    }
    error = 0;
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  copy_decimal(value, result);
  if (value.bits[0] || value.bits[1] || value.bits[2]) {
    error = get_mashtab(value) - 1;
    int znak = get_sign(value);
    if (error + 1 > 0) {
      s21_decimal tmp_10 = {10, 0, 0, 0};
      value.bits[3] = 0;
      while (error--) {
        int_div(value, tmp_10, &value);
      }
      int_div(value, tmp_10, result);
      set_accur(result, 0);
    } else {
    }
    set_znak(result, znak);
    error = 0;
  }
  return error;
}