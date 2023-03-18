#include <check.h>

#include "credit.c"
#include "credit.h"
#include "s21_calc.h"
// gcc -g -coverage mytest_calc.c s21_calc.c -o test.out -I -l -lcheck

//// Тест для double number
START_TEST(number_1) {
  double num[SIZE] = {0};

  char str1[] = "1.345";
  number(str1, num);
  ck_assert_msg(*num == 1.345, "FAILED number_1_1");

  char str2[] = "0.345";
  number(str2, num);
  ck_assert_msg(*num == 0.345, "FAILED number_1_2");

  char str3[] = "1000.345";
  number(str3, num);
  ck_assert_msg(*num == 1000.345, "FAILED number_1_3");

  char str4[] = "234567890.34554569090984";
  number(str4, num);
  ck_assert_msg(*num == 234567890.34554569090984, "FAILED number_1_4");

  char str5[] = "10.3000405";
  number(str5, num);
  ck_assert_msg(*num == 10.3000405, "FAILED number_1_5");

  char str6[] = "0";
  number(str6, num);
  ck_assert_msg(*num == 0, "FAILED number_1_6");

  char str7[] = "1000";
  number(str7, num);
  ck_assert_msg(*num == 1000, "FAILED number_1_7");

  char str8[] = "0.0300";
  number(str8, num);
  ck_assert_msg(*num == 0.0300, "FAILED number_1_8");
}
END_TEST

START_TEST(number_err) {
  double num[SIZE] = {0};

  ck_assert_msg(number("01.345", num) == -1, "FAILED number_err_1");
  ck_assert_msg(number("1.34.5", num) == -1, "FAILED number_err_2");
  ck_assert_msg(number("1,345", num) == -1, "FAILED number_err_3");
  ck_assert_msg(number("s1,345", num) == -1, "FAILED number_err_4");
  ck_assert_msg(number("1,h345", num) == -1, "FAILED number_err_5");
  ck_assert_msg(number("1,-345", num) == -1, "FAILED number_err_6");
  ck_assert_msg(number("(0,3459587474736", num) == -1, "FAILED number_err_7");
  ck_assert_msg(number("0,34595874747.36", num) == -1, "FAILED number_err_8");
  ck_assert_msg(number("0,34595874747+36", num) == -1, "FAILED number_err_9");
  ck_assert_msg(number("0.34595874747+36", num) == -1, "FAILED number_err_10");
  ck_assert_msg(number("0.34595874747sin36", num) == -1,
                "FAILED number_err_11");
  ck_assert_msg(number("sin0.34595874747", num) == -1, "FAILED number_err_12");
  ck_assert_msg(number("00.34595874747", num) == -1, "FAILED number_err_13");
  ck_assert_msg(number("00..34595874747", num) == -1, "FAILED number_err_14");
  ck_assert_msg(number("..34595874747", num) == -1, "FAILED number_err_15");
  ck_assert_msg(number(".34595874747", num) == 0, "FAILED number_err_16");
  ck_assert_msg(number("00", num) == -1, "FAILED number_err_17");
  ck_assert_msg(number("l8", num) == -1, "FAILED number_err_18");
  ck_assert_msg(number("0200", num) == -1, "FAILED number_err_19");
  ck_assert_msg(number("09", num) == -1, "FAILED number_err_20");
  ck_assert_msg(number("9.", num) == -1, "FAILED number_err_21");
  ck_assert_msg(number(".2", num) == 0, "FAILED number_err_22");
  ck_assert_msg(number("-3", num) == 0, "FAILED number_err_23");
}
END_TEST

START_TEST(parser_sin) {
  Stack_t stack_N[10] = {0};

  ck_assert_msg(parser("5+12s", stack_N) == -1, "FAILED parser_sin_1");
  ck_assert_msg(parser("sin(", stack_N) == -1, "FAILED parser_sin_2");
  ck_assert_msg(parser("sin()", stack_N) == -1, "FAILED parser_sin_3");
  ck_assert_msg(parser("sin(5/)", stack_N) == -1, "FAILED parser_sin_4");
  ck_assert_msg(parser("sin(4.5)+cos(5", stack_N) == -1, "FAILED parser_sin_5");
  ck_assert_msg(parser("/sin(5)", stack_N) == -1, "FAILED parser_sin_6");
  ck_assert_msg(parser("sin4", stack_N) == -1, "FAILED parser_sin_7");
  ck_assert_msg(parser("4sin(45)", stack_N) == -1, "FAILED parser_sin_8");
  ck_assert_msg(parser("1+sib(4)", stack_N) == -1, "FAILED parser_sin_9");
  ck_assert_msg(parser("1+sin(4)", stack_N) == 0, "FAILED parser_sin_10");
  ck_assert_msg(parser("-cos(4*2)+sin(4)", stack_N) == 0, "F parser_sin_10");
}
END_TEST

