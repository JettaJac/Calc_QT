/**
 * @file      s21_calc.c
 * @author    jettajac
 * @brief
 * @version   0.1
 * @date      2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "s21_calc.h"

// #include "credit.c"
#include "helpers_functions.c"

/**
 * @brief          Основная функция калькулятора
 *
 * @param str      - Строка с арифметическим выражением
 * @param str_x    - Принимает значение X
 * @param result   - Возвращает итоговый результат арифмитического выражения
 * @return         - Вернет 0, если число поданно корректно и 1, если есть
 * ошибки
 */

int s21_calc(char *str, char *str_x, double *result) {
  Stack_t stack[STACK_MAX_SIZE] = {0};
  Stack_t polish[STACK_MAX_SIZE] = {0};
  stack->size = 0;
  int err = -1;

  if (str != NULL && str_x != NULL && result != 0) {
    strcpy(stack->x, str_x);
    err = parser(str, stack);
    // printstack(stack);
    if (err == TRUE) {
      err = polish_notation(stack, polish);
      // printstack(polish);
      if (err == TRUE) {
        err = matematika(polish, result);
      }
    }
  } else {
    err = FAIL;
  }
  return err;
}

/**
 * @brief          Парсим строчку арифмитеческого выражения
 *
 * @param str      - Строка с арифметическим выражением
 * @param stack    - Принимает значение X
 * @return         - Вернет 0, если число поданно корректно и 1, если есть
 * ошибки
 */

int parser(char *str, Stack_t *stack) {
  // flags fl = {0};
  int err = TRUE;
  char val[SIZE] = {0};
  int tmp = -1;
  char data_before[SIZE] = {0};
  char data_after[SIZE] = {0};
  int symbol_after = 0;
  int symbol_before = 0;
  int symbol = 0;
  int brackets = 0;
  int len = strlen(str);

  for (int symbol = 0; symbol < (len) && err == TRUE; symbol++) {
    err = FAIL;
    tmp = types(str, &symbol, val);
    if (symbol != 0) {
      symbol_before = prev_next_ch(-1, str, symbol, data_before);
    }
    symbol_after = prev_next_ch(1, str, symbol, data_after);
    if (*val == 'x') {
      strcpy(val, stack->x);
      tmp = 9;
      err = TRUE;
    }
    if (tmp != -1 && brackets >= 0) {
      // int res = parser_conditions(&fl);
      if (*val == ' ') {
        symbol++;
      } else if (tmp == 9 && check_number(val) == 0) {
        if (*data_after == ')' || symbol_after == 1 || symbol_after == 2 ||
            *data_after == '^' || *data_after == 'm' || symbol == (len - 1)) {
          err = TRUE;
        }
      } else if (symbol == len - 1) {
        if (*val == ')' || (tmp == 9 && check_number(val) == 0) ||
            *val == 'x') {
          err = TRUE;
          if (*val == ')') {
            brackets--;
          }
        }
      } else if (symbol == 0 &&
                 (*val == ')' || tmp == 2 || *val == 'm' || *val == '^')) {
      } else if ((symbol == 0 && tmp == 1 &&
                  (symbol_after == 4 || *data_after == '(' ||
                   *data_after == 'x' || symbol_after == 9)) ||
                 (tmp == 1 && (*data_before == '(' || *data_before == '^') &&
                  (symbol_after == 9 || symbol_after == 4 ||
                   *data_after == '(' || *data_after == 'x'))) {
        err = TRUE;
        intunar_znak(val, &tmp);
      } else if (tmp == 1 || (tmp == 2 && symbol != 0)) {
        if (symbol_after != 1 && symbol_after != 2 && *data_after != ')') {
          err = TRUE;
        }
      } else if (*val == ')') {
        if (*data_after == '\0' || *data_after == '^' || *data_after == ')' ||
            *data_after == 'm' || symbol_after == 1 || symbol_after == 2) {
          brackets--;
          err = TRUE;
        }
      } else if ((tmp == 4 && *val != 'm') || *val == '(') {
        brackets++;
        err = TRUE;
        if (*data_after == ')' || *data_after == '^' || symbol_after == 2) {
          err = FAIL;
        }
      } else if (*val == 'm') {
        int symbol_tmp = symbol - 2;
        symbol_before = prev_next_ch(-1, str, symbol_tmp, data_before);
        if (symbol_before == 9 || *data_before == ')' || *data_before == 'x') {
          symbol_after = prev_next_ch(1, str, symbol, data_after);
          if (symbol_after == 9 || *data_after == '(' || *data_after == 'x') {
            err = TRUE;
          }
        }
      } else if (tmp == 5) {
        err = TRUE;
      } else if (tmp < 6 && tmp > 0) {
        err = FAIL;
      }
      if (err == TRUE) {
        push(stack, val, tmp);
      }
    } else
      err = FAIL;
  }
  if (types(str, &symbol, val) == -1 || brackets != 0) err = FAIL;
  return err;
}

/**
 * @brief          Создаем польскую анотацию из арифмитического выражения
 *
 * @param stack    - Стек из операторов и операндов в арифмитической
 * последовательности
 * @param polish   - Стек из операторов и операндов в польской натации
 * @return         - Вернет 0, если число поданно корректно и 1, если есть
 * ошибки
 */

