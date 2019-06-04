#include "ellistabonentpo.h"
#include "ui_ellistabonentpo.h"

Ellistabonentpo::Ellistabonentpo(PO_Subscriber* subscriber, int index,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ellistabonentpo)
{
    ui->setupUi(this);
    this->subscriber = subscriber;
    ui->po_numobj->setProperty("intValue", QVariant(index));
    ui->po_sip_name->setText(QString::number(subscriber->sip_number()));
    ui->radio->setChecked((subscriber->flags()&1));
    ui->autoanswer->setChecked((subscriber->flags()&1<<1));
    ui->ats->setChecked((subscriber->flags()&1<<2));
}

void Ellistabonentpo::Save() {
    subscriber->set_sip_number(ui->po_sip_name->text().toInt());
    int checkstatus = 0;
    if(ui->radio->isChecked() == true) checkstatus |= 1;
    if(ui->autoanswer->isChecked() == true) checkstatus |= 1<<1;
    if(ui->ats->isChecked() == true) checkstatus |= 1<<2;
    subscriber->set_flags(checkstatus);
}
Ellistabonentpo::~Ellistabonentpo()
{
    delete ui;
}
