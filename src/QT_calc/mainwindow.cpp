/*!
 * @file      mainwindow.cpp
 * @author    jettajac
 * @brief
 * @version   0.1
 * @date      2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//customPlot = new QCustomPlot(this);
    connect(ui->pushButton_0, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_lb, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_rb, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_atag, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_x, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_pov, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()),this, SLOT(digits_functions()));
    connect(ui->pushButton_mod, SIGNAL(clicked()),this, SLOT(digits_numbers()));
    connect(ui->pushButton_bin, SIGNAL(clicked()),this, SLOT(operations()));

    ui->pushButton_x->setCheckable(true);
    ui->pushButton_eq->setCheckable(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left) {
       ui->data_x->setText("2");
    }
}


void MainWindow::digits_functions()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;
    if (!(ui->pushButton_eq->isChecked())) {
        if (ui->result_show->text() == "0"){
            ui->result_show->setText("");
        }
        new_label = ui->result_show->text() + button->text() + '(';
        ui->result_show->setText(new_label);
    }

}


void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;

    if (ui->err_c->text() == "" && !(ui->pushButton_eq->isChecked()) && ui->data_x->text() == "X"){ /*ui->data_x->text() == "X"  && ui->err_x->text() == ""*/

        if(ui->result_show->text().contains(".") && button->text() == "0") {
            new_label = ui->result_show->text() + button->text();
        } else if (ui->result_show->text() == "0"){
            ui->result_show->setText("");
            if (button->text() == "X"){
                new_label = (ui->result_show->text() + "x");
            } else if (button->text() == "÷" || button->text() == "*") {
                new_label = ("");
            } else {
                new_label = (ui->result_show->text() + button->text());
            }
        } else if (button->text() == "X"){
                new_label = (ui->result_show->text() + "x");
        } else if (button->text() == "mod" && ui->result_show->text().back() == '^'){
                new_label = ui->result_show->text();
        } else if ((ui->result_show->text().back() == '.' || ui->result_show->text().back() == 'x' || ui->result_show->text().back() == ')') && (button->text() == "(")) {
                new_label = ui->result_show->text();
//        } else if (button->text() == "0" && !(ui->result_show->text().contains(".")) && !(ui->result_show->text().back() == ')')){
//                new_label = ui->result_show->text();
        } else if (ui->result_show->text().back() == '.' && button->text() == ")" ) {
                 new_label = ui->result_show->text();
                 new_label.chop(1);
                 ui->result_show->setText(new_label + button->text());
                 new_label = ui->result_show->text();
        } else {
             new_label = (ui->result_show->text() + button->text());
        }
        ui->result_show->setText(new_label);

    }
}


void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;
     if (!(ui->pushButton_eq->isChecked())) {
        if(button->text() == "+/-") {
            all_numbers = (ui->result_show->text()).toDouble();
            all_numbers = all_numbers* -1;
            new_label = QString::number(all_numbers, 'g', 10);
            ui->result_show->setText(new_label);
         } else if(button->text() == "%") {
                all_numbers = (ui->result_show->text()).toDouble();
                all_numbers = all_numbers* 0.01;
                new_label = QString::number(all_numbers, 'g', 15);
                ui->result_show->setText(new_label);
        }
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
   if (!(ui->pushButton_eq->isChecked())) {
        if (ui->result_show->text().back() == '+' || ui->result_show->text().back() == '-' || ui->result_show->text().back() == '*' ||
                ui->result_show->text().back() == '/' || ui->result_show->text().back() == '%' || ui->result_show->text().back() == '^' || ui->result_show->text().back() == '(') {
            ui->result_show->setText(ui->result_show->text() + "0.");
        } else if (ui->result_show->text().back() == '.') {
        } else {
            ui->result_show->setText(ui->result_show->text() + ".");
        }
   }

}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_x->setChecked(false);
    ui->pushButton_eq->setChecked(false);
    ui->err_x->setText("");

    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_div->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_graph->setChecked(false);

    ui->result_show->setText("0");
    ui->data_x->setText("X");
    ui->err_c->setText("");
}

void MainWindow::on_pushButton_del_clicked()
{
    if (!(ui->pushButton_eq->isChecked())) {
          QString new_label = ui->result_show->text();
          new_label.chop(1);
          ui->result_show->setText(new_label);
    }
}


void MainWindow::on_doubleSpinBox_x_valueChanged(double arg1)
{
    input_x = arg1;
}