int polish_notation(Stack_t *stack, Stack_t *polish) {
  int err = TRUE;
  Stack_t znak = {0};
  int len = stack->size;
  char doub[SIZE];  // Временная переменная для стека знак

  for (int count = 1; count <= len; count++) {
    if (stack->pri[count] == 9) {
      push(polish, stack->data[count], stack->pri[count]);
    } else if (*stack->data[count] == '(' || stack->pri[count] == 4) {
      push(&znak, stack->data[count], stack->pri[count]);
    } else if (*stack->data[count] == ')') {
      for (int len = znak.size;
           *znak.data[len] != '(' && znak.pri[len] != 4 && err == TRUE; len--) {
        strcpy(doub, znak.data[znak.size]);
        pop_push(&znak, polish, doub, znak.pri[znak.size + 1]);
        if (len == 0) err = FAIL;
      }
      if (*znak.data[znak.size] == '(' || znak.pri[znak.size] == 4) {
        pop(&znak);
        strcpy(doub, znak.data[znak.size + 1]);
        if (znak.pri[znak.size + 1] == 4) {
          push(polish, doub, znak.pri[znak.size + 1]);
        }
      }
    } else if (stack->pri[count]) {
      polish_check(&znak, polish, stack, count);
    }
    if (count == len) {
      int len_znak = znak.size;
      for (; len_znak > 0; len_znak--) {
        strcpy(doub, znak.data[znak.size]);
        pop_push(&znak, polish, doub, znak.pri[znak.size + 1]);
        err = TRUE;
      }
    }
  }
  return err;
}

/**
 * @brief          Создаем польскую анотацию из арифмитического выражения
 *
 * @param polish   - Стек из операторов и операндов в польской натации
 * @param result   - Возвращает итоговый результат арифмитического выражения
 * @return         - Вернет 0, если число поданно корректно и 1, если есть
 * ошибки
 */

int matematika(Stack_t *polish, double *result) {
  int err = TRUE;
  double res = -0;
  Stack_t num = {0};
  int size_v = polish->size;

  for (int len = 1; len <= size_v; len++) {
    if (*polish->data[len] == 'u' || *polish->data[len] == 'p') {
      if (*polish->data[len] == 'u') {
        res = -num.number[num.size];
      } else {
        res = num.number[num.size];
      }
      num.size--;
      push_num(&num, &res, 9);
    } else if (polish->pri[len] == 9) {
      push(&num, polish->data[len], polish->pri[len]);
      res = num.number[num.size];
    } else if (*polish->data[len] == '+') {
      res = num.number[num.size] + num.number[num.size - 1];
      num.size = num.size - 2;
      push_num(&num, &res, 9);
    } else if (*polish->data[len] == '-') {
      res = num.number[num.size - 1] - num.number[num.size];
      num.size = num.size - 2;
      push_num(&num, &res, 9);
    } else if (*polish->data[len] == '*') {
      res = num.number[num.size] * num.number[num.size - 1];
      num.size = num.size - 2;
      push_num(&num, &res, 9);
    } else if (*polish->data[len] == '/') {
      if (num.number[num.size] != 0) {
        res = num.number[num.size - 1] / num.number[num.size];
        num.size = num.size - 2;
        push_num(&num, &res, 9);
      } else {
        err = ZERO;
      }
    } else if (*polish->data[len] == '^') {
      res = pow(num.number[num.size - 1], num.number[num.size]);
      num.size = num.size - 2;
      push_num(&num, &res, 9);
    } else if (strncmp(polish->data[len], "cos(", 4) == 0) {
      res = cos(num.number[num.size]);
      matemat_res(&num, &res, 1);
    } else if (strncmp(polish->data[len], "sin(", 4) == 0) {
      res = sin(num.number[num.size]);
      matemat_res(&num, &res, 1);
    } else if (strncmp(polish->data[len], "tan(", 4) == 0) {
      res = tan(num.number[num.size]);
      matemat_res(&num, &res, 1);
    } else if (strncmp(polish->data[len], "acos(", 5) == 0) {
      if (num.number[num.size] >= -1 && num.number[num.size] <= 1) {
        res = acos(num.number[num.size]);
        matemat_res(&num, &res, 1);
      } else {
        err = EFUC;
      }
    } else if (strncmp(polish->data[len], "asin(", 5) == 0) {
      if (num.number[num.size] >= -1 && num.number[num.size] <= 1) {
        res = asin(num.number[num.size]);
        matemat_res(&num, &res, 1);
      } else {
        err = EFUC;
      }
    } else if (strncmp(polish->data[len], "atan(", 5) == 0) {
      res = atan(num.number[num.size]);
      matemat_res(&num, &res, 1);
    } else if (strncmp(polish->data[len], "log(", 4) == 0) {
      if (num.number[num.size] > 0) {
        res = log10(num.number[num.size]);
        matemat_res(&num, &res, 1);
      } else {
        err = EFUC;
      }
    } else if (strncmp(polish->data[len], "ln(", 3) == 0) {
      if (num.number[num.size] > 0) {
        res = log(num.number[num.size]);
        matemat_res(&num, &res, 1);
      } else {
        err = EFUC;
      }
    } else if (strncmp(polish->data[len], "sqrt(", 5) == 0) {
      if (num.number[num.size] >= 0) {
        res = sqrt(num.number[num.size]);
        matemat_res(&num, &res, 1);
      } else {
        err = EFUC;
      }
    } else if (strncmp(polish->data[len], "mod", 3) == 0) {
      if (num.number[num.size] != 0) {
        res = fmod(num.number[num.size - 1], num.number[num.size]);
        matemat_res(&num, &res, 2);
      } else {
        err = ZERO;
      }
    }
  }
  *result = res;
  return err;
}
