#include <check.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "s21_sprintf.h"
#include "s21_string.h"

//#define BUFF_SIZE 4096

START_TEST(s21_memset_test) {
  char src1[15] = "1234567890";
  char src2[11] = "123";
  char n = '1';
  char w = 'w';
  char src3[3] = {0};
  char *res1 = NULL, *res2 = NULL;

  res1 = (char *)s21_memset(src1, n, 11);
  res2 = (char *)memset(src1, n, 11);
  ck_assert_str_eq(res1, res2);

  res1 = (char *)s21_memset(src2, '\0', 2);
  res2 = (char *)memset(src2, '\0', 2);
  ck_assert_str_eq(res1, res2);

  res1 = (char *)s21_memset(src3, w, 2);
  res2 = (char *)memset(src3, w, 2);
  ck_assert_str_eq(res1, res2);
}
END_TEST
START_TEST(s21_memcmp_test) {
  char str11[100] = "12345", str12[100] = "776832768178",
       str13[100] = "-1213002%s", str14[100] = "999010s";
  char str21[100] = "12345", str23[100] = "-1213002%s",
       str24[100] = "99901asdass", str1[100] = "123456789", str2[10] = "2",
       str31[150] = "12345679088123456789123456789012345", str32[150] = " ";
  ck_assert_int_eq(s21_memcmp(str11, str21, 5), memcmp(str11, str21, 5));
  ck_assert_int_eq(s21_memcmp(str13, str23, 5), memcmp(str13, str23, 5));
  ck_assert_int_eq(s21_memcmp(str14, str24, 5), memcmp(str14, str24, 5));
  ck_assert_int_eq(s21_memcmp(str12, str24, 5), memcmp(str12, str24, 5));
  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
  ck_assert_int_eq(s21_memcmp(str31, str32, 10), memcmp(str31, str32, 10));
  ck_assert_int_eq(s21_memcmp(str32, str31, 10), memcmp(str32, str31, 10));
  ck_assert_int_eq(s21_memcmp(str31, str32, 0), memcmp(str31, str32, 0));

  // 3 function
}
END_TEST
START_TEST(s21_memcpy_test) {
  // ++
  char str11[100] = "1234", str12[100] = "776832768178",
       str13[100] = "-1213002%s", str14[100] = "";
  char str21[100] = "1234", str22[100] = "776hgcx1", str23[100] = "-1213002%s",
       str24[100] = "", str31[100] = "12345679088123456789123456789012345";
  ck_assert_str_eq(s21_memcpy(str11, str21, 5), memcpy(str11, str21, 5));
  ck_assert_str_eq(s21_memcpy(str12, str22, 5), memcpy(str12, str22, 5));
  ck_assert_str_eq(s21_memcpy(str13, str23, 5), memcpy(str13, str23, 5));
  ck_assert_str_eq(s21_memcpy(str14, str24, 5), memcpy(str14, str24, 5));
  ck_assert_str_eq(s21_memcpy(str12, str24, 5), memcpy(str12, str24, 5));
  ck_assert_str_eq(s21_memcpy(str12, str24, 5), memcpy(str12, str24, 5));
  ck_assert_str_eq(s21_memcpy(str31, str24, 0), memcpy(str31, str24, 0));
}
END_TEST
START_TEST(s21_strcmp_test) {
  char str11[100] = "1234", str13[100] = "-1213002%s", str14[100] = "999010s",
       str15[1000] = "99901212423154252521552315213512352352423423hhhh",
       str16[100] = " ";
  char str21[100] = "1234", str23[100] = "-1213002%s",
       str24[100] = "99901lkjlk",
       str25[1000] = "99901212423154252521552315213512352352423423hhhh";
  ck_assert_int_eq(s21_strcmp(str11, str21), strcmp(str11, str21));
  ck_assert_int_eq(s21_strcmp(str13, str23), strcmp(str13, str23));
  ck_assert_int_eq(s21_strcmp(str14, str24), strcmp(str14, str24));
  ck_assert_int_eq(s21_strcmp(str11, str21), strcmp(str11, str21));
  ck_assert_int_eq(s21_strcmp(str11, str11), strcmp(str11, str11));
  ck_assert_int_eq(s21_strcmp(str15, str25), strcmp(str15, str25));
  ck_assert_int_eq(s21_strcmp(str15, str16), strcmp(str15, str16));
}
END_TEST
START_TEST(s21_strcpy_test) {
  char str11[100] = "1234", str12[100] = "776832768178",
       str13[100] = "-1213002%s", str14[100] = "";
  char str21[100] = "1234", str22[100] = "776vfcxx1", str23[100] = "-1213002%s",
       str24[100] = "";
  char str111[100] = "1234", str121[100] = "776832768178",
       str131[100] = "-1213002%s", str141[100] = "";
  char str211[100] = "1234", str221[100] = "776vfcxx1",
       str231[100] = "-1213002%s", str241[100] = "";
  ck_assert_str_eq(s21_strcpy(str11, str21), strcpy(str111, str211));
  ck_assert_str_eq(s21_strcpy(str12, str22), strcpy(str121, str221));
  ck_assert_str_eq(s21_strcpy(str13, str23), strcpy(str131, str231));
  ck_assert_str_eq(s21_strcpy(str14, str24), strcpy(str141, str241));
  ck_assert_str_eq(s21_strcpy(str12, str23), strcpy(str121, str231));
}
END_TEST
START_TEST(s21_strncmp_test) {
  // ++
  char str11[100] = "1234", str12[100] = "776832768178",
       str13[100] = "-1213002%s", str14[100] = "999010s";
  char str21[100] = "1234", str22[100] = "776vfcxx1", str23[100] = "-1213002%s",
       str24[100] = "99901lkjlk";
  ck_assert_int_eq(s21_strncmp(str11, str21, 5), strncmp(str11, str21, 5));
  ck_assert_int_eq(s21_strncmp(str12, str22, 5), strncmp(str12, str22, 5));
  ck_assert_int_eq(s21_strncmp(str13, str23, 100), strncmp(str13, str23, 50));
  ck_assert_int_eq(s21_strncmp(str14, str24, 5), strncmp(str14, str24, 5));
  ck_assert_int_eq(s21_strncmp(str11, str21, 0), strncmp(str11, str21, 0));

  // 11's function
}
END_TEST
START_TEST(s21_strcat_test) {
  char src1[10] = "Frf";
  char src2[4] = "Gtg";
  char src3[4] = "";
  char *res1, *res2;

  res1 = s21_strcat(src1, src2);
  res2 = strcat(src1, src2);
  ck_assert_str_eq(res1, res2);

  res1 = s21_strcat(src1, src3);
  res2 = strcat(src1, src3);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_strncat_test) {
  char src1[10] = "Frf";
  char src2[4] = "Gtg";
  char src3[4] = "";
  char *res1, *res2;

  res1 = s21_strncat(src1, src2, 3);
  res2 = strncat(src1, src2, 3);
  ck_assert_str_eq(res1, res2);

  res1 = s21_strncat(src1, src3, 9);
  res2 = strncat(src1, src3, 9);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_strstr_test) {
  char src1[7] = "Frf";
  char src2[4] = "rf";
  char src3[7] = "";
  char src4[4] = "";
  char *res1, *res2;

  res1 = s21_strstr(src1, src2);
  res2 = strstr(src1, src2);
  ck_assert_str_eq(res1, res2);

  res1 = s21_strstr(src3, src4);
  res2 = strstr(src3, src4);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(s21_strlen_test) {
  // ++
  char str1[100] = "1234", str2[100] = "Look", str3[100] = "00000000",
       str4[100] = "-1-2-3-4-5", str5[100] = "";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));
  ck_assert_int_eq(s21_strlen(str4), strlen(str4));
  ck_assert_int_eq(s21_strlen(str5), strlen(str5));

  // 1 function
}
END_TEST

