#ifndef GRAFIC_H
#define GRAFIC_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QtMath>
#include <iostream>

extern "C" {
    #include "../s21_calc.h"
    #include <string>
}

namespace Ui {
class Grafic;
}

class Grafic : public QMainWindow
{
    Q_OBJECT

public:
    explicit Grafic(QWidget *parent, QString str_out);
    ~Grafic();
    QString str;

private:
    Ui::Grafic *ui;

    double xBegin, xEnd, h, X;
    double yBegin, yEnd, Y;
    int err3 = 0;
    int N = 0;

    QVector<double> x,y;
    QTimer *timer;
    int time;
    void ChangeFunc();
    void StaticFunc();

//public slots:
//    void slot();

private slots:
    void TimerSlot();
    void on_pushButton_gr_clicked();
};

#endif // GRAFIC_H



