#include "pop_up.h"
#include "ui_pop_up.h"
#include "radio_components.hpp"

pop_up::pop_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pop_up)
{
    ui->setupUi(this);
}

pop_up::pop_up(QWidget *parent, Radio * other) :
    QDialog(parent),
    ui(new Ui::pop_up)
{
    single = other;
    ui->setupUi(this);
    ui->lineEdit->setText(single->type);
    ui->lineEdit_3->setText(QString::number(single->cost));
    ui->lineEdit_2->setText(single->specifications);
}

pop_up::~pop_up()
{
    delete ui;
}

void pop_up::on_pushButton_clicked()
{

    QString type = ui->lineEdit->text();
    QString cost = ui->lineEdit_3->text();
    QString specs = ui->lineEdit_2->text();
    type.replace(";",",").simplified();
    cost.replace(";",",").simplified();
    specs.replace(";",",").simplified();
    bool check = false;
    int x = cost.toInt(&check);
    if (!check) {
        ui->lineEdit_3->setText("Это не число!!!");
    }
    this->single->type = type;
    this->single->cost = x;
    this->single->specifications = specs;

    if (check) {
        this->close();
    }
}