START_TEST(s21_strchr_test) {
  // ++
  char str1[100] = "1234", str2[100] = "Look", str3[100] = "00000000",
       str4[100] = "-1-2-3-4-5", str5[100] = "";
  ck_assert_ptr_eq(s21_strchr(str1, 50), strchr(str1, 50));
  ck_assert_ptr_eq(s21_strchr(str2, 99), strchr(str2, 99));
  ck_assert_ptr_eq(s21_strchr(str3, 48), strchr(str3, 48));
  ck_assert_ptr_eq(s21_strchr(str4, 53), strchr(str4, 53));
  ck_assert_ptr_eq(s21_strchr(str5, 37), strchr(str5, 37));

  // 2 function
}
END_TEST

START_TEST(s21_strpbrk_test) {
  // ++
  char str1[100] = "1234", str2[100] = "Look", str3[100] = "00000000",
       str4[100] = "-1-2-3-4-5", str5[100] = "", str6[100] = "1654",
       str7[100] = "c", str8[100] = "0";

  ck_assert_ptr_eq(s21_strpbrk(str1, str6), strpbrk(str1, str6));
  ck_assert_ptr_eq(s21_strpbrk(str2, str7), strpbrk(str2, str7));
  ck_assert_ptr_eq(s21_strpbrk(str1, str7), strpbrk(str1, str7));
  ck_assert_ptr_eq(s21_strpbrk(str3, str8), strpbrk(str3, str8));
  ck_assert_ptr_eq(s21_strpbrk(str4, str6), strpbrk(str4, str6));
  ck_assert_ptr_eq(s21_strpbrk(str5, str1), strpbrk(str5, str1));

  // 3 function
}
END_TEST

