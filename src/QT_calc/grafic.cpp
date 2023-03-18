/*!
 * @file      grafic.cpp
 * @author    jettajac
 * @brief
 * @version   0.1
 * @date      2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "grafic.h"
#include "ui_grafic.h"



Grafic::Grafic(QWidget *parent, QString str_out) :
    QMainWindow(parent),
    ui(new Ui::Grafic)
{
    ui->setupUi(this);
    str = str_out;

    ui->label_fun->setText("y = " + str);

    xBegin = ui->spinBox_xs->value();
    xEnd = ui->spinBox_xe->value();
    yBegin = ui->spinBox_ys->value();
    yEnd = ui->spinBox_ye->value();

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

}

Grafic::~Grafic()
{
    delete ui;
}

void Grafic::TimerSlot()
{

    if(time <= 20*N)
    {
        if(X <= xEnd)
        {

            QString input = str;
            std::string str_pp = input.toStdString();
            std::string str_pp_x = std::to_string(X);

//            QString input_x = QString::fromStdString(std::to_string(X));; // Альтернативный способ преобразования дабл в стринги по указате
//            std::string str_pp_x = input_x.toStdString();

            char *str_input = new char[str_pp.length() + 1];
            char *str_x = new char[str_pp_x.length() + 1];
            strcpy(str_input, str_pp.c_str());
            strcpy(str_x, str_pp_x.c_str());

            err3 = s21_calc(str_input, str_x, &Y);

            if (err3 == 0){
                x.push_back(X);
                y.push_back(Y);
            }
            X += h;
        }
        time +=20;
     } else {
        time = 0;
        timer->stop();
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
}

void Grafic::StaticFunc(){
    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    N = 5000;
    X=xBegin;
    h = (xEnd - xBegin)/5000;
    int err2 = 0;

    for (int count = 0; count < N ; count++){

            X = X + h;

            QString input = str;
            std::string str_pp = input.toStdString();
            std::string str_pp_x = std::to_string(X);
//            QString input_x = QString::fromStdString(std::to_string(X));;
//            std::string str_pp_x = input_x.toStdString();

            char *str_input = new char[str_pp.length() + 1];
            strcpy(str_input, str_pp.c_str());
            char *str_x = new char[str_pp_x.length() + 1];
            strcpy(str_x, str_pp_x.c_str());
            err2 = s21_calc(str_input, str_x, &Y);
        if (err2 == 0){
            x.push_back(X);
            y.push_back(Y);
        }
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

}

void Grafic::ChangeFunc()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (TimerSlot()));
    ui->widget->clearGraphs();
    time = 0;
    timer->start(20);
    X=xBegin;
    x.clear();
    y.clear();
}

void Grafic::on_pushButton_gr_clicked()
{
    xBegin = ui->spinBox_xs->value();
    xEnd = ui->spinBox_xe->value();
    yBegin = ui->spinBox_ys->value();
    yEnd = ui->spinBox_ye->value();

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

    h = (xEnd - xBegin)/400;
    N =  (xEnd - xBegin)/h +2;

    if (ui->dinamicButton->isChecked()) {
        ChangeFunc();
    } else {
         StaticFunc();
    }
}