START_TEST(parser_cos) {
  Stack_t stack_N[10] = {0};

  char str1[] = "=cos";
  char str2[] = "cos(";
  char str3[] = "cos()";
  char str4[] = "cos(5/)";
  char str5[] = "cos(4.5)+cos(5";
  char str6[] = "*cos(5)";
  char str7[] = "cosn4";
  char str8[] = "4cos(45)";
  char str9[] = "1+ces(5)";
  char str10[] = "1+cos(4)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_1_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_1_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_1_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_1_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_1_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_1_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_1_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_1_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_1_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_1_10");
}
END_TEST

START_TEST(parser_tan) {
  Stack_t stack_N[10] = {0};

  char str1[] = "=tan";
  char str2[] = "tan(";
  char str3[] = "tan()";
  char str4[] = "tan(5/)";
  char str5[] = "tan(4.5)+tan(5";
  char str6[] = "*tan(5)";
  char str7[] = "tann4";
  char str8[] = "4tan(45)";
  char str9[] = "1+tas(8)";
  char str10[] = "1+tan(4)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_tan_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_tan_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_tan_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_tan_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_tan_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_tan_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_tan_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_tan_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_tan_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_tan_10");
}
END_TEST

START_TEST(parser_asin) {
  Stack_t stack_N[10] = {0};

  char str1[] = "5+12s";
  char str2[] = "asin(";
  char str3[] = "asin()";
  char str4[] = "asin(5/)";
  char str5[] = "asin(4.5)+cos(5";
  char str6[] = "*asin(5)";
  char str7[] = "asin4";
  char str8[] = "4asin(45)";
  char str9[] = "1+asik(4)";
  char str10[] = "1+asin(4)";
  char str11[] = "asin(0.2)";
  char str12[] = "asin(8)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_asin_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_asin_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_asin_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_asin_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_asin_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_asin_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_asin_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_asin_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_asin_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_asin_10");
  ck_assert_msg(parser(str11, stack_N) == 0, "FAILED parser_asin_11");
  ck_assert_msg(parser(str12, stack_N) == 0, "FAILED parser_asin_12");
}
END_TEST

START_TEST(parser_acos) {
  Stack_t stack_N[10] = {0};

  char str1[] = "=acos";
  char str2[] = "acos(";
  char str3[] = "acos()";
  char str4[] = "acos(5/)";
  char str5[] = "acos(4.5)+acos(5";
  char str6[] = "/acos(5)";
  char str7[] = "acosn4";
  char str8[] = "4acos(45)";
  char str9[] = "1+aces(5)";
  char str10[] = "acos(8)";
  char str11[] = "acos(8)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_acos_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_acos_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_acos_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_acos_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_acos_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_acos_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_acos_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_acos_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_acos_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_acos_10");
  ck_assert_msg(parser(str11, stack_N) == 0, "FAILED parser_acos_11");
}
END_TEST

START_TEST(parser_atan) {
  Stack_t stack_N[10] = {0};

  char str1[] = "=atan";
  char str2[] = "atan(";
  char str3[] = "atan()";
  char str4[] = "atan(5/)";
  char str5[] = "atan(4.5)+atan(5";
  char str6[] = "+atan(5x)";
  char str7[] = "atann4";
  char str8[] = "4atan(45)";
  char str9[] = "1+atas(8)";
  char str10[] = "atan(8)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_atan_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_atan_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_atan_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_atan_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_atan_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_atan_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_atan_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_atan_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_atan_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_atan_10");
}
END_TEST

START_TEST(parser_sqrt) {
  Stack_t stack_N[10] = {0};

  char str1[] = "+sqrt";
  char str2[] = "sqrt(";
  char str3[] = "sqrt()";
  char str4[] = "sqrt(5/)";
  char str5[] = "sqrtn(4.5)";
  char str6[] = "*sqrt(5)";
  char str7[] = "sqrt4";
  char str8[] = "4sqrt(45)";
  char str9[] = "1+sqrt(8)";
  char str10[] = "1+(-sqrt(8))";
  char str11[] = "sqrt(-4)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_sqrt_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_sqrt_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_sqrt_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_sqrt_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_sqrt_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_sqrt_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_sqrt_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_sqrt_8");
  ck_assert_msg(parser(str9, stack_N) == 0, "FAILED parser_sqrt_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_sqrt_10");
  ck_assert_msg(parser(str11, stack_N) == 0, "FAILED parser_sqrt_10");
}
END_TEST

START_TEST(parser_log) {
  Stack_t stack_N[10] = {0};

  char str1[] = "+log";
  char str2[] = "log(";
  char str3[] = "log()";
  char str4[] = "log(5/)";
  char str5[] = "logn(4.5)";
  char str6[] = "/log(5)";
  char str7[] = "log4";
  char str8[] = "4log(45)";
  char str9[] = "1+logt(8)";
  char str10[] = "log(5)";
  char str11[] = "ln(34)+log(5)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_log_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_log_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_log_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_log_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_log_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_log_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_log_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_log_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_log_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_log_10");
  ck_assert_msg(parser(str11, stack_N) == 0, "FAILED parser_log_11");
}
END_TEST