void MainWindow::on_pushButton_plus_clicked()
{
        if (!(ui->pushButton_eq->isChecked())) {
        if (ui->result_show->text().back() == '+' || ui->result_show->text().back() == '-' || ui->result_show->text().back() == '*' ||
                ui->result_show->text().back() == '/' || ui->result_show->text().back() == '^') {
        } else if (ui->result_show->text().back() == '.') {
            QString new_label = ui->result_show->text();
            new_label.chop(1);
            ui->result_show->setText(new_label + "+");
        } else if (ui->result_show->text() == "0"){
            ui->result_show->setText("+");
        } else {
            ui->result_show->setText(ui->result_show->text() + "+");
        }
    }
}


void MainWindow::on_pushButton_minus_clicked()
{
    if (!(ui->pushButton_eq->isChecked())) {
        if (ui->result_show->text().back() == '+' || ui->result_show->text().back() == '-' || ui->result_show->text().back() == '*' ||
                ui->result_show->text().back() == '/' || ui->result_show->text().back() == '^') {
        } else if (ui->result_show->text().back() == '.') {
            QString new_label = ui->result_show->text();
            new_label.chop(1);
            ui->result_show->setText(new_label + "-");
        } else if (ui->result_show->text() == "0"){
            ui->result_show->setText("-");
        } else {
            ui->result_show->setText(ui->result_show->text() + "-");
        }
    }
}


void MainWindow::on_pushButton_mult_clicked()
{
  if (!(ui->pushButton_eq->isChecked())) {
        if (ui->result_show->text().back() == '+' || ui->result_show->text().back() == '-' || ui->result_show->text().back() == '*' ||
                ui->result_show->text().back() == '/' || ui->result_show->text().back() == '(' || ui->result_show->text().back() == '^') {
        } else if (ui->result_show->text().back() == '.') {
            QString new_label = ui->result_show->text();
            new_label.chop(1);
            ui->result_show->setText(new_label + "*");
        } else {
            ui->result_show->setText(ui->result_show->text() + "*");
        }
    }
}


void MainWindow::on_pushButton_div_clicked()
{
    if (!(ui->pushButton_eq->isChecked())) {
        if (ui->result_show->text().back() == '+' || ui->result_show->text().back() == '-' || ui->result_show->text().back() == '*' ||
                    ui->result_show->text().back() == '/' || ui->result_show->text().back() == '(' || ui->result_show->text().back() == '^') {
            } else if (ui->result_show->text().back() == '.') {
                QString new_label = ui->result_show->text();
                new_label.chop(1);
                ui->result_show->setText(new_label + "/");
            } else {
                ui->result_show->setText(ui->result_show->text() + "/");
            }
    }
}


void MainWindow::on_pushButton_graph_clicked()
{
    if (!(ui->pushButton_eq->isChecked())) {
        grafic = new Grafic(nullptr, ui->result_show->text());
        grafic->show();
   }
}


void MainWindow::on_pushButton_credit_clicked()
{
    credit = new Credit(nullptr);
    credit->show();
}


void MainWindow::on_pushButton_eq_clicked()
{
    double labelNumber, num_second;
    QString new_label;

    if(ui->err_x->text() == "X" && (ui->data_x->text() == "X")) {

        ui->err_x->setText("X");
        ui->data_x->setText("");
        ui->pushButton_x->setChecked(false);

    }  else {

        QString input = ui->result_show->text();
        //std::stod(label);

        std::string str_pp = input.toStdString();
        std::string str_pp_x = std::to_string(input_x);
        char *str_input = new char[str_pp.length() + 1];
        char *str_x = new char[str_pp_x.length() + 1];
        strcpy(str_input, str_pp.c_str());
        strcpy(str_x, str_pp_x.c_str());
        ui->err_x->setText("");

        double result = 0.0;
        ui->err_c->setText("X");
        err = s21_calc(str_input, str_x, &result);
        if (err == 0){
            new_label = QString::number(result, 'g', 20);
            ui->result_show->setText(new_label);
            ui->err_c->setText("");
                   ui->err_x->setText("X");
                ui->data_x->setText("X");
            delete[] str_input;
        }else if (err == -1){
            ui->result_show->clear();
            ui->data_x->clear();
            ui->result_show->setText("Data entered incorrectly");

        }else if (err == -2){
            ui->result_show->clear();
             ui->data_x->clear();
            ui->result_show->setText("Division by ZERO");
        } if (err == -3) {
            ui->result_show->clear();
            ui->data_x->clear();
            ui->result_show->setText("Incorrect value in function");
        }
     }
 }
