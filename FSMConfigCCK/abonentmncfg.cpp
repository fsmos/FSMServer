#include "abonentmncfg.h"
#include "ui_abonentmncfg.h"

abonentmncfg::abonentmncfg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::abonentmncfg)
{
    ui->setupUi(this);
}

abonentmncfg::~abonentmncfg()
{
    delete ui;
}

void abonentmncfg::on_pushButton_clicked()
{

}