START_TEST(parser_ln) {
  Stack_t stack_N[10] = {0};
  char str1[] = "+ln";
  char str2[] = "ln(";
  char str3[] = "ln()";
  char str4[] = "ln(5/)";
  char str5[] = "lnn(4.5)";
  char str6[] = "+ln(5i)";
  char str7[] = "ln4";
  char str8[] = "4ln(45)";
  char str9[] = "1+lnt(8)";
  char str10[] = "ln(5)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_ln_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_ln_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_ln_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_ln_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_ln_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_ln_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_ln_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED parser_ln_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_ln_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_ln_10");
}
END_TEST

START_TEST(parser_mod) {
  Stack_t stack_N[10] = {0};

  char str1[] = "+mod";
  char str2[] = "mod(";
  char str3[] = "5mod()";
  char str4[] = "mod(5/)";
  char str5[] = "modn4";
  char str6[] = "+mod5)";
  char str7[] = "mod4";
  char str8[] = "4mod(45)";
  char str9[] = "1+modt(8)";
  char str10[] = "1mod3";
  char str11[] = "(3+4)mod(3+1)";
  char str12[] = "7mod3";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED parser_mod_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED parser_mod_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED parser_mod_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED parser_mod_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED parser_mod_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED parser_mod_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED parser_mod_7");
  ck_assert_msg(parser(str8, stack_N) == 0, "FAILED parser_mod_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED parser_mod_9");
  ck_assert_msg(parser(str10, stack_N) == 0, "FAILED parser_mod_10");
  ck_assert_msg(parser(str11, stack_N) == 0, "FAILED parser_mod_11");
  ck_assert_msg(parser(str12, stack_N) == 0, "FAILED parser_mod_12");
}
END_TEST

START_TEST(parser_x) {
  Stack_t stack_N[10] = {0};

  ck_assert_msg(parser("+x^", stack_N) == -1, "FAILED parser_x_1");
  ck_assert_msg(parser("x(", stack_N) == -1, "FAILED parser_x_2");
  ck_assert_msg(parser("mx*5", stack_N) == -1, "FAILED parser_x_3");
  ck_assert_msg(parser("5x()", stack_N) == -1, "FAILED parser_x_4");
  ck_assert_msg(parser("sinx", stack_N) == -1, "FAILED parser_x_5");
  ck_assert_msg(parser("x+", stack_N) == -1, "FAILED parser_x_6");
  ck_assert_msg(parser("5+x", stack_N) == 0, "FAILED parser_x_7");
  ck_assert_msg(parser("5*x", stack_N) == 0, "FAILED parser_x_8");
  ck_assert_msg(parser("5x", stack_N) == -1, "FAILED parser_x_9");
  ck_assert_msg(parser("5(-x)", stack_N) == -1, "FAILED parser_x_10");
  ck_assert_msg(parser("5*(-x)", stack_N) == 0, "FAILED parser_x_11");
}
END_TEST

START_TEST(parser_pow) {
  Stack_t stack_N[10] = {0};

  ck_assert_msg(parser("x^)", stack_N) == -1, "FAILED parser_pow_1");
  ck_assert_msg(parser("5^", stack_N) == -1, "FAILED parser_pow_2");
  ck_assert_msg(parser("^", stack_N) == -1, "FAILED parser_pow_3");
  ck_assert_msg(parser("^5", stack_N) == -1, "FAILED parser_pow_4");
  ck_assert_msg(parser("sin(^5)", stack_N) == -1, "FAILED parser_pow_5");
  ck_assert_msg(parser("^+", stack_N) == -1, "FAILED parser_pow_6");
  ck_assert_msg(parser("5^2", stack_N) == 0, "FAILED parser_pow_7");
  ck_assert_msg(parser("5^(2+1)", stack_N) == 0, "FAILED parser_pow_8");
  ck_assert_msg(parser("2^2^2^2", stack_N) == 0, "FAILED parser_pow_9");
  ck_assert_msg(parser("5^+4", stack_N) == 0, "FAILED parser_pow_10");
  ck_assert_msg(parser("5^-4", stack_N) == 0, "FAILED parser_pow_11");
  ck_assert_msg(parser("5^(-4+cos(5))", stack_N) == 0, "FAILED parser_pow_12");
  ck_assert_msg(parser("2^(-1+1*3)", stack_N) == 0, "FAILED parser_pow_13");
}
END_TEST

START_TEST(znak_1) {
  double num[20];
  char x[10] = "2";

  s21_calc("-(5+6)", x, num);
  ck_assert_msg(*num == -11, "FAILED znak_1");
}
END_TEST

