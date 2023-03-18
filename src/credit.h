#ifndef SRC_CORE_CREDIT_H
#define SRC_CORE_CREDIT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_calc.h"

/**
 * @brief                   Сруктура вводных данных и результатов для кредитного
 * калькулятора
 *
 * @param type              - Тип платежа Аунитетный или Дифференцированный
 * @param total_credit      - Общая сумма кредита
 * @param period            - Количестко периодов (месяцев или лет)
 * @param period_uom        - Какой период, в месяцах или в годах
 * @param month_min         - Минимальная сумма ежемесячного платежа
 * @param month_max         - Максимальная сумма ежемесячного платежа
 * @param percent_rate      - Процент в год
 *
 * @param overpayment       - Переплата (только проценты)
 * @param total_overpayment - Общая сумма выплат с учетом тела кредита
 */

typedef struct credit {
  int type;  // Payment type Annuity or Differentiated
  int total_credit;
  double period;    // Loan period
  char period_uom;  // Period: months or years
  double month_min;
  double month_max;
  double percent_rate;
  double overpayment;  // Loan repayment (interest)
  double total_overpayment;
} credit_t;

int calc_credit(credit_t *data);

#endif  //  SRC_CORE_CREDIT_H