START_TEST(s21_strtok_test) {
  // ++
  char str1[100] = "NULL", str2[100] = "1/2/3/4", str3[100] = "1234",
       str4[100] = "HELP! !--HELLO--! ==BUE==", str6[100] = "NULL";
  ck_assert_msg(s21_strtok(str1, str6) == strtok(str1, str6), "1 test failed");
  ck_assert_msg(s21_strtok(str4, str6) == strtok(str4, str6), "2 test failed");
  ck_assert_msg(s21_strtok(str2, str3) == strtok(str2, str3), "3 test failed");
  ck_assert_msg(s21_strtok(str1, str3) == strtok(str1, str3), "3 test failed");
  ck_assert_msg(s21_strtok(str4, str3) == strtok(str4, str3), "3 test failed");
  ck_assert_ptr_eq(s21_strtok(str1, str6), strtok(str1, str6));
}
END_TEST

// test int

START_TEST(s21_strcspn_test) {
  char str11[100] = "1234", str12[100] = "776832768178",
       str13[100] = "-1213002%s", str14[100] = "";
  char str21[100] = "", str22[100] = "798", str23[100] = "-1213002%s",
       str24[100] = "1234";
  ck_assert_msg(s21_strcspn(str11, str21) == strcspn(str11, str21),
                "1 test failed");
  ck_assert_msg(s21_strcspn(str12, str22) == strcspn(str12, str22),
                "2 test failed");
  ck_assert_msg(s21_strcspn(str13, str23) == strcspn(str13, str23),
                "3 test failed");
  ck_assert_msg(s21_strcspn(str14, str24) == strcspn(str14, str24),
                "4 test failed");
  ck_assert_msg(s21_strcspn(str12, str23) == strcspn(str12, str23),
                "5 test failed");
}
END_TEST
START_TEST(s21_strspn_test) {
  // ++
  char str11[100] = "1234", str12[100] = "776832768178",
       str13[100] = "-1213002%s", str14[100] = "";
  char str21[100] = "", str22[100] = "798", str23[100] = "-1213002%s",
       str24[100] = "1234";
  ck_assert_int_eq(s21_strspn(str11, str21), strspn(str11, str21));
  ck_assert_int_eq(s21_strspn(str12, str22), strspn(str12, str22));
  ck_assert_int_eq(s21_strspn(str13, str23), strspn(str13, str23));
  ck_assert_int_eq(s21_strspn(str14, str24), strspn(str14, str24));
  ck_assert_int_eq(s21_strspn(str12, str23), strspn(str12, str23));

  // 19 function
}
END_TEST

START_TEST(s21_strncpy_test) {
  // ++
  char str11[100] = "1234", str12[100] = "776832768178",
       str13[100] = "-1213002%s", str14[100] = "";
  char str21[100] = "1234", str22[100] = "776bgtnhy1",
       str23[100] = "-1213002%s", str24[100] = "";
  char str111[100] = "1234", str121[100] = "776832768178",
       str131[100] = "-1213002%s", str141[100] = "";
  char str211[100] = "1234", str221[100] = "776bgtnhy1",
       str231[100] = "-1213002%s", str241[100] = "";
  ck_assert_str_eq(s21_strncpy(str11, str21, 5), strncpy(str111, str211, 5));
  ck_assert_str_eq(s21_strncpy(str12, str22, 7), strncpy(str121, str221, 7));
  ck_assert_str_eq(s21_strncpy(str13, str23, 5), strncpy(str131, str231, 5));
  ck_assert_str_eq(s21_strncpy(str14, str24, 7), strncpy(str141, str241, 7));
  ck_assert_str_eq(s21_strncpy(str12, str23, 5), strncpy(str121, str231, 5));

  // 13's function
}
END_TEST

START_TEST(s21_memmove_test) {
  // ++
  char str1[50] = "123456789", str2[50] = "Hi_guys", str3[50] = "asdfghjkl[]",
       str4[50] = "111111111", str5[50] = "",
       str6[] = "12345679088123456789123456789012345", str7[] = "3456",
       str8[] = "";
  ck_assert_str_eq(s21_memmove(&str1[4], &str1[3], 3),
                   memmove(&str1[4], &str1[3], 3));
  ck_assert_str_eq(s21_memmove(&str1[4], " ", 1), memmove(&str1[4], " ", 1));
  ck_assert_str_eq(s21_memmove(&str1[6], &str1[3], 5),
                   memmove(&str1[6], &str1[3], 5));
  ck_assert_str_eq(s21_memmove(str2, str3, 5), memmove(str2, str3, 5));
  ck_assert_str_eq(s21_memmove(str4, str5, 5), memmove(str4, str5, 5));
  ck_assert_str_eq(s21_memmove(str6, str7, 5), memmove(str6, str7, 5));
  ck_assert_str_eq(s21_memmove(str6, str8, 1), memmove(str6, str8, 1));

  // 5 function
}
END_TEST

