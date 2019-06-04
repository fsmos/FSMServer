#include "r168sett.h"
#include "ui_r168sett.h"

r168sett::r168sett(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::r168sett)
{
    ui->setupUi(this);
}

r168sett::~r168sett()
{
    delete ui;
}
