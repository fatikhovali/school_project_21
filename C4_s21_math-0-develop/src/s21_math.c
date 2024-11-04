#include "s21_math.h"

int s21_abs(int x) {
  x = (x >= 0) ? x : -x;
  return x;
}

long double s21_fabs(double x) {
  x = (x >= 0) ? x : -x;
  return x;
}

long double s21_ceil(double x) {
  long double res = (long double)x;
  if (((x - (long long)x) != 0) && (x > 0)) {
    res = (long double)((long long)(x + 1));
  } else if ((x - (long long)x) != 0) {
    res = (long double)((long long)x);
  }
  x = res;
  return x;
}

long double s21_floor(double x) {
  long double res = (long double)x;
  if (((x - (long long)x) != 0) && (x < 0)) {
    res = (long double)((long long)(x - 1));
  } else if ((x - (long long)x) != 0) {
    res = (long double)((long long)x);
  }
  x = res;
  return x;
}

long double s21_fmod(double x, double y) {
  long double result = 0.0;
  int flag = 1;
  if (x < 0) flag = -1;
  if (!S21_IS_NAN(x) && !S21_IS_NAN(y) && !(S21_IS_INF(x) && S21_IS_INF(y)) &&
      !(s21_fabs(y) < S21_EPS)) {
    if (s21_fabs(x) < S21_EPS) {
      result = 0.0;
    } else if (S21_IS_INF(y)) {
      result = x;
    } else {
      long double delta_x = x;
      long double delta_y = y;
      long long div = delta_x / delta_y;
      if (flag == -1 && (delta_x - div * delta_y) == 0.0)
        result = -0.0;
      else
        result = delta_x - div * delta_y;
    }
  } else {
    result = S21_NAN;
  }
  return result;
}

long double privedenie_x(double x) {
  return (x > S21_2PI || x < -S21_2PI) ? s21_fmod(x, S21_2PI) : x;
}

long double s21_sin(double x) {
  long double sum;
  if (x == S21_INF || x == -S21_INF) {
    sum = S21_NAN;
  } else {
    x = privedenie_x(x);
    long double teylor = x, i = 1.0;
    sum = x;
    while (s21_fabs(teylor) > S21_EPS) {
      teylor = -1 * teylor * x * x / (2 * i * (2 * i + 1));
      i += 1.0;
      sum += teylor;
    }
  }
  return sum;
}

long double s21_cos(double x) {
  long double sum;
  if (x == S21_INF || x == -S21_INF) {
    sum = S21_NAN;
  } else {
    x = privedenie_x(x);
    long double teylor = 1;
    sum = 1;
    int i = 0;
    while (s21_fabs(teylor) > S21_EPS) {
      teylor = -teylor * x * x / ((i + 1) * (i + 2));
      sum += teylor;
      i += 2;
    }
  }
  return sum;
}

long double s21_tan(double x) {
  long double value;
  if (x == S21_PI / 2)
    value = S21_NAN;
  else
    value = s21_sin(x) / s21_cos(x);
  return value;
}

long double s21_atan(double x) {
  long double y = 0;
  if (x > -1 && x < 1) {
    y = sum_atan(x);
  } else if (x == -1 || x == 1) {
    y = S21_PI / (4 * x);
  } else if (x > 1 || x < -1) {
    y = S21_PI * s21_fabs(x) / (2 * x) - sum_atan(1 / x);
  }
  return y;
}

long double sum_atan(double x) {
  long double teylor = x, sum = x, i = 1.0;
  while (s21_fabs(teylor) > S21_EPS) {
    teylor = -1 * teylor * x * x * (2 * i - 1) / (2 * i + 1);
    i += 1.0;
    sum += teylor;
  }
  return sum;
}

long double s21_asin(double x) {
  long double y = x, sum = x;
  long double i = 1.0;
  while (s21_fabs(sum) > 1e-17) {
    if (x < -1 || x > 1) {
      y = S21_NAN;
      break;
    }
    if (x == 1 || x == -1) {
      y = S21_PI / 2 * x;
      break;
    }
    sum *= x * x * (2 * i - 1) * (2 * i - 1) / ((2 * i + 1) * 2 * i);
    i += 1;
    y += sum;
  }
  return y;
}

long double s21_acos(double x) { return S21_PI / 2.0 - s21_asin(x); }

long double s21_exp(double x) {
  long double res, result;
  int fl = 0, count = 1;
  if (x < 0) {
    fl = 1;
    x = x * (-1);
  }
  for (res = 1, result = 1; s21_fabs(res) > S21_EPS; count++) {
    res = res * x / count;
    result = result + res;
    if (result > S21_MAX) {
      result = S21_INF;
      break;
    }
  }
  if (fl) {
    if (result < S21_MAX) {
      result = 1. / result;
    } else {
      result = 0;
    }
  }
  x = result;
  return x;
}

int num_isnan(double __x) {
  int result = 0;
  if (__x != __x) {
    result = 1;
  }
  return result;
}

long double s21_log(double x) {
  int i = 2;
  long double result = x - 1;
  long double s = result, ten = x;
  if (x < 0) {
    result = S21_NAN;
  } else if (x == S21_INF) {
    result = S21_INF;
  } else if (num_isnan(x) == 1) {
    result = S21_NAN;
  } else if (x == 0.0) {
    result = -S21_INF;
  } else if (x < 2.0 + S21_EPS) {
    x = x - 1;
    while (s21_fabs(s / i) > S21_EPS) {
      s *= -1 * x;
      result += s / i;
      i += 1;
    }
  } else {
    int k = 0;
    while (ten > 1.0) {
      ten /= 10;
      k++;
    }
    result = s21_log(ten) + k * s21_LN10;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result;
  if (exp == 0) {
    result = 1;
  } else if (exp < 0 && base == 0) {
    result = S21_INF;
  } else if (exp == -INFINITY) {
    result = 0;
  } else if (exp == INFINITY) {
    if (base == -1 || base == 1) {
      result = 1;
    } else if (base < 1 && base > -1) {
      result = 0;
    } else {
      result = S21_INF;
    }
  } else {
    if (base < 0) {
      base = -1 * base;
      result = s21_exp(exp * s21_log(base));
      if (s21_fmod(exp, 2) != 0) {
        result = -1 * result;
      }
    } else {
      result = s21_exp(exp * s21_log(base));
    }
  }
  return result;
}

long double s21_sqrt(double x) {
  long double guess = 1.0;
  long double prev;
  if (x < 0) {
    guess = S21_NAN;
  }
  do {
    prev = guess;
    guess = (guess + x / guess) / 2;
  } while (s21_fabs(prev - guess) > 0.0000001);
  return guess;
}