START_TEST(parser_space) {
  Stack_t stack_N[10] = {0};

  ck_assert_msg(parser("(cos(6 4)", stack_N) == -1, "FAILED parser_space_1");
  ck_assert_msg(parser("(cos(6) + sin( 5 )", stack_N) == -1,
                "FAILED parser_space_1");
  ck_assert_msg(parser("sin( 5 )", stack_N) == -1, "FAILED parser_space_1");
  ck_assert_msg(parser("4 + 3", stack_N) == -1, "FAILED parser_space_1");
  ck_assert_msg(parser("(sin( 1 * 2 * 38 + 1))", stack_N) == -1,
                "FAILED parser_space_1");
}
END_TEST

START_TEST(znak_err) {
  Stack_t stack_N[10] = {0};

  char str1[] = "5+*6";
  char str2[] = "55+";
  char str3[] = "+-6";
  char str4[] = "+";
  char str5[] = "-";
  char str6[] = "*";
  char str7[] = "/";
  char str8[] = "-/8";
  char str9[] = "(sin(1*2*38+))";
  char str10[] = "/5";
  char str11[] = "+(*5)";
  char str12[] = "(5+-5)";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED znak_err_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED znak_err_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED znak_err_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED znak_err_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED znak_err_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED znak_err_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED znak_err_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED znak_err_8");
  ck_assert_msg(parser(str9, stack_N) == -1, "FAILED znak_err_9");
  ck_assert_msg(parser(str10, stack_N) == -1, "FAILED znak_err_10");
  ck_assert_msg(parser(str11, stack_N) == -1, "FAILED znak_err_11");
  ck_assert_msg(parser(str12, stack_N) == -1, "FAILED znak_err_12");
}
END_TEST

START_TEST(brackets_err) {
  Stack_t stack_N[10] = {0};

  char str1[] = "sin(2*(2*2)";
  char str2[] = "()sin(1*2*3(8)";
  char str3[] = "((sin(1*2*3(8))";
  char str4[] = "(sin(1*2*38+))";
  char str5[] = "(/5)";
  char str6[] = "(*5)";
  char str7[] = "(5*)";
  char str8[] = "1+)*5-4(";

  ck_assert_msg(parser(str1, stack_N) == -1, "FAILED brackets_err_1");
  ck_assert_msg(parser(str2, stack_N) == -1, "FAILED brackets_err_2");
  ck_assert_msg(parser(str3, stack_N) == -1, "FAILED brackets_err_3");
  ck_assert_msg(parser(str4, stack_N) == -1, "FAILED brackets_err_4");
  ck_assert_msg(parser(str5, stack_N) == -1, "FAILED brackets_err_5");
  ck_assert_msg(parser(str6, stack_N) == -1, "FAILED brackets_err_6");
  ck_assert_msg(parser(str7, stack_N) == -1, "FAILED brackets_err_7");
  ck_assert_msg(parser(str8, stack_N) == -1, "FAILED brackets_err_8");
}
END_TEST

START_TEST(previous_next_ch) {
  int tmp = 1;
  char num[SIZE] = {0};
  char str[] = "0.345";

  prev_next_ch(1, str, 0, num);
  ck_assert_msg(strcmp(num, ".") == 0, "FAILED prev_next_ch_1");

  prev_next_ch(-1, str, 1, num);
  ck_assert_msg(strcmp(num, "0") == 0, "FAILED prev_next_ch_2");

  tmp = prev_next_ch(-1, str, 0, num);
  ck_assert_msg(tmp == -1, "FAILED prev_next_ch_3");

  tmp = prev_next_ch(1, str, 4, num);
  ck_assert_msg(tmp == -1, "FAILED prev_next_ch_4");
}

END_TEST

