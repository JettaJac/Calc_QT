#ifndef CREDIT_H
#define CREDIT_H

#include <QMainWindow>

extern "C" {
    #include "../credit.h"
    #include <string>
}

namespace Ui {
class Credit;
}

class Credit : public QMainWindow
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();



private slots:
//    void on_doubleSpinBox_2_textChanged(const QString &arg1);
//    void on_spinBox_totalcredit_textChanged(const QString &arg1);
    void on_pushButton_clicked();
//    void on_checkBox_stateChanged(int arg1);
//    void on_checkBox_aunt_stateChanged(int arg1);

    void on_checkBox_aunt_stateChanged(int arg1);

    void on_checkBox_diff_stateChanged(int arg1);

    void on_checkBox_month_stateChanged(int arg1);

    void on_checkBox_year_stateChanged(int arg1);

private:
    Ui::Credit *ui;

//    typedef struct credit {
//        int type;               // Payment type Annuity or Differentiated
//        int total_credit;
//        double period;             // Loan period
//        char period_uom;        // Period: months or years
//        double month_min;
//        double month_max;
//        double percent_rate;
//        double overpayment;     // Loan repayment (interest)
//        double total_overpayment;
//    } credit_t;


//    typedef struct credit {
//        int type;               // Payment type Annuity or Differentiated
//        int total_credit;
//        double period;             // Loan period
//        char period_uom;        // Period: months or years
//        double month_min;
//        double month_max;
//        double percent_rate;
//        double overpayment;     // Loan repayment (interest)
//        double total_overpayment;
//    } credit_t;

//    credit_t *credit_N;
};

#endif // CREDIT_H