START_TEST(s21_strrchr_test) {
  char str1[100] = "123412341234", str2[100] = "Sensation!",
       str3[100] = "00000000", str4[100] = "-1-2-3-4-5", str5[100] = "",
       str6[100] = " ", str7[100] = "1f2t3_4:5^6`=t_retro";
  ck_assert_msg(s21_strrchr(str1, '0') == strrchr(str1, '0'), "test 1 failed");
  ck_assert_msg(s21_strrchr(str2, 'i') == strrchr(str2, 'i'), "test 2 failed");
  ck_assert_msg(s21_strrchr(str3, '0') == strrchr(str3, '0'), "test 3 failed");
  ck_assert_msg(s21_strrchr(str4, '-') == strrchr(str4, '-'), "test 4 failed");
  ck_assert_msg(s21_strrchr(str5, '1') == strrchr(str5, '1'), "test 5 failed");
  ck_assert_msg(s21_strrchr(str6, '^') == strrchr(str6, '^'), "test 6 failed");
  ck_assert_msg(s21_strrchr(str7, ' ') == strrchr(str7, ' '), "test 7 failed");
  ck_assert_msg(s21_strrchr(str7, '_') == strrchr(str7, '_'), "test 8 failed");
}
END_TEST

START_TEST(s21_memchr_test) {
  char str0[10] = "", str1[100] = "123412341234", str2[100] = "Sensation!",
       str3[100] = "00000000", str4[100] = "-1-2-3-4-5",
       str5[100] = "daseqweqwe",
       str6[10000] = "12345679088123456789123456789012345",
       str7[100] = "123456790";
  size_t bytes_b = 9, bytes_c = 12;
  ck_assert_str_eq(s21_memchr(str1, '2', bytes_b), memchr(str1, '2', bytes_b));
  ck_assert_msg(s21_memchr(str0, '\0', 0) == s21_NULL, "test 2 failed");
  ck_assert_ptr_eq(s21_memchr(str2, 'i', bytes_b), memchr(str2, 'i', bytes_b));
  ck_assert_str_eq(s21_memchr(str3, '0', bytes_b), memchr(str3, '0', bytes_b));
  ck_assert_str_eq(s21_memchr(str4, '-', bytes_b), memchr(str4, '-', bytes_b));
  ck_assert_ptr_eq(s21_memchr(str5, '1', bytes_b), memchr(str5, '1', bytes_b));
  ck_assert_msg(s21_memchr(str6, 'u', bytes_b) == s21_NULL, "test 6 failed");
  ck_assert_str_eq(s21_memchr(str6, '8', bytes_c), memchr(str6, '8', bytes_c));
  ck_assert_msg(s21_memchr(str7, ' ', bytes_c) == s21_NULL,
                "test 8 failed");  //
  ck_assert_str_eq(s21_memchr(str7, '\0', bytes_c),
                   memchr(str7, '\0', bytes_c));
}
END_TEST

START_TEST(s21_strerror_test) {
  int b = -3, c = 0;
  for (int a = 0; a < 200; a++) {
    ck_assert_str_eq(s21_strerror(a), strerror(a));
  }
  ck_assert_str_eq(s21_strerror(b), strerror(b));
  ck_assert_str_eq(s21_strerror(c), strerror(c));
}
END_TEST