START_TEST(matematika_simple) {
  double res[SIZE] = {0};
  int tmp = 1;
  char x[SIZE] = "1";

  char str[SIZE] = "0.345+5";
  s21_calc(str, x, res);
  ck_assert_msg(*res == 5.345, "FAILED matematika_simple_1");

  s21_calc("5+7-3-2", x, res);
  ck_assert_msg(*res == 7, "FAILED matematika_simple_2");

  s21_calc("5+7-3*2", x, res);
  ck_assert_msg(*res == 6, "FAILED matematika_simple_3");

  s21_calc("5+7*3-3*2", x, res);
  ck_assert_msg(*res == 20, "FAILED matematika_simple_4");

  s21_calc("5+7-3/2", x, res);
  ck_assert_msg(*res == 10.5, "FAILED matematika_simple_5");

  s21_calc("3*(5+6)-2*4-(8*9/3-6)", x, res);
  ck_assert_msg(*res == 7, "FAILED matematika_simple_6");

  s21_calc("3*(5+6)-2*4-(8*9/3-6)/7", x, res);
  ck_assert_msg(*res == 22.4285714285714286, "FAILED matematika_simple_7");

  s21_calc("3*(5+6)-2*4-(8*9/3-6)/7-2*3", x, res);
  ck_assert_msg(*res == 16.4285714285714286, "FAILED matematika_simple_8");

  s21_calc("3-(5+6)*(2+4)-8*9-6/7-2*3", x, res);
  ck_assert_msg(*res == -141.8571428571428571, "FAILED matematika_simple_9");

  tmp = s21_calc("(5+4-2*5)/(5-5)", x, res);
  ck_assert_msg(tmp == -2, "FAILED FAILED matematika_simple_10");

  tmp = s21_calc("(4+10)/0*2+1", x, res);
  ck_assert_msg(tmp == -2, "FAILED FAILED matematika_simple_11");

  s21_calc("80/2", x, res);
  ck_assert_msg(*res == 40, "FAILED matematika_simple_12");

  s21_calc("80/(2-10)", x, res);
  ck_assert_msg(*res == -10, "FAILED matematika_simple_13");

  s21_calc("80/(-10)", x, res);
  ck_assert_msg(*res == -8, "FAILED matematika_simple_14");

  s21_calc("-80/(-10)", x, res);
  ck_assert_msg(*res == 8, "FAILED matematika_simple_15");

  s21_calc("-(5+1)", x, res);
  ck_assert_msg(*res == -6, "FAILED matematika_simple_16");

  s21_calc("-(-(5+2)*4)", x, res);
  ck_assert_msg(*res == 28, "FAILED matematika_simple_17");

  s21_calc("-(+(5+2)*4)", x, res);
  ck_assert_msg(*res == -28, "FAILED matematika_simple_18");

  s21_calc("5", x, res);
  ck_assert_msg(*res == 5, "FAILED matematika_simple_19");

  s21_calc("-5", x, res);
  ck_assert_msg(*res == -5, "FAILED matematika_simple_20");

  s21_calc("sin(cos(log(5^2)))", x, res);
  *res = *res - (0.17115002489);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_simple_21");

  s21_calc("sin(cos(tan(acos(asin(atan(log(-1*ln(sqrt(5mod3^-2+x))))))))", x,
           res);
  *res = *res - (0.71188622115482);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_simple_21");

  s21_calc("sqrt((-2)*(-2))", x, res);
  *res = *res - (2);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_simple_21");
}
END_TEST

START_TEST(matematika_trig_1) {
  double res[SIZE] = {0};
  char x[SIZE] = "46";

  char *str = "sin(5)";
  s21_calc(str, x, res);
  *res = *res - (-0.95892427466);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_1");

  s21_calc("cos(5)", x, res);
  *res = *res - (0.28366218546);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_2");

  s21_calc("cos(45)", x, res);
  *res = *res - (0.52532198881);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_3");

  s21_calc("cos(45)+sin(67)", x, res);
  *res = *res - (0.98687716056);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_4");

  s21_calc("-cos(45)+sin(67)", x, res);
  *res = *res - (0.98687716056);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_5");

  s21_calc("-cos(45)", x, res);
  *res = *res - (-0.52532198881);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_6");

  s21_calc("1-cos(45)", x, res);
  *res = *res - (0.47467801118);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_7");

  s21_calc("1-(-cos(45))", x, res);
  *res = *res - (1.52532198882);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_8");

  s21_calc("1-(-(-cos(45)))", x, res);
  *res = *res - (0.47467801118);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_9");

  s21_calc("acos(0.5)", x, res);
  *res = *res - (1.0471975511966);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_10");

  s21_calc("asin(0.5)", x, res);
  *res = *res - (0.523598775598299);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_10");

  s21_calc("atan(x)", x, res);
  *res = *res - (1.5490606199531);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_10");

  s21_calc("sin(x)", x, res);
  *res = *res - (0.90178834764881);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_trig_1_10");
}
END_TEST

START_TEST(matematika_log_1) {
  double res[SIZE] = {0};
  char x[SIZE] = "1";

  s21_calc("log(5)", x, res);
  *res = *res - (0.6989700043360189);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_log_1_1");

  s21_calc("ln(5)", x, res);
  *res = *res - (1.6094379124341004);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_log_1_2");

  s21_calc("log(45)", x, res);
  *res = *res - (1.6532125137753437);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_log_1_3");

  s21_calc("ln(45)+log(67)", x, res);
  *res = *res - (5.6327372924711462);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_log_1_4");

  s21_calc("(-log(45)+sin(67))-(ln(10)+log(56))", x, res);
  *res = *res - (-6.55950561275);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_log_1_5");

  s21_calc("-ln(45-20)", x, res);
  *res = *res - (-3.2188758248682007);
  ck_assert_msg(*res <= 0.00000001, "FAILED matematika_log_1_6");
}
END_TEST

