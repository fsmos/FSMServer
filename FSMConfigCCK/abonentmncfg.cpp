#include "abonentmncfg.h"
#include "ui_abonentmncfg.h"

abonentmncfg::abonentmncfg(MN_Channel* channel,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::abonentmncfg)
{
    ui->setupUi(this);
    this->channel = channel;
    if(this->channel->subscriberforcall_size() > 0) ui->t101->setText(QString::number(channel->subscriberforcall(0)));
    if(this->channel->subscriberforcall_size() > 1) ui->t102->setText(QString::number(channel->subscriberforcall(1)));
    if(this->channel->subscriberforcall_size() > 2) ui->t103->setText(QString::number(channel->subscriberforcall(2)));
    if(this->channel->subscriberforcall_size() > 3) ui->t104->setText(QString::number(channel->subscriberforcall(3)));
    if(this->channel->subscriberforcall_size() > 4) ui->t105->setText(QString::number(channel->subscriberforcall(4)));
    if(this->channel->subscriberforcall_size() > 5) ui->t106->setText(QString::number(channel->subscriberforcall(5)));
    if(this->channel->subscriberforcall_size() > 6) ui->t107->setText(QString::number(channel->subscriberforcall(6)));
    if(this->channel->subscriberforcall_size() > 7) ui->t108->setText(QString::number(channel->subscriberforcall(7)));
    if(this->channel->subscriberforcall_size() > 8) ui->t109->setText(QString::number(channel->subscriberforcall(8)));
    if(this->channel->subscriberforcall_size() > 9) ui->t110->setText(QString::number(channel->subscriberforcall(9)));

}

abonentmncfg::~abonentmncfg()
{
    delete ui;
}

void abonentmncfg::on_pushButton_clicked()
{

     if(ui->t101->text() != "") {
         if(this->channel->subscriberforcall_size() > 0) {
             this->channel->mutable_subscriberforcall()->Set(0,ui->t101->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t101->text().toInt());
         }
     }
     if(ui->t102->text() != "") {
         if(this->channel->subscriberforcall_size() > 1) {
             this->channel->mutable_subscriberforcall()->Set(1,ui->t102->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t102->text().toInt());
         }
     }
     if(ui->t103->text() != "") {
         if(this->channel->subscriberforcall_size() > 2) {
             this->channel->mutable_subscriberforcall()->Set(2,ui->t103->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t103->text().toInt());
         }
     }
     if(ui->t104->text() != "") {
         if(this->channel->subscriberforcall_size() > 3) {
             this->channel->mutable_subscriberforcall()->Set(3,ui->t104->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t104->text().toInt());
         }
     }
     if(ui->t105->text() != "") {
         if(this->channel->subscriberforcall_size() > 4) {
             this->channel->mutable_subscriberforcall()->Set(4,ui->t105->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t105->text().toInt());
         }
     }
     if(ui->t106->text() != "") {
         if(this->channel->subscriberforcall_size() > 5) {
             this->channel->mutable_subscriberforcall()->Set(5,ui->t106->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t106->text().toInt());
         }
     }
     if(ui->t107->text() != "") {
         if(this->channel->subscriberforcall_size() > 6) {
             this->channel->mutable_subscriberforcall()->Set(6,ui->t107->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t107->text().toInt());
         }
     }
     if(ui->t108->text() != "") {
         if(this->channel->subscriberforcall_size() > 7) {
             this->channel->mutable_subscriberforcall()->Set(7,ui->t108->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t108->text().toInt());
         }
     }
     if(ui->t109->text() != "") {
         if(this->channel->subscriberforcall_size() > 8) {
             this->channel->mutable_subscriberforcall()->Set(8,ui->t109->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t109->text().toInt());
         }
     }
     if(ui->t110->text() != "") {
         if(this->channel->subscriberforcall_size() > 9) {
             this->channel->mutable_subscriberforcall()->Set(9,ui->t110->text().toInt());
         } else {
             this->channel->mutable_subscriberforcall()->Add(ui->t110->text().toInt());
         }
     }
     accept();
}