START_TEST(int_to_str) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%d\n%d";
  int a1 = 228;
  int a2 = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, a1, a2),
                   sprintf(str2, format, a1, a2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_flags) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%+d% d%-d%#d%05d";
  int a1 = 444;
  int a2 = 228;
  int a3 = 69;
  int a4 = 6;
  ck_assert_int_eq(s21_sprintf(str1, format, a1, a2, a3, a4, a4),
                   sprintf(str2, format, a1, a2, a3, a4, a4));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_width) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format1 = "%+-25.3d%25.15d%*d";
  int a1 = 444;
  int a2 = 228;
  int a3 = 69;
  ck_assert_int_eq(s21_sprintf(str1, format1, a1, a2, 6, a3),
                   sprintf(str2, format1, a1, a2, 6, a3));

  char *format2 = "%+-5.3d%6.5d%5d";
  int a4 = 444;
  int a5 = 228;
  int a6 = 69;
  ck_assert_int_eq(s21_sprintf(str1, format2, a4, a5, a6),
                   sprintf(str2, format2, a4, a5, a6));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_length) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%+10.3d%#5.6hd%05ld%-10.5d%#4.5hd%*.6ld";
  int a1 = 444;
  short int a2 = 228;
  long int a3 = 69111112412412;
  ck_assert_int_eq(s21_sprintf(str1, format, a1, a2, a3, a1, a2, 7, a3),
                   sprintf(str2, format, a1, a2, a3, a1, a2, 7, a3));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_procent) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%+10.3d%%\n";
  int a1 = 444;
  ck_assert_int_eq(s21_sprintf(str1, format, a1), sprintf(str2, format, a1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_zero) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%+10.3d%%\n";
  int a1 = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, a1), sprintf(str2, format, a1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// test int

// test float

START_TEST(float_to_str) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%f\n%f";
  float a1 = 228.14569999;
  float a2 = -69.120000000999;
  ck_assert_int_eq(s21_sprintf(str1, format, a1, a2),
                   sprintf(str2, format, a1, a2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_flags) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%+f\n%-10f%#f%05f";
  float a1 = 228.1456999;
  float a2 = 69.1200000000000000009;
  ck_assert_int_eq(s21_sprintf(str1, format, a1, a2, a1, a2),
                   sprintf(str2, format, a1, a2, a1, a2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_precision) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%5.5Lf|%4.7f|%10.10Lf|%0.0f|%.*Lf";
  long double d1 = 91999.124125125125;
  double d2 = 0.0123456;
  ck_assert_int_eq(s21_sprintf(str1, format, d1, d2, d1, d2, 5, d1),
                   sprintf(str2, format, d1, d2, d1, d2, 5, d1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_complex_test1) {
  char str1[255] = {'\0'};
  char str2[255] = {'\0'};

  short h1 = 0;
  int r2 = sprintf(str2, "%+f %+d %+hd %+ld %+i", 0.0f, 0, h1, 0l, 0);
  int r1 = s21_sprintf(str1, "%+f %+d %+hd %+ld %+i", 0.0f, 0, h1, 0l, 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r2, r1);
}
END_TEST

START_TEST(float_complex_test2) {
  char str1[255] = {'\0'};
  char str2[255] = {'\0'};

  int r2 = sprintf(str2,
                   "1 %+-10.3f 2 %+10.2f 3 % 15.f 4 %+.6f 5 %.10f 6 %-10.f 7 "
                   "%5.19f 8 %25.f 9 %+10.f 10 %.f",
                   2546.4324, 3452.4325, 5678.43256, 456789.243242,
                   3456789123.43245, 12345.6788, 34.4325432, 4325678.43242,
                   34567.2345432, 34567.43244);
  int r1 = s21_sprintf(str1,
                       "1 %+-10.3f 2 %+10.2f 3 % 15.f 4 %+.6f 5 %.10f 6 %-10.f "
                       "7 %5.19f 8 %25.f 9 %+10.f 10 %.f",
                       2546.4324, 3452.4325, 5678.43256, 456789.243242,
                       3456789123.43245, 12345.6788, 34.4325432, 4325678.43242,
                       34567.2345432, 34567.43244);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r2, r1);
}
END_TEST

START_TEST(float_complex_test3) {
  char str1[255] = {'\0'};
  char str2[255] = {'\0'};

  int r2 = sprintf(str2, "%+34.10f%.10i%15.1d%25.*s", 25.3456, 1234, 6, 4567,
                   "HELLOMYDEARFRIEND");
  int r1 = s21_sprintf(str1, "%+34.10f%.10i%15.1d%25.*s", 25.3456, 1234, 6,
                       4567, "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r2, r1);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r2, r1);
}
END_TEST

START_TEST(float_zero) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%5.5f|%4.7f|%10.10f|%0.0f";
  double zero = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, zero, zero, zero, zero),
                   sprintf(str2, format, zero, zero, zero, zero));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// test float

// test unsigned

START_TEST(unsigned_precision) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%.5u|%.10u|%.0u|%10.*u";
  unsigned d1 = 91999.0;
  ck_assert_int_eq(s21_sprintf(str1, format, d1, d1, d1, 5, d1),
                   sprintf(str2, format, d1, d1, d1, 5, d1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_test) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  sprintf(str1, "%2.5u%%\n", -4);
  s21_sprintf(str2, "%2.5u%%\n", -4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_flags) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  sprintf(str1, "%-10u%%\n%03u|%*u", 421, 69, 10, 228);
  s21_sprintf(str2, "%-10u%%\n%03u|%*u", 421, 69, 10, 228);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_length) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  short unsigned key_h = 421;
  sprintf(str1, "%-10hu%%\n", key_h);
  s21_sprintf(str2, "%-10hu%%\n", key_h);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_length_flags) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  long unsigned key_l = 421;
  sprintf(str1, "%-10lu%%\n", key_l);
  s21_sprintf(str2, "%-10lu%%\n", key_l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_zero) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  long unsigned zero = 0;
  sprintf(str1, "%-10lu%%\n", zero);
  s21_sprintf(str2, "%-10lu%%\n", zero);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// test unsigned

// test mantiss

START_TEST(mantis_zero) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  double zero = 0;
  sprintf(str1, "%-10e%%\n", zero);
  s21_sprintf(str2, "%-10le%%\n", zero);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(mantis_to_str) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%e\n%e";
  float a1 = 228.14569999;
  float a2 = 69.120000000999;
  ck_assert_int_eq(s21_sprintf(str1, format, a1, a2),
                   sprintf(str2, format, a1, a2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(mantis_flags) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%+f\n%-10f\n% .3e %03e %#.3e %*.2Le";
  float a1 = -228.145;
  float a2 = 69.1;
  float a3 = 444.1;
  long double a4 = 555124.1512412125125;
  ck_assert_int_eq(s21_sprintf(str1, format, a1, a2, a3, a1, a2, 6, a4),
                   sprintf(str2, format, a1, a2, a3, a1, a2, 6, a4));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(mantis_length_flags) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  double key_l = 421;
  sprintf(str1, "%-10.5e%%\n", key_l);
  s21_sprintf(str2, "%-10.5e%%\n", key_l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(mantis_precision) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  double d = 421.124;
  sprintf(str1, "%.5e%%\n%.1e\n%.2e|%.*e", d, d, d, 6, d);
  s21_sprintf(str2, "%.5e%%\n%.1e\n%.2e|%.*e", d, d, d, 6, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// test mantiss

// test g flag

START_TEST(gflag_test) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  double d = 421.124;
  sprintf(str1, "%.5g%%\n%#.1g\n%0.2g|%*.g", d, d, d, 8, d);
  s21_sprintf(str2, "%.5g%%\n%#.1g\n%0.2g|%*.g", d, d, d, 8, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(gflag_flags) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  double key_l = 421.124567;
  sprintf(str1, "%-10.5g%%\n%05g|%#.2g", key_l, key_l, key_l);
  s21_sprintf(str2, "%-10.5g%%\n%05g|%#.2g", key_l, key_l, key_l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(gflag_less_then1) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};

  double d = 0.124151515;
  sprintf(str1, "%.5g%%\n%.1g\n%.*g|%#.6g", d, d, 8, d, d);
  s21_sprintf(str2, "%.5g%%\n%.1g\n%.*g|%#.6g", d, d, 8, d, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

//------------hex--------------
START_TEST(hex_precision) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%.15x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_many_flags) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%#-5.10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_zero) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%#x";
  unsigned val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_short) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%#hx";
  unsigned short val = 12352;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_long) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%#lx";
  unsigned long val = 18571757371571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(hex_one_longer_width) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%#2x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(hex_two_longer_width) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%#30x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
//------------------flags octal---------------------
END_TEST
START_TEST(octal_width) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%15o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_flags) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%-16o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_precision) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(octal_many_flags) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%-5.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_zero) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_hash) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%#o";
  int val = 57175;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_short1) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%hd";
  short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_long) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%lo";
  long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_many) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%lo, %o, %ho, %.5o, %5.o";
  long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};

  char *format = "%lo";
  long int val = 84518;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf42) {
  char str1[BUFF_SIZE] = {"\0"};
  char str2[BUFF_SIZE] = {"\0"};
  char format[] = "%#5p";
  int a = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, &a), sprintf(str2, format, &a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_Csprintf_test) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};

  sprintf(str1, "%1c %c", 'H', 'z');
  s21_sprintf(str2, "%1c %c", 'H', 'z');
  ck_assert_str_eq(str1, str2);

  sprintf(str1, "%10c %2c", 'H', 'z');
  s21_sprintf(str2, "%10c %2c", 'H', 'z');
  ck_assert_str_eq(str1, str2);

  sprintf(str1, "%-1c %-c", 'H', 'z');
  s21_sprintf(str2, "%-1c %-c", 'H', 'z');
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_Usprintf_test) {
  char str1[100] = {'\0'};
  char str2[100] = {'\0'};

  sprintf(str1, "%2.5u%%\n", 4);
  s21_sprintf(str2, "%2.5u%%\n", 4);
  ck_assert_str_eq(str1, str2);

  sprintf(str1, "%2.5u%%\n", -4);
  s21_sprintf(str2, "%2.5u%%\n", -4);
  ck_assert_str_eq(str1, str2);

  sprintf(str1, "%10.5u%%\n", 4);
  s21_sprintf(str2, "%10.5u%%\n", 4);
  ck_assert_str_eq(str1, str2);

  sprintf(str1, "%-10u%%\n", 421);
  s21_sprintf(str2, "%-10u%%\n", 421);
  ck_assert_str_eq(str1, str2);

  short unsigned key_h = 421;
  sprintf(str1, "%-10hu%%\n", key_h);
  s21_sprintf(str2, "%-10hu%%\n", key_h);
  ck_assert_str_eq(str1, str2);

  long unsigned key_l = 421;
  sprintf(str1, "%-10lu%%\n", key_l);
  s21_sprintf(str2, "%-10lu%%\n", key_l);
  ck_assert_str_eq(str1, str2);
  char c[255] = {'\0'}, d[255] = {'\0'};
  s21_sprintf(c, "%10.s %10ls %-10ls %-3ls %.ls %.3ls %.10ls", "hello",
              L"hello", L"hello", L"hello", L"hello", L"hello", L"hello");
  sprintf(d, "%10.s %10ls %-10ls %-3ls %.ls %.3ls %.10ls", "hello", L"hello",
          L"hello", L"hello", L"hello", L"hello", L"hello");
  ck_assert_str_eq(c, d);
}
END_TEST