START_TEST(matematika_mod) {
  double res[SIZE] = {0};
  char x[SIZE] = "1";

  s21_calc("45mod4", x, res);
  ck_assert_msg(*res == 1, "FAILED matematika_mod_1");

  s21_calc("(2+3*5)mod(3*2)", x, res);
  ck_assert_msg(*res == 5, "FAILED matematika_mod_2");

  s21_calc("(2^2^2)mod3", x, res);
  ck_assert_msg(*res == 1, "FAILED matematika_mod_3");

  s21_calc("5mod2+33mod6*6", x, res);
  ck_assert_msg(*res == 19, "FAILED matematika_mod_4");

  s21_calc("(-7)mod(7mod4)", x, res);
  ck_assert_msg(*res == -1, "FAILED matematika_mod_5");

  s21_calc("-ln(45-20)", x, res);
  ck_assert_msg(*res == -3.2188758248682007, "FAILED matematika_mod_6");
}
END_TEST

START_TEST(matematika_pow) {
  double res[SIZE] = {0};
  char x[SIZE] = "1";

  s21_calc("2^(-1+1*3)", x, res);
  ck_assert_msg(*res == 4, "FAILED matematika_pow_1");

  s21_calc("2^(-1+1*3)+5*4", x, res);
  ck_assert_msg(*res == 24, "FAILED matematika_pow_2");

  s21_calc("2^(-2)", x, res);
  ck_assert_msg(*res == 0.25, "FAILED matematika_pow_3");

  s21_calc("(-3^(-3)", x, res);
  *res = *res - (-0.037037037037037);
  ck_assert_msg(*res >= 0.00000001, "FAILED matematika_pow_4");
}
END_TEST

START_TEST(matematika_x) {
  double res[SIZE] = {0};
  char x[SIZE] = "5";

  s21_calc("x^2+3*x", x, res);
  ck_assert_msg(*res == 40, "FAILED matematika_x_1");

  s21_calc("3*x", x, res);
  ck_assert_msg(*res == 15, "FAILED matematika_x_2");

  s21_calc("x*3", x, res);
  ck_assert_msg(*res == 15, "FAILED matematika_x_3");

  s21_calc("3*x+2*x", x, res);
  ck_assert_msg(*res == 25, "FAILED matematika_x_4");

  s21_calc("3*x+2+x", x, res);
  ck_assert_msg(*res == 22, "FAILED matematika_x_5");

  s21_calc("-x", x, res);
  ck_assert_msg(*res == -5, "FAILED matematika_x_6");

  char x2[SIZE] = "-5";

  s21_calc("x^2+3*x", x2, res);
  ck_assert_msg(*res == 10, "FAILED matematika_x_7");

  s21_calc("3*x", x2, res);
  ck_assert_msg(*res == -15, "FAILED matematika_x_8");

  s21_calc("x*3", x2, res);
  ck_assert_msg(*res == -15, "FAILED matematika_x_9");

  s21_calc("3*x+2*x", x2, res);
  ck_assert_msg(*res == -25, "FAILED matematika_x_10");

  s21_calc("3*x+2+x", x2, res);
  ck_assert_msg(*res == -18, "FAILED matematika_x_11");

  s21_calc("-x", x2, res);
  ck_assert_msg(*res == 5, "FAILED matematika_x_12");
}
END_TEST

