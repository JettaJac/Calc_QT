/*!
 * @file      credit.cpp
 * @author    jettajac
 * @brief
 * @version   0.1
 * @date      2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);

    credit_t *credit;
}

Credit::~Credit()
{
    delete ui;
}


//typedef struct credit {
//    int type;               // Payment type Annuity or Differentiated
//    int total_credit;
//    double period;             // Loan period
//    char period_uom;        // Period: months or years
//    double month_min;
//    double month_max;
//    double percent_rate;
//    double overpayment;     // Loan repayment (interest)
//    double total_overpayment;
//} credit_t;




//void Credit::on_doubleSpinBox_2_textChanged(const QString &arg1)
//{
//    QString total_credit = arg1;
//}


//void Credit::on_spinBox_totalcredit_textChanged(const QString &arg1)
//{
//    QString total_credit_q = arg1;
////    total_credit
////    credit_N->total_credit = ui->spinBox_totalcredit->value();;
//}


void Credit::on_pushButton_clicked()
{
      int err = 0;
//    QString input = str;
//    std::string str_pp = input.toStdString();
//    char *str_input = new char[str_pp.length() + 1];
//    strcpy(str_input, str_pp.c_str());
//    char *str_x = new char[str_pp_x.length() + 1];
//    err2 = s21_calc(str_input, str_x, &Y);

    credit_t *credit_N = new credit_t[1];


//    char *str_input = new char[str_pp.length() + 1];



    credit_N->total_credit = ui->spinBox_totalcredit->value();

    if (ui->checkBox_diff->isChecked()) {
        credit_N->type = 1;
    } else if (ui->checkBox_aunt->isChecked()) {
        credit_N->type = 2;
    } else {
     err = 1;
    }
    credit_N->period = ui->doubleSpinBox_period->value();
    ;
    if (ui->checkBox_year->isChecked()) {
        credit_N->period_uom = 'y';
    } else if (ui->checkBox_month->isChecked()) {
        credit_N->period_uom = 'm';
    } else {
        err = 1;
    }
    credit_N->percent_rate = ui->doubleSpinBox_precent_rate->value();

    int err2 = calc_credit(credit_N);
    if (err == 0 && err2 == 0) {


    //    QString m_min = QString::fromStdString(std::to_string(credit_N->month_min));;
        QString m_min = QString("%1").arg(QString::number (credit_N->month_min, 'f', 0));
        ui->month_min->setText(m_min);

    //    QString m_max = QString::fromStdString(std::to_string(credit_N->month_max));;
        QString m_max = QString("%1").arg(QString::number (credit_N->month_max, 'f', 0));
        ui->month_max->setText(m_max);

    //    QString tmp = QString::fromStdString(std::to_string(credit_N->overpayment));;
        QString over_m = QString("%1").arg(QString::number (credit_N->overpayment, 'f', 0)); // Выводим только целое число
        ui->overpayment->setText(over_m);

    //    QString t_over_m = QString::fromStdString(std::to_string(credit_N->total_overpayment));;
        QString t_over_m = QString("%1").arg(credit_N->total_overpayment, 0,'f', 0); // Выводим только целое число альтернатива
        ui->total_overpayment->setText(t_over_m);
    } else {
        ui->month_min->setText("0");
        ui->month_max->setText("0");
        ui->overpayment->setText("0");
        ui->total_overpayment->setText("0");
    }
}


void Credit::on_checkBox_aunt_stateChanged(int arg1)
{
    ui->checkBox_diff->setChecked(false);

}


void Credit::on_checkBox_diff_stateChanged(int arg1)
{
    ui->checkBox_aunt->setChecked(false);
}


void Credit::on_checkBox_month_stateChanged(int arg1)
{
    ui->checkBox_year->setChecked(false);
}


void Credit::on_checkBox_year_stateChanged(int arg1)
{
    ui->checkBox_month->setChecked(false);
}