START_TEST(to_lower_test1) {
  char str[] = "SchooL21 EvolutioN";
  char expected[] = "school21 evolution";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test2) {
  char str[] = "123456789Q";
  char expected[] = "123456789q";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test3) {
  char str[] = "What is this, Alan?";
  char expected[] = "what is this, alan?";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test4) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test5) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test1) {
  char str[] = "Shlepa";
  char src[] = "I love my . He is very kind!";
  s21_size_t index = 10;
  char expected[] = "I love my Shlepa. He is very kind!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test2) {
  char str[] = "Hello, ";
  char src[] = "World!";
  s21_size_t index = 0;
  char expected[] = "Hello, World!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test3) {
  char str[] = "";
  char src[] = "";
  s21_size_t index = 100;
  char *expected = "";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test4) {
  char *src = NULL;
  char *str = NULL;
  s21_size_t index = 100;
  char *expected = NULL;
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test5) {
  char str[] = "Monkey";
  char src[] = "Crazy  ";
  s21_size_t index = 6;
  char expected[] = "Crazy Monkey ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_str_null) {
  char *str = NULL;
  char src[] = "Crazy  ";
  s21_size_t index = 6;
  char expected[] = "Crazy  ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(all_empty) {
  char str[] = "";
  char trim_ch[] = "";
  char expected[] = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(str_empty) {
  char str[] = "";
  char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char expected[] = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(trim_empty) {
  char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char trim_ch[] = "";
  char expected[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(trim_and_str_eq) {
  char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq";
  char expected[] = "1";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(trim_test1) {
  char str[] = "+!!++Cra+zy++00";
  char trim_ch[] = "+!0-";
  char expected[] = "Cra+zy";
  char *got = (char *)s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(trim_test2) {
  char str[] = "Ab000cd0";
  char trim_ch[] = "003";
  char expected[] = "Ab000cd";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(trim_test3) {
  char str[] = "DoNotTouch";
  char trim_ch[] = "Not";
  char expected[] = "DoNotTouch";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(trim_test4) {
  char str[] = "&* !!sc21 * **";
  char trim_ch[] = "&!* ";
  char expected[] = "sc21";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(trim_test5) {
  char str[] = " Good morning!    ";
  char trim_ch[] = " ";
  char expected[] = "Good morning!";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(null_ptr_trim_chars) {
  char str[] = "        abc ";
  char *trim_ch = " ";
  char expected[] = "abc";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(to_upper_test1) {
  char str[] = "good job";
  char expected[] = "GOOD JOB";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test2) {
  char str[] = "empty";
  char expected[] = "EMPTY";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test3) {
  char str[] = "1+1*1";
  char expected[] = "1+1*1";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test4) {
  char str[] = " ";
  char expected[] = " ";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test5) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf = 0;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_memset_test);
  tcase_add_test(tc1_1, s21_strcat_test);
  tcase_add_test(tc1_1, s21_strncat_test);
  tcase_add_test(tc1_1, s21_strstr_test);
  tcase_add_test(tc1_1, s21_strlen_test);
  tcase_add_test(tc1_1, s21_strchr_test);
  tcase_add_test(tc1_1, s21_strpbrk_test);
  tcase_add_test(tc1_1, s21_strtok_test);
  tcase_add_test(tc1_1, s21_memcmp_test);
  tcase_add_test(tc1_1, s21_memcpy_test);
  tcase_add_test(tc1_1, s21_strcmp_test);
  tcase_add_test(tc1_1, s21_strcpy_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strncmp_test);
  tcase_add_test(tc1_1, s21_strpbrk_test);
  tcase_add_test(tc1_1, s21_strspn_test);
  tcase_add_test(tc1_1, s21_strncpy_test);
  tcase_add_test(tc1_1, s21_memmove_test);
  tcase_add_test(tc1_1, s21_strrchr_test);
  tcase_add_test(tc1_1, s21_memchr_test);
  tcase_add_test(tc1_1, s21_strerror_test);

  tcase_add_test(tc1_1, test_sprintf42);
  tcase_add_test(tc1_1, s21_Csprintf_test);
  tcase_add_test(tc1_1, s21_Usprintf_test);

  tcase_add_test(tc1_1, int_to_str);
  tcase_add_test(tc1_1, int_flags);
  tcase_add_test(tc1_1, int_width);
  tcase_add_test(tc1_1, int_length);
  tcase_add_test(tc1_1, int_procent);
  tcase_add_test(tc1_1, int_zero);

  tcase_add_test(tc1_1, float_to_str);
  tcase_add_test(tc1_1, float_flags);
  tcase_add_test(tc1_1, float_precision);
  tcase_add_test(tc1_1, float_complex_test1);
  tcase_add_test(tc1_1, float_complex_test2);
  tcase_add_test(tc1_1, float_complex_test3);
  tcase_add_test(tc1_1, float_zero);

  tcase_add_test(tc1_1, unsigned_precision);
  tcase_add_test(tc1_1, unsigned_test);
  tcase_add_test(tc1_1, unsigned_flags);
  tcase_add_test(tc1_1, unsigned_length);
  tcase_add_test(tc1_1, unsigned_length_flags);
  tcase_add_test(tc1_1, unsigned_zero);

  tcase_add_test(tc1_1, mantis_zero);
  tcase_add_test(tc1_1, mantis_to_str);
  tcase_add_test(tc1_1, mantis_flags);
  tcase_add_test(tc1_1, mantis_length_flags);
  tcase_add_test(tc1_1, mantis_precision);

  tcase_add_test(tc1_1, gflag_test);
  tcase_add_test(tc1_1, gflag_flags);
  tcase_add_test(tc1_1, gflag_less_then1);

  tcase_add_test(tc1_1, hex_precision);
  tcase_add_test(tc1_1, hex_many_flags);
  tcase_add_test(tc1_1, hex_zero);
  tcase_add_test(tc1_1, hex_short);
  tcase_add_test(tc1_1, hex_long);
  tcase_add_test(tc1_1, hex_one_longer_width);
  tcase_add_test(tc1_1, hex_two_longer_width);

  tcase_add_test(tc1_1, octal_width);
  tcase_add_test(tc1_1, octal_flags);
  tcase_add_test(tc1_1, octal_precision);
  tcase_add_test(tc1_1, octal_many_flags);
  tcase_add_test(tc1_1, octal_zero);
  tcase_add_test(tc1_1, octal_hash);
  tcase_add_test(tc1_1, octal_short1);
  tcase_add_test(tc1_1, octal_long);
  tcase_add_test(tc1_1, octal_many);
  tcase_add_test(tc1_1, octal);

  tcase_add_test(tc1_1, to_lower_test1);
  tcase_add_test(tc1_1, to_lower_test2);
  tcase_add_test(tc1_1, to_lower_test3);
  tcase_add_test(tc1_1, to_lower_test4);
  tcase_add_test(tc1_1, to_lower_test5);
  tcase_add_test(tc1_1, insert_test1);
  tcase_add_test(tc1_1, insert_test2);
  tcase_add_test(tc1_1, insert_test3);
  tcase_add_test(tc1_1, insert_test4);
  tcase_add_test(tc1_1, insert_test5);
  tcase_add_test(tc1_1, insert_str_null);
  tcase_add_test(tc1_1, all_empty);
  tcase_add_test(tc1_1, str_empty);
  tcase_add_test(tc1_1, trim_empty);
  tcase_add_test(tc1_1, trim_and_str_eq);
  tcase_add_test(tc1_1, trim_test1);
  tcase_add_test(tc1_1, trim_test2);
  tcase_add_test(tc1_1, trim_test3);
  tcase_add_test(tc1_1, trim_test4);
  tcase_add_test(tc1_1, trim_test5);
  tcase_add_test(tc1_1, null_ptr_trim_chars);
  tcase_add_test(tc1_1, to_upper_test1);
  tcase_add_test(tc1_1, to_upper_test2);
  tcase_add_test(tc1_1, to_upper_test3);
  tcase_add_test(tc1_1, to_upper_test4);
  tcase_add_test(tc1_1, to_upper_test5);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