START_TEST(matematika_err) {
  double res[SIZE] = {0};
  char x[SIZE] = "-1";

  ck_assert_msg(s21_calc("-cos(45)sin(67)", x, res) == -1,
                "FAILED matematika_err_1");
  ck_assert_msg(s21_calc("1 - cos(45)", x, res) == -1,
                "FAILED matematika_err_1");
  ck_assert_msg(s21_calc("-cos(45)+sin(-67)", x, res) == 0,
                "FAILED matematika_err_2");
  ck_assert_msg(s21_calc("-cos(+45)+sin(67)", x, res) == 0,
                "FAILED matematika_err_3");
  ck_assert_msg(s21_calc("-ln(45)+sin(67)", x, res) == 0,
                "FAILED matematika_err_4");
  ck_assert_msg(s21_calc("5mod4+sin(67)", x, res) == 0,
                "FAILED matematika_err_5");
  ck_assert_msg(s21_calc("2^2^2", x, res) == 0, "FAILED matematika_err_6");
  ck_assert_msg(s21_calc("2^2^", x, res) == -1, "FAILED matematika_err_7");
  ck_assert_msg(s21_calc("2^(-1+1*3)", x, res) == 0, "FAILED matematika_err_8");
  ck_assert_msg(s21_calc("2^(-1+1*3)+5*4", x, res) == 0,
                "FAILED matematika_err_9");
  ck_assert_msg(s21_calc("log(-45)", x, res) == -3, "FAILED matematika_err_10");
  ck_assert_msg(s21_calc("6mod(-4)", x, res) == 0, "FAILED matematika_err_11");
  ck_assert_msg(s21_calc("(-5)mod(-4)", x, res) == 0,
                "FAILED matematika_err_12");
  ck_assert_msg(s21_calc("(-5)mod(6mod4)", x, res) == 0,
                "FAILED matematika_err_13");
  ck_assert_msg(s21_calc("(2+3*5)mod(3*2)", x, res) == 0,
                "FAILED matematika_err_14");
  ck_assert_msg(s21_calc("atan(3*2)", x, res) == 0, "FAILED matematika_err_15");
  ck_assert_msg(s21_calc("asin(5)", x, res) == -3, "FAILED matematika_err_16");
  ck_assert_msg(s21_calc("asin(0.4)", x, res) == 0, "FAILED matematika_err_17");
  ck_assert_msg(s21_calc("acos(5)", x, res) == -3, "FAILED matematika_err_18");
  ck_assert_msg(s21_calc("acos(0.5)", x, res) == 0, "FAILED matematika_err_19");
  ck_assert_msg(s21_calc("atan(5)", x, res) == 0, "FAILED matematika_err_20");
  ck_assert_msg(s21_calc("sin(0.4)", x, res) == 0, "FAILED matematika_err_21");
  ck_assert_msg(s21_calc("cos(5)", x, res) == 0, "FAILED matematika_err_22");
  ck_assert_msg(s21_calc("tan(5)", x, res) == 0, "FAILED matematika_err_23");
  ck_assert_msg(s21_calc("ln(-5)", x, res) == -3, "FAILED matematika_err_24");
  ck_assert_msg(s21_calc("log(-5)", x, res) == -3, "FAILED matematika_err_24");
  ck_assert_msg(s21_calc("10mod(5-5)", x, res) == -2,
                "FAILED matematika_err_25");
  ck_assert_msg(s21_calc("10mod(-x)", x, res) == 0, "FAILED matematika_err_26");
  ck_assert_msg(s21_calc("10modx", x, res) == 0, "FAILED matematika_err_27");
  ck_assert_msg(s21_calc("xmod5", x, res) == 0, "FAILED matematika_err_28");
  ck_assert_msg(s21_calc("(-x)mod5", x, res) == 0, "FAILED matematika_err_29");
  ck_assert_msg(s21_calc("sqrt(x)", x, res) == -3, "FAILED matematika_err_30");
  ck_assert_msg(s21_calc("sqrt(-1)", x, res) == -3, "FAILED matematika_err_31");
  ck_assert_msg(s21_calc("sqrt(4)", x, res) == 0, "FAILED matematika_err_32");
  ck_assert_msg(s21_calc("5^-3)", x, res) == -1, "FAILED matematika_err_32");
}
END_TEST

// START_TEST(matematika_memory) {
//   Stack_t stack_N[10] = {0};
//   Stack_t polish[10] = {0};
//   double res[SIZE] = {0};
//   char x[SIZE] = "-1";

//   ck_assert_msg(parser(NULL, stack_N) == -4, "FAILED parser_atan_1");
//   ck_assert_msg(parser("sqrt(4)", NULL) == -4, "FAILED parser_atan_1");
//   ck_assert_msg(s21_calc("sqrt(4)", x, NULL) == -4,
//                 "FAILED matematika_memory_1");
//   ck_assert_msg(s21_calc("sqrt(4)", NULL, res) == -4,
//                 "FAILED matematika_memory_1");
//   ck_assert_msg(s21_calc(NULL, x, res) == -4, "FAILED matematika_memory_1");
//   ck_assert_msg(matematika(NULL, res) == -4, "FAILED matematika_memory_1");
//   ck_assert_msg(matematika(polish, NULL) == -4, "FAILED
//   matematika_memory_1"); ck_assert_msg(polish_notation(stack_N, NULL) == -4,
//                 "FAILED matematika_memory_1");
//   ck_assert_msg(polish_notation(NULL, polish) == -4,
//                 "FAILED matematika_memory_1");
// }

START_TEST(matematika_other) {
  Stack_t stack_N[1] = {0};
  double value[SIZE] = {0.7};

  push_num(stack_N, value, 1);
  push_num(stack_N, value, 1);
  // ck_assert_msg(push_num(stack_N, &value, 1) == -100, "FAILED
  // matematika_other");

  ck_assert_msg(check_number("10") == 0, "FAILED matematika_other_1");
  ck_assert_msg(check_number("01") == -1, "FAILED matematika_other_2");
  ck_assert_msg(check_number("01.") == -1, "FAILED matematika_other_3");
  ck_assert_msg(check_number("00.") == -1, "FAILED matematika_other_4");
  ck_assert_msg(check_number("0.001") == 0, "FAILED matematika_other_5");
  ck_assert_msg(check_number("001") == -1, "FAILED matematika_other_6");
  ck_assert_msg(check_number("100000.00001") == 0, "FAILED matematika_other_7");
  ck_assert_msg(check_number("0.0000000001") == 0, "FAILED matematika_other_8");
  ck_assert_msg(check_number("00") == -1, "FAILED matematika_other_9");
  ck_assert_msg(check_number("00..") == -1, "FAILED matematika_other_10");
  ck_assert_msg(check_number("0.0.1") == -1, "FAILED matematika_other_11");
  ck_assert_msg(check_number("00.1") == -1, "FAILED matematika_other_12");
  ck_assert_msg(check_number("0.1") == 0, "FAILED matematika_other_13");
  ck_assert_msg(check_number("-0.1") == 0, "FAILED matematika_other_14");
  ck_assert_msg(check_number("-3") == 0, "FAILED matematika_other_15");
  ck_assert_msg(check_number("-0.0001") == 0, "FAILED matematika_other_16");
  ck_assert_msg(check_number("-0.000000") == 0, "FAILED matematika_other_17");
  ck_assert_msg(check_number("0.000000") == 0, "FAILED matematika_other_18");
}
END_TEST

