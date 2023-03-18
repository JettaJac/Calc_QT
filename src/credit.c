
/**
 * @file      credit.c
 * @author    jettajac
 * @brief
 * @version   0.1
 * @date      2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "credit.h"

/**
 * @brief          Кредитный калькулятор
 *
 * @param data     - Структура с вводными данными и результатом
 */

int calc_credit(credit_t *data) {
  int err = 1;
  double monthly_pay = 0.0;  // Ежемесячный платеж без %
  double overpayment = 0.0;  //
  double percent =
      data->percent_rate / 1200.0;  // Процентная ставка в рамках одного месяца
  int period_coeff =
      data->period_uom == 'y' ? 12 : 1;  // Определяем год или месяц
  int period = data->period * period_coeff;  // Количество месяцев, кредита

  if (data->type == 1) {  // Дифференцированный платеж
    monthly_pay = data->total_credit / period;  // Сумма ежемес.платежа (тело)
    for (int i = 0; i < period; i++) {
      overpayment += data->total_credit * percent;  // Максимальные переплаты %
      data->total_credit -= monthly_pay;
      if (i == 0) {
        data->month_max = overpayment + monthly_pay;
      } else if (i == period - 1) {
        data->month_min = monthly_pay * (1 + percent);
      }
      data->overpayment = overpayment;
      data->total_overpayment = overpayment + data->total_credit;
    }
    // printf("ПРОЦЕНТ_A _  %f - max: %f, min: %f  === %f   Общая сумма кредита
    // - %f\n", percent, data->month_max, data->month_min, data->overpayment,
    // data->total_overpayment);
    err = 0;
  } else {
    double tmp_percent = powl(1 + percent, period);
    double count_percent = percent * tmp_percent / (tmp_percent - 1);
    data->month_min = data->total_credit * count_percent;
    data->month_max = data->month_min;
    data->total_overpayment = roundl(data->month_min * 100) / 100 * period;
    data->overpayment = data->total_overpayment - data->total_credit;
    // printf("ПРОЦЕНТ_D _  %f - max: %f, min: %f  === %f   Общая сумма кредита
    // - %f\n", percent, data->month_max, data->month_min, data->overpayment,
    // data->total_overpayment);
    err = 0;
  }
  return err;
}