#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pbcoffee->setEnabled(false);
    ui->pbtea->setEnabled(false);
    ui->pbmilk->setEnabled(false);
    ui->pbreset->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::moneyChange(int diff)
{
    this->money += diff;
    ui->lcdNumber->display(this->money);
    if(this->money != 0)
        ui->pbreset->setEnabled(true);
    else
        ui->pbreset->setEnabled(false);
    if(this->money < 100)
        ui->pbcoffee->setEnabled(false);
    if(this->money < 150)
        ui->pbtea->setEnabled(false);
    if(this->money < 200)
        ui->pbmilk->setEnabled(false);
    if(this->money >= 100)
        ui->pbcoffee->setEnabled(true);
    if(this->money >= 150)
        ui->pbtea->setEnabled(true);
    if(this->money >= 200)
        ui->pbmilk->setEnabled(true);
}

void Widget::on_pb10_clicked()
{
    moneyChange(10);
}

void Widget::on_pb50_clicked()
{
    moneyChange(50);
}

void Widget::on_pb100_clicked()
{
    moneyChange(100);
}

void Widget::on_pb500_clicked()
{
    moneyChange(500);
}

void Widget::on_pbcoffee_clicked()
{
    moneyChange(-100);
}

void Widget::on_pbtea_clicked()
{
    moneyChange(-150);
}

void Widget::on_pbmilk_clicked()
{
    moneyChange(-200);
}

void Widget::on_pbreset_clicked()
{
    int coin[4] = { 500, 100, 50, 10 }, result[4] = { 0, };
    for(int i = 0; i < 4; i++)
    {
        result[i] = this->money / coin[i];
        this->money = this->money % coin[i];
    }

    moneyChange(0);
    char buf[100];
    sprintf(buf, "500원 %d개\n100원 %d개\n50원 %d개\n10원 %d개", result[0], result[1], result[2], result[3]);
    QMessageBox::information(this, "Change", buf);
}