START_TEST(credit_calc) {
  credit_t credit_N[10];
  credit_N->type = 1;
  credit_N->total_credit = 60000;
  credit_N->period = 6;
  credit_N->period_uom = 'm';  // y - year, m - month
  credit_N->percent_rate = 24;
  credit_N->overpayment = 0.0;
  credit_N->month_min = 0.0;
  credit_N->month_max = 0.0;

  calc_credit(credit_N);
  ck_assert_msg(credit_N->overpayment == 4200, "FAILED credit_a_1");
  ck_assert_msg(credit_N->month_max == 11200, "FAILED credit_a_2");
  ck_assert_msg(credit_N->month_min == 10200, "FAILED credit_a_3");

  credit_N->period_uom = 'y';
  credit_N->period = 0.5;
  calc_credit(credit_N);

  credit_N->overpayment = credit_N->overpayment - 4200;
  ck_assert_msg(credit_N->overpayment <= 0, "FAILED credit_a_4");
  credit_N->month_max = credit_N->month_max - 10120;
  ck_assert_msg(credit_N->month_max <= 0, "FAILED credit_a_5");

  credit_N->type = 2;
  calc_credit(credit_N);

  credit_N->overpayment = credit_N->overpayment - 4400;
  ck_assert_msg(credit_N->overpayment <= 0, "FAILED credit_d_1");
  credit_N->month_max = credit_N->month_max - 10740;
  ck_assert_msg(credit_N->month_max <= 0, "FAILED credit_d_2");
  credit_N->month_min = credit_N->month_min - 10740;
  ck_assert_msg(credit_N->month_min <= 0, "FAILED credit_d_3");

  credit_N->period_uom = 'm';
  credit_N->period = 6;
  calc_credit(credit_N);

  credit_N->overpayment = credit_N->overpayment - 4269;
  ck_assert_msg(credit_N->overpayment <= 0, "FAILED credit_d_4");
  credit_N->month_max = credit_N->month_max - 10711;
  ck_assert_msg(credit_N->month_max <= 0, "FAILED credit_d_5");
}
END_TEST

Suite *s21_calc_suite(void) {
  Suite *suite = suite_create("s21_calc_suite");
  TCase *tcase_core = tcase_create("s21_calc_suite");

  suite_add_tcase(suite, tcase_core);

  tcase_add_test(tcase_core, number_1);
  tcase_add_test(tcase_core, number_err);
  tcase_add_test(tcase_core, parser_sin);
  tcase_add_test(tcase_core, parser_cos);
  tcase_add_test(tcase_core, parser_tan);
  tcase_add_test(tcase_core, parser_asin);
  tcase_add_test(tcase_core, parser_acos);
  tcase_add_test(tcase_core, parser_atan);
  tcase_add_test(tcase_core, parser_log);
  tcase_add_test(tcase_core, parser_ln);
  tcase_add_test(tcase_core, parser_x);
  tcase_add_test(tcase_core, parser_sqrt);
  tcase_add_test(tcase_core, parser_space);
  tcase_add_test(tcase_core, parser_pow);
  tcase_add_test(tcase_core, parser_mod);
  tcase_add_test(tcase_core, znak_1);
  tcase_add_test(tcase_core, znak_err);
  tcase_add_test(tcase_core, brackets_err);
  tcase_add_test(tcase_core, previous_next_ch);

  tcase_add_test(tcase_core, matematika_simple);
  tcase_add_test(tcase_core, matematika_trig_1);
  tcase_add_test(tcase_core, matematika_log_1);
  tcase_add_test(tcase_core, matematika_mod);
  tcase_add_test(tcase_core, matematika_pow);
  tcase_add_test(tcase_core, matematika_x);
  tcase_add_test(tcase_core, matematika_err);
  // tcase_add_test(tcase_core, matematika_memory);
  tcase_add_test(tcase_core, matematika_other);
  tcase_add_test(tcase_core, credit_calc);

  return suite;
}

int main(void) {
  Suite *suite = s21_calc_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_ENV);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
