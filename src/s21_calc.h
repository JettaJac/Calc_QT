
/**
 * @file s21__calc.h
 * @author jettajac
 * @brief
 * @version 0.1
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SRC_S21_calc_H
#define SRC_S21_calc_H

// 9: number
// 1: + and -
// 2: * and /
// 3: ()
// 4: sin, cos, tg, ctg, log, square root,
// 5:  x, ^. mod
// 6:  unar

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//// Libraries and files used
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <credit.h>
// #include <unistd.h>
// #include <stdnoreturn.h>
// #include <stdbool.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//// Error code
#define TRUE 0
#define FAIL -1
#define ZERO -2
#define EFUC -3  // неправильно введены значения в функциях

// #define size_t
// #define STACK_OVERFLOW 10
#define STACK_MAX_SIZE 100
#define INIT_SIZE 10

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102
// typedef double T;

#define SIZE 300
#define SIZE_N 100

/**
 * @brief           Структура стека для записи чисел и операторов
 *
 * @param data       - Cтэк чисел в строковом эквиваленте
 * @param number     - Cтэк чисел в числовом эквиваленте
 * @param pri  - Приоритет стека
 * @param x          - Значение Х
 *@param size       - Количество элементов в стеке
 */

typedef struct stack_tag {
  char data[STACK_MAX_SIZE][SIZE];
  double number[STACK_MAX_SIZE];
  int pri[STACK_MAX_SIZE];  // prioritet
  char x[SIZE];
  size_t size;
  // double *x;
  // size_t top;
} Stack_t;

typedef struct {
  char str[SIZE];
  char val[SIZE];
  int tmp;
  char data_before[SIZE];
  char data_after[SIZE];
  int symbol_after;
  int symbol_before;
  int symbol;
  int brackets;
} flags;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//// Stack functions
void push(Stack_t *stack, char *value, int prioritet);
void push_num(Stack_t *stack, double *value, int prioritet);
void pop(Stack_t *stack);
void pop_push(Stack_t *stack, Stack_t *stack2, char *val, int tmp);
void printvalue_stack(char *value);
void printstack(Stack_t *stack);

int prev_next_ch(int flag, char *str, int symbol, char *value);
int number(char *str, double *number);

int s21_calc(char *str, char *str_x, double *result);
int parser(char *str, Stack_t *stack);
int polish_notation(Stack_t *stack, Stack_t *polish);
int matematika(Stack_t *polish, double *result);
void matemat_res(Stack_t *number, double *res, int tmp);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//// Check functions
int check_number(char *str);
int check_funcs(char *str, int *count);
int polish_check(Stack_t *znak, Stack_t *polish, Stack_t *stack, int count);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//// Parsing
int types(char *str, int *lent, char *value);
int pars_baskets(char *val, int tmp, int symbol);
int unar_znak(char *val, int *tmp);

// int parser_conditions(int *symbol, flags *fl);
// int parser_check (flags *fl);

#endif  // SRC_S21_calc_H